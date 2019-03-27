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

  RenderChar('a', event->pos().x()-8, event->pos().y()-13);
  this->update();
}

void MainWindow::RenderChar(char ch, unsigned char x, unsigned char y) {
  const unsigned char ch1[13] = {0xCF, 0xCF, 0xC7, 0xD3, 0xD9, 0x00, 0x00, 0xDF, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF};

  byte row_byte = x / 8;
  byte shift_bits = x - (row_byte * 8);



  for(size_t i = 0; i < 13; i++) {
    byte right_mask = (ch1[i] >> (8 - shift_bits)) | (0xFF << (shift_bits));
    byte left_mask = (ch1[i] << (shift_bits)) | (0xFF >> (8 - shift_bits));

    buffer[row_byte + ((y+i) * BUFFER_COLS)] &= left_mask;
    buffer[row_byte + ((y+i) * BUFFER_COLS) + 1] &= right_mask;
  }
}

/*
void MainWindow::RenderChar(char ch, unsigned char x, unsigned char y) {
  const unsigned char ch1[13] = {0xCF, 0xCF, 0xC7, 0xD3, 0xD9, 0x00, 0x00, 0xDF, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF};

  byte row_byte = x / 8;
  byte shift_bits = x - row_byte;



  for(size_t i = 0; i < 13; i++) {
    byte left_mask = (ch1[i] >> (shift_bits)) | (0xFF << (8 - shift_bits));
    byte right_mask = (ch1[i] << (8 - shift_bits)) | (0xFF >> shift_bits);

    buffer[row_byte + ((y+i) * BUFFER_COLS) + 1] &= right_mask;
    buffer[row_byte + ((y+i) * BUFFER_COLS)] &= left_mask;
  }
}*/

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
