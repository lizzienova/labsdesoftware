/* Nome: Rafaela Bessa || Matrícula: */
/* Nome: Lis Almeida || Matrícula:  */

#include "bigint.h"
#include <stdio.h>
#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];

// se val for negativo, preencher os bytes restantes com 0xFF
// se val for positiivo, preencher os bytes restantes com 0x00

void big_val (BigInt res, long val)
{
    unsigned char extende;
    if (val<0)
    {
        extende=0xFF;
    }
    else{
        extende=0x00;
    }
    for(int i=0; i<16; i++)
    {
        res[i]=extende; //zera o vetor
    }
    for(int i=0; i<8; i++)
    {
        res[i]=(val>>(8*i)) & 0xFF;
    }
}

void print_bigint(BigInt a) {
    printf("{");
    for (int i = 0; i < 16; i++) {
        printf("0x%02X,", a[i]);
        if (i < 15) printf(" ");
    }
    printf("}");
    printf("\n");
}



