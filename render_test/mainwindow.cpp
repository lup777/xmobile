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
  this->resize(QSize((BUFFER_COLS * 8 * ZOOM)+MARGIN+REPLACE_X, (BUFFER_ROWS * ZOOM)+MARGIN+REPLACE_X));
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
  /*RenderLine(0, 0, (BUFFER_COLS * 8)-1, 0); //BUFFER_ROWS
  RenderLine((BUFFER_COLS * 8)-1, 0, (BUFFER_COLS * 8)-1, BUFFER_ROWS-1);
  RenderLine((BUFFER_COLS * 8)-1, BUFFER_ROWS, 0, BUFFER_ROWS-1);
  RenderLine(0, BUFFER_ROWS-1, 0, 0);*/
  RenderRectangle(0, 0, (BUFFER_COLS * 8) - 1, BUFFER_ROWS - 1);

  zone.clear();

  //RenderDot(event->pos().x()-8, event->pos().y()-13);
  RenderCircle(64,60,30);
  RenderCircle(64,60,25);
  RenderCircle(70,70,25);
  RenderLine(40, 20, mx, my);

  const unsigned char ch1[13] = {0xCF, 0xCF, 0xC7, 0xD3, 0xD9, 0x00, 0x00, 0xDF, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF};
  const unsigned char ch2[13] = {0xE3, 0xC1, 0xC9, 0xE3, 0xF3, 0x61, 0x0C, 0x1C, 0x00, 0x61, 0xFF, 0xFF, 0xFF};

  RenderChar(ch1, mx-8, my-13);
  RenderChar(ch1, mx-16, my-13);
  RenderChar(ch1, mx-24, my-13);
  RenderChar(ch1, mx-32, my-13);

  RenderChar(ch2, mx-8, my-26);
  RenderChar(ch2, mx-16, my-26);
  RenderChar(ch2, mx-24, my-26);
  RenderChar(ch2, mx-32, my-26);


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

void MainWindow::RenderRectangle(byte x, byte y, byte x1, byte y1) {// coordinates and coordinates
  RenderLine(x, y, x1, y);
  RenderLine(x1, y, x1, y1);
  RenderLine(x1, y1, x, y1);
  RenderLine(x, y1, x, y);
}

void MainWindow::RenderCircle(byte x, byte y, byte r) {
  //x^2 + y^2 = r^2
  for (size_t i = 0; i < r; i+=1) {
    RenderDot(i + x, (sqrt(pow(r, 2) - pow(i, 2))) + y);
    RenderDot(i + x, -(sqrt(pow(r, 2) - pow(i, 2))) + y);
    RenderDot(-i + x, (sqrt(pow(r, 2) - pow(i, 2))) + y);
    RenderDot(-i + x, -(sqrt(pow(r, 2) - pow(i, 2))) + y);
  }
}

void MainWindow::RenderDot(byte x, byte y) {
  if (y > BUFFER_ROWS || x > (BUFFER_COLS * 8))
    return;

  byte row_byte = x / 8;
  byte shift_bits = x - (row_byte * 8);

  byte left_mask = ~(0x01 << (shift_bits));

  size_t left_byte_id = row_byte + (y * BUFFER_COLS);

  if ((left_byte_id >= 0) && (left_byte_id < BUFFER_SIZE))
    buffer[left_byte_id] &= left_mask;

  zone.update(x, y);
}

void MainWindow::RenderLine(byte x, byte y, byte ex, byte ey) {
  float dx = ex - x;
  float dy = ey - y;

  float steps = sqrt(pow(dx,2) + pow(dy,2));

  float step_x = dx / steps;
  float step_y = dy / steps;

  for (size_t i = 0 ; i < steps; i++) {
    RenderDot(x+(step_x*i), y+(step_y*i));
  }
}

#define FONT_HEIGHT_BITS 13
void MainWindow::RenderChar(const byte* ch, unsigned char x, unsigned char y) {

  byte row_byte = x / 8;
  byte shift_bits = x - (row_byte * 8);
  if (row_byte+1 >= BUFFER_COLS) // right byte is out of buffer width
    return;

  for(size_t i = 0; i < FONT_HEIGHT_BITS; i++) {
    byte right_mask = (ch[i] >> (8 - shift_bits)) | (0xFF << (shift_bits));
    byte left_mask = (ch[i] << (shift_bits)) | (0xFF >> (8 - shift_bits));

    size_t left_byte_id = row_byte + ((y+i) * BUFFER_COLS);
    size_t right_byte_id = row_byte + ((y+i) * BUFFER_COLS) + 1;

    if ((left_byte_id >= 0) && (left_byte_id < BUFFER_SIZE)) {
      buffer[left_byte_id] &= left_mask;
      zone.update(row_byte * 8, y);
      zone.update(row_byte * 8, y + FONT_HEIGHT_BITS);
    }

    if ((right_byte_id > 0) && (right_byte_id < BUFFER_SIZE )) {
      buffer[right_byte_id] &= right_mask;
      zone.update(row_byte * 8, y);
      zone.update(row_byte * 8, y + FONT_HEIGHT_BITS);
    }
  }
}

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter p(this);

#if DRAW_FULL_BUFFER==1
  for(size_t col = 0; col < BUFFER_COLS; col++) {
    for(size_t row = 0; row < BUFFER_ROWS; row++) {
#else
  for(size_t col = zone.x()/8; col < zone.ex()/8; col++) {
    for(size_t row = zone.y(); row < zone.ey(); row++) {
#endif
      unsigned char byte_ = buffer[col + (row * BUFFER_COLS)];

      for(size_t bit = 0; bit < 8; bit ++) {
        if((byte_ & (1 << bit)) == 0) {
          //p.drawPoint((col*8) + bit, row);
          size_t x = (col*8) + bit;
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
