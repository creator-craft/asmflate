#pragma once

void init_write_buffer(unsigned short*);
void buf_write(unsigned short v, unsigned char length);
void end_buf_write();

void init_read_buffer(unsigned short*);
unsigned short buf_read(unsigned char length);
