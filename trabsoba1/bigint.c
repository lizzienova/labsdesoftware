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

void big_shl(BigInt res, BigInt a, int n)
// deve deslocar o valor de a para a esquerda n bits (n entre 0 e 127)
//armazenar em res o resultado
{
    int n_qtbytes=n/8; // quantos bytes temos que deslocar
    int n_qtbits=n%8; //quantos bits restantes temos que deslocar 
    //pra zerar tudo
    for (int i=0; i<16; i++)
    {
        res[i]=0;
    }
    for (int i=15; i>=n_qtbytes; i--) //enquanto i for maior ou igual a quantidade de bytes
    {
        res[i]=a[i-n_qtbytes]; //movendo apenas os bytes por enqt
    }
    if (n_qtbits>0) //se existem bits restantes da divisão de bytes anterior
    {
        unsigned char bitsresto=0; //bits restantes. Começa com 0 ja que o primeiro loop nao terá 
        for (int i=0; i<16; i++)
        {
            unsigned char atual=res[i];
            res[i]= (atual<<n_qtbits) | bitsresto; //move e junta
            bitsresto=atual>>(8-n_qtbits); //atualiza com os bits que restam e que devem ir pro próximo byte
        }
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



