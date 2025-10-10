/* Nome: Rafaela Bessa || Matrícula: 2420043 || Turma: 33A */
/* Nome: Lis Almeida || Matrícula: xxxx || Turma: 33A */
#include <stdio.h>
#include "bigint.h"

#define NUM_BYTES (NUM_BITS/8)

/**
*@brief Função auxiliar para imprimir um BigInt no formato {0x01, 0x00, ...}.
* Esta função é essencial para visualizar os resultados dos testes.
*@param a: O array BigInt (128 bits) a ser impresso.
**/
void print_bigint(BigInt a) {
    printf("{");
    for (int i = 0; i < NUM_BYTES; i++) {
        printf("0x%02X", a[i]);
        if (i < NUM_BYTES - 1) printf(", ");
    }
    printf("}"); // Removido o '\n' para dar mais controle ao printf da main
}

int main() {
    BigInt a, b, res;
    int n; // Variável para shifts

    printf("======================================\n");
    printf("====== TESTES DE ATRIBUICAO (big_val) ======\n");
    printf("======================================\n");
    big_val(a, 1);
    printf("Valor 1: ");
    print_bigint(a);
    printf("\n");
    big_val(a, -1);
    printf("Valor -1: ");
    print_bigint(a);
    printf("\n");
    big_val(a, 2147483647L); // MAX_INT (Exemplo de long)
    printf("Valor MAX_INT (2^31-1): ");
    print_bigint(a);
    printf("\n\n");

    // -------------------------------------------------------------
    
    printf("================================\n");
    printf("====== TESTES DE SOMA (big_sum) ======\n");
    printf("================================\n");
    
    big_val(a, 5);
    big_val(b, 10);
    big_sum(res, a, b);
    printf("1. 5 + 10 = ");
    print_bigint(res);
    printf(" (Esperado: 15)\n");

    big_val(a, -1);
    big_val(b, 1);
    big_sum(res, a, b);
    printf("2. -1 + 1 = ");
    print_bigint(res);
    printf(" (Esperado: 0)\n");

    big_val(a, -5);
    big_val(b, -10);
    big_sum(res, a, b);
    printf("3. -5 + (-10) = ");
    print_bigint(res);
    printf(" (Esperado: -15)\n\n");

    // -------------------------------------------------------------

    printf("===================================\n");
    printf("====== TESTES DE SUBTRACAO (big_sub) ======\n");
    printf("===================================\n");
    
    big_val(a, 20);
    big_val(b, 5);
    big_sub(res, a, b);
    printf("1. 20 - 5 = ");
    print_bigint(res);
    printf(" (Esperado: 15)\n");

    big_val(a, 5);
    big_val(b, 10);
    big_sub(res, a, b);
    printf("2. 5 - 10 = ");
    print_bigint(res);
    printf(" (Esperado: -5)\n");

    big_val(a, -10);
    big_val(b, -5);
    big_sub(res, a, b);
    printf("3. -10 - (-5) = ");
    print_bigint(res);
    printf(" (Esperado: -5)\n\n");

    // -------------------------------------------------------------

    printf("======================================\n");
    printf("====== TESTES DE MULTIPLICACAO (big_mul) ======\n");
    printf("======================================\n");
    
    big_val(a, 3);
    big_val(b, 4);
    big_mul(res, a, b);
    printf("1. 3 * 4 = ");
    print_bigint(res);
    printf(" (Esperado: 12)\n");

    big_val(a, -2);
    big_val(b, 3);
    big_mul(res, a, b);
    printf("2. -2 * 3 = ");
    print_bigint(res);
    printf(" (Esperado: -6)\n");

    big_val(a, -5);
    big_val(b, -2);
    big_mul(res, a, b);
    printf("3. -5 * -2 = ");
    print_bigint(res);
    printf(" (Esperado: 10)\n\n");

    // -------------------------------------------------------------

    printf("==================================================\n");
    printf("====== TESTES DE SHIFT ARITMETICO DIREITA (big_sar) ======\n");
    printf("==================================================\n");
    
    big_val(a, -2);
    n = 1;
    big_sar(res, a, n);
    printf("1. -2 >> %d = ", n);
    print_bigint(res);
    printf(" (Esperado: -1)\n");

    big_val(a, -128);
    n = 8;
    big_sar(res, a, n);
    printf("2. -128 >> %d = ", n);
    print_bigint(res);
    printf(" (Esperado: -1)\n");

    big_val(a, 128);
    n = 4;
    big_sar(res, a, n);
    printf("3. 128 >> %d = ", n);
    print_bigint(res);
    printf(" (Esperado: 8)\n\n");

    // -------------------------------------------------------------
    
    printf("==========================================\n");
    printf("====== TESTES DE SHIFT ESQUERDA (big_shl) ======\n");
    printf("==========================================\n");

    big_val(a, 1);
    n = 1;
    big_shl(res, a, n);
    printf("1. (1 << %d) = ", n);
    print_bigint(res);
    printf(" (Esperado: 2)\n");

    big_val(a, 8);
    n = 8;
    big_shl(res, a, n);
    printf("2. (8 << %d) = ", n);
    print_bigint(res);
    printf(" (Esperado: 2048)\n"); // 8 * 256

    big_val(a, -1);
    n = 1;
    big_shl(res, a, n);
    printf("3. (-1 << %d) = ", n);
    print_bigint(res);
    printf(" (Esperado: -2)\n");

    big_val(a, -128);
    n = 8;
    big_shl(res, a, n);
    printf("4. (-128 << %d) = ", n);
    print_bigint(res);
    printf(" (Esperado: -32768)\n\n");

    // -------------------------------------------------------------
    
    printf("==============================================\n");
    printf("====== TESTES DE SHIFT LOGICO DIREITA (big_shr) ======\n");
    printf("==============================================\n");

    big_val(a, -1); // -1 é 0xFF...FF
    n = 1;
    big_shr(res, a, n);
    printf("1. (-1 >> %d) Logico = ", n);
    print_bigint(res);
    printf(" (Esperado: 0x7FFF...FF)\n");
    
    big_val(a, -256); // 0x00, 0xFF, 0xFF...FF
    n = 8;
    big_shr(res, a, n);
    printf("2. (-256 >> %d) Logico = ", n);
    print_bigint(res);
    printf(" (Esperado: 0xFF, 0x00, 0xFF...FF)\n\n");

    return 0;
}