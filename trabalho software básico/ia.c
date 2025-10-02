/* Rafaela_Bessa 2420043 3WA */
/* Lis_Villanova Matricula 3WA */

#include <stdio.h>
#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];
#define BIGINT_SIZE (NUM_BITS/8)
#include "bigint.h"

/* Atribuição (com extensão) */
void big_val (BigInt res, long val){
    int i;
    for(i = 0; i < BIGINT_SIZE; i++){
        res[i] = (val >> (i * 8)) & 0xFF;
    }
    if(val < 0){
        for(i = sizeof(long); i < BIGINT_SIZE; i++){
            res[i] = 0xFF;
        }
    }
}

/* Operações Aritméticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a){
    int i;
    for(i = 0; i < BIGINT_SIZE; i++){
        res[i] = ~a[i];
    }
    BigInt one;
    big_val(one, 1);
    big_sum(res, res, one);
}

/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b){
    int i;
    unsigned int carry = 0;
    for(i = 0; i < BIGINT_SIZE; i++){
        unsigned int sum = a[i] + b[i] + carry;
        res[i] = sum & 0xFF;
        carry = (sum >> 8) & 0xFF;
    }
}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b){
    BigInt b_comp2;
    big_comp2(b_comp2, b);
    big_sum(res, a, b_comp2);
}

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b){
    BigInt temp_res;
    big_val(temp_res, 0);
    BigInt temp_a;
    big_val(temp_a, 0);
    int i, j;
    for(i = 0; i < BIGINT_SIZE; i++){
        for(j = 0; j < BIGINT_SIZE; j++){
            if(i + j < BIGINT_SIZE){
                unsigned int mul = a[i] * b[j];
                BigInt mul_shifted;
                big_val(mul_shifted, mul);
                big_shl(mul_shifted, mul_shifted, (i + j) * 8);
                big_sum(temp_res, temp_res, mul_shifted);
            }
        }
    }
    for(i = 0; i < BIGINT_SIZE; i++){
        res[i] = temp_res[i];
    }
}

/* Operações de Deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n){
    int byte_shift = n / 8;
    int bit_shift = n % 8;
    int i;

    for(i = BIGINT_SIZE - 1; i >= 0; i--){
        if(i - byte_shift < 0){
            res[i] = 0;
        } else {
            res[i] = a[i - byte_shift] << bit_shift;
            if(i - byte_shift - 1 >= 0 && bit_shift != 0){
                res[i] |= a[i - byte_shift - 1] >> (8 - bit_shift);
            }
        }
    }
}

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n){
    int byte_shift = n / 8;
    int bit_shift = n % 8;
    int i;

    for(i = 0; i < BIGINT_SIZE; i++){
        if(i + byte_shift >= BIGINT_SIZE){
            res[i] = 0;
        } else {
            res[i] = a[i + byte_shift] >> bit_shift;
            if(i + byte_shift + 1 < BIGINT_SIZE && bit_shift != 0){
                res[i] |= a[i + byte_shift + 1] << (8 - bit_shift);
            }
        }
    }
}

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n){
    int byte_shift = n / 8;
    int bit_shift = n % 8;
    int i;
    unsigned char sign_byte = (a[BIGINT_SIZE - 1] & 0x80) ? 0xFF : 0x00;

    for(i = 0; i < BIGINT_SIZE; i++){
        if(i + byte_shift >= BIGINT_SIZE){
            res[i] = sign_byte;
        } else {
            res[i] = a[i + byte_shift] >> bit_shift;
            if(i + byte_shift + 1 < BIGINT_SIZE && bit_shift != 0){
                res[i] |= a[i + byte_shift + 1] << (8 - bit_shift);
            }
        }
    }
}