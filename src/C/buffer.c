#include "buffer.h"

unsigned short *out_data, used_bits = 0;
unsigned long out_current_value = 0;

unsigned short *in_data, available_bits = 0;
unsigned long in_current_value = 0;


void init_write_buffer(unsigned short *data) {
  out_data = data;
  used_bits = 0;
  out_current_value = 0;
}

void buf_write(unsigned short v, unsigned char length) {
  out_current_value |= v << used_bits;
  used_bits += length;
  if (used_bits >= 16) {
    *(out_data++) = out_current_value & 0xFFFF;
    out_current_value >>= 16;
    used_bits -= 16;
  }
}
void end_buf_write() { buf_write(0, 16 - used_bits); }


void init_read_buffer(unsigned short *data) {
  in_data = data;
  available_bits = 0;
  out_current_value = 0;
}

unsigned short buf_read(unsigned char length) {
  if (available_bits < length) {
    in_current_value |= *(in_data++) << available_bits;
    available_bits += 16;
  }
  unsigned short tmp_res = in_current_value;
  in_current_value >>= length;
  available_bits -= length;
  return tmp_res;
}
