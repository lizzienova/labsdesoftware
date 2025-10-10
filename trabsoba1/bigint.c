/* Nome: Rafaela Bessa || Matrícula: 2420043 || Turma: 33A */
/* Nome: Lis Almeida || Matrícula: xxxx || Turma: 33A */

#include "bigint.h"
#include <stdio.h> 

#define NUM_BYTES (NUM_BITS/8)

/**
*@brief Atribui um valor 'long' (64 bits assinado) a um BigInt de 128 bits.
* Realiza a extensão de sinal apropriada (res = val).
*@param res: O BigInt de destino (128 bits).
*@param val: O valor 'long' de 64 bits a ser atribuído.
**/
void big_val (BigInt res, long val)
{
    unsigned long uvalor = (unsigned long) val;
    // Define o byte de extensão: 0xFF para valor negativo, 0x00 para positivo.
    unsigned char byte_extensao = (val < 0) ? 0xFF : 0x00;

    int n = sizeof(long);
    if (n > NUM_BYTES) n = NUM_BYTES;

    // 1. Copia os bytes do long (little-endian: byte menos significativo em res[0]).
    for (int i = 0; i < n; i++) {
        // Isola o byte e o armazena em res[i].
        res[i] = (uvalor >> (8 * i)) & 0xFF;
    }
    // 2. Extensão de sinal: preenche os bytes restantes.
    for (int i = n; i < NUM_BYTES; i++) {
        res[i] = byte_extensao;
    }
}

/**
*@brief Calcula o Complemento a 2 do operando 'a' (negação). res = -a.
* Implementado como: Inverter bits (Complemento a 1) e somar 1.
*@param res: O BigInt de destino (resultado).
*@param a: O BigInt de origem (operando).
**/
void big_comp2(BigInt res, BigInt a)
{
    /* 1. Complemento a 1 (inversão de bits) */
    for (int i = 0; i < NUM_BYTES; i++) {
        res[i] = ~a[i];
    }
    
    /* 2. Soma 1 com propagação do "vai-um" (little-endian) */
    unsigned char vai_um = 1;
    for (int i = 0; i < NUM_BYTES; i++) {
        unsigned short soma = (unsigned short)res[i] + vai_um;
        res[i] = (unsigned char)(soma & 0xFF); 
        vai_um = (unsigned char)(soma >> 8);    
        if (!vai_um) break; 
    }
}

/**
*@brief Realiza a soma de dois BigInts. res = a + b.
* Usa "vai-um" para propagar o carry entre os bytes (little-endian).
*@param res: O BigInt de destino (resultado).
*@param a: O primeiro BigInt (operando).
*@param b: O segundo BigInt (operando).
**/
void big_sum(BigInt res, BigInt a, BigInt b) {
    unsigned int vai_um = 0;
    for (int i = 0; i < NUM_BYTES; i++) {
        // Soma os bytes atuais e o "vai-um" do byte anterior.
        unsigned int soma = (unsigned int)a[i] + (unsigned int)b[i] + vai_um;
        res[i] = (unsigned char)(soma & 0xFF); 
        vai_um = soma >> 8;                     
    }
}

/**
*@brief Realiza a subtração de dois BigInts. res = a - b.
* Implementada como soma do complemento a 2: res = a + (-b).
*@param res: O BigInt de destino (resultado).
*@param a: O minuendo (operando).
*@param b: O subtraendo (operando).
**/
void big_sub(BigInt res, BigInt a, BigInt b) {
    BigInt negado_b;
    // 1. Calcula o complemento a 2 do subtraendo: negado_b = -b.
    big_comp2(negado_b, b);
    // 2. Realiza a soma: res = a + negado_b.
    big_sum(res, a, negado_b);
}

