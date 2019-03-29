#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

#define ZOOM 1
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

  void update(byte x, byte y) {
    if (x < x_)
      x_ = x;
    if (y < y_)
      y_ = y;

    if (ex_ < x)
      ex_ = x;
    if (ey_ < y)
      ey_ = y;

    /*if (x_ < 0)
      x_ = 0;
    if (y_ < 0)
      y_ = 0;*/
    if (ex_ > (BUFFER_COLS * 8)-1)
      ex_ = (BUFFER_COLS * 8)-1;
    if (ey_ > BUFFER_ROWS)
      ey_ = BUFFER_ROWS;
  }

  byte x() {
    return (x_/8)*8;
  }
  byte y() {
    return y_;
  }
  byte ex() {
    return ((ex_ + 8)/8)*8;
  }
  byte ey() {
    return ey_;
  }

  byte x_;
  byte y_;
  byte ex_;
  byte ey_;
} Zone;

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
  void RenderSubBuffer(short x, short y, short dx, short dy, const byte* subbuffer);

private:
  Ui::MainWindow *ui;
  byte buffer[BUFFER_SIZE];
  byte sub_buffer[100*15];
  byte* display_buffer;
  word display_buffer_rows;
  word display_buffer_cols;
  word display_buffer_size;
  Zone zone;
};

#endif // MAINWINDOW_H
