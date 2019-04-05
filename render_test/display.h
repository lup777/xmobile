#ifndef DISPLAY_H
#define DISPLAY_H

#include "druid_types.h"
#include "zone.h"


class Display
{
public:
  Display();
  ~Display();
  bool Resize(word x, word y);
  byte* Buffer();
  void Clear();
  word buf_rows();
  word buf_cols();
  word buf_size();


public:
  byte* buffer_ = nullptr;
  Zone zone_;

private:

  word buf_rows_ = 0;
  word buf_cols_ = 0;
  word buf_size_ = 0;

};

#endif // DISPLAY_H