/**
*@brief Realiza a multiplicação de dois BigInts, tratando o sinal. res = a * b.
* Estratégia: Multiplica as magnitudes (unsigned) e ajusta o sinal do resultado no final.
*@param res: O BigInt de destino (resultado, armazena os 128 bits menos significativos).
*@param a: O multiplicando (operando).
*@param b: O multiplicador (operando).
**/
void big_mul(BigInt res, BigInt a, BigInt b) {
    /* Tratamento de sinal: */
    int sinal_a = (a[NUM_BYTES - 1] & 0x80) ? 1 : 0;
    int sinal_b = (b[NUM_BYTES - 1] & 0x80) ? 1 : 0;
    int resultado_negativo = sinal_a ^ sinal_b;

    BigInt abs_a, abs_b;
    // Cópia ou negação de 'a' para obter a magnitude (sem usar memcpy).
    if (sinal_a) big_comp2(abs_a, a); else {
        for (int i = 0; i < NUM_BYTES; i++) abs_a[i] = a[i];
    }
    // Cópia ou negação de 'b' para obter a magnitude (sem usar memcpy).
    if (sinal_b) big_comp2(abs_b, b); else {
        for (int i = 0; i < NUM_BYTES; i++) abs_b[i] = b[i];
    }

    /* 1. Multiplicação sem sinal: array temporário de 256 bits (32 bytes) */
    unsigned char temp[NUM_BYTES * 2];
    // Inicializa 'temp' com zero (substitui memset).
    for (int i = 0; i < NUM_BYTES * 2; i++) temp[i] = 0x00;

    for (int i = 0; i < NUM_BYTES; i++) {
        unsigned int vai_um = 0;
        for (int j = 0; j < NUM_BYTES; j++) {
            unsigned int posicao = i + j;
            // Multiplica byte por byte + o "vai-um" + o valor já existente em temp.
            unsigned int multiplicacao = (unsigned int)abs_a[i] * (unsigned int)abs_b[j];
            unsigned int soma = (unsigned int)temp[posicao] + multiplicacao + vai_um;
            
            temp[posicao] = (unsigned char)(soma & 0xFF);
            vai_um = soma >> 8;
        }
        // Propaga o "vai-um" restante para o próximo byte.
        temp[i + NUM_BYTES] = (unsigned char)((unsigned int)temp[i + NUM_BYTES] + vai_um);
    }

    /* 2. Aplica o sinal final */
    BigInt resultado_temp;
    // Copia os 128 bits LSB do resultado para 'resultado_temp'.
    for (int i = 0; i < NUM_BYTES; i++) resultado_temp[i] = temp[i];

    if (resultado_negativo) {
        // Se o resultado deve ser negativo, calcula o complemento a 2 final.
        big_comp2(res, resultado_temp);
    } else {
        // Copia o resultado para 'res'.
        for (int i = 0; i < NUM_BYTES; i++) res[i] = resultado_temp[i];
    }
}

/**
*@brief Realiza um deslocamento lógico para a esquerda. res = a << n.
* O shift left move os dados para bytes de índice maior e preenche os bits menos significativos com 0.
*@param res: O BigInt de destino (resultado).
*@param a: O BigInt a ser deslocado (operando).
*@param n: O número de bits para deslocar (deve estar em [0, 127]).
**/
void big_shl(BigInt res, BigInt a, int n)
{
    if (n == 0) {
        // Cópia simples se n for 0.
        if (res != a) {
            for (int i = 0; i < NUM_BYTES; i++) res[i] = a[i];
        }
        return;
    }
    int n_qtbytes = n / 8;
    int n_qtbits  = n % 8;

    /* 1) Deslocamento por bytes: move os bytes existentes e zera os de entrada. */
    // Zera os bytes menos significativos que foram deslocados para fora.
    for (int i = 0; i < n_qtbytes && i < NUM_BYTES; i++) {
        res[i] = 0x00;
    }
    // Copia os bytes de 'a' para 'res' (deslocamento de bytes).
    for (int i = n_qtbytes; i < NUM_BYTES; i++) {
        res[i] = a[i - n_qtbytes];
    }

    /* 2) Deslocamento por bits (propagação de "vai-um", da direita para a esquerda) */
    if (n_qtbits > 0) {
        unsigned char carry = 0;
        // O loop começa do byte de dados mais baixo (n_qtbytes) para propagar o carry.
        for (int i = n_qtbytes; i < NUM_BYTES; i++) { 
            // Bits que "vazam" para o próximo byte (o novo carry)
            unsigned char proximo_carry = (unsigned char)(res[i] >> (8 - n_qtbits));
            // Shift do byte atual + bits do byte anterior (carry)
            res[i] = (unsigned char)((res[i] << n_qtbits) | carry);
            carry = proximo_carry;
        }
    }
}

