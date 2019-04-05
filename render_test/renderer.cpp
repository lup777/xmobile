#include "renderer.h"

Renderer::Renderer(short x, short y)
{
    //main_display.Resize(BUFFER_COLS << 3, BUFFER_ROWS);
  main_display.Resize(x, y);
  sub_display.Resize(15 << 3, 100);

  display = &sub_display;

  RenderCircle(64,60,30);
  RenderCircle(64,60,25);
  RenderCircle(70,70,25);

  display = &main_display;
}

void Renderer::render() {
  display->Clear();

  byte sub_test[3*13] = {0xff, 0xff, 0x0, 0x1c, 0x9f, 0xcf, 0xe7, 0xf3, 0x31, 0x0, 0xff, 0xff, 0xff,
                         0xFF, 0xFF, 0xFF, 0xC3, 0x83, 0x9F, 0x83, 0x99, 0x01, 0x03, 0xFF, 0xFF, 0xFF,
                         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  byte id = 1;
  Display d;
  d.Resize(8, 13);
  for (int i = 0 ; i < d.buf_size(); i++) {
    d.buffer_[i] = sub_test[(id * 13) + i];
  }
  //RenderSubBuffer(0, 0, &d);

  for (int i = 0; i < reverce_dots.size(); i++) {
    RenderDot(reverce_dots[i].first, reverce_dots[i].second, true);
  }

  for (int i = 0; i < dots.size(); i++) {
    RenderDot(dots[i].first, dots[i].second, false);
  }

  emit RenderCompleteSignal();
}
void Renderer::RenderZone() {
  RenderZone(display);
}

void Renderer::RenderZone(Display* disp) {
  Zone tmp1 = display->zone_;
  Zone tmp = disp->zone_;
  RenderRectangle(disp->zone_.x(), disp->zone_.y(), disp->zone_.ex(), disp->zone_.ey());
  disp->zone_ = tmp;
  display->zone_ = tmp1;
}

void Renderer::RenderRectangle(short x, short y, short x1, short y1) {// coordinates and coordinates
  RenderLine(x, y, x1, y);
  RenderLine(x1, y, x1, y1);
  RenderLine(x1, y1, x, y1);
  RenderLine(x, y1, x, y);
}

void Renderer::RenderCircle(short x, short y, short r) {
  //x^2 + y^2 = r^2
    short p1 = r * r; //pow(r, 2);

  for (short i = 0; i < r; i+=1) {
    short p2 = i * i; //pow(i, 2);
    short sqrt_ = sqrt(p1 - p2);
    RenderDot(i + x, sqrt_ + y, false);
    RenderDot(i + x, -sqrt_ + y, false);
    RenderDot(-i + x, sqrt_ + y, false);
    RenderDot(-i + x, -sqrt_ + y, false);
  }
}

void Renderer::RenderDot(short x, short y, bool reverce) {
  if (y >= display->buf_rows() || x >= (display->buf_cols() << 3))
    return;
  if (y < 0 || x < 0)
    return;
//qDebug() << "RenderDot(" << x << ", " << y << ")";
  byte row_byte = x >> 3; // x / 8
  byte shift_bits = x & 0x07; ;//x - (row_byte << 3); // x - (row * 8)

  byte left_mask = ~(0x01 << shift_bits);

  word left_byte_id = row_byte + (y * display->buf_cols());

  if (left_byte_id < display->buf_size())
    if (!reverce) {// set
      display->buffer_[left_byte_id] &= left_mask;
      display->zone_.update(x - shift_bits, y);
    } else {
      display->buffer_[left_byte_id] |= ~left_mask;
    }
}

void Renderer::RenderLine(short x, short y, short ex, short ey) { // coordinates of the start and the end
  float dx = ex - x;
  float dy = ey - y;

  //float steps = sqrt(pow(dx,2) + pow(dy,2));
  float steps = sqrt((dx*dx) + (dy*dy));

  float step_x = dx / steps;
  float step_y = dy / steps;

  for (short i = 0 ; i < steps; i++) {
    RenderDot(x+(step_x*i), y+(step_y*i), false);
  }
}

void Renderer::RenderSubBuffer(short tar_x, short tar_y, Display* sub_disp_) {
  if (tar_x < 0 || tar_x > (display->buf_cols() << 3))
    return;

  short tar_col_id_byte = tar_x >> 3; // columnt number in target buffer
  byte shift_bits = tar_x & 0x07; // tar_x - (tar_x / 8)*8;

  for(short src_cur_col = 0; src_cur_col < (sub_disp_->buf_cols()); src_cur_col++) {
    for(short src_cur_row = 0; src_cur_row < sub_disp_->buf_rows(); src_cur_row += 1) { // i - current line number in source buffer

      word src_byte_id = (sub_disp_->buf_cols() * src_cur_row) + src_cur_col;

      byte right_mask = ( sub_disp_->buffer_[ src_byte_id] >> (8 - shift_bits)) | (0xFF << (shift_bits));
      byte left_mask = ( sub_disp_->buffer_[ src_byte_id] << (shift_bits)) | (0xFF >> (8 - shift_bits));

      word tar_cur_col = tar_col_id_byte + src_cur_col;
      word left_byte_id = tar_cur_col + ((src_cur_row + tar_y) * display->buf_cols()); // byte id in target buffer

      if (left_byte_id >= display->buf_size()
              || tar_cur_col > display->buf_cols()
              || tar_y + src_cur_row >= display->buf_rows())
        continue;

      display->buffer_[left_byte_id] &= left_mask;
      display->zone_.update(tar_cur_col << 3, tar_y);
      display->zone_.update(tar_cur_col << 3, tar_y + src_cur_row);

      if (left_byte_id + 1 >= display->buf_size()
              || tar_cur_col > display->buf_cols()
              || tar_y + src_cur_row >= display->buf_rows())
        continue;

      display->buffer_[left_byte_id + 1] &= right_mask;
      display->zone_.update((tar_cur_col + 1) << 3, tar_y);
      display->zone_.update((tar_cur_col + 1) << 3, tar_y + src_cur_row);
    }
  }
  //RenderZone(sub_disp_);
}

void Renderer::ResizeDisplay(short x, short y) {
  display->Resize(x, y);
  render();

  for(int i = 0; i < dots.size(); i++) {
    dots[i].first -= display->zone_.x();
    dots[i].second -= display->zone_.y();
  }
}

void Renderer::AddDot(short x, short y, bool reverced) {
  qDebug() << "Add dot(" << x << ", " << y << ", " << reverced << "";
  for(int i = 0; i < dots.size(); i++) {
    if (dots[i].first == x && dots[i].second == y) {
      dots.erase(dots.begin() + i);
      return;
    }
  }

  if (!reverced)
    dots.push_back(QPair<short, short>(x, y));
  else
    reverce_dots.push_back(QPair<short, short>(x, y));
}
