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

        // por enquanto só p0 existe
        if (idx == 0) return -24;

        // se quiser tratar p1, p2, p3, pode colocar depois
        return -24 - idx*4;  // fictício, dependerá do seu prólogo
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
        // movl $val, %eax (b8 val) ou movl $val, %ecx (b9 val) etc.
        escreve_byte(code, pos, 0xB8 | reg_code); // B8 para %eax, B9 para %ecx, etc.
        escreve_int(code, pos, val);
    } else { // Variável (vX) ou Parâmetro (p0)
        char offset = pega_offset(operando);
        // movl offset(%rbp), %eax (8B 45 offset)
        escreve_byte(code, pos, 0x8B);
        escreve_byte(code, pos, 0x45 + (reg_code << 3)); // 0x45 (para %eax)
        escreve_byte(code, pos, offset);
    }
}

void gera_codigo(FILE *f, unsigned char code[], funcp *entry) {
    char linha[256];
    int pos = 0; 
    int enderecos_funcoes[50]; // Guarda o início de cada função LBS
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
            

            escreve_byte(code, &pos, 0x48);
            escreve_byte(code, &pos, 0x83);
            escreve_byte(code, &pos, 0xec);
            escreve_byte(code, &pos, 0x20); // 32 bytes

            escreve_byte(code, &pos, 0x89);
            escreve_byte(code, &pos, 0x7d);
            escreve_byte(code, &pos, 0xe8);
        }

        else if (strcmp(comando, "end") == 0) {
            // Ret
        }

        else if (strcmp(comando, "ret") == 0) {
            char varpc[10];
            sscanf(linha, "ret %s", varpc);

            // Move o valor para %eax
            if (varpc[0] == '$') { //Se for uma constante em LBS
                int val = atoi(varpc + 1);
                // mov $val, %eax -> b8
                escreve_byte(code, &pos, 0xb8);
                escreve_int(code, &pos, val);
            } else { // Se na verdade for uma variavel ou p0
                char offset = pega_offset(varpc);
                // mov offset(%rbp), %eax -> 8b 45 offset
                escreve_byte(code, &pos, 0x8b);
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset);
            }

            // leave/ret
            escreve_byte(code, &pos, 0xc9);
            escreve_byte(code, &pos, 0xc3);
        }

        // --- tudo q começa com v
        else if (linha[0] == 'v') {
            int idx_dest;
            char op1[10], op[5], op2[10];
            
            // aritmetica
            if (sscanf(linha, "v%d = %s %s %s", &idx_dest, op1, op, op2) == 4) { //analisa se é operação de aritmética
                char offset_dest = -20 + (idx_dest * 4); //onde salvar o resultado
        
                // 1. CARREGAR op1 em %eax (Registrador de Destino: 0x00 para %eax)
                 carrega_operando(code, &pos, op1, 0x0); //mov pra eax


                //OPERAÇÃO DE SOMA!!!!
                //2 casos: ou to somando com uma constante ou to somando com outra variavel
                if (strcmp(op, "+") == 0) {
                    if (op2[0] == '$') { // addl $C, %eax
                        int val = atoi(op2 + 1);
                        // addl $val, %eax -> 05 val
                        escreve_byte(code, &pos, 0x05);
                        escreve_int(code, &pos, val);
                    } else { // addl op2(%rbp), %eax
                        char offset_op2 = pega_offset(op2);
                        // addl offset(%rbp), %eax -> 03 45 offset
                        escreve_byte(code, &pos, 0x03);
                        escreve_byte(code, &pos, 0x45);
                        escreve_byte(code, &pos, offset_op2);
                    }
                } 
                else if (strcmp(op, "-") == 0) {
                    // OPERAÇÃO SUBTRAÇÃO!!!!!!!
                    if (op2[0] == '$') { // subl $C, %eax
                        int val = atoi(op2 + 1);
                        
                        // subl $val, %eax -> 2d val (Instrução para 32-bit imediato)
                        escreve_byte(code, &pos, 0x2d);
                        escreve_int(code, &pos, val);
                        
                    } else { // subl op2(%rbp), %eax
                        char offset_op2 = pega_offset(op2);
                        
                        // subl offset(%rbp), %eax -> 2b 45 offset
                        escreve_byte(code, &pos, 0x2b);
                        escreve_byte(code, &pos, 0x45);
                        escreve_byte(code, &pos, offset_op2);
                    }
                }
                else if (strcmp(op, "*") == 0) {   //MULTIPLICACAO
                    // multiplicação usa imull
                    if (op2[0] == '$') {
                        int val = atoi(op2 + 1);

                        // imull $val, %eax → 69 c0 val
                        escreve_byte(code, &pos, 0x69);
                        escreve_byte(code, &pos, 0xC0);
                        escreve_int(code, &pos, val);
                    }
                    else {
                        char off2 = pega_offset(op2);

                        // imull off(%rbp), %eax → 0F AF 45 off
                        escreve_byte(code, &pos, 0x0F);
                        escreve_byte(code, &pos, 0xAF);
                        escreve_byte(code, &pos, 0x45);
                        escreve_byte(code, &pos, off2);
                    }
                }
                // 3. SALVAR RESULTADO de %eax em vX
                // movl %eax, dest(%rbp) -> 89 45 offset
                escreve_byte(code, &pos, 0x89);
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset_dest);
            }
            else if (sscanf(linha, "v%d = call %s %s", &idx_dest, op1, op2) == 3) {
                // fazer call
                printf("Call ainda nao implementado\n");
            }
            // Atribuição
            else if (sscanf(linha, "v%d = %s", &idx_dest, op1) == 2) {
                char offset_dest = -20 + (idx_dest * 4);

                if (op1[0] == '$') { // constante
                    int val = atoi(op1 + 1);
                    // movl $val, offset(%rbp) -> c7 45 offset val
                    escreve_byte(code, &pos, 0xc7);
                    escreve_byte(code, &pos, 0x45);
                    escreve_byte(code, &pos, offset_dest);
                    escreve_int(code, &pos, val);
                } 
                else { // variavel ou parametro
                    char offset_orig = pega_offset(op1);
                    // movl orig(%rbp), %ecx -> 8b 4d offset_orig
                    escreve_byte(code, &pos, 0x8b);
                    escreve_byte(code, &pos, 0x4d);
                    escreve_byte(code, &pos, offset_orig);

                    // movl %ecx, dest(%rbp) -> 89 4d offset_dest
                    escreve_byte(code, &pos, 0x89);
                    escreve_byte(code, &pos, 0x4d);
                    escreve_byte(code, &pos, offset_dest);
                }
            }
        }
        // fazer zret
    }
    if (cont > 0) {
        *entry = (funcp)((void*)(code + enderecos_funcoes[cont - 1]));
        } else {
        *entry = NULL;
        }
}