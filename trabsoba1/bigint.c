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
    unsigned long uval=(unsigned long) val;
    unsigned char extende;
    if (val<0)
    {
        extende=0xFF;
    }
    else{
        extende=0x00;
    }
    for(int i=0; i<sizeof(long); i++)
    {
        res[i]=(uval>>(8*i))& 0xFF;
    }
    for (int i=sizeof(long); i<16; i++)
    {
        res[i]=extende;
    }
}

void big_shl(BigInt res, BigInt a, int n)
// deve deslocar o valor de a para a esquerda n bits (n entre 0 e 127)
//armazenar em res o resultado
{
    int n_qtbytes=n/8; // quantos bytes temos que deslocar
    int n_qtbits=n%8; //quantos bits restantes temos que deslocar 
    unsigned char sinal;
    if(a[15] & 0x80)
    {
        sinal=0xFF; //negativo
    }
    else
    {
        sinal=0x00; //positivo
    }
    //pra zerar tudo
    for (int i=0; i<16; i++)
    {
        res[i]=sinal;
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

void big_shr(BigInt res, BigInt a, int n)
{
    int n_qtbytes=n/8; // quantos bytes temos que deslocar
    int n_qtbits=n%8; //quantos bits restantes temos que deslocar 
    //inicializar com 0
    for(int i=0; i<16; i++)
    {
        res[i]=0;
    }
    for (int i=0; i<16-n_qtbytes; i++)
    {
        res[i]=a[i+n_qtbytes];
    }
    if (n_qtbits>0)
    {
        unsigned char bitsresto=0;
        for (int i=15; i>=0; i--)
        {
            unsigned char temporario=res[i];
            res[i]=(temporario>>n_qtbits) | bitsresto; //desloca p direita "n" bits e "junta" os bits q "vazaram" do outro byte anterior
            bitsresto=temporario<<(8-n_qtbits); //movimentação p posição certa
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



