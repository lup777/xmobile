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
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  for(size_t i = 0; i < BUFFER_SIZE; i++) {
      buffer[i] = 0xFF;
  }
  zone.clear();

  //RenderDot(event->pos().x()-8, event->pos().y()-13);
  RenderCircle(64,60,30);
  RenderCircle(64,60,25);
  RenderCircle(70,70,25);
  RenderLine(40, 20,
             event->pos().x(), event->pos().y());

  const unsigned char ch1[13] = {0xCF, 0xCF, 0xC7, 0xD3, 0xD9, 0x00, 0x00, 0xDF, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF};
  const unsigned char ch2[13] = {0xE3, 0xC1, 0xC9, 0xE3, 0xF3, 0x61, 0x0C, 0x1C, 0x00, 0x61, 0xFF, 0xFF, 0xFF};

  RenderChar(ch1, event->pos().x()-8, event->pos().y()-13);
  RenderChar(ch1, event->pos().x()-16, event->pos().y()-13);
  RenderChar(ch1, event->pos().x()-24, event->pos().y()-13);
  RenderChar(ch1, event->pos().x()-32, event->pos().y()-13);

  RenderChar(ch2, event->pos().x()-8, event->pos().y()-26);
  RenderChar(ch2, event->pos().x()-16, event->pos().y()-26);
  RenderChar(ch2, event->pos().x()-24, event->pos().y()-26);
  RenderChar(ch2, event->pos().x()-32, event->pos().y()-26);


  RenderZone();

  this->update();
}

void MainWindow::RenderZone() {
  RenderLine(zone.x(), zone.y(), zone.x(), zone.ey()-1);
  RenderLine(zone.x(), zone.ey(), zone.ex()-1, zone.ey());
  RenderLine(zone.ex()-1, zone.ey()-1, zone.ex()-1, zone.y());
  RenderLine(zone.ex()-1, zone.y(), zone.x(), zone.y());
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

  if ((left_byte_id > 0) && (left_byte_id < BUFFER_SIZE))
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

void MainWindow::RenderChar(const byte* ch, unsigned char x, unsigned char y) {

  byte row_byte = x / 8;
  byte shift_bits = x - (row_byte * 8);

  for(size_t i = 0; i < 13; i++) {
    byte right_mask = (ch[i] >> (8 - shift_bits)) | (0xFF << (shift_bits));
    byte left_mask = (ch[i] << (shift_bits)) | (0xFF >> (8 - shift_bits));

    size_t left_byte_id = row_byte + ((y+i) * BUFFER_COLS);
    size_t right_byte_id = row_byte + ((y+i) * BUFFER_COLS) + 1;

    if ((left_byte_id > 0) && (left_byte_id < BUFFER_SIZE)) {
      buffer[left_byte_id] &= left_mask;
      zone.update(row_byte * 8, y);
      zone.update(row_byte * 8, y+13);
    }

    if ((right_byte_id > 0) && (right_byte_id < BUFFER_SIZE )) {
      buffer[right_byte_id] &= right_mask;
      zone.update(row_byte * 8, y);
      zone.update(row_byte * 8, y+13);
    }
  }
}

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter p(this);
  for(size_t col = 0; col < BUFFER_COLS; col++) {
    for(size_t row = 0; row < BUFFER_ROWS; row++) {
        unsigned char byte_ = buffer[col + (row * BUFFER_COLS)];

      for(size_t bit = 0; bit < 8; bit ++) {
        if((byte_ & (1 << bit)) == 0) {
          //p.drawPoint((col*8) + bit, row);
          byte x = (col*8) + bit;
          byte y = row;
          x *= ZOOM;
          y *= ZOOM;
          for(size_t i = 0; i < ZOOM; i++)
            for(size_t j = 0; j < ZOOM; j++)
              p.drawPoint(x+i, y+j);
        }
      }
    }
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}
