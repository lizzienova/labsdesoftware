/*
int calcula(float f);
double boba (float val) {
int i;
int pos;
double d[5];        #se um double tem 8 bytes, 5 doubles serão 4 bytes
for (i=0; i<5; i++) {
pos = calcula(val);
d[pos] += val;          #reescrever isso como 
                        #temp=d[pos]
                        #temp=temp+val
                        #d[pos]=temp
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
    movss %xmm0, -24(%rbp)  #salvo float val na pilha
    leaq -64(%rbp), %r13

    movl $0, %ebx   #i=0
    movl $0, %r12d  #pos=0
    xorps   %xmm15, %xmm15      #zerando xmm15 pra poder usar como auxiliar zerando d[5]
    movl $0, %r15d              #contador pro loop que zera meu array

zera_array:
    cmpl $5, %r15
    jge loop
    movss -24(%rbp), %xmm0      #toda vez que entrar em loop ele pega meu float que salvei e restaura aqui
    leaq -64(%rbp, %r15, 8), %r14
    movsd %xmm15, (%r14)
    inc %r15d
    jmp zera_array

loop:
    cmpl $5, %ebx   #if i>=5
    jge fim
    call calcula
    leaq(%r13, %eax, 8), %r14   #temp=&d[pos] || pos tem seu valor em eax depois de chamar calcula
    movsd (%r14), %xmm1
    movss -24(%rbp), %xmm2
    cvtss2sd %xmm2, %xmm2
    addsd %xmm2, %xmm1          #d[pos]+=val
    movsd %xmm1, (%r14)
    inc %ebx
    jmp loop

fim:
    movsd -64(%rbp), %xmm0
    movq -8(%rbp), %rbx     #restauro rbx
    movq -16(%rbp), %r12    #restauro r12
    leave
    ret

