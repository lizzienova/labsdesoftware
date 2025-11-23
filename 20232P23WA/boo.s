/*
struct S
{
int v;
struct S *prox;
};
extern int norma[];
int boo(struct S *s, int n)
{
int acum = 0;
while (s)
{
s->v = acerta(norma, n+acum);
acum += n;
s = s->prox;
}
return acum;
}
*/

.text
.globl boo
boo:
    pushq %rbp
    movq %rsp, %rbp
    subq ???, %rsp

    movl $0, %r12d  #acum=0

loop:
    cmpq $0, %rdi   #if s==null
    je fim
    movl %esi, %r13d    #movo n para r13d pra somar com acum
    addl %r12d, %r13d   #n+acum
    leaq norma(%rip), %rdi

