#include "zone.h"

#include <QDebug>

Zone::Zone(word buf_cols, word buf_rows)
{
  BUFFER_COLS = buf_cols;
  BUFFER_ROWS = buf_rows;
  clear();
}

void Zone::clear() {
  x_ = y_ = 255;
  ex_ = ey_ = 0;
  clean = true;
}

void Zone::update(word x, word y) { // bits, bits
  if (x < x_) {
    x_ = x;
    clean = false;
  }
  if (y < y_) {
    clean = false;
    y_ = y;
  }

  if (ex_ < x) {
    ex_ = x;
    clean = false;
  }

  if (ey_ < y) {
    clean = false;
    ey_ = y;
  }

  if (ex_ > ((BUFFER_COLS) << 3)) {
    clean = false;
    ex_ = ((BUFFER_COLS) << 3);
  }

  if (ey_ > BUFFER_ROWS) {
    clean = false;
    ey_ = BUFFER_ROWS;
  }
  qDebug() << "zone: " << x_ << ", " << y_ << ", " << ex_ << ", " << ey_;
}

word Zone::x() {
  if (clean == true)
    return 0;
  return x_ & 0xFC; // (x_/8)*8;
}
word Zone::y() {
  if (clean == true)
    return 0;
  return y_;
}
word Zone::ex() {
  if (clean == true)
    return 0;
  return (ex_ + 8) & 0xFC; // ((ex_ + 8)/8)*8;
}
word Zone::ey() {
  if (clean == true)
    return 0;
  return ey_;
}
