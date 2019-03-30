#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  main_display.buffer = buffer;
  main_display.buf_rows = BUFFER_ROWS;
  main_display.buf_cols = BUFFER_COLS;
  main_display.buf_size = BUFFER_SIZE;

  for(word i = 0; i < main_display.buf_size; i++) {
    main_display.buffer[i] = 0xFF;
  }

  sub_display.buf_rows = 100;
  sub_display.buf_cols = 15;
  sub_display.buf_size = sub_display.buf_rows * sub_display.buf_cols;
  sub_display.buffer = sub_buffer;

  for (word i = 0; i < sub_display.buf_size; i++)
    sub_display.buffer[i] = 0xFF;

  display = &main_display;

  display = &sub_display;

  RenderCircle(64,60,30);
  RenderCircle(64,60,25);
  RenderCircle(70,70,25);

  display = &main_display;

  this->resize(QSize(((display->buf_cols << 3) * ZOOM)+MARGIN+REPLACE_X, (display->buf_rows * ZOOM)+MARGIN+REPLACE_X));
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  int mx = event->pos().x() - REPLACE_X;
  int my = event->pos().y() - REPLACE_Y;

  if (mx > (display->buf_cols * 8 * ZOOM))
    return;
  if (my > (display->buf_rows * ZOOM))
    return;
  if (mx < 0)
    return;
  if (my < 0)
    return;


  for(size_t i = 0; i < display->buf_size; i++) {
      display->buffer[i] = 0xFF;
  }

  RenderRectangle(0, 0, (display->buf_cols << 3) - 1, display->buf_rows - 1);

  display->zone.clear();

  RenderSubBuffer(mx, my, &sub_display);
  RenderLine(40, 20, mx, my);
  RenderLine(mx, my, mx+50, my-10);

  byte sub_test[7*13] = {0xFF, 0xFF, 0x00, 0x00, 0x8F, 0xC7, 0xF3, 0xF9, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0x3C, 0x3C, 0x9C, 0x99, 0x99, 0xD3, 0xC3, 0xC3, 0xE7, 0xE1, 0xF1,
                               0xFF, 0xFF, 0x1C, 0x99, 0xC1, 0xC3, 0xC3, 0xC9, 0x98, 0x1C, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0xC3, 0x83, 0x9F, 0x83, 0x99, 0x01, 0x03, 0xFF, 0xFF, 0xFF,
                               0x9F, 0x83, 0xF1, 0xC1, 0x81, 0x38, 0x3D, 0x19, 0x81, 0xC3, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xCC, 0xC0, 0x9C, 0x80, 0xC0, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x33, 0xF3, 0xF3, 0xC1, 0xC1, 0xFF, 0xFF, 0xFF};

  {
      DispBuf d;

      for (byte i = 0; i < 7; i++) {
        d.buffer = sub_test + (i * 13);
        d.buf_cols = 1;
        d.buf_rows = 13;
        RenderSubBuffer(mx + (i << 3), my, &d);
      }
  }
  RenderCircle(mx, my, 20);

  RenderZone();

  /*for (int i = 0; i < 200; i++) {
    buffer[(5 + BUFFER_COLS) + (i * BUFFER_COLS)] = 0;
  }*/

  this->update();
}

void MainWindow::RenderZone() {
  Zone tmp = display->zone;
  RenderRectangle(display->zone.x(), display->zone.y(), display->zone.ex(), display->zone.ey());
  display->zone = tmp;
}

void MainWindow::RenderRectangle(short x, short y, short x1, short y1) {// coordinates and coordinates
  RenderLine(x, y, x1, y);
  RenderLine(x1, y, x1, y1);
  RenderLine(x1, y1, x, y1);
  RenderLine(x, y1, x, y);
}

void MainWindow::RenderCircle(short x, short y, short r) {
  //x^2 + y^2 = r^2
  for (short i = 0; i < r; i+=1) {
    RenderDot(i + x, (sqrt(pow(r, 2) - pow(i, 2))) + y);
    RenderDot(i + x, -(sqrt(pow(r, 2) - pow(i, 2))) + y);
    RenderDot(-i + x, (sqrt(pow(r, 2) - pow(i, 2))) + y);
    RenderDot(-i + x, -(sqrt(pow(r, 2) - pow(i, 2))) + y);
  }
}

