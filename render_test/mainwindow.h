#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

#define ZOOM 1
#define BUFFER_ROWS (200 )
#define BUFFER_COLS (25 )
#define BUFFER_SIZE (BUFFER_COLS * BUFFER_ROWS)

#define REPLACE_X 40
#define REPLACE_Y 40
#define MARGIN 40

#define DRAW_FULL_BUFFER 1

typedef unsigned char byte;
typedef unsigned short word;

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

  void RenderChar(const byte* ch, unsigned char x, unsigned char y);
  void RenderDot(byte x, byte y);
  void RenderLine(byte x, byte y, byte ex, byte ey); // coordinates and lengths
  void RenderZone();
  void RenderCircle(byte x, byte y, byte r);
  void RenderRectangle(byte x, byte y, byte x1, byte y1);
  void RenderSubBuffer(byte x, byte y, byte dx, byte dy, const byte* subbuffer);

private:
  Ui::MainWindow *ui;
  unsigned char buffer[BUFFER_SIZE];
  Zone zone;
};

#endif // MAINWINDOW_H
