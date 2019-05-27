#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->plainTextEdit->hide();
  //centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
  //this->setMouseTracking(true);
  REPLACE_X = 40;
  REPLACE_Y = 40;
  ZOOM = ui->spinBox_3->value();

  display = &main_display;
  ui->spinBox->setValue(BUFFER_COLS);
  ui->spinBox_2->setValue(BUFFER_ROWS);
  //main_display.buf_rows = BUFFER_ROWS;
  //main_display.buf_cols = BUFFER_COLS;
  //main_display.buf_size = BUFFER_SIZE;
  //main_display.buffer = new byte[BUFFER_SIZE];//buffer;

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
  //ui->spinBox->setValue((event->x() / ZOOM) + REPLACE_X - MARGIN);
  //ui->spinBox_2->setValue((event->y() / ZOOM) + REPLACE_X - MARGIN);
  qDebug("mouse move");
}
//
void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->delta() == 0)
    return;

  int window_half_x = this->window()->size().width() / 2;
  int window_half_y = this->window()->size().height() / 2;

  int new_mx = (event->x() - REPLACE_X) / (ZOOM + 1);
  int new_my = (event->y() - REPLACE_Y) / (ZOOM + 1);

  if (event->delta() > 0) {
    ui->spinBox_3->setValue(ZOOM + 1);
  } else {
    ui->spinBox_3->setValue(ZOOM - 1);
  }

  int new_replace_x = window_half_x - (new_mx * ZOOM);
  int new_replace_y = window_half_y - (new_my * ZOOM);

  REPLACE_X = new_replace_x;
  REPLACE_Y = new_replace_y;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  int mx = (event->x() - REPLACE_X) / ZOOM;
  int my = (event->y() - REPLACE_Y) / ZOOM;

  if(event->buttons() == Qt::LeftButton) {
    for(int i = 0; i < dots.size(); i++) {
      if (dots[i].first == mx && dots[i].second == my) {
        dots.erase(dots.begin() + i);
        return;
      }
    }
    /*if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier)) {
      reverce_dots.push_back(QPair<short, short>(mx, my));
    } else {
      dots.push_back(QPair<short, short>(mx, my));
    }*/
  }

  if(event->buttons() == Qt::RightButton) {
    short shift_x = display->zone.x();
    short shift_y = display->zone.y();

    if (display->buffer != NULL)
      delete [] display->buffer;

    display->buf_rows = display->zone.ey() - display->zone.y() + 1;
    display->buf_cols = (display->zone.ex() >> 3) - (display->zone.x() >> 3);

    ui->spinBox->setValue((display->zone.ex() >> 3) - (display->zone.x() >> 3));
    ui->spinBox_2->setValue(display->zone.ey() - display->zone.y() + 1);
    /*display->buf_cols = (display->zone.ex() >> 3) - (display->zone.x() >> 3);
    display->buf_rows = display->zone.ey() - display->zone.y() + 1;
    display->buf_size = (display->buf_cols) * display->buf_rows;
    display->buffer = new byte[display->buf_size];
    qDebug() << "cols: " << display->buf_cols;
    qDebug() << "size: " << display->buf_size;*/
    for(int i = 0; i < dots.size(); i++) {
      dots[i].first -= shift_x;
      dots[i].second -= shift_y;
    }
  }

  render();
  this->update();
}


