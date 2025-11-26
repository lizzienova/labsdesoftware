.text
.globl boo

boo:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rdi, -8(%rbp)     
    movl    %esi, -12(%rbp)    
    movl    %edx, -16(%rbp)

loop:
    movl    -12(%rbp), %eax  
    testl   %eax, %eax
    jz      fim   
    decl    -12(%rbp)       
    movq    -8(%rbp), %rdi  
    movl    (%rdi), %edi      
    movl    -16(%rbp), %esi    
    call    f
    movq    -8(%rbp), %rdi    
    movl    %eax, 4(%rdi)     
    addq    $8, -8(%rbp)       
    jmp     loop

fim:
    leave
    ret