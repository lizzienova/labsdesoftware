/*
#include <stdio.h>

char S2[] = {65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0};

int main (void) {
  char *pc = S2;
  while (*pc){
    if (*pc!=123 && *pc!= 125)
    {
        printf ("%c", *pc);
    }
    pc++;
  }
  printf("\n");
  return 0;
}

*/

.data
nums: .byte 65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0
Sf: .string "%c"

.text
.globl main

main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/

movq $nums, %rbx    /* *pc=nums */

inicio:
cmpb $0, (%rbx)     /* if(*pc==0)  */
je L2
cmpb $123, (%rbx) /* if (*pc==123) */
je L1
cmpb $125, (%rbx)
je L1
movl (%rbx), %eax
/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

L1:
addq $1, %rbx
jmp inicio

L2:
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/