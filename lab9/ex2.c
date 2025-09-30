#include <stdio.h>

int fat(int n);

int main(void)
{
    int result;
    int n=5;
    result=fat(n);
    printf("fat(%d)=%d\n", n, result);
    return 0;
}