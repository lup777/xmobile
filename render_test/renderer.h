#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QDebug>

#include "druid_types.h"
#include "display.h"

//#define ZOOM 3
#define BUFFER_ROWS (200 )
#define BUFFER_COLS (25 )
#define BUFFER_COLS_BITS (25 * 8)
#define BUFFER_SIZE (BUFFER_COLS * BUFFER_ROWS)

//#define REPLACE_X 40
//#define REPLACE_Y 40

class Renderer : public QObject
{
  Q_OBJECT

public:
  Renderer(short x, short y);
  virtual ~Renderer() {}
  void RenderChar(const byte* ch, short x, short y, short dy);
  void RenderDot(short x, short y, bool reverce);
  void RenderLine(short x, short y, short ex, short ey); // coordinates and lengths
  void RenderZone(Display* disp);
  void RenderZone();
  void RenderCircle(short x, short y, short r);
  void RenderRectangle(short x, short y, short x1, short y1);
  void RenderSubBuffer(short x, short y, Display* sub_disp_);
  void render();

  void ResizeDisplay(short x, short y);
  Display* GetDisplay() {
    return display;
  }
  void AddDot(short x, short y, bool reverced);

signals:
  void RenderCompleteSignal(void);


private:
  byte buffer[BUFFER_SIZE];
  byte sub_buffer[100*15];

  Display main_display;
  Display sub_display;
  Display* display;

  QVector<QPair<short, short> > dots;
  QVector<QPair<short, short> > reverce_dots;
};

#endif // RENDERER_H
