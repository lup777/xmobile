#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <QPoint>


class ShaderObject
{
public:
  ShaderObject();
  virtual ~ShaderObject() {}

  QPoint Position();

private:
  QPoint position_;
};

#endif // SHADEROBJECT_H
