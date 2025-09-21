#include <stdio.h>

int main() {
    printf("Quadrados dos numeros de 1 a 10:\n");

    for (int i = 1; i <= 10; i++) {
        int quadrado = i * i;
        printf("O quadrado de %d e %d\n", i, quadrado);
    }

    return 0;
}