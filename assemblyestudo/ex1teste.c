#include <stdio.h>

extern int max_of_two(int x, int y); // Adicione esta linha

int main() {
    // ... outros testes
    
    printf("\n--- Testes max_of_two ---\n");
    
    // Teste 1: x > y
    int x1 = 10, y1 = 5;
    int r1 = max_of_two(x1, y1); // Esperado: 10
    printf("Teste 1: max(%d, %d) -> Resultado: %d | Esperado: 10\n", x1, y1, r1);

    // Teste 2: x < y
    int x2 = 3, y2 = 7;
    int r2 = max_of_two(x2, y2); // Esperado: 7
    printf("Teste 2: max(%d, %d) -> Resultado: %d | Esperado: 7\n", x2, y2, r2);
    
    // Teste 3: x == y
    int x3 = 8, y3 = 8;
    int r3 = max_of_two(x3, y3); // Esperado: 8
    printf("Teste 3: max(%d, %d) -> Resultado: %d | Esperado: 8\n", x3, y3, r3);
    
    // Teste 4: Números Negativos
    int x4 = -1, y4 = -5;
    int r4 = max_of_two(x4, y4); // Esperado: -1
    printf("Teste 4: max(%d, %d) -> Resultado: %d | Esperado: -1\n", x4, y4, r4);

    return 0;
}