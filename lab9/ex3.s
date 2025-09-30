/* rip apionta para a próxima instrução a ser executada
rsp aponta para o topo da pilha
rbp aponta para a base do ra corrente
*/

.text
.globl foo
foo:
    pushq %rbp  #salva a base do RA da função chamadora e ao mesmo tempo realinha o topo da pilha em múltiplo de 16
    movq %rsp, %rbp     #cria a base do RA da função chamada
    subq ???, %rsp
    #TODO: Salvar registradores callee-saved usados na função chamada

/*    void foo (int a[], int n) 
  int i;
  int s = 0;
  for (i=0; i<n; i++) tentar converter para while
    while(i<n){
    temp= a[i];
    s += temp;
   if (a[i] == 0) 
      a[i] = s;
     s = 0;
       i++;
    }
*/

#n vai estar em edi pois é primeiro argumento

movl $0, %r13d #s=0
movl $0, %r12d #i=0

loop:
cmpl %edi, %r12d
jl fim



