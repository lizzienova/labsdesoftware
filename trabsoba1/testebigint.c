/* Nome: Rafaela Bessa || Matrícula: 2420043 || Turma: 3WA */
/* Nome: Lis Almeida || Matrícula: 2421294 || Turma: 3WA */
#include <stdio.h>
#include "bigint.h"

#define NUM_BYTES (NUM_BITS/8)

// Protótipos das funções de teste
int testa_certo(BigInt obtido, BigInt esperado, const char *nome_funcao, int num_teste);
int teste_da_big_val(void);
int teste_da_big_comp2(void);
int teste_da_big_sum(void);
int teste_da_big_sub(void);
int teste_da_big_mul(void);
int teste_da_big_shl(void);
int teste_da_big_shr(void);
int teste_da_big_sar(void);

// Função auxiliar (mantida para debug, mas não usada na contagem de erros)
void print_bigint(BigInt a) {
    printf("{");
    for (int i = 0; i < NUM_BYTES; i++) {
        printf("0x%02X", a[i]);
        if (i < NUM_BYTES - 1) printf(", ");
    }
    printf("}");
}


// FUNÇÃO DE COMPARAÇÃO
/**
*@brief Compara dois BigInts byte a byte e imprime a falha detalhada, se houver
*@param obtido: O resultado da função testada
*@param esperado: O resultado que deveria ser obtido
*@param nome_funcao: Nome da função sendo testada (para relatório)
*@param num_teste: Número do teste
*@return 1 se houver erro, 0 se passar
**/
int testa_certo(BigInt obtido, BigInt esperado, const char *nome_funcao, int num_teste) {
    int erro = 0;
    
    // compara byte a byte
    for (int i = 0; i < NUM_BYTES; i++) {
        if (obtido[i] != esperado[i]) {
            // se encontrar a primeira diferença, registra o erro e para o loop
            if (erro == 0) {
                 printf("\n--- FALHA DETECTADA ---\n");
                 printf("Erro em %s, Teste %d\n", nome_funcao, num_teste);
                 printf("Obtido:    "); print_bigint(obtido); printf("\n");
                 printf("Esperado:  "); print_bigint(esperado); printf("\n");
            }
            erro = 1;
            break; // já detectamos a falha, não precisa de mais bytes
        }
    }
    return erro;
}


// TESTES DE CADA FUNÇÃO DA BIBLIOTECA

int teste_da_big_val(void) {
    BigInt res, esperado;
    int erros = 0;
    const char *msg = "big_val";

    // testando valor positivo (1)
    big_val(res, 1);
    esperado[0] = 0x01;
    for (int i = 1; i < NUM_BYTES; i++) esperado[i] = 0x00;
    erros += testa_certo(res, esperado, msg, 1);

    // testando valor negativo (-1)
    big_val(res, -1);
    for (int i = 0; i < NUM_BYTES; i++) esperado[i] = 0xFF;
    erros += testa_certo(res, esperado, msg, 2);

    // testando zero (0)
    big_val(res, 0);
    for (int i = 0; i < NUM_BYTES; i++) esperado[i] = 0x00;
    erros += testa_certo(res, esperado, msg, 3);
    
    // testando extensão de sinal positiva (2^31 - 1)
    // 2147483647L = 0x7FFFFFFF (32 bits)
    big_val(res, 2147483647L);
    esperado[0] = 0xFF; esperado[1] = 0xFF; esperado[2] = 0xFF; esperado[3] = 0x7F;
    for (int i = 4; i < NUM_BYTES; i++) esperado[i] = 0x00;
    erros += testa_certo(res, esperado, msg, 4);

    return erros;
}

int teste_da_big_comp2(void) {
    BigInt a, res, esperado;
    int erros = 0;
    const char *msg = "big_comp2";

    // teste de +1 para -1
    big_val(a, 1);
    big_comp2(res, a);
    big_val(esperado, -1);
    erros += testa_certo(res, esperado, msg, 1);

    // teste de -1 para +1
    big_val(a, -1);
    big_comp2(res, a);
    big_val(esperado, 1);
    erros += testa_certo(res, esperado, msg, 2);

    // teste do zero (0 -> 0)
    big_val(a, 0);
    big_comp2(res, a);
    big_val(esperado, 0);
    erros += testa_certo(res, esperado, msg, 3);

    // teste de propagação de carry (ex: -128 -> +128)
    big_val(a, -128); // a = {0x80, FF, FF...}
    big_comp2(res, a);
    big_val(esperado, 128); // esperado = {0x80, 00, 00...}
    erros += testa_certo(res, esperado, msg, 4);

    return erros;
}

