    .text
    .globl add2

add2:
    pushq   %rbp
    movq    %rsp, %rbp
    cmpq    $0, %rdi          
    je      fim            
    movl    (%rdi), %eax       
    movl    %eax, -4(%rbp)      
    movq    8(%rdi), %rdi     
    call    add2                
    addl    -4(%rbp), %eax    
    leave
    ret

fim:
    movl    $0, %eax
    leave
    ret