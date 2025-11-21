#include <stdio.h>
#include "temp1.h"

int a = 1024; //D

int main (void) {   //T
  b();    //U
  printf("%d\n", a);    //U
  return 0;
}