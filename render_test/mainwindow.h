#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

#define BUFFER_ROWS 200
#define BUFFER_COLS 25
#define BUFFER_SIZE (BUFFER_COLS * BUFFER_ROWS)

typedef unsigned char byte;
typedef struct UpdatedZoneClass {
  UpdatedZoneClass() {
    clear();
  }
  void clear() {
    x_ = y_ = 200;
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

  void RenderChar(char ch, unsigned char x, unsigned char y);
  void RenderDot(byte x, byte y);
  void RenderLine(byte x, byte y, byte ex, byte ey);
  void RenderZone();

private:
  Ui::MainWindow *ui;
  unsigned char buffer[BUFFER_SIZE];
  Zone zone;
};

#endif // MAINWINDOW_H