int teste_da_big_sum(void) {
    BigInt a, b, res, esperado;
    int erros = 0;
    const char *msg = "big_sum";

    // positivo + positivo (5 + 10 = 15)
    big_val(a, 5);
    big_val(b, 10);
    big_sum(res, a, b);
    big_val(esperado, 15);
    erros += testa_certo(res, esperado, msg, 1);

    // negativo + positivo (cancela) (-1 + 1 = 0)
    big_val(a, -1);
    big_val(b, 1);
    big_sum(res, a, b);
    big_val(esperado, 0);
    erros += testa_certo(res, esperado, msg, 2);

    // negativo + negativo (-5 + -10 = -15)
    big_val(a, -5);
    big_val(b, -10);
    big_sum(res, a, b);
    big_val(esperado, -15);
    erros += testa_certo(res, esperado, msg, 3);

    // soma com propagação de carry (exemplo de overflow no byte)
    big_val(a, 0xFF); // 255
    big_val(b, 1);    // 1
    big_sum(res, a, b);
    big_val(esperado, 256); // 256 = {0x00, 0x01, 0x00...}
    erros += testa_certo(res, esperado, msg, 4);

    return erros;
}

int teste_da_big_sub(void) {
    BigInt a, b, res, esperado;
    int erros = 0;
    const char *msg = "big_sub";

    // positivo - positivo (20 - 5 = 15)
    big_val(a, 20);
    big_val(b, 5);
    big_sub(res, a, b);
    big_val(esperado, 15);
    erros += testa_certo(res, esperado, msg, 1);

    // positivo - maior positivo (5 - 10 = -5)
    big_val(a, 5);
    big_val(b, 10);
    big_sub(res, a, b);
    big_val(esperado, -5);
    erros += testa_certo(res, esperado, msg, 2);

    // negativo - negativo (-10 - (-5) = -5)
    big_val(a, -10);
    big_val(b, -5);
    big_sub(res, a, b);
    big_val(esperado, -5);
    erros += testa_certo(res, esperado, msg, 3);

    return erros;
}

int teste_da_big_mul(void) {
    BigInt a, b, res, esperado;
    int erros = 0;
    const char *msg = "big_mul";

    // positivo * positivo (3 * 4 = 12)
    big_val(a, 3);
    big_val(b, 4);
    big_mul(res, a, b);
    big_val(esperado, 12);
    erros += testa_certo(res, esperado, msg, 1);

    // negativo * positivo (-2 * 3 = -6)
    big_val(a, -2);
    big_val(b, 3);
    big_mul(res, a, b);
    big_val(esperado, -6);
    erros += testa_certo(res, esperado, msg, 2);

    // negativo * negativo (-5 * -2 = 10)
    big_val(a, -5);
    big_val(b, -2);
    big_mul(res, a, b);
    big_val(esperado, 10);
    erros += testa_certo(res, esperado, msg, 3);

    // multiplicação grande (4096 * 4096 = 16777216)
    big_val(a, 4096); // 0x1000
    big_val(b, 4096); // 0x1000
    big_mul(res, a, b);
    big_val(esperado, 16777216); // 0x100 0000
    erros += testa_certo(res, esperado, msg, 4);

    return erros;
}

