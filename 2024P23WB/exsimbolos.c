#include <stdio.h>
extern short s; //U
void f1(void) { //T
s--;
printf ("s = %hd\n", s);    //U
}

void f2(void) { //T
f1();   
}


#include <stdio.h>
void f2(void); //U
short s = 101;  //D
int main(void) {    //T
printf("s = %08hx\n", s);   //U
f2();   //U
return 0;
}

//se juntarmos os dois módulos, printf em main terá como saída 101 em hexadecimal
//e chamando f2, a saída será 100