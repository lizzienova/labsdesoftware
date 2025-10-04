#include <stdio.h>
#include "bigint.h"

int main() {
    BigInt a, res;
/*
    big_val(a, -1);
    printf("-1: \n");
    print_bigint(a);
    printf("\n");

    big_val(a, 0);
    printf("0: \n");
    print_bigint(a);
    printf("\n");

    big_val(a, 0x123456789ABCDEF);
    printf("0x123456789ABCDEF: \n");
    print_bigint(a);
    printf("\n");
    */

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
    big_shl(res,a,127);
    printf("a = ");
    print_bigint(a);
    printf("a << %d = ", 127);
    print_bigint(res);
    printf("\n");

    return 0;
}