void MainWindow::render() {
  /*int mx = 100 - REPLACE_X;
  int my = 110 - REPLACE_Y;
  //int mx = event->pos().x() - REPLACE_X;
  //int my = event->pos().y() - REPLACE_Y;

  if (mx > (display->buf_cols * 8 * ZOOM))
    return;
  if (my > (display->buf_rows * ZOOM))
    return;
  if (mx < 0)
    return;
  if (my < 0)
    return;*/


  for(size_t i = 0; i < display->buf_size; i++) {
      display->buffer[i] = 0xFF;
  }


  display->zone.clear();
  /*display->zone.clear();

  RenderSubBuffer(mx, my, &sub_display);
  RenderLine(40, 20, mx, my);
  RenderLine(mx, my, mx+50, my-10);
*/
  byte sub_test[3*13] = {0xff, 0xff, 0x0, 0x1c, 0x9f, 0xcf, 0xe7, 0xf3, 0x31, 0x0, 0xff, 0xff, 0xff,
                         0xFF, 0xFF, 0xFF, 0xC3, 0x83, 0x9F, 0x83, 0x99, 0x01, 0x03, 0xFF, 0xFF, 0xFF,
                         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  byte sub_test2[2*50] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xff, 0xbf, 0xfe, 0xbf, 0xfe, 0xdf, 0xfe, 0xdf, 0xfd, 0xef, 0xfd, 0xf, 0xfc, 0xef, 0xfb, 0xf7, 0xfb, 0xf7, 0xf7, 0xc3, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  byte id = 1;
  DispBuf d;
  //d.buffer = sub_test + (id * 13);
  d.buf_cols = 1;
  d.buf_rows = 13;

  d.buffer = sub_test2;
  d.buf_cols = 2;
  d.buf_rows = 50;
  RenderSubBuffer(0, 0, &d);
  //RenderCircle(8,11, 6);

  for (int i = 0; i < reverce_dots.size(); i++) {
    RenderDot(reverce_dots[i].first, reverce_dots[i].second, true);
  }

  for (int i = 0; i < dots.size(); i++) {
    RenderDot(dots[i].first, dots[i].second, false);
  }

  /*RenderCircle(mx, my, 20);

  //RenderRectangle(0, 0, (display->buf_cols << 3) - 1, display->buf_rows - 1);

  display->zone.clear();


*/
  //RenderZone();

  /*for (int i = 0; i < 200; i++) {
    buffer[(5 + BUFFER_COLS) + (i * BUFFER_COLS)] = 0;
  }*/

  this->update();
}
void MainWindow::RenderZone() {
  RenderZone(display);
}

void MainWindow::RenderZone(DispBuf* disp) {
  Zone tmp1 = display->zone;
  Zone tmp = disp->zone;
  RenderRectangle(disp->zone.x(), disp->zone.y(), disp->zone.ex(), disp->zone.ey());
  disp->zone = tmp;
  display->zone = tmp1;
}

void MainWindow::RenderRectangle(short x, short y, short x1, short y1) {// coordinates and coordinates
  RenderLine(x, y, x1, y);
  RenderLine(x1, y, x1, y1);
  RenderLine(x1, y1, x, y1);
  RenderLine(x, y1, x, y);
}

void MainWindow::RenderCircle(short x, short y, short r) {
  //x^2 + y^2 = r^2
    short p1 = r * r; //pow(r, 2);

  for (short i = 0; i < r; i+=1) {
    short p2 = i * i; //pow(i, 2);
    short sqrt_ = sqrt(p1 - p2);
    RenderDot(i + x, sqrt_ + y, false);
    RenderDot(i + x, -sqrt_ + y, false);
    RenderDot(-i + x, sqrt_ + y, false);
    RenderDot(-i + x, -sqrt_ + y, false);
  }
}

void MainWindow::RenderDot(short x, short y, bool reverce) {
  if (y >= display->buf_rows || x >= (display->buf_cols << 3))
    return;
  if (y < 0 || x < 0)
    return;
//qDebug() << "RenderDot(" << x << ", " << y << ")";
  byte row_byte = x >> 3; // x / 8
  byte shift_bits = x & 0x07; ;//x - (row_byte << 3); // x - (row * 8)

  byte left_mask = ~(0x01 << shift_bits);

  word left_byte_id = row_byte + (y * display->buf_cols);

  if (left_byte_id < display->buf_size)
    if (!reverce) {// set
      display->buffer[left_byte_id] &= left_mask;
      display->zone.update(x - shift_bits, y);
    } else {
      display->buffer[left_byte_id] |= ~left_mask;
    }


}

void MainWindow::RenderLine(short x, short y, short ex, short ey) { // coordinates of the start and the end
  float dx = ex - x;
  float dy = ey - y;

  //float steps = sqrt(pow(dx,2) + pow(dy,2));
  float steps = sqrt((dx*dx) + (dy*dy));

  float step_x = dx / steps;
  float step_y = dy / steps;

  for (short i = 0 ; i < steps; i++) {
    RenderDot(x+(step_x*i), y+(step_y*i), false);
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
              || tar_cur_col > display->buf_cols
              || tar_y + src_cur_row >= display->buf_rows)
        continue;

      display->buffer[left_byte_id] &= left_mask;
      display->zone.update(tar_cur_col << 3, tar_y);
      display->zone.update(tar_cur_col << 3, tar_y + src_cur_row);

      if (left_byte_id + 1 >= display->buf_size
              || tar_cur_col > display->buf_cols
              || tar_y + src_cur_row >= display->buf_rows)
        continue;

      display->buffer[left_byte_id + 1] &= right_mask;
      display->zone.update((tar_cur_col + 1) << 3, tar_y);
      display->zone.update((tar_cur_col + 1) << 3, tar_y + src_cur_row);
    }
  }
  //RenderZone(sub_disp_);
}

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter p(this);

  render();

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

  QPen pen(QColor(0xFF, 0, 0, 0x80), 1 * ZOOM, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin); // red
  p.setPen(pen);
  p.drawRect((display->zone.x() * ZOOM) + REPLACE_X + (ZOOM / 2),
             (display->zone.y() * ZOOM) + REPLACE_Y + (ZOOM / 2),
             (display->zone.ex() - display->zone.x()) * ZOOM,
             (display->zone.ey() - display->zone.y()) * ZOOM);

  QPen pen2(QColor(0x00, 0xFF, 0, 0x80), 1 * ZOOM, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
  p.setPen(pen2);
  p.drawRect((0 * 8 * ZOOM) + REPLACE_X + (ZOOM / 2),
             (0 * ZOOM) + REPLACE_Y + (ZOOM / 2),
             (display->buf_cols * 8) * ZOOM,
             display->buf_rows * ZOOM);

  //std::cout << "zone: " << display->zone.x() << ", " << display->zone.y() << ", " << display->zone.ex() << ", " << display->zone.ey() << std::endl;
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_released()
{
  bool bStatus;
  if (ui->plainTextEdit->isVisible()) {
    ui->plainTextEdit->hide();
    /*QStringList strings = ui->plainTextEdit->toPlainText().split(QRegExp("[, ]"),QString::SkipEmptyParts);

    for (int i = 0; (i < display->buf_size) && (i < strings.size()); i++) {
      display->buffer[i] = (strings[i].toUInt(&bStatus,16));
      qDebug() << "next: " << display->buffer[i];


    }*/

  } else {
    ui->plainTextEdit->show();
    ui->plainTextEdit->clear();
    QString code;
    for(int i = 0; i < display->buf_size; i++) {
       code += "0x";
       code += QString::number( display->buffer[i], 16 );
       code += ", ";
    }
    ui->plainTextEdit->appendPlainText(code);
    ui->spinBox->setValue(display->buf_cols);
    ui->spinBox_2->setValue(display->buf_rows);
  }
}

void MainWindow::on_spinBox_3_valueChanged(int v)
{
  ZOOM = v;
  //this->resize(QSize(((display->buf_cols << 3) * ZOOM)+MARGIN+REPLACE_X, (display->buf_rows * ZOOM)+MARGIN+REPLACE_X));
  this->update();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
  if (arg1 < 0)
    return;
  display->buf_cols = arg1;
  //display->buf_rows = display->zone.ey() - display->zone.y() + 1;
  display->buf_size = (display->buf_cols) * display->buf_rows;

  display->buffer = new byte[display->buf_size];

  qDebug() << "cols: " << display->buf_cols;
  qDebug() << "size: " << display->buf_size;

  render();
  this->update();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
  if (arg1 < 0)
    return;
  //display->buf_cols = (display->zone.ex() >> 3) - (display->zone.x() >> 3);
  display->buf_rows = arg1;
  display->buf_size = (display->buf_cols) * display->buf_rows;

  display->buffer = new byte[display->buf_size];

  qDebug() << "rows: " << display->buf_rows;
  qDebug() << "size: " << display->buf_size;

  render();
  this->update();
}
