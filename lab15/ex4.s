.text
.globl foo3
foo3:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq %rbx, -8(%rbp)
    pxor %xmm0, %xmm0 #aprendi que essa função serve pra zerar aquele registrador
    movsd %xmm0, -16(%rbp)
    movl $0, %ebx
loop:
    movl %ebx, %eax
    cmpl %esi, %eax
    jge fim
    movsd (%rdi), %xmm0
    call sin
    movsd -16(%rbp), %xmm1
    addsd %xmm0, %xmm1
    movsd %xmm1, -16(%rbp)
    addq $8, %rdi
    incl %ebx
    jmp loop

fim:
    movsd -16(%rbp), %xmm0
    movq -8(%rbp), %rbx
    leave
    ret