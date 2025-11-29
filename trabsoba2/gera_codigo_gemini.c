// esse tem as alteracoes do gemini

/* Rafaela Bessa 2420043 3WA */
/* Lis de Almeida Matricula 3WA */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gera_codigo.h"

static void escreve_int(unsigned char code[], int *pos, int valor) {
    code[*pos] = valor & 0xFF;
    code[*pos + 1] = (valor >> 8) & 0xFF;
    code[*pos + 2] = (valor >> 16) & 0xFF;
    code[*pos + 3] = (valor >> 24) & 0xFF;
    *pos += 4;
}

static void escreve_byte(unsigned char code[], int *pos, unsigned char val) {
    code[*pos] = val;
    (*pos)++;
}

static char pega_offset(char *var) {
    if (var[0] == 'p') {
        int idx = atoi(var+1);
        if (idx == 0) return -24; // p0 fica em -24
        return -24 - idx*4; 
    }
    else if (var[0] == 'v') {
        int idx = atoi(var + 1);
        return -20 + (idx * 4);
    }
    return 0;
}

static void carrega_operando(unsigned char code[], int *pos, char *operando, unsigned char reg_code) {
    if (operando[0] == '$') { // Constante
        int val = atoi(operando + 1);
        escreve_byte(code, pos, 0xB8 + reg_code); 
        escreve_int(code, pos, val);
    } else { // Variável (vX) ou Parâmetro (p0)
        char offset = pega_offset(operando);
        escreve_byte(code, pos, 0x8B);
        escreve_byte(code, pos, 0x45 + (reg_code << 3)); 
        escreve_byte(code, pos, offset);
    }
}

void gera_codigo(FILE *f, unsigned char code[], funcp *entry) {
    char linha[256];
    int pos = 0; 
    int enderecos_funcoes[50]; 
    int cont = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        if (linha[0] == '\n' || linha[0] == '\0') continue;

        char comando[20];
        if (sscanf(linha, "%s", comando) != 1) continue;

        if (strcmp(comando, "function") == 0) {
            enderecos_funcoes[cont] = pos;
            cont++;

            // PRÓLOGO
            escreve_byte(code, &pos, 0x55); // push %rbp
            escreve_byte(code, &pos, 0x48); // mov %rsp, %rbp
            escreve_byte(code, &pos, 0x89);
            escreve_byte(code, &pos, 0xe5);
            
            escreve_byte(code, &pos, 0x48); // sub $32, %rsp
            escreve_byte(code, &pos, 0x83);
            escreve_byte(code, &pos, 0xec);
            escreve_byte(code, &pos, 0x20); 

            // ESSAS SAO AS LINHAS QUE VOCE JA TINHA E QUE SALVAM O P0
            // mov %edi, -24(%rbp)
            escreve_byte(code, &pos, 0x89);
            escreve_byte(code, &pos, 0x7d);
            escreve_byte(code, &pos, 0xe8);
        }

        else if (strcmp(comando, "end") == 0) {
            escreve_byte(code, &pos, 0xc9); // leave
            escreve_byte(code, &pos, 0xc3); // ret
        }

        else if (strcmp(comando, "ret") == 0) {
            char varpc[10];
            sscanf(linha, "ret %s", varpc);
            carrega_operando(code, &pos, varpc, 0); // carrega em %eax
            escreve_byte(code, &pos, 0xc9);
            escreve_byte(code, &pos, 0xc3);
        }

        // --- ZRET (Implementado aqui) ---
        else if (strcmp(comando, "zret") == 0) {
            char var_cond[10], var_ret[10];
            sscanf(linha, "zret %s %s", var_cond, var_ret);

            carrega_operando(code, &pos, var_cond, 0); // Carrega condicao em %eax

            // cmp $0, %eax
            escreve_byte(code, &pos, 0x83);
            escreve_byte(code, &pos, 0xf8);
            escreve_byte(code, &pos, 0x00);

            // jne (pula se nao for zero)
            escreve_byte(code, &pos, 0x75);
            int idx_pulo = pos; 
            escreve_byte(code, &pos, 0x00); // placeholder

            // Codigo do retorno
            carrega_operando(code, &pos, var_ret, 0); 
            escreve_byte(code, &pos, 0xc9); 
            escreve_byte(code, &pos, 0xc3); 

            // Corrige pulo
            code[idx_pulo] = pos - (idx_pulo + 1);
        }

        else if (linha[0] == 'v') {
            int idx_dest;
            char op1[10], op[5], op2[10];
            int funcID;
            
            // --- CALL (Implementado aqui) ---
            if (sscanf(linha, "v%d = call %d %s", &idx_dest, &funcID, op2) == 3) {
                // Passar parametro em %edi
                carrega_operando(code, &pos, op2, 0); // poe em %eax
                escreve_byte(code, &pos, 0x89);       // mov %eax, %edi
                escreve_byte(code, &pos, 0xc7);

                // Call relativo
                escreve_byte(code, &pos, 0xE8);
                int target = enderecos_funcoes[funcID];
                int offset = target - (pos + 4);
                escreve_int(code, &pos, offset);

                // Salva retorno na variavel
                char offset_dest = -20 + (idx_dest * 4);
                escreve_byte(code, &pos, 0x89);
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset_dest);
            }
            // Aritmetica
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
            // Atribuicao simples
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