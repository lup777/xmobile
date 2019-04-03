#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>
#include <QPair>
#include <QVector>
#include <QDebug>

//#define ZOOM 3
#define BUFFER_ROWS (200 )
#define BUFFER_COLS (25 )
#define BUFFER_COLS_BITS (25 * 8)
#define BUFFER_SIZE (BUFFER_COLS * BUFFER_ROWS)

//#define REPLACE_X 40
//#define REPLACE_Y 40
#define MARGIN 40

#define DRAW_FULL_BUFFER 1

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned short uint16_t;

typedef struct UpdatedZoneClass {
  UpdatedZoneClass() {
    clear();
  }
  void clear() {
    x_ = y_ = 255;
    ex_ = ey_ = 0;
    clean = true;
  }

  void update(word x, word y) { // bits, bits
    //qDebug() << "update zone: " << x << " : " << y;


    //if (clean == true) {
    //  x_ = y_ = ex_ = ey_;
   // }

    if (x < x_) {
      x_ = x;
      clean = false;
    }
    if (y < y_) {
      clean = false;
      y_ = y;
    }

    if (ex_ < x) {
      ex_ = x;
      clean = false;
    }

    if (ey_ < y) {
      clean = false;
      ey_ = y;
    }

    if (ex_ > ((BUFFER_COLS) << 3)) {
      clean = false;
      ex_ = ((BUFFER_COLS) << 3);
    }

    if (ey_ > BUFFER_ROWS) {
      clean = false;
      ey_ = BUFFER_ROWS;
    }
    qDebug() << "zone: " << x_ << ", " << y_ << ", " << ex_ << ", " << ey_;
  }

  word x() {
    if (clean == true)
      return 0;
    return x_ & 0xFC; // (x_/8)*8;
  }
  word y() {
    if (clean == true)
      return 0;
    return y_;
  }
  word ex() {
    if (clean == true)
      return 0;
    return (ex_ + 8) & 0xFC; // ((ex_ + 8)/8)*8;
  }
  word ey() {
    if (clean == true)
      return 0;
    return ey_;
  }
private:
  word x_; // coordinates
  word y_; // coordinates
  word ex_; // coordinates
  word ey_; // coordinates
  bool clean;
} Zone;

typedef struct struct_display_buffer {
    byte* buffer;
    word buf_rows;
    word buf_cols;
    word buf_size;
    Zone zone;
} DispBuf;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void paintEvent(QPaintEvent *);
  void mouseMoveEvent(QMouseEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent *event);

  void RenderChar(const byte* ch, short x, short y, short dy);
  void RenderDot(short x, short y, bool reverce);
  void RenderLine(short x, short y, short ex, short ey); // coordinates and lengths
  void RenderZone(DispBuf* disp);
  void RenderZone();
  void RenderCircle(short x, short y, short r);
  void RenderRectangle(short x, short y, short x1, short y1);
  void RenderSubBuffer(short x, short y, DispBuf* sub_disp_);
  void render();

private slots:
  void on_pushButton_released();
  void on_spinBox_3_valueChanged(int arg1);

  void on_spinBox_valueChanged(int arg1);

  void on_spinBox_2_valueChanged(int arg1);

private:
  Ui::MainWindow *ui;
  byte buffer[BUFFER_SIZE];
  byte sub_buffer[100*15];

  DispBuf main_display;
  DispBuf sub_display;
  DispBuf* display;
  QVector<QPair<short, short> > dots;
  QVector<QPair<short, short> > reverce_dots;
  byte ZOOM;
  int REPLACE_X;
  int REPLACE_Y;
};

#endif // MAINWINDOW_H
