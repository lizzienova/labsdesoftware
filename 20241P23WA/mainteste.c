#include <stdio.h>

void foo(double *vd, int n);

int main(void) {
    double arr[6];
    int i;

    /* inicializa com valores não-zero pra vermos a mudança */
    for (i = 0; i < 6; ++i) arr[i] = (double)(i + 1) * 1.5;

    printf("Antes:\n");
    for (i = 0; i < 6; ++i) printf("arr[%d] = %g\n", i, arr[i]);

    /* chama sua função assembly, por exemplo para limpar os primeiros 4 elementos */
    foo(arr, 4);

    printf("\nDepois (após foo(arr,4)):\n");
    for (i = 0; i < 6; ++i) printf("arr[%d] = %g\n", i, arr[i]);

    return 0;
}