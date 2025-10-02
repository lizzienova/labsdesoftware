#pragma once
#ifndef BIGINT_H
#define BIGINT_H
#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS / 8];

// Protótipos das funções
void big_val(BigInt res, long val);
void print_bigint(BigInt a);
// (coloque os outros protótipos aqui depois)

#endif
