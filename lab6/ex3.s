.data
nums:  .int  10, -21, -30, 45
Sf:  .string "%d\n"    # string de formato para printf

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/


movl  $0, %ebx  /* i = 0; */
movq  $nums, %r12  /* r12 = &nums */

L1:
  cmpl $4, %ebx /* if(i==4) */
  je L3
  movl  $0x01, %r13d
  andl (%r12),%r13d
  cmpl $0,%r13d
  je L2
  addl $1, %ebx          # i++
  addq $4, %r12          # p++
  jmp L1


L2:
movl (%r12),%eax
/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/
  addl $1, %ebx          # i++
  addq $4, %r12          # p++
  jmp L1


L3:
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/