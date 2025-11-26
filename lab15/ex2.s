.text
.globl foo1

foo1:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp
    movss %xmm1, -4(%rbp)
    cvtss2sd %xmm0, %xmm0
    call sin
    cvtsd2ss %xmm0, %xmm0
    movss -4(%rbp), %xmm1 
    addss %xmm1, %xmm0
    leave
    ret