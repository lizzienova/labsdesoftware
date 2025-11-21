#include <stdio.h>
#include <math.h> // Necessário para M_PI e para a comparação de float/double

// Declaração da função Assembly
extern double trig_calc(double angle);

int main() {
    printf("--- Testes da Função trig_calc (sin(x) + cos(x)) ---\n");
    
    // Teste 1: Ângulo PI/2 (90 graus)
    // sin(PI/2) = 1.0, cos(PI/2) = 0.0. Esperado: 1.0
    double angle1 = M_PI / 2.0; 
    double resultado1 = trig_calc(angle1);
    double esperado1 = sin(angle1) + cos(angle1);
    printf("Teste 1: 90 graus (%.3f rad) -> Resultado: %.4f | Esperado: %.4f\n", angle1, resultado1, esperado1);
    
    // Teste 2: Ângulo 0 (0 graus)
    // sin(0) = 0.0, cos(0) = 1.0. Esperado: 1.0
    double angle2 = 0.0;
    double resultado2 = trig_calc(angle2);
    double esperado2 = sin(angle2) + cos(angle2);
    printf("Teste 2: 0 graus (%.3f rad) -> Resultado: %.4f | Esperado: %.4f\n", angle2, resultado2, esperado2);
    
    // Teste 3: Ângulo PI (180 graus)
    // sin(PI) ≈ 0.0, cos(PI) = -1.0. Esperado: -1.0
    double angle3 = M_PI;
    double resultado3 = trig_calc(angle3);
    double esperado3 = sin(angle3) + cos(angle3);
    printf("Teste 3: 180 graus (%.4f rad) -> Resultado: %.4f | Esperado: %.4f\n", angle3, resultado3, esperado3);

    // Teste 4: Ângulo aleatório (para verificar precisão)
    double angle4 = 0.5; // Em radianos
    double resultado4 = trig_calc(angle4);
    double esperado4 = sin(angle4) + cos(angle4);
    printf("Teste 4: 0.5 radianos -> Resultado: %.4f | Esperado: %.4f\n", resultado4, esperado4);

    return 0;
}