/*
int acerta (int u[], int i)
{
return u[i];
}
*/

.text
.globl acerta
acerta:
    movslq %esi, %rsi
    imulq $4, %rsi
    addq %rdi, %rsi
    movl (%rsi), %eax
    ret