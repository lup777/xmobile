//render.c
#include "render.h"

#include "global.h"
#include "epd.h"
#include "fonts.h"

#define DISPLAY_BUFFER_COLS_BYTE 25
#define DISPLAY_BUFFER_ROWS_BITS 200
#define DISPLAY_BUFFER_SIZE (DISPLAY_BUFFER_ROWS_BITS * DISPLAY_BUFFER_COLS_BYTE)

DispBuf display;

void displayInit(void) {
  display.buffer = pvPortMalloc(DISPLAY_BUFFER_SIZE);

  if (display.buffer == NULL) {
    _log("disp buf malloc(%d) FAILED", DISPLAY_BUFFER_SIZE);
    for(;;) {}
    return;
  }

  display.buf_size = DISPLAY_BUFFER_SIZE;
  _log("disp buf malloc(%d) OK", display.buf_size);
  

  for (size_t i = 0; i < display.buf_size; i++)
    display.buffer[i] = 0xFF;

  zoneClear();
  display.buf_rows = DISPLAY_BUFFER_ROWS_BITS;
  display.buf_cols = DISPLAY_BUFFER_COLS_BYTE;
  display.buf_size = DISPLAY_BUFFER_SIZE;

  SPIC_Init(display.buf_rows);
  EPD_Init();
}

void displayFlush(void) {
  EPD_StartPartial();

  
  for (size_t col = 0; col < (size_t)display.buf_cols; col++ ) {
    EPD_ContinuePartial(display.buf_cols - col - 1, // col number byte
			display.buf_rows - 0, // start row number bit
			display.buffer + col, // pointer to first data byte
			display.buf_rows, // steps
			display.buf_cols); // step size
  }
  EPD_UpdatePartial();

  EPD_StopPartial();
  /*_log("(%d:%d) (%d:%d)", zoneX(),
       zoneY(),
       zoneEx(),
       zoneEy());*/
  
  zoneClear();
    for(word i = 0; i < display.buf_size; i++)
      display.buffer[i] = 0xFF;
}

void displayRenderDot(short x, short y, DispBuf* display_) {
  if (y > display_->buf_rows || x > (display_->buf_cols << 3))
    return;
  if (y < 0 || x < 0)
    return;

  byte row_byte = x >> 3; // x / 8
  byte shift_bits = x & 0x07; ;//x - (row_byte << 3); // x - (row * 8)

  byte left_mask = ~(0x01 << shift_bits);

  word left_byte_id = row_byte + (y * display_->buf_cols);

  if (left_byte_id < display_->buf_size)
    display_->buffer[left_byte_id] &= left_mask;

  zoneUpdate(x - shift_bits, y, &display);
}

void displayRenderLine(short x, short y, short ex, short ey,
			    DispBuf* display_) {
  // x, y, ex, ey - coordinates of the start and the end
  float dx = ex - x;
  float dy = ey - y;

  //float steps = sqrt(pow(dx,2) + pow(dy,2));
  float steps = sqrt((dx*dx) + (dy*dy));

  float step_x = dx / steps;
  float step_y = dy / steps;

  for (short i = 0 ; i < steps; i++) {
    displayRenderDot(x+(step_x*i), y+(step_y*i), display_);
  }
}

void displayRenderCircle(short x, short y, short r, DispBuf* display_) {
  //x^2 + y^2 = r^2
  short p1 = r * r; //pow(r, 2);

  for (short i = 0; i < r; i+=1) {
    short p2 = i * i; //pow(i, 2);
    short sqrt_ = sqrt(p1 - p2);
    displayRenderDot(i + x, sqrt_ + y, display_);
    displayRenderDot(i + x, -sqrt_ + y, display_);
    displayRenderDot(-i + x, sqrt_ + y, display_);
    displayRenderDot(-i + x, -sqrt_ + y, display_);
  }
}

void displayRenderRectangle(short x, short y, short x1, short y1,
			    DispBuf* display_) {
  // coordinates and coordinates
  displayRenderLine(x, y, x1, y, display_);
  displayRenderLine(x1, y, x1, y1, display_);
  displayRenderLine(x1, y1, x, y1, display_);
  displayRenderLine(x, y1, x, y, display_);
}

