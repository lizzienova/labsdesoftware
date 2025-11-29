/* Nome: Rafaela Bessa || Matrícula: 2420043 || Turma: 3WA */
/* Nome: Lis Almeida || Matrícula: 2421294 || Turma: 3WA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gera_codigo.h"

/**
 * @brief Escreve um valor inteiro de 32 bits no vetor de código (Little Endian)
 * * @param code O vetor de bytes onde o código está sendo gerado
 * @param pos Ponteiro para a posição atual de escrita no vetor
 * @param valor O valor inteiro a ser escrito
 */
static void escreve_int(unsigned char code[], int *pos, int valor) {
    code[*pos] = valor & 0xFF;
    code[*pos + 1] = (valor >> 8) & 0xFF;
    code[*pos + 2] = (valor >> 16) & 0xFF;
    code[*pos + 3] = (valor >> 24) & 0xFF;
    *pos += 4;
}

/**
 * @brief Escreve um único byte (8 bits) no vetor de código
 * * @param code O vetor de bytes onde o código está sendo gerado
 * @param pos Ponteiro para a posição atual de escrita no vetor
 * @param val O byte a ser escrito (instrução ou dado)
 */
static void escreve_byte(unsigned char code[], int *pos, unsigned char val) {
    code[*pos] = val;
    (*pos)++;
}

/**
 * @brief Calcula o deslocamento de memória (offset) de uma variável na pilha
 * * @param var String contendo o nome da variável (ex: "v0", "v1" ou "p0")
 * @return O deslocamento (negativo) em relação ao registrador base (%rbp)
 */
static char pega_offset(char *var) {
    if (var[0] == 'p') {
        int idx = atoi(var+1);
        if (idx == 0) return -24; // p0 é guardado na posição -24
        return -24 - idx*4; 
    }
    else if (var[0] == 'v') {
        int idx = atoi(var + 1);
        return -20 + (idx * 4); // v0 começa em -20, v1 em -16...
    }
    return 0;
}

/**
 * @brief Gera instruções Assembly para carregar um operando para um registrador
 * Identifica se é constante ($) ou memória (v/p) e gera o opcode correto
 * * @param code O vetor de bytes
 * @param pos Ponteiro para a posição atual
 * @param operando String do operando (ex: "$10", "v0")
 * @param reg_code Código do registrador de destino (0 para %eax, etc)
 */
static void carrega_operando(unsigned char code[], int *pos, char *operando, unsigned char reg_code) {
    if (operando[0] == '$') { // Se for Constante ($10)
        int val = atoi(operando + 1);
        escreve_byte(code, pos, 0xB8 + reg_code); // Código do MOV imediato
        escreve_int(code, pos, val);
    } else { // Se for Variável (v0) ou Parâmetro (p0)
        char offset = pega_offset(operando);
        escreve_byte(code, pos, 0x8B); // Código do MOV memória
        escreve_byte(code, pos, 0x45 + (reg_code << 3)); 
        escreve_byte(code, pos, offset);
    }
}

/**
 * @brief Função principal que traduz código LBS para código de máquina x86-64
 * * @param f Arquivo de texto aberto contendo o código fonte LBS
 * @param code Vetor de bytes onde o código binário será escrito
 * @param entry Ponteiro de retorno para armazenar o endereço da função gerada
 */
