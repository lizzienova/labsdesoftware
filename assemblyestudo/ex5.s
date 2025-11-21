/*
#include <math.h>

double trig_calc(double angle) {
    return sin(angle) + cos(angle);
}
*/


/* LEMBRAR QUE CALLER-SAVED SEMPMRE SAO SOBRESCRITOS E NAO PODEM SALVAR NADA, DEVE SER SALVO NA PILHA!!! */
.globl trig_calc
.extern sin
.extern cos

trig_calc:
    pushq %rbp 
    movq %rsp, %rbp 
    subq $16, %rsp
    movsd %xmm0, -16(%rbp)            /* salvo "angle" em -16 na pilha */
    call sin                          /* angle ja esta em xmm0 pois é o primeiro argumento da função, e ao chamar call sin esse valor é retornado em xmm0 também */
    movsd %xmm0, -8(%rbp)             /* salvo sin(angle) em -8 na pilha */
    movsd -16(%rbp), %xmm0            /* coloco angle em xmm0 para que possa ser chamado cos(angle) */
    call cos                          /* está em xmm0 o resultado de cos(angle) */
    addsd -8(%rbp), %xmm0            /* faço a soma de sin(angle) + cos(angle) */
    leave
    ret