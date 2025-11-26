.text
.globl add

add:
    pushq   %rbp
    movq    %rsp, %rbp

    movl    $0, %eax

loop:
    cmpq    $0, %rdi    
    je      fim          

    addl    (%rdi), %eax   
    movq    8(%rdi), %rdi  
    jmp     loop

fim:
    leave
    ret