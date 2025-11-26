#include <stdio.h>

struct X {
  int a;
  short b;
  int c;
} x;

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

