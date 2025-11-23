/*
void foo(double *vd, int n) {
    while (n--) {
        *vd = 0.0;
        vd++;
    }
}
*/

/*
dicionario:
double *vd = rdi
int n = esi
nao preciso reservar espaço na pilha porque nao tem variavel local
*/

.text
.globl foo
foo:
    pushq %rbp
    movq %rsp, %rbp
    movq $0, %rax   #pra poder zerar meu *vd
    movq %rax, %xmm0

LOOP:
    cmpl $0, %esi   #if n=0
    je FIM
    decl %esi   #n--
    movsd %xmm0, (%rdi) #*vd=0
    addq $8, %rdi
    jmp LOOP

FIM:
    leave
    ret


