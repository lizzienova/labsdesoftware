/*
int clear_low_bit(int n) {
    return n & 0xFFFFFFFC; // Limpa os 2 bits menos significativos
}
*/

/* dicionario

int n esta em %edi 
0xFFFFFFFC

*/

.text
.globl clear_low_bit
clear_low_bit:
    movl %edi, %eax
    andl $0xFFFFFFFC, %eax
    ret

