/*
int acerta (int u[], int i)
{
return u[i];
}
*/

.text
.globl acerta
acerta:
    leaq(%rdi, %rsi, 4), %rax   #rax=&u[i]
    movl (%rax), %eax           #u[i]
    ret
