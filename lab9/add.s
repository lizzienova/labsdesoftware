# int add(int a, int b, int c)
#return a+b+c

.text
.globl add
add:
    pushq %rbp #salva a base do RA da função chamadora
    movq %rsp, %rbp #cria a base do RA da função chamadora
    subq $16, %rsp #abre espaço para o RA da função chamada

    #salvar valor dos registradores no calle-saved
    movq %r13, -8(%rbp) #salva o valor do r13 da função chamadora e é r13 e não r13d porque você pode estar usando só a parte baixa do registrador, mas a parte alta dele também é modificada

#return a+b+c;
#    temp=c      #c está em edx (3o argumento)
    movl %edx, %r13d
    
#    temp=temp+b     #b está em esi (2o argumento)
    addl %esi, %r13d

#    temp=temp+a #a está em edi (1o argumento)
    addl %edi, %r13d

#    return temp
    movl %r13d, %eax

    #restaurar valores dos registradores callee-saved
    movq -8(%rbp), %r13 #restaurando valor original


    leave
    ret