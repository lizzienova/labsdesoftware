#include <stdio.h>
#include "bigint.h"

int main() {
    BigInt a;

    big_val(a, 1);
    printf("1: ");
    print_bigint(a);

    big_val(a, -1);
    printf("-1: ");
    print_bigint(a);

    big_val(a, 0);
    printf("0: ");
    print_bigint(a);

    big_val(a, 0x123456789ABCDEF);
    printf("0x123456789ABCDEF: ");
    print_bigint(a);
    return 0;
}
