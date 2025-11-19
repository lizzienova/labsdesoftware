/*
int foo (int x) {
  return x+1;
}

Dicionário

int x é primeiro argumento então vai tá em edi

*/

.text
.globl foo

foo:
    addl $1, %edi
    movl %edi, %eax
    leave
    ret
    
