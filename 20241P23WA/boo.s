/*
struct exam { float val; int tipo; };
double inv (double val);
float boo (double d, float bias) {
int i;
struct exam temp[5];
for (i=0; i<5; i++) {
temp[i].val = inv(d);
temp[i].tipo = i;
}
return temp[0].val + bias;
}
*/

/*
dicionario
double d = xmm0
float bias = xmm1
int i = ebx
struct exam temp 8 bytes no total
struct exam temp[5] vai então ter 40 bytes no total
temp[0] -40
temp[1] -32
temp[2] -24
temp[3] -16
temp[4] -8
temp[i].val ->offset 0
temp[i].tipo -> offset 4
total de bytes=44+8(do registrador int)=52
alinhando em 16= 64
*/

.text
.globl boo
boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp
    movq %rbx, -48(%rbp) 
    movl $0, %ebx   #i=0
    movq %rbp, %r12     
    subq $40, %r12      # r12 = &temp[0] porque como vimos temp[0] tá em -40(%rbp)
    movsd %xmm0, -56(%rbp)  #salvo double d na pilha

LOOP:
    cmpl $5, %ebx   #if i=5
    jge FIM
    movl %ebx, %r13d    #r13d=i
    immull $8, %r13d    #i*8, pra saber em qual temp[i] estamos
    movslq  %r13d, %r13 #estendendo o registrador de int pra 64bits
    addq %r12, %r13     #r13=&temp[i]
    call inv            #como double d ja tava em xmm0 fiz direto | inv é double e minha struct pede float
    cvtsd2ss %xmm0, %xmm0   #conversão
    movss %xmm0, 0(%r13)    #passo o valor da função inv para temp[i].val
    movsd -56(%rbp), %xmm0
    movl %ebx, 4(%r13)      #faço temp[i].tipo=i
    incl %ebx               #i++
    jmp LOOP

FIM:
#return temp[0].val +bias
#temp[0] tá sempre em r12 como defini la em cima entao
#a funcao boo é float então retorna em xmm0
    movss -40(%rbp), %xmm0   #movo temp[0].val para xmm0 
    addss %xmm1, %xmm0      #somo com float bias
    movq -48(%rbp), %rbx     #restauro rbx
    leave
    ret
