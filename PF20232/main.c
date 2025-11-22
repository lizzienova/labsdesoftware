#include <stdio.h>

/* função C pura */
int corta(int v[], int i)
{
    return v[i];
}

long int boo_c(int *a, int n) {
    long int acc = 0;
    while (n--) {
        acc += corta(a, n);
        a++;
    }
    return acc;
}

/* função assembly */
long int boo(int *a, int n);

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;

    long int result_c   = boo_c(arr, n);
    long int result_asm = boo(arr, n);

    printf("Resultado C   : %ld\n", result_c);
    printf("Resultado ASM : %ld\n", result_asm);

    if (result_c == result_asm)
        printf("✅ Os resultados batem!\n");
    else
        printf("❌ Os resultados NÃO batem!\n");

    return 0;
}
