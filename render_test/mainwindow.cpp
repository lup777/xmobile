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
  //RenderDot(event->pos().x()-8, event->pos().y()-13);
  RenderLine(0, 0,
             event->pos().x(), event->pos().y());

  RenderChar('a', event->pos().x()-8, event->pos().y()-13);
  RenderChar('a', event->pos().x()-16, event->pos().y()-13);
  RenderChar('a', event->pos().x()-24, event->pos().y()-13);
  RenderChar('a', event->pos().x()-32, event->pos().y()-13);

  RenderChar('a', event->pos().x()-8, event->pos().y()-26);
  RenderChar('a', event->pos().x()-16, event->pos().y()-26);
  RenderChar('a', event->pos().x()-24, event->pos().y()-26);
  RenderChar('a', event->pos().x()-32, event->pos().y()-26);

  RenderChar('a', event->pos().x()-8, event->pos().y()-39);
  RenderChar('a', event->pos().x()-16, event->pos().y()-39);
  RenderChar('a', event->pos().x()-24, event->pos().y()-39);
  RenderChar('a', event->pos().x()-32, event->pos().y()-39);
  this->update();
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

void MainWindow::RenderChar(char ch, unsigned char x, unsigned char y) {
  const unsigned char ch1[13] = {0xCF, 0xCF, 0xC7, 0xD3, 0xD9, 0x00, 0x00, 0xDF, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF};

  byte row_byte = x / 8;
  byte shift_bits = x - (row_byte * 8);

  for(size_t i = 0; i < 13; i++) {
    byte right_mask = (ch1[i] >> (8 - shift_bits)) | (0xFF << (shift_bits));
    byte left_mask = (ch1[i] << (shift_bits)) | (0xFF >> (8 - shift_bits));

    size_t left_byte_id = row_byte + ((y+i) * BUFFER_COLS);
    size_t right_byte_id = row_byte + ((y+i) * BUFFER_COLS) + 1;

    if ((left_byte_id > 0) && (left_byte_id < BUFFER_SIZE))
      buffer[left_byte_id] &= left_mask;

    if ((right_byte_id > 0) && (right_byte_id < BUFFER_SIZE ))
      buffer[right_byte_id] &= right_mask;
  }
}

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter p(this);
  for(size_t col = 0; col < BUFFER_COLS; col++) {
    for(size_t row = 0; row < BUFFER_ROWS; row++) {
        unsigned char byte_ = buffer[col + (row * BUFFER_COLS)];

      for(size_t bit = 0; bit < 8; bit ++) {
        if((byte_ & (1 << bit)) == 0)
          p.drawPoint((col*8) + bit, row);
      }
    }
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}
