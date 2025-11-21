#include <stdio.h>
#include <math.h>

// Declaração da nova função Assembly
extern double sum_three(double a, double b, double c);

int main() {
    printf("\n--- Testes da Função sum_three (a + b + c) ---\n");
    
    // Teste 1: Números positivos
    double a1 = 10.5;
    double b1 = 20.0;
    double c1 = 30.0;
    double r1 = sum_three(a1, b1, c1); // Esperado: 10.5 + 20.0 + 30.0 = 60.5
    printf("Teste 1: (%.1f + %.1f + %.1f) -> Resultado: %.1f | Esperado: 60.5\n", a1, b1, c1, r1);

    // Teste 2: Números com zero
    double a2 = 1.0;
    double b2 = 0.0;
    double c2 = 2.5;
    double r2 = sum_three(a2, b2, c2); // Esperado: 1.0 + 0.0 + 2.5 = 3.5
    printf("Teste 2: (%.1f + %.1f + %.1f) -> Resultado: %.1f | Esperado: 3.5\n", a2, b2, c2, r2);
    
    // Teste 3: Números negativos
    double a3 = -5.0;
    double b3 = -10.0;
    double c3 = 8.0;
    double r3 = sum_three(a3, b3, c3); // Esperado: -5.0 + (-10.0) + 8.0 = -7.0
    printf("Teste 3: (%.1f + %.1f + %.1f) -> Resultado: %.1f | Esperado: -7.0\n", a3, b3, c3, r3);

    return 0;
}