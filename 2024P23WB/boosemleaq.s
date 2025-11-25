/*
int calcula(float f);
double boba (float val) {
int i;
int pos;
double d[5];
for (i=0; i<5; i++) {
pos = calcula(val);
d[pos] += val;
}
return d[0];
}
*/

.text
.globl boba
boba:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp
    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movss %xmm0, -24(%rbp)  #salvar float na pilha
    leaq -64(%rbp), %r15    #d[0] em r15

    movl $0, %ebx   #i=0
    movl $0, %r12d  #pos=0

# cada d[i] vai ter 8x5=40bytes

loop:
    cmpl $5, %ebx   #if i=5
    jge fim
    movss -24(%rbp), xmm0
    call calcula
    movl %eax, %r12d    #pega oq calcula retorna e poe em pos 
    imull $8, %r12d     #pos*8                         
    movslq %r12d, %r12  #extende pos               
    addq %r15, %r12     #d[pos]  
    cvtss2sd -24(%rbp), %xmm1   #converto float pra double e salvo em xmm1
    movsd (%r12), %xmm0
    addsd %xmm1, %xmm0
    movsd %xmm0, (%r12)
    incl %ebx
    jmp loop

fim:
    movsd -64(%rbp), %xmm0
    movq -8(%rbp), rbx
    movq -16(%rbp), %r12
    leave
    ret

    
                        
