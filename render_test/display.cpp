#include "display.h"

Display::Display()
  : zone_(0,0)
{

}

Display::~Display() {
  if (buffer_)
    delete [] buffer_;
}

bool Display::Resize(word x, word y) {
  buf_cols_ = x >> 3;
  buf_rows_ = y;
  buf_size_ = x * y;

  buffer_ = new byte[buf_size_];

  if (buffer_ == nullptr)
    return false;

  zone_ = Zone(buf_cols_, buf_rows_);
  Clear();
  return true;
}

void Display::Clear() {
  for(word i = 0; i < buf_size_; i++) {
    buffer_[i] = 0xFF;
  }
  zone_.clear();
}

byte* Display::Buffer() {
  return buffer_;
}

word Display::buf_rows() {
  return buf_rows_;
}
word Display::buf_cols() {
  return buf_cols_;
}
word Display::buf_size() {
  return buf_size_;
}
