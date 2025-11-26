.text
.globl pack1

pack1:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $32, %rsp

    movq    $0, %r10
    cvtsi2sd %r10, %xmm0
    movl    $0, %r11d   

FOR:
    cmpl    %esi, %r11d    
    jge     FIM

    # salvar variáveis
    movsd   %xmm0, -8(%rbp)
    movq    %rdi, -16(%rbp)
    movl    %esi, -20(%rbp)
    movl    %r11d, -24(%rbp)

    # calcular px[i]
    movslq  %r11d, %rcx     
    leaq    (%rdi,%rcx,8), %rdx 

    # carregar argumentos
    movl    (%rdx), %edi        
    cvtss2sd 4(%rdx), %xmm0    

    call    foo

    addsd   -8(%rbp), %xmm0
    movsd   %xmm0, -8(%rbp)

    # restaurar variáveis
    movq    -16(%rbp), %rdi
    movl    -20(%rbp), %esi
    movl    -24(%rbp), %r11d

    incl    %r11d
    jmp     FOR

FIM:
    movsd   -8(%rbp), %xmm0
    leave
    ret