void gera_codigo(FILE *f, unsigned char code[], funcp *entry) {
    char linha[256];
    int pos = 0; 
    int enderecos_funcoes[50]; // Guarda endereços das funções para o CALL
    int cont = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        if (linha[0] == '\n' || linha[0] == '\0') continue;

        char comando[20];
        if (sscanf(linha, "%s", comando) != 1) continue;

        // --- Tradução de FUNCTION ---
        if (strcmp(comando, "function") == 0) {
            enderecos_funcoes[cont] = pos;
            cont++;

            // Prólogo: push %rbp; mov %rsp, %rbp
            escreve_byte(code, &pos, 0x55);
            escreve_byte(code, &pos, 0x48);
            escreve_byte(code, &pos, 0x89);
            escreve_byte(code, &pos, 0xe5);
            
            // Aloca 32 bytes na pilha: sub $32, %rsp
            escreve_byte(code, &pos, 0x48);
            escreve_byte(code, &pos, 0x83);
            escreve_byte(code, &pos, 0xec);
            escreve_byte(code, &pos, 0x20); 

            // Salva p0 (%edi) na memória (-24(%rbp))
            escreve_byte(code, &pos, 0x89);
            escreve_byte(code, &pos, 0x7d);
            escreve_byte(code, &pos, 0xe8);
        }

        // Tradução de END 
        else if (strcmp(comando, "end") == 0) {
            escreve_byte(code, &pos, 0xc9); // leave
            escreve_byte(code, &pos, 0xc3); // ret
        }

        // Tradução de RET 
        else if (strcmp(comando, "ret") == 0) {
            char varpc[10];
            sscanf(linha, "ret %s", varpc);
            
            carrega_operando(code, &pos, varpc, 0); // Move para %eax
            
            escreve_byte(code, &pos, 0xc9); // leave
            escreve_byte(code, &pos, 0xc3); // ret
        }

        // Tradução de ZRET 
        else if (strcmp(comando, "zret") == 0) {
            char var_cond[10], var_ret[10];
            sscanf(linha, "zret %s %s", var_cond, var_ret);

            carrega_operando(code, &pos, var_cond, 0); // Condição em %eax

            // cmp $0, %eax
            escreve_byte(code, &pos, 0x83);
            escreve_byte(code, &pos, 0xf8);
            escreve_byte(code, &pos, 0x00);

            // jne (pula se não for zero)
            escreve_byte(code, &pos, 0x75);
            int idx_pulo = pos; 
            escreve_byte(code, &pos, 0x00); // Placeholder

            // Retorno
            carrega_operando(code, &pos, var_ret, 0); 
            escreve_byte(code, &pos, 0xc9); 
            escreve_byte(code, &pos, 0xc3); 

            // Backpatching: corrige o pulo
            code[idx_pulo] = pos - (idx_pulo + 1);
        }

        // Comandos com Variáveis (v...)
        else if (linha[0] == 'v') {
            int idx_dest;
            char op1[10], op[5], op2[10];
            int funcID;
            
            // CALL
            if (sscanf(linha, "v%d = call %d %s", &idx_dest, &funcID, op2) == 3) {
                // Passa parâmetro (mov %eax, %edi)
                carrega_operando(code, &pos, op2, 0); 
                escreve_byte(code, &pos, 0x89);
                escreve_byte(code, &pos, 0xc7);

                // Call relativo
                escreve_byte(code, &pos, 0xE8);
                int target = enderecos_funcoes[funcID];
                int offset = target - (pos + 4);
                escreve_int(code, &pos, offset);

                // Salva retorno
                char offset_dest = -20 + (idx_dest * 4);
                escreve_byte(code, &pos, 0x89);
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset_dest);
            }
            
            // ARITMÉTICA (+, -, *)
            else if (sscanf(linha, "v%d = %s %s %s", &idx_dest, op1, op, op2) == 4) {
                char offset_dest = -20 + (idx_dest * 4);
                carrega_operando(code, &pos, op1, 0x0);

                if (strcmp(op, "+") == 0) {
                    if (op2[0] == '$') { 
                        escreve_byte(code, &pos, 0x05); escreve_int(code, &pos, atoi(op2 + 1));
                    } else { 
                        escreve_byte(code, &pos, 0x03); escreve_byte(code, &pos, 0x45); escreve_byte(code, &pos, pega_offset(op2));
                    }
                } 
                else if (strcmp(op, "-") == 0) {
                    if (op2[0] == '$') { 
                        escreve_byte(code, &pos, 0x2d); escreve_int(code, &pos, atoi(op2 + 1));
                    } else { 
                        escreve_byte(code, &pos, 0x2b); escreve_byte(code, &pos, 0x45); escreve_byte(code, &pos, pega_offset(op2));
                    }
                }
                else if (strcmp(op, "*") == 0) {
                    if (op2[0] == '$') {
                        escreve_byte(code, &pos, 0x69); escreve_byte(code, &pos, 0xC0); escreve_int(code, &pos, atoi(op2 + 1));
                    } else {
                        escreve_byte(code, &pos, 0x0F); escreve_byte(code, &pos, 0xAF); escreve_byte(code, &pos, 0x45); escreve_byte(code, &pos, pega_offset(op2));
                    }
                }
                escreve_byte(code, &pos, 0x89); escreve_byte(code, &pos, 0x45); escreve_byte(code, &pos, offset_dest);
            }
            
            // ATRIBUIÇÃO SIMPLES
            else if (sscanf(linha, "v%d = %s", &idx_dest, op1) == 2) {
                char offset_dest = -20 + (idx_dest * 4);
                carrega_operando(code, &pos, op1, 0); 
                escreve_byte(code, &pos, 0x89); escreve_byte(code, &pos, 0x45); escreve_byte(code, &pos, offset_dest);
            }
        }
    }
    
    if (cont > 0) *entry = (funcp)((void*)(code + enderecos_funcoes[cont - 1]));
    else *entry = NULL;
}