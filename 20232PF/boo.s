/*
int corta(int v[], int i);
long int boo (int *a, int n) {
 long int acc = 0;
 while (n--)
 {
 acc += corta(a, n);
 a++;
 }
 return acc;
}
*/

/*
dicionario
int *a      rdi
int n       esi
acc         escolhi r12
reescrevendo acc+=corta(a,n)
temp=acc
temp=temp+corta(a,n)
acc=temp
*/

.text
.globl boo
boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq $0, %r12       /* acc=0 */
    movq %rdi, %rbx     /* salvando a em calle-saved */
    movl %esi, %r13d   /* salvando n em calle-saved */
    movq %rbx, -8(%rbp) 
    movq %r13, -16(%rbp) 
    movq %r12, -24(%rbp)

    /* loop */
loop:
    cmpl $0, %r13d
    je fim
    decl %r13d
    movq %r12, %r14     /* temp=r14 */
    movq %rbx, %rdi     /* passando 'a' como primeiro arg */
    movl %r13d, %esi    /* passando 'n' como segundo arg */
    call corta          /* retorna em eax */
    movslq %eax, %rax   /* aumento pra long int pra ficar em acc */
    addq %rax, %r14
    movq %r14, %r12
    addq $4, %rbx       /* a++ sendo que a tem 8 bytes */
    jmp loop

fim:
    movq %r12, %rax
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r13
    movq -24(%rbp), %r12
    leave
    ret