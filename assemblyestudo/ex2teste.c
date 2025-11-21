#include <stdio.h>

// Declaração da função Assembly
extern void add_to_pointer(int *ptr, int val);

int main() {
    printf("--- Testes da Função add_to_pointer ---\n");
    
    // Teste 1: Adição simples
    int a = 10;
    int b = 5;
    add_to_pointer(&a, b); // Deve ser: 10 + 5 = 15
    printf("Teste 1: A (10) + B (5) -> Resultado: %d | Esperado: 15\n", a);

    // Teste 2: Adição com número negativo
    int x = 50;
    int y = -20;
    add_to_pointer(&x, y); // Deve ser: 50 + (-20) = 30
    printf("Teste 2: X (50) + Y (-20) -> Resultado: %d | Esperado: 30\n", x);

    // Teste 3: Adição com zero
    int z = 100;
    int w = 0;
    add_to_pointer(&z, w); // Deve ser: 100 + 0 = 100
    printf("Teste 3: Z (100) + W (0) -> Resultado: %d | Esperado: 100\n", z);
    
    return 0;
}