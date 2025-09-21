.data
nums:  .int  10, -21, -30, 45
Sf:  .string "%d\n"    # string de formato para printf

.text
.globl  main
main:

movl $0, %ebx /* i=0 */
movl $0, %r12d /* soma=0 */

inicio: 
cmpl $4, %ebx /* if(i==4) */
jge L1
movl nums(, %ebx, 4), %r13d
addl %r13d, %r12d
addl $1, %ebx
jmp inicio


L1:
/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/