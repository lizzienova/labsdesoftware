.text
.globl foo

foo:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)

    movl $0, %ebx   #i=0
    movl $0, %eax
    cvtsi2sd %eax, %xmm5
    movss %xmm0, %xmm6      #salvar lim

loop: 
    cmpl $5, %ebx
    jge fim
    movl %rbx, %r12d 
    movslq %r12d, %r12
    imulq $8, %r12
    addq %rdi, %r12     #agora tenho st[i]
    movw %bx, 0(%r12)
    movss 4(%r12), %xmm0
    movss %xmm6, %xmm1
    call boba
    cvtss2sd %xmm0, %xmm0
    addsd %xmm0, %xmm5
    incl %ebx
    jmp loop

fim: 
    movsd %xmm5, %xmm0
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret
