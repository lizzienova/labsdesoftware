#include <stdio.h>

extern int clear_low_bit(int n); // Adicione esta linha

int main() {
    // ... outros testes
    
    printf("\n--- Testes clear_low_bit ---\n");
    
    // 1. Teste: Bits 00 (sem mudança)
    int n1 = 12; // Binário: ...1100. Limpar 00 -> 12 (Esperado)
    int r1 = clear_low_bit(n1); 
    printf("Teste 1: N (%d) -> Resultado: %d | Esperado: 12\n", n1, r1);

    // 2. Teste: Bits 01
    int n2 = 13; // Binário: ...1101. Limpar 01 -> 12 (Esperado)
    int r2 = clear_low_bit(n2); 
    printf("Teste 2: N (%d) -> Resultado: %d | Esperado: 12\n", n2, r2);

    // 3. Teste: Bits 10
    int n3 = 14; // Binário: ...1110. Limpar 10 -> 12 (Esperado)
    int r3 = clear_low_bit(n3); 
    printf("Teste 3: N (%d) -> Resultado: %d | Esperado: 12\n", n3, r3);

    // 4. Teste: Bits 11
    int n4 = 15; // Binário: ...1111. Limpar 11 -> 12 (Esperado)
    int r4 = clear_low_bit(n4); 
    printf("Teste 4: N (%d) -> Resultado: %d | Esperado: 12\n", n4, r4);

    return 0;
}