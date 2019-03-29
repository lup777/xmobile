#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //painter = new QPainter();
  for(size_t i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = 0xFF;
  }
  this->resize(QSize(((BUFFER_COLS << 3) * ZOOM)+MARGIN+REPLACE_X, (BUFFER_ROWS * ZOOM)+MARGIN+REPLACE_X));
  display_buffer = buffer;
  display_buffer_rows = BUFFER_ROWS;
  display_buffer_cols = BUFFER_COLS;
  display_buffer_size = BUFFER_SIZE;
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  int mx = event->pos().x() - REPLACE_X;
  int my = event->pos().y() - REPLACE_Y;

  if (mx > (BUFFER_COLS * 8 * ZOOM) + REPLACE_X)
    return;
  if (my > (BUFFER_ROWS * ZOOM) + REPLACE_Y)
    return;
  if (mx < 0)
    return;
  if (my < 0)
    return;


  for(size_t i = 0; i < BUFFER_SIZE; i++) {
      buffer[i] = 0xFF;
  }

  RenderRectangle(0, 0, (BUFFER_COLS * 8) - 1, BUFFER_ROWS - 1);

  zone.clear();

  //RenderDot(event->pos().x()-8, event->pos().y()-13);

  display_buffer_rows = 100;
  display_buffer_cols = 15;
  display_buffer_size = display_buffer_rows * display_buffer_cols;
  display_buffer = sub_buffer;

  for (word i = 0; i < display_buffer_size; i++)
    sub_buffer[i] = 0xFF;

  RenderCircle(64,60,30);
  //RenderCircle(64,60,25);
 //RenderCircle(70,70,25);

  display_buffer = buffer;
  display_buffer_rows = BUFFER_ROWS;
  display_buffer_cols = BUFFER_COLS;
  display_buffer_size = BUFFER_SIZE;
  RenderSubBuffer(mx/8,0, 15 << 3, 100, sub_buffer);

  RenderLine(40, 20, mx, my);
  RenderLine(mx, my, mx+50, my-10);

  const byte sub_test[7*13] = {0xFF, 0xFF, 0x00, 0x00, 0x8F, 0xC7, 0xF3, 0xF9, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0x3C, 0x3C, 0x9C, 0x99, 0x99, 0xD3, 0xC3, 0xC3, 0xE7, 0xE1, 0xF1,
                               0xFF, 0xFF, 0x1C, 0x99, 0xC1, 0xC3, 0xC3, 0xC9, 0x98, 0x1C, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0xC3, 0x83, 0x9F, 0x83, 0x99, 0x01, 0x03, 0xFF, 0xFF, 0xFF,
                               0x9F, 0x83, 0xF1, 0xC1, 0x81, 0x38, 0x3D, 0x19, 0x81, 0xC3, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xCC, 0xC0, 0x9C, 0x80, 0xC0, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x33, 0xF3, 0xF3, 0xC1, 0xC1, 0xFF, 0xFF, 0xFF};

  for (byte i = 1; i < 2; i++) {
    RenderSubBuffer(mx, my, 1 << 3, 13, sub_test + (i * 13));
  }
  RenderCircle(mx, my, 20);

  RenderZone();

  /*for (int i = 0; i < 200; i++) {
    buffer[(5 + BUFFER_COLS) + (i * BUFFER_COLS)] = 0;
  }*/

  this->update();
}

void MainWindow::RenderZone() {
  Zone tmp = zone;
  RenderRectangle(zone.x(), zone.y(), zone.ex()-1, zone.ey()-1);
  zone = tmp;
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
  if (y > display_buffer_rows || x > (display_buffer_cols << 3))
    return;
  if (y < 0 || x < 0)
    return;

  byte row_byte = x >> 3; // x / 8
  byte shift_bits = x & 0x07; ;//x - (row_byte << 3); // x - (row * 8)

  byte left_mask = ~(0x01 << shift_bits);

  word left_byte_id = row_byte + (y * display_buffer_cols);

  if (left_byte_id < display_buffer_size)
    display_buffer[left_byte_id] &= left_mask;

  zone.update(x, y);
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

void MainWindow::RenderSubBuffer(short tar_x, short tar_y, short src_dx, short src_dy, const byte* subbuffer) {
  if (tar_x < 0 || tar_x > (display_buffer_cols << 3))
    return;

  short row_byte = tar_x >> 3; // columnt number in target buffer
  byte shift_bits = tar_x & 0x07; // tar_x - (tar_x / 8)*8;
  if (row_byte + 1 >= display_buffer_cols) // right byte is out of buffer width
    return;

  for(short src_cur_col = 0; src_cur_col < (src_dx >> 3); src_cur_col++) {

    for(short src_cur_row = 0; src_cur_row < src_dy; src_cur_row += 1) { // i - current line number in source buffer

      word src_byte_id = ((src_dx >> 3) * src_cur_row) + src_cur_col;

      byte right_mask = ( subbuffer[ src_byte_id + 1] >> (8 - shift_bits)) | (0xFF << (shift_bits));
      byte left_mask = ( subbuffer[ src_byte_id] << (shift_bits)) | (0xFF >> (8 - shift_bits));

      //word left_byte_id = row_byte + ((y+i) * display_buffer_cols);
      word left_byte_id = (tar_x + src_cur_col) + ((src_cur_row + tar_y) * display_buffer_cols); // byte id in target buffer

      if (left_byte_id < display_buffer_size && left_byte_id > 0) {
        display_buffer[left_byte_id] &= left_mask;
        zone.update(row_byte << 3, tar_y);
        zone.update(row_byte << 3, tar_y + src_dy);
      }

      if (left_byte_id + 1 < display_buffer_size) {
        display_buffer[left_byte_id + 1] &= right_mask;
        zone.update((row_byte + 1) << 3, tar_y);
        zone.update((row_byte + 1) << 3, tar_y + src_dy);
      }
    }
  }
}

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter p(this);

  /*display_buffer_rows = 100;
  display_buffer_cols = 15;
  display_buffer_size = display_buffer_rows * display_buffer_cols;
  display_buffer = sub_buffer;*/

#if DRAW_FULL_BUFFER==1
  for(size_t col = 0; col < display_buffer_cols; col++) {
    for(size_t row = 0; row < display_buffer_rows; row++) {
#else
  for(size_t col = zone.x() >> 3; col < zone.ex() >> 3; col++) {
    for(size_t row = zone.y(); row < zone.ey(); row++) {
#endif
      unsigned char byte_ = display_buffer[col + (row * display_buffer_cols)];

      for(size_t bit = 0; bit < 8; bit ++) {
        if((byte_ & (1 << bit)) == 0) {
          //p.drawPoint((col*8) + bit, row);
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
  QPen pen(Qt::red, 1*ZOOM, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
  p.setPen(pen);
  p.drawRect((zone.x()*ZOOM)+REPLACE_X, (zone.y()*ZOOM)+REPLACE_Y, (zone.ex()-zone.x())*ZOOM, (zone.ey()-zone.y())*ZOOM);
}

MainWindow::~MainWindow()
{
  delete ui;
}