void displayRenderText(short x, short y,
		       char* text, size_t len,
		       DispBuf* display_) {
  DispBuf pic;
  pic.buf_cols = 1; // byte
  pic.buf_rows = 13; // bits
  uint8_t buffer[13];
  pic.buffer = buffer;

  for (size_t i = 0; i < len; i++) {
    uint8_t* tmp = (uint8_t*)FONT_GetPicture8x13( (uint8_t)(text[i]) );

    for (byte j = 0; j < 13; j++) {
      pic.buffer[j] = pgm_read_byte(tmp+j);
    }
    displayRenderSubBuffer(x + ((pic.buf_cols * i) << 3),
			   y,
			   &pic,
			   display_);
    //_log("--> 0x%02X", text[i]);
  }
}

void displayRenderSubBuffer(short tar_x, short tar_y,
			    DispBuf* sub_disp_, DispBuf* display_) {
  if (tar_x < 0 || tar_x > (display_->buf_cols << 3))
    return;

  short tar_col_id_byte = tar_x >> 3; // columnt number in target buffer
  byte shift_bits = tar_x & 0x07; // tar_x - (tar_x / 8)*8;

  for(short src_cur_col = 0; src_cur_col < (sub_disp_->buf_cols); src_cur_col++) {
    for(short src_cur_row = 0; src_cur_row < sub_disp_->buf_rows; src_cur_row += 1) {
      // i - current line number in source buffer

      word src_byte_id = (sub_disp_->buf_cols * src_cur_row) + src_cur_col;
      //_log("-> 0x%02X", sub_disp_->buffer[ src_byte_id]);
      byte right_mask = ( sub_disp_->buffer[ src_byte_id] >> (8 - shift_bits))
	| (0xFF << (shift_bits));
      
      byte left_mask = ( sub_disp_->buffer[ src_byte_id] << (shift_bits))
	| (0xFF >> (8 - shift_bits));

      short tar_cur_col = tar_col_id_byte + src_cur_col;
      word left_byte_id = tar_cur_col +
	((src_cur_row + tar_y) *
	 display_->buf_cols); // byte id in target buffer

      if (left_byte_id >= display_->buf_size
              || tar_cur_col > display_->buf_cols
              || tar_y + src_cur_row >= display_->buf_rows)
        continue;

      //_log("0x%02X 0x%02X", display_->buffer[left_byte_id], display_->buffer[left_byte_id + 1]);

      
      display_->buffer[left_byte_id] &= left_mask;

      zoneUpdate(tar_cur_col << 3, tar_y, display_);
      zoneUpdate(tar_cur_col << 3, tar_y + src_cur_row, display_);

      if (left_byte_id + 1 >= display_->buf_size
              || tar_cur_col > display_->buf_cols
              || tar_y + src_cur_row >= display_->buf_rows)
        continue;

      display_->buffer[left_byte_id + 1] &= right_mask;
      //_log("-> 0x%02X 0x%02X", display_->buffer[left_byte_id], display_->buffer[left_byte_id + 1]);      
      zoneUpdate((tar_cur_col + 1) << 3, tar_y, display_);
      zoneUpdate((tar_cur_col + 1) << 3, tar_y + src_cur_row, display_);
    }
  }
}

void zoneUpdate(short x, short y, DispBuf* display_) {

  if (x < display_->zone.x_) {
      display_->zone.x_ = x;
      display_->zone.clean = false;
    }
    if (y < display_->zone.y_) {
      display_->zone.clean = false;
      display_->zone.y_ = y;
    }

    if (display_->zone.ex_ < x) {
      display_->zone.ex_ = x;
      display_->zone.clean = false;
    }

    if (display_->zone.ey_ < y) {
      display_->zone.clean = false;
      display_->zone.ey_ = y;
    }

    if (display_->zone.ex_ > ((display_->buf_cols) << 3)) {
      display_->zone.clean = false;
      display_->zone.ex_ = ((display_->buf_cols) << 3);
    }

    if (display_->zone.ey_ > display_->buf_rows) {
      display_->zone.clean = false;
      display_->zone.ey_ = display_->buf_rows;
    }
}

void zoneClear(void) {
  display.zone.x_ = display.zone.y_ = display.buf_rows;
  display.zone.ex_ = display.zone.ey_ = 0;
  display.zone.clean = true;
}

word zoneX(void) {
  if (display.zone.clean)
    return 0;
  return display.zone.x_ & 0xFC; // (x_/8)*8;
}
word zoneY(void) {
  if (display.zone.clean)
    return 0;
  return display.zone.y_;
}
word zoneEx(void) {
  if (display.zone.clean)
    return 0;
  return (display.zone.ex_ + 8) & 0xFC; // ((ex_ + 8)/8)*8;
}
word zoneEy(void) {
  if (display.zone.clean)
    return 0;
  return display.zone.ey_;
}