/**
*@brief Realiza um deslocamento lógico para a direita. res = a >> n (lógico).
* O shift right lógico preenche os bits mais significativos (MSB) com 0.
*@param res: O BigInt de destino (resultado).
*@param a: O BigInt a ser deslocado (operando).
*@param n: O número de bits para deslocar (deve estar em [0, 127]).
**/
void big_shr(BigInt res, BigInt a, int n)
{
    if (n == 0) {
        if (res != a) {
            for (int i = 0; i < NUM_BYTES; i++) res[i] = a[i];
        }
        return;
    }
    int n_qtbytes = n / 8;
    int n_qtbits  = n % 8;

    /* 1) Deslocamento por bytes: move os bytes existentes e zera os de entrada. */
    // Copia os bytes de 'a' para 'res' (deslocamento de bytes).
    for (int i = 0; i < NUM_BYTES - n_qtbytes; i++) {
        res[i] = a[i + n_qtbytes];
    }
    // Zera os bytes que entraram (mais significativos, índice maior).
    for (int i = NUM_BYTES - n_qtbytes; i < NUM_BYTES; i++) {
        res[i] = 0x00;
    }

    /* 2) Deslocamento por bits (propagação de "vai-um", da esquerda para a direita) */
    if (n_qtbits > 0) {
        unsigned char carry = 0;
        // O loop varre do byte mais significativo (índice 15) para o menos significativo (índice 0).
        for (int i = NUM_BYTES - 1; i >= 0; i--) {
            // Bits que "vazam" para o byte anterior (o novo carry)
            unsigned char proximo_carry = (unsigned char)(res[i] << (8 - n_qtbits));
            // Shift do byte atual + bits do byte posterior (carry)
            res[i] = (unsigned char)((res[i] >> n_qtbits) | carry);
            carry = proximo_carry;
        }
    }
}

/**
*@brief Realiza um deslocamento aritmético para a direita. res = a >> n (aritmético).
* O shift right aritmético preserva o sinal, preenchendo o MSB com o bit de sinal.
*@param res: O BigInt de destino (resultado).
*@param a: O BigInt a ser deslocado (operando).
*@param n: O número de bits para deslocar (deve estar em [0, 127]).
**/
void big_sar(BigInt res, BigInt a, int n)
{
    if (n == 0) {
        if (res != a) {
            for (int i = 0; i < NUM_BYTES; i++) res[i] = a[i];
        }
        return;
    }
    int n_qtbytes = n / 8;
    int n_qtbits  = n % 8;

    /* Define o valor de preenchimento (extensão de sinal) */
    unsigned char preenchimento_sinal = (a[NUM_BYTES - 1] & 0x80) ? 0xFF : 0x00;

    /* 1) Deslocamento por bytes */
    // Copia os bytes de 'a' para 'res' (deslocamento de bytes).
    for (int i = 0; i < NUM_BYTES - n_qtbytes; i++) {
        res[i] = a[i + n_qtbytes];
    }
    // Preenche os bytes que entraram (mais significativos) com o bit de sinal.
    for (int i = NUM_BYTES - n_qtbytes; i < NUM_BYTES; i++) {
        res[i] = preenchimento_sinal;
    }

    /* 2) Deslocamento por bits (propagação de "vai-um" com preenchimento de sinal) */
    if (n_qtbits > 0) {
        // Carry inicial: bit de sinal deslocado para ser inserido no byte mais significativo.
        unsigned char carry = (preenchimento_sinal << (8 - n_qtbits)); 
        
        for (int i = NUM_BYTES - 1; i >= 0; i--) {
            // Bits que "vazam" para o byte anterior (o novo carry)
            unsigned char proximo_carry = (unsigned char)(res[i] << (8 - n_qtbits));
            // Shift do byte atual + bits do byte posterior (carry/preenchimento)
            res[i] = (unsigned char)((res[i] >> n_qtbits) | carry);
            carry = proximo_carry;
        }
    }
}