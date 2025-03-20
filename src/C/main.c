#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "buffer.h"
#include "huffman.h"

unsigned char fin[65536];

int main(int argc, char **argv) {
  long size;
  int in_fd;

  if (argc < 2) return 1;

  in_fd = open(argv[1], O_RDONLY);
  if (in_fd == -1) return 2;

  size = read(in_fd, fin, 65536);
  if (size == -1) return 3;


  huffmanTests();


  close(in_fd);
  return 0;
}



unsigned char buf[32000];
void bufferTests() {
  init_write_buffer((unsigned short*)buf);
  buf_write(0b101010101010101, 15);
  buf_write(0x98DA, 16);
  buf_write(0b1010, 4);
  end_buf_write();

  init_read_buffer((unsigned short*)buf);
  printf("%X\n", buf_read(15));
  printf("%X\n", buf_read(16));
  printf("%X\n", buf_read(4));
}
