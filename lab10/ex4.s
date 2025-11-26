/*
int f(int x);

void map2 (int* um, int * outro, int n) {
  int i;
  for (i=0; i<n; i++)
    *(outro+i) = f(*(um+i));
}
*/

.text
.globl map2
map2:
	pushq %rbp /
	movq %rsp, %rbp   
    subq $32, %rsp
    movq %rbx, -8(%rbp)
    movl $0, %ebx  #i=0

for:
    cmpl %edx, %ebx  #if (i==n)
    jge fim
    movslq %ebx, %r10    
    imulq $4, %r10      
    addq %rsi, %r10      
    movslq %ebx, %r11  
    imulq $4, %r11      
    addq %rdi, %r11    
    movq %rdi, -16(%rbp)
    movq %rsi, -24(%rbp)
    movl %edx, -28(%rbp) 
    movq (%r11), %edi
    call f
    movq -16(%rbp), %rdi
    movq -24(%rbp), %rsi
    movl -28(%rbp), %edx
    movl %eax, (%r10)   
    incl %ebx   
    jmp for

fim:
    movq -8(%rbp), %rbx
    leave
    ret
#nao precisei restaurar meus reg aqui no final


