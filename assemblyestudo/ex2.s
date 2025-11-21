/*
void add_to_pointer(int *ptr, int val) {
    *ptr = *ptr + val;
}
*/

/*
preciso quebrar essa funcao em mais partes pra fazer sentido em assembly
temp =*ptr
temp=temp+val
*ptr=temp
*/

/*
dicionario

int *ptr é ponteiro então tem 64 bits 8 bytes e deve ficar em rdi por ser 1arg 
int val é só um int de 4 bytes e ta em segundo argumento então fica em %esi

*/

.text
.globl add_to_pointer
add_to_pointer:
    movl (%rdi), %eax       #temp=*ptr
    addl %esi, %eax         #temp=temp+val
    movl %eax, (%rdi)       #*ptr=temp
    ret