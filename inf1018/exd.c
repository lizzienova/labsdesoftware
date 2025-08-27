#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main(void) {
  char c1 = 'a';
  char c2 = 97;
  dump(&c1, sizeof(c1));

  dump(&c2, sizeof(c2));
  return 0;
}
