/* Nome: Rafaela Bessa || Matrícula: */
/* Nome: Lis Almeida || Matrícula:  */


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
        extend=0x00;
    }
    for(int i=0; i<16; i++)
    {
        res[i]=extend; //zera o vetor
    }
    for(int i=0; i<8; i++)
    {
        res[i]=(val>>(8*i)) & 0xFF;
    }
}



