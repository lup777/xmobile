#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  renderer(200, 200)
{
  ui->setupUi(this);
  ui->plainTextEdit->hide();
  //centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
  //this->setMouseTracking(true);
  REPLACE_X = 40;
  REPLACE_Y = 40;
  ZOOM = ui->spinBox_3->value();

  //display = &main_display;
  ui->spinBox->setValue(BUFFER_COLS);
  ui->spinBox_2->setValue(BUFFER_ROWS);
  /*//main_display.buf_rows = BUFFER_ROWS;
  //main_display.buf_cols = BUFFER_COLS;
  //main_display.buf_size = BUFFER_SIZE;
  //main_display.buffer = new byte[BUFFER_SIZE];//buffer;

  for(word i = 0; i < main_display.buf_size; i++) {
    main_display.buffer[i] = 0xFF;
  }

  sub_display.buf_rows = 100;
  sub_display.buf_cols = 15;
  sub_display.buf_size = sub_display.buf_rows * sub_display.buf_cols;
  sub_display.buffer = sub_buffer;

  for (word i = 0; i < sub_display.buf_size; i++)
    sub_display.buffer[i] = 0xFF;

  display = &main_display;

  display = &sub_display;

  RenderCircle(64,60,30);
  RenderCircle(64,60,25);
  RenderCircle(70,70,25);

  display = &main_display;*/
  connect(&renderer, &Renderer::RenderCompleteSignal, this, &MainWindow::on_renderComplete);
  Display* display = renderer.GetDisplay();
  this->resize(QSize(((display->buf_cols() << 3) * ZOOM)+MARGIN+REPLACE_X, (display->buf_rows() * ZOOM)+MARGIN+REPLACE_X));

}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  //ui->spinBox->setValue((event->x() / ZOOM) + REPLACE_X - MARGIN);
  //ui->spinBox_2->setValue((event->y() / ZOOM) + REPLACE_X - MARGIN);
  qDebug("mouse move");
}
//
void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->delta() == 0)
    return;

  int window_half_x = this->window()->size().width() / 2;
  int window_half_y = this->window()->size().height() / 2;

  int new_mx = (event->x() - REPLACE_X) / (ZOOM + 1);
  int new_my = (event->y() - REPLACE_Y) / (ZOOM + 1);

  if (event->delta() > 0) {
    ui->spinBox_3->setValue(ZOOM + 1);
  } else {
    ui->spinBox_3->setValue(ZOOM - 1);
  }

  int new_replace_x = window_half_x - (new_mx * ZOOM);
  int new_replace_y = window_half_y - (new_my * ZOOM);

  REPLACE_X = new_replace_x;
  REPLACE_Y = new_replace_y;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  int mx = (event->x() - REPLACE_X) / ZOOM;
  int my = (event->y() - REPLACE_Y) / ZOOM;

  if(event->buttons() == Qt::LeftButton) {

    if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier)) {
      renderer.AddDot(mx, my, true);
    } else {
      renderer.AddDot(mx, my, false);
    }
  }

  if(event->buttons() == Qt::RightButton) {
    Zone zone = renderer.GetDisplay()->zone_;

    ui->spinBox->setValue((zone.ex() >> 3) - (zone.x() >> 3));
    ui->spinBox_2->setValue(zone.ey() - zone.y() + 1);
  }

  renderer.render();
}




void MainWindow::paintEvent(QPaintEvent *) {
  QPainter p(this);

  Display* display = renderer.GetDisplay();

#if DRAW_FULL_BUFFER==1
  for(size_t col = 0; col < display->buf_cols(); col++) {
    for(size_t row = 0; row < display->buf_rows(); row++) {
#else
  for(word col = display->zone.x() >> 3; col < (display->zone.ex() >> 3); col++) {
    for(word row = display->zone.y(); row < display->zone.ey(); row++) {
#endif
      unsigned char byte_ = display->buffer_[col + (row * display->buf_cols())];

      for(size_t bit = 0; bit < 8; bit ++) {
        if((byte_ & (1 << bit)) == 0) {
          size_t x = (col << 3) + bit;
          size_t y = row;
          x *= ZOOM;
          y *= ZOOM;
          for(size_t i = 0; i < ZOOM; i++)
            for(size_t j = 0; j < ZOOM; j++)
              p.drawPoint(x+i+REPLACE_X, y+j+REPLACE_Y);
        }
      }
    }
  }
  qDebug() << "paintEvent >>>" ;

  QPen pen(QColor(0xFF, 0, 0, 0x80), 1 * ZOOM, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin); // red
  p.setPen(pen);
  Zone zone = display->zone_;
  p.drawRect((zone.x() * ZOOM) + REPLACE_X + (ZOOM / 2),
             (zone.y() * ZOOM) + REPLACE_Y + (ZOOM / 2),
             (zone.ex() - zone.x()) * ZOOM,
             (zone.ey() - zone.y()) * ZOOM);

  QPen pen2(QColor(0x00, 0xFF, 0, 0x80), 1 * ZOOM, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
  p.setPen(pen2);
  p.drawRect((0 * 8 * ZOOM) + REPLACE_X + (ZOOM / 2),
             (0 * ZOOM) + REPLACE_Y + (ZOOM / 2),
             (display->buf_cols() * 8) * ZOOM,
             display->buf_rows() * ZOOM);

  //std::cout << "zone: " << display->zone.x() << ", " << display->zone.y() << ", " << display->zone.ex() << ", " << display->zone.ey() << std::endl;
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_released()
{
  bool bStatus;
  if (ui->plainTextEdit->isVisible()) {
    ui->plainTextEdit->hide();
    /*QStringList strings = ui->plainTextEdit->toPlainText().split(QRegExp("[, ]"),QString::SkipEmptyParts);

    for (int i = 0; (i < display->buf_size) && (i < strings.size()); i++) {
      display->buffer[i] = (strings[i].toUInt(&bStatus,16));
      qDebug() << "next: " << display->buffer[i];


    }*/

  } else {
    ui->plainTextEdit->show();
    ui->plainTextEdit->clear();
    QString code;
    qDebug() << "buffer size: " << renderer.GetDisplay()->buf_size();
    for(int i = 0; i < renderer.GetDisplay()->buf_size(); i++) {
       code += "0x";
       code += QString::number( renderer.GetDisplay()->buffer_[i], 16 );
       code += ", ";
    }
    ui->plainTextEdit->appendPlainText(code);
    ui->spinBox->setValue(renderer.GetDisplay()->buf_cols());
    ui->spinBox_2->setValue(renderer.GetDisplay()->buf_rows());
  }
}

void MainWindow::on_spinBox_3_valueChanged(int v)
{
  ZOOM = v;
  //this->resize(QSize(((display->buf_cols << 3) * ZOOM)+MARGIN+REPLACE_X, (display->buf_rows * ZOOM)+MARGIN+REPLACE_X));
  this->update();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
  if (arg1 < 0)
    return;

  renderer.ResizeDisplay(arg1 << 3, renderer.GetDisplay()->buf_rows());
  //renderer.render();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
  if (arg1 < 0)
    return;

  renderer.ResizeDisplay(renderer.GetDisplay()->buf_cols() << 3, arg1);
  //renderer.render();
}

void MainWindow::on_renderComplete() {
  qDebug() << "on_renderComplete";
  update();
}
