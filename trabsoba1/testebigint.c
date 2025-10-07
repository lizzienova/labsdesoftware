#include <stdio.h>
#include "bigint.h"
int main() {
    BigInt a, b, res;

    printf("===== TESTES DE SOMA =====\n");
    big_val(a, 5);
    big_val(b, 10);
    big_sum(res, a, b);
    printf("5 + 10 = ");
    print_bigint(res);
    printf("\n");

    big_val(a, -1);
    big_val(b, 1);
    big_sum(res, a, b);
    printf("-1 + 1 = ");
    print_bigint(res);
    printf("\n");

    printf("===== TESTES DE SUBTRACAO =====\n");
    big_val(a, 20);
    big_val(b, 5);
    big_sub(res, a, b);
    printf("20 - 5 = ");
    print_bigint(res);
    printf("\n");

    big_val(a, 5);
    big_val(b, 10);
    big_sub(res, a, b);
    printf("5 - 10 = ");
    print_bigint(res);
    printf("\n");

    printf("===== TESTES DE MULTIPLICACAO =====\n");
    big_val(a, 3);
    big_val(b, 4);
    big_mul(res, a, b);
    printf("3 * 4 = ");
    print_bigint(res);
    printf("\n");

    big_val(a, -2);
    big_val(b, 3);
    big_mul(res, a, b);
    printf("-2 * 3 = ");
    print_bigint(res);
    printf("\n");

    printf("===== TESTES DE SHIFT ARITMETICO DIREITA =====\n");
    big_val(a, -2);
    big_sar(res, a, 1);
    printf("-2 >> 1 = ");
    print_bigint(res);
    printf("\n");

    big_val(a, -128);
    big_sar(res, a, 8);
    printf("-128 >> 8 = ");
    print_bigint(res);
    printf("\n");

    big_val(a, 128);
    big_sar(res, a, 4);
    printf("128 >> 4 = ");
    print_bigint(res);
    printf("\n");

    printf("===== TESTES DE SHIFT ESQUERDA =====\n");
    big_val(a,1);
    big_shl(res,a,1);
    printf("a = ");
    print_bigint(a);
    printf("a << %d = ", 1);
    print_bigint(res);
    printf("\n");

    big_val(a, 8);
    big_shl(res, a, 8);
    printf("a = ");
    print_bigint(a);
    printf("a << %d = ", 8);
    print_bigint(res);
    printf("\n");

    big_val(a,12);
    big_shl(res,a,12);
    printf("a = ");
    print_bigint(a);
    printf("a << %d = ", 12);
    print_bigint(res);
    printf("\n");

    big_val(a,127);
    big_shl(res,a,7);
    printf("a = ");
    print_bigint(a);
    printf("a << %d = ", 7);
    print_bigint(res);
    printf("\n");

    big_val(a,-1);
    big_shl(res,a,1);
    printf("a = ");
    print_bigint(a);
    printf("a << %d = ", 1);
    print_bigint(res);
    printf("\n");

    big_val(a,-128);
    big_shl(res,a,8);
    printf("a = ");
    print_bigint(a);
    printf("a << %d = ", 8);
    print_bigint(res);
    printf("\n");

    return 0;
}
