#ifndef ZONE_H
#define ZONE_H

#include "druid_types.h"

class Zone
{
public:
  Zone(word buf_cols, word buf_rows);

  void update(word x, word y);
  void clear();
  word x();
  word y();
  word ex();
  word ey();

private:
  word x_; // coordinates
  word y_; // coordinates
  word ex_; // coordinates
  word ey_; // coordinates
  bool clean;
  word BUFFER_COLS;
  word BUFFER_ROWS;
};

#endif // ZONE_H
