#include <stdio.h>

// Declaração da função foo, que será definida externamente em Assembly
extern double foo(double a, int b);

int main() {
    // --- Casos de Teste ---
    
    // 1. Caso Padrão: Multiplicação de A por (-B)
    double a1 = 5.0;
    int b1 = 3;
    double resultado1 = foo(a1, b1); // Esperado: 5.0 * (-3) = -15.0
    printf("Teste 1: foo(%.1f, %d) -> Resultado: %.1f | Esperado: -15.0\n", a1, b1, resultado1);

    // 2. B é negativo: (-B) se torna positivo
    double a2 = 10.5;
    int b2 = -2;
    double resultado2 = foo(a2, b2); // Esperado: 10.5 * (-(-2)) = 10.5 * 2 = 21.0
    printf("Teste 2: foo(%.1f, %d) -> Resultado: %.1f | Esperado: 21.0\n", a2, b2, resultado2);

    // 3. A é negativo: (-B) * (-A)
    double a3 = -4.0;
    int b3 = 5;
    double resultado3 = foo(a3, b3); // Esperado: -4.0 * (-5) = 20.0
    printf("Teste 3: foo(%.1f, %d) -> Resultado: %.1f | Esperado: 20.0\n", a3, b3, resultado3);

    // 4. B é zero: Multiplicação por zero (negado)
    double a4 = 99.9;
    int b4 = 0;
    double resultado4 = foo(a4, b4); // Esperado: 99.9 * (0) = 0.0
    printf("Teste 4: foo(%.1f, %d) -> Resultado: %.1f | Esperado: 0.0\n", a4, b4, resultado4);

    return 0;
}