int teste_da_big_shl(void) {
    BigInt a, res, esperado;
    int erros = 0;
    const char *msg = "big_shl";

    // shift de 1 bit (1 << 1 = 2)
    big_val(a, 1);
    big_shl(res, a, 1);
    big_val(esperado, 2);
    erros += testa_certo(res, esperado, msg, 1);

    // shift de 8 bits (8 << 8 = 2048) -> teste de shift de byte
    big_val(a, 8);
    big_shl(res, a, 8);
    big_val(esperado, 2048);
    erros += testa_certo(res, esperado, msg, 2);

    // shift negativo de 1 bit (-1 << 1 = -2)
    big_val(a, -1);
    big_shl(res, a, 1);
    big_val(esperado, -2);
    erros += testa_certo(res, esperado, msg, 3);

    // shift negativo de 8 bits (-128 << 8 = -32768)
    big_val(a, -128);
    big_shl(res, a, 8);
    big_val(esperado, -32768);
    erros += testa_certo(res, esperado, msg, 4);

    return erros;
}

int teste_da_big_shr(void) {
    BigInt a, res, esperado;
    int erros = 0;
    const char *msg = "big_shr";

    // positivo shift de 8 bits (256 >> 8 = 1)
    big_val(a, 256); // {0x00, 0x01, 0x00...}
    big_shr(res, a, 8);
    big_val(esperado, 1);
    erros += testa_certo(res, esperado, msg, 1);

    // shift Lógico de -1 por 1 bit (deve entrar 0 no MSB)
    big_val(a, -1); // {FF, FF, ..., FF}
    big_shr(res, a, 1);
    
    // o valor esperado (0x7FFF...FF) é o maior positivo
    esperado[0] = 0xFF; // LSB
    for (int i = 1; i < NUM_BYTES - 1; i++) esperado[i] = 0xFF;
    esperado[NUM_BYTES - 1] = 0x7F; // preenchido com 0
    erros += testa_certo(res, esperado, msg, 2);

    // shift Lógico de -256 por 8 bits (deve entrar 0)
    big_val(a, -256); // {0x00, 0xFF, FF...}
    big_shr(res, a, 8);
    
    // resultado: {0xFF, FF, ..., 0x00}
    for (int i = 0; i < NUM_BYTES - 1; i++) esperado[i] = 0xFF;
    esperado[NUM_BYTES - 1] = 0x00; 
    erros += testa_certo(res, esperado, msg, 3);

    return erros;
}

int teste_da_big_sar(void) {
    BigInt a, res, esperado;
    int erros = 0;
    const char *msg = "big_sar";

    // negativo shift de 1 bit (-2 >> 1 = -1)
    big_val(a, -2);
    big_sar(res, a, 1);
    big_val(esperado, -1);
    erros += testa_certo(res, esperado, msg, 1);

    // negativo shift de 8 bits (-128 >> 8 = -1)
    big_val(a, -128);
    big_sar(res, a, 8);
    big_val(esperado, -1);
    erros += testa_certo(res, esperado, msg, 2);

    // positivo shift de 4 bits (128 >> 4 = 8)
    big_val(a, 128);
    big_sar(res, a, 4);
    big_val(esperado, 8);
    erros += testa_certo(res, esperado, msg, 3);

    return erros;
}


// MAIN PRINCIPAL

int main() {
    int falhas = 0;
    int total_testes = 0;

    printf("===============================\n");
    printf("           TESTES\n");
    printf("===============================\n");

    falhas += teste_da_big_val();
    total_testes += 4;
    printf("TESTE big_val: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");

    falhas += teste_da_big_comp2();
    total_testes += 4;
    printf("TESTE big_comp2: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");

    falhas += teste_da_big_sum();
    total_testes += 4;
    printf("TESTE big_sum: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");

    falhas += teste_da_big_sub();
    total_testes += 3;
    printf("TESTE big_sub: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");
    
    falhas += teste_da_big_mul();
    total_testes += 4;
    printf("TESTE big_mul: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");

    falhas += teste_da_big_shl();
    total_testes += 4;
    printf("TESTE big_shl: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");

    falhas += teste_da_big_shr();
    total_testes += 3;
    printf("TESTE big_shr: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");

    falhas += teste_da_big_sar();
    total_testes += 3;
    printf("TESTE big_sar: %s\n", (falhas == 0) ? "PASSOU" : "FALHOU");
    
    printf("\n========================================\n");
    printf("  RESULTADO FINAL: %d falhas em %d testes. \n", falhas, total_testes);
    printf("========================================\n");
    
    return (falhas != 0); // Retorna código de erro 1 se houver falhas
}