/* Nome: Rafaela Bessa || Matrícula: 2420043 || Turma: 33A */
/* Nome: Lis Almeida || Matrícula: xxxx || Turma: 33A */

#include "bigint.h"
#include <stdio.h>
#include <string.h>
#define NUM_BITS 128
#define NUM_BYTES (NUM_BITS/8)
typedef unsigned char BigInt[NUM_BITS/8];

// se val for negativo, preencher os bytes restantes com 0xFF
// se val for positiivo, preencher os bytes restantes com 0x00

//printa no modelo do enunciado {0x01, 0x00...}
void print_bigint(BigInt a) {
    printf("{");
    for (int i = 0; i < 16; i++) {
        printf("0x%02X", a[i]);
        if (i < 15) printf(", ");
    }
    printf("}\n");
}


/* Atribuição (com extensão) */
void big_val (BigInt res, long val)
{
    unsigned long uval=(unsigned long) val;
    unsigned char extende;
    if (val<0)
    {
        extende=0xFF; //preenche com 0xFF se o valor for negativo
    }
    else{
        extende=0x00; //preenche com 0x00 se o valor for positivo
    }
    for(int i=0; i<sizeof(long) && i < NUM_BYTES; i++) //faz a copia dos primerios bytes de val para os primeiros bytes do bigint (little endian)
    {
        res[i]=(uval>>(8*i))& 0xFF; //cada byte individualmente
    }
    for (int i=sizeof(long); i<NUM_BYTES; i++) //preenche os bytes restantes
    {
        res[i]=extende;
    }
}


/* Operações Aritméticas */

/* res = -a*/

void big_comp2(BigInt res, BigInt a)
{
    //copia a para res
    for (int i=0; i<(NUM_BITS/8); i++)
    {
        res[i]=a[i];
    }
    for (int i=0; i<(NUM_BITS/8); i++) //inverte todos os bits que colocamos em res
    {
        res[i]=~res[i];
    }
    unsigned char vai_um=1;
    for (int i=0; i<(NUM_BITS/8); i++) //soma 1 ao número invertido
    {
        unsigned short soma=res[i]+vai_um; //soma com meu "vai_um" que é 1
        res[i]=soma & 0xFF; //armazena o byte resultante
        vai_um=(soma>>8)&0x01; //atualiza meu "vai_um"
        if(!vai_um) break; //se não tiver mais resto, para
    }
}


/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b) {
    unsigned int vai_um = 0;
    for (int i = 0; i < NUM_BYTES; i++) {
        unsigned int soma = a[i] + b[i] + vai_um;
        res[i] = (unsigned char)(soma & 0xFF);
        vai_um = soma >> 8;
    }
}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b) {
    int emprestimo = 0;
    for (int i = 0; i < NUM_BYTES; i++) {
        int diferenca = (int)a[i] - (int)b[i] - emprestimo;
        if (diferenca < 0) {
            diferenca += 256;
            emprestimo = 1;
        } else {
            emprestimo = 0;
        }
        res[i] = (unsigned char)(diferenca & 0xFF);
    }
}

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b) {
    unsigned short temporario[NUM_BYTES * 2] = {0};

    for (int i = 0; i < NUM_BYTES; i++) {
        unsigned int vai_um = 0;
        for (int j = 0; j < NUM_BYTES; j++) {
            unsigned int pos = i + j;
            unsigned int multiplicacao = temporario[pos] + a[i] * b[j] + vai_um;
            temporario[pos] = multiplicacao & 0xFF;
            vai_um = multiplicacao >> 8;
        }
        temporario[i + NUM_BYTES] = vai_um;
    }

    for (int i = 0; i < NUM_BYTES; i++) {
        res[i] = (unsigned char)temporario[i];
    }
}


/* Operações de Deslocamento */

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
    for(int i=0; i<16; i++) //incializa onde colocaremos nosso valor com 0s
    {
        res[i]=0;
    }
    for (int i=0; i<16-n_qtbytes; i++) //desloca os bytes, copiando os que "restam" depois do deslocamento 
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
