#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>

#define BUFFER_ROWS 200
#define BUFFER_COLS 24
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

private:
  Ui::MainWindow *ui;
  unsigned char buffer[BUFFER_SIZE];
};

#endif // MAINWINDOW_H
