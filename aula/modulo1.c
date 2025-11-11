#include <stdio.h>
#include "header.h"

//extern int a
//se na header estiver escrito algo como extern long int, por exemplo, haverá um erro
int a=0;

float fun2(float a, int b)
{
    return a+b;
}

static int fun4(int x)
{
    return x+1;
}

int main(void)
{
    int i=1;
    float f=3.14;
    static intj=4;
    i=fun1(i,f);
    printf("%d %d\n", i, fun4(j));
    return 0;
}

//os dois modulos se conectam
//oq defini como "static" é um símbolo mas em letra minúscula