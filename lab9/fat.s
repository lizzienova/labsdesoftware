/* 
Dicionário
Reg Var
edi n
*/

/* rip apionta para a próxima instrução a ser executada
rsp aponta para o topo da pilha
rbp aponta para a base do ra corrente
*/

.text
.globl fat 
fat:
    pushq %rbp  #salva a base do RA da função chamadora e ao mesmo tempo realinha o topo da pilha em múltiplo de 16
    movq %rsp, %rbp     #cria a base do RA da função chamada
    subq $16, %rsp

    #Salvar registradores callee-saved usados na função chamada
    movq %r15, -8(%rbp)     #salva o valor de r15 no RA

# if(n==0)

cmpl $0, %edi
jne ELSE 

#return 1;

movl $1, %eax
jmp RETORNA

#else
ELSE:

# temp=n;
movl %edi, %r15d

#temp=temp-1;
decl %r15d

#result=fat(temp);
#salvar registradores callee-saved antes de chamar a função
movl %edi, -12(%rbp) #salvei no RA

#chamar a função
movl %r15d, %edi
call fat

#restaurar os registradores callee-saved
movl -12(%rbp), %edi #faz isso porque o valor de edi pode ser modificado pela função. Pego do RA e devolvo esse valor original pro edi

#result=result*n; #em eax está o valor retornado
imull %edi, %eax

#return result
    #mover o valor de result para eax
    #mas ja esta em eax porque eax é o registrador de retorno sempre


RETORNA:
    #restaurar os callee-saved
    movq -8(%rbp), %r15

    #destruir RA
    leave
#OU!!! NÃO OS DOIS AO MESMO TEMPO 
#   movq %rbp, %rsp
#   popq, %rbp

    #retornar
    ret

