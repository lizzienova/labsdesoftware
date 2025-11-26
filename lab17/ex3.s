.text
.globl pack

pack:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    $0, %r10
    cvtsi2sd    %r10, %xmm0

WHILE:
    cmpq    $0, %rdi
    je      FIM

    movq    %rdi, -8(%rbp)
    movsd   %xmm0, -16(%rbp)

    movsd   8(%rdi), %xmm0 
    movl    (%rdi), %edi    
    call foo

    addsd   -16(%rbp), %xmm0

    movq   -8(%rbp), %rdi
    movq    16(%rdi), %rdi
    jmp WHILE

FIM:    
    leave
    ret