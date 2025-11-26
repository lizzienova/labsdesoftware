.text
.globl foo2

foo2:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    call sin
    movsd %xmm0, -8(%rbp)
    movsd %xmm1, %xmm0
    call cos
    addsd -8(%rbp), %xmm0  
    leave
    ret