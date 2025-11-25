#include <stdio.h>
int main(void) {
  unsigned int x = 0x87654321;
  unsigned int y, z;

  y = x & 0x000000ff;

  z = (x & 0x00ffffff) | 0xff000000;

  printf("%08x %08x\n", y, z);
}