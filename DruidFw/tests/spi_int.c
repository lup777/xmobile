// spi_int.c

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

volatile bool g_cs;
volatile bool g_dc;

typedef unsigned char uint8_t;

void taskYIELD() {}

void EPD_CSHi() {
  g_cs = true;
}

void EPD_CSLo() {
  g_cs = false;
}

void EPD_SelectData() {
  g_dc = 1;
}

#define pdFALSE false
#define pdTRUE true

typedef struct struct_spi_order {
  uint8_t* buffer;             // pointer to data
  size_t length;               // buffer length
  bool is_pgm;                 // is buffer is in pgm
  size_t repeat;               // how many times send buffer
} SpiOrder;

size_t xMessageBufferReceiveFromISR(SpiOrder* from, SpiOrder* to, size_t size, void* tmp) {
  if (from == NULL)
    return 0;
  //printf("read messsage buffer (%ld)\n", sizeof(SpiOrder));
  memcpy(to, from, sizeof(SpiOrder));
  return size;
}

typedef void* BaseType_t;

void test(SpiOrder* g_epd_tx_buffer_handle) {
  static SpiOrder order = {0};
  static size_t sent_cnt = 0; // they should be equal on start,
                                  // even if order is not inited
  static size_t repeat_cnt = 0;
  BaseType_t hptw = pdFALSE;
  size_t received_bytes;

/*  printf("order.length: %ld\n", order.length);
  printf("sent_cnt: %ld\n", sent_cnt);
  printf("order.repeat: %ld\n", order.repeat);
  printf("repeat_cnt: %ld\n", repeat_cnt);*/

  if (sent_cnt >= order.length) {
    repeat_cnt ++;

    if (repeat_cnt < order.repeat) {
      sent_cnt = 0; // repeat transfering buffer
      // continue transferring
    } else {
      received_bytes = xMessageBufferReceiveFromISR(g_epd_tx_buffer_handle,
                                                    &order,
                                                    sizeof(order),
                                                    &hptw);
      if (received_bytes != sizeof(order)) { // last order was sent, no more to TX
        printf("read not ok\n");
        // Stop transfering
        // sent_cnt EQ order.length, so ...
      } else { // received new order, starting to tx it
        printf("read ok\n");
        sent_cnt = 0; // last order was sent full, ready to start TX the next one
        repeat_cnt = 0;
      }
    }
  }

  // continue transferring
  if (sent_cnt < order.length) {
    EPD_SelectData();
    if (order.is_pgm)
      //SPIC.DATA = pgm_read_byte(order.buffer + sent_cnt);
      printf(" %02X ", order.buffer[sent_cnt]);
    else
      //SPIC.DATA = order.buffer[sent_cnt];
      printf(" %02X ", order.buffer[sent_cnt]);
    sent_cnt ++;
  } else { // all data from current order was sent
           // Also it can be if we need to send only one byte.
           // In this case we need only to drive CS hi.
    EPD_CSHi(); // Stop transfering
    printf("\nthe end\n");
  }

  if ( hptw != pdFALSE )
    taskYIELD();
}

void sendGen(uint8_t sample, size_t size, size_t repeat) {
  SpiOrder order_;
  g_cs = false;
  uint8_t buffer_[100];

  buffer_[0] = sample;

  order_.buffer = buffer_;
  order_.is_pgm = false;
  order_.repeat = repeat;
  order_.length = size;

  printf("-------\n");
  test(&order_);
  while(g_cs == false)
    test(NULL);
  printf("\n-------\n");
}

void sendRam(uint8_t* buffer, size_t size) {
  SpiOrder order_;
  g_cs = false;
  uint8_t buffer_[100];

  for(int i = 0; i < size; i ++)
    buffer_[i] = buffer[i];

  order_.buffer = buffer_;
  order_.is_pgm = false;
  order_.repeat = 1;
  order_.length = size;

  printf("-------\n");
  test(&order_);
  while(g_cs == false)
    test(NULL);
  printf("\n-------\n");
}

int main() {

  {
    uint8_t buffer[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    sendRam(buffer, 7);
  }

  {
    uint8_t buffer[] = {0x08, 0x09, 0x0A};
    sendRam(buffer, 3);
  }

  {
    uint8_t buffer[] = {0x08, 0x09, 0x0A};
    sendGen(0xAB, 1, 50);
  }

  {
    uint8_t buffer[] = {0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    sendRam(buffer, 5);
  }

  return 0;
}
