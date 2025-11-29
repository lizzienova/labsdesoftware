#include <stdio.h>
#include <stdlib.h>
#include "gera_codigo.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    funcp funcLBS = NULL;
    // O enunciado sugere 300, mas vamos usar 1024 para garantir segurança se o código for grande
    unsigned char code[1024]; 
    int res;
    int parametro = 10; // Valor padrão de teste se você não digitar nada

    /* 1. Verifica se o usuário passou o nome do arquivo */
    if (argc < 2) {
        printf("Erro: Faltou o nome do arquivo.\n");
        printf("Uso correto: %s <arquivo_lbs> [parametro_opcional]\n", argv[0]);
        return 1;
    }

    /* 2. Verifica se o usuário passou um número para testar (opcional) */
    if (argc > 2) {
        parametro = atoi(argv[2]);
    } else {
        printf("Aviso: Nenhum parametro informado. Usando valor padrao: %d\n", parametro);
    }

    /* 3. Abre o arquivo para leitura */
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    /* 4. Gera o codigo */
    // Passamos o arquivo aberto, o buffer 'code' e o endereço do ponteiro da função
    gera_codigo(fp, code, &funcLBS);
    
    // Fechamos o arquivo, pois o gerador já leu tudo o que precisava
    fclose(fp);

    /* 5. Verifica erros de geração */
    if (funcLBS == NULL) {
        printf("Erro na geracao do codigo: Nenhuma funcao encontrada.\n");
        return 1;
    }

    /* 6. Chama a função gerada */
    printf("--- Executando funcao LBS ---\n");
    printf("Entrada (p0): %d\n", parametro);
    
    // A mágica acontece aqui: chamamos o vetor de bytes como se fosse uma função C
    res = (*funcLBS)(parametro); 
    
    printf("Saida (retorno): %d\n", res);
    printf("-----------------------------\n");

    return 0;
}