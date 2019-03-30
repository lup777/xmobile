#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

#define ZOOM 2
#define BUFFER_ROWS (200 )
#define BUFFER_COLS (25 )
#define BUFFER_COLS_BITS (25 * 8)
#define BUFFER_SIZE (BUFFER_COLS * BUFFER_ROWS)

#define REPLACE_X 40
#define REPLACE_Y 40
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
    x_ = y_ = BUFFER_ROWS;
    ex_ = ey_ = 0;
  }

  void update(word x, word y) {
    if (x < x_)
      x_ = x;
    if (y < y_)
      y_ = y;

    if (ex_ < x)
      ex_ = x;
    if (ey_ < y)
      ey_ = y;

    if (ex_ > ((BUFFER_COLS - 1) << 3))
      ex_ = ((BUFFER_COLS - 1) << 3);
    if (ey_ > BUFFER_ROWS)
      ey_ = BUFFER_ROWS;
  }

  word x() {
    if (ex_ == 0 || ey_ == 0)
      return 0;
    return x_ & 0xFC; // (x_/8)*8;
  }
  word y() {
    if (ex_ == 0 || ey_ == 0)
      return 0;
    return y_;
  }
  word ex() {
    if (ex_ == 0 || ey_ == 0)
      return 0;
    return (ex_ + 8) & 0xFC; // ((ex_ + 8)/8)*8;
  }
  word ey() {
    if (ex_ == 0 || ey_ == 0)
      return 0;
    return ey_;
  }

  word x_; // coordinates
  word y_; // coordinates
  word ex_; // coordinates
  word ey_; // coordinates
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

  void RenderChar(const byte* ch, short x, short y, short dy);
  void RenderDot(short x, short y);
  void RenderLine(short x, short y, short ex, short ey); // coordinates and lengths
  void RenderZone();
  void RenderCircle(short x, short y, short r);
  void RenderRectangle(short x, short y, short x1, short y1);
  void RenderSubBuffer(short x, short y, DispBuf* sub_disp_);

private:
  Ui::MainWindow *ui;
  byte buffer[BUFFER_SIZE];
  byte sub_buffer[100*15];

  DispBuf main_display;
  DispBuf sub_display;
  DispBuf* display;
};

#endif // MAINWINDOW_H