void MainWindow::RenderDot(short x, short y) {
  if (y > display->buf_rows || x > (display->buf_cols << 3))
    return;
  if (y < 0 || x < 0)
    return;

  byte row_byte = x >> 3; // x / 8
  byte shift_bits = x & 0x07; ;//x - (row_byte << 3); // x - (row * 8)

  byte left_mask = ~(0x01 << shift_bits);

  word left_byte_id = row_byte + (y * display->buf_cols);

  if (left_byte_id < display->buf_size)
    display->buffer[left_byte_id] &= left_mask;

  display->zone.update(x - shift_bits, y);
}

void MainWindow::RenderLine(short x, short y, short ex, short ey) { // coordinates of the start and the end
  float dx = ex - x;
  float dy = ey - y;

  //float steps = sqrt(pow(dx,2) + pow(dy,2));
  float steps = sqrt((dx*dx) + (dy*dy));

  float step_x = dx / steps;
  float step_y = dy / steps;

  for (short i = 0 ; i < steps; i++) {
    RenderDot(x+(step_x*i), y+(step_y*i));
  }
}

void MainWindow::RenderSubBuffer(short tar_x, short tar_y, DispBuf* sub_disp_) {
  if (tar_x < 0 || tar_x > (display->buf_cols << 3))
    return;

  short tar_col_id_byte = tar_x >> 3; // columnt number in target buffer
  byte shift_bits = tar_x & 0x07; // tar_x - (tar_x / 8)*8;

  for(short src_cur_col = 0; src_cur_col < (sub_disp_->buf_cols); src_cur_col++) {
    for(short src_cur_row = 0; src_cur_row < sub_disp_->buf_rows; src_cur_row += 1) { // i - current line number in source buffer

      word src_byte_id = (sub_disp_->buf_cols * src_cur_row) + src_cur_col;

      byte right_mask = ( sub_disp_->buffer[ src_byte_id] >> (8 - shift_bits)) | (0xFF << (shift_bits));
      byte left_mask = ( sub_disp_->buffer[ src_byte_id] << (shift_bits)) | (0xFF >> (8 - shift_bits));

      word tar_cur_col = tar_col_id_byte + src_cur_col;
      word left_byte_id = tar_cur_col + ((src_cur_row + tar_y) * display->buf_cols); // byte id in target buffer

      if (left_byte_id >= display->buf_size
              || tar_cur_col + 1 >= display->buf_cols
              || tar_y + src_cur_row >= display->buf_rows)
        continue;

      display->buffer[left_byte_id] &= left_mask;
      display->zone.update(tar_cur_col << 3, tar_y);
      display->zone.update(tar_cur_col << 3, tar_y + src_cur_row);

      if (left_byte_id + 1 >= display->buf_size
              || tar_cur_col + 1 >= display->buf_cols
              || tar_y + src_cur_row >= display->buf_rows)
        continue;

      display->buffer[left_byte_id + 1] &= right_mask;
      display->zone.update((tar_cur_col + 1) << 3, tar_y);
      display->zone.update((tar_cur_col + 1) << 3, tar_y + src_cur_row);
    }
  }
}

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter p(this);

#if DRAW_FULL_BUFFER==1
  for(size_t col = 0; col < display->buf_cols; col++) {
    for(size_t row = 0; row < display->buf_rows; row++) {
#else
  for(word col = display->zone.x() >> 3; col < (display->zone.ex() >> 3); col++) {
    for(word row = display->zone.y(); row < display->zone.ey(); row++) {
#endif
      unsigned char byte_ = display->buffer[col + (row * display->buf_cols)];

      for(size_t bit = 0; bit < 8; bit ++) {
        if((byte_ & (1 << bit)) == 0) {
          size_t x = (col << 3) + bit;
          size_t y = row;
          x *= ZOOM;
          y *= ZOOM;
          for(size_t i = 0; i < ZOOM; i++)
            for(size_t j = 0; j < ZOOM; j++)
              p.drawPoint(x+i+REPLACE_X, y+j+REPLACE_Y);
        }
      }
    }
  }
  QPen pen(Qt::red, 1 * ZOOM, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
  p.setPen(pen);
  p.drawRect((display->zone.x() * ZOOM) + REPLACE_X,
             (display->zone.y() * ZOOM) + REPLACE_Y,
             (display->zone.ex() - display->zone.x()) * ZOOM,
             (display->zone.ey() - display->zone.y()) * ZOOM);
}

MainWindow::~MainWindow()
{
  delete ui;
}
