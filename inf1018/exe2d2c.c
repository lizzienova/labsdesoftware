#include <ctype.h>
#include <stdio.h>

int string2num (char *s, int base) {
  int a = 0;
  for (; *s; s++){
  int digito=0;
    if (isdigit(*s)){
        digito=*s-'0';
    }
    else if(isalpha(*s))
    {
        digito=tolower(*s)-'a'+10;
    }
    else{
        continue;
    }
    a = a*base + digito;
}
  return a;
}

int main (void) {
  printf("%d\n", string2num("1a", 16));
  printf("%d\n", string2num("a09b", 16));
  printf("%d\n", string2num("z09b", 36));
  return 0;
}