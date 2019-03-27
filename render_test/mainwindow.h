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

private:
  Ui::MainWindow *ui;
  unsigned char buffer[BUFFER_SIZE];
};

#endif // MAINWINDOW_H
