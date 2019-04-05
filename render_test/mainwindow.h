#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>
#include <QPair>
#include <QVector>
#include <QDebug>

#include "renderer.h"

#define MARGIN 40

#define DRAW_FULL_BUFFER 1

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



private slots:
  void on_pushButton_released();
  void on_spinBox_3_valueChanged(int arg1);

  void on_spinBox_valueChanged(int arg1);

  void on_spinBox_2_valueChanged(int arg1);

public slots:
  void on_renderComplete();

private:
  Ui::MainWindow *ui;


  Renderer renderer;
  byte ZOOM;
  int REPLACE_X;
  int REPLACE_Y;
};

#endif // MAINWINDOW_H
