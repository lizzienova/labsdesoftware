/* Nome: Rafaela Bessa || Matrícula: 2420043 || Turma: 33A */
/* Nome: Lis Almeida || Matrícula: 2421294 || Turma: 33A */
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
    printf("}"); // Mantém o controle do newline na função chamadora
}

int main() {
    BigInt a, b, res;
    int n; 

    printf("======================================\n");
    printf("    TESTES DE ATRIBUICAO (big_val) \n");
    printf("======================================\n");
    big_val(a, 1);
    printf("Valor 1: ");
    print_bigint(a);
    printf("\n");
    big_val(a, -1);
    printf("Valor -1: ");
    print_bigint(a);
    printf("\n");
    big_val(a, 2147483647L); // MAX_INT (exemplo de um long)
    printf("Valor MAX_INT (2^31-1): ");
    print_bigint(a);
    printf("\n\n");
    big_val(a, 0);
    printf("Valor 0: ");
    print_bigint(a);
    printf("\n");

    // -------------------------------------------------------------

    printf("======================================\n");
    printf("    TESTES DE COMPLEMENTO DE DOIS (big_comp2) \n");
    printf("======================================\n");

    big_val(a,1);
    big_comp2(res,a);
    printf("Complemento de 2 de (+1): ");
    print_bigint(res);
    printf("  (Esperado: -1 -> todos os bytes 0xFF)\n\n");

    big_val(a, 0);
    big_comp2(res, a);
    printf("Complemento de 2 de (0): ");
    print_bigint(res);
    printf("  (Esperado: 0 -> todos os bytes 0x00)\n\n");

    big_val(a, -1);
    big_comp2(res, a);
    printf("Complemento de 2 de (-1): ");
    print_bigint(res);
    printf("  (Esperado: +1 -> byte menos significativo = 0x01)\n\n");

    big_val(a, 127);
    big_comp2(res, a);
    printf("Complemento de 2 de (+127): ");
    print_bigint(res);
    printf("  (Esperado: -127 -> representação negativa em complemento de dois)\n\n");

    big_val(a, -128);
    big_comp2(res, a);
    printf("Complemento de 2 de (-128): ");
    print_bigint(res);
    printf("  (Esperado: +128 -> byte menos significativo 0x80, resto 0x00)\n\n");


    // -------------------------------------------------------------

    printf("================================\n");
    printf("     TESTES DE SOMA (big_sum) \n");
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
    printf("     TESTES DE SUBTRACAO (big_sub) \n");
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
    printf("     TESTES DE MULTIPLICACAO (big_mul) \n");
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
    printf("    TESTES DE SHIFT ARITMETICO DIREITA (big_sar) \n");
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
    printf("     TESTES DE SHIFT ESQUERDA (big_shl) \n");
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
    printf("     TESTES DE SHIFT LOGICO DIREITA (big_shr) \n");
    printf("==============================================\n");

    big_val(a, -1); // -1 é 0xFF...FF
    n = 1;
    big_shr(res, a, n);
    printf("1. (-1 >> %d) Logico = ", n);
    print_bigint(res);
    printf(" (Esperado: 0x7FFF...FF)\n");
    
    big_val(a, -256); 
    n = 8;
    big_shr(res, a, n);
    printf("2. (-256 >> %d) Logico = ", n);
    print_bigint(res);
    printf(" (Esperado: 15 bytes FF, 1 byte 00 no MSB)\n\n");

    return 0;
}