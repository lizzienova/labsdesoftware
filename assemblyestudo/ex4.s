/*
double sum_three(double a, double b, double c) {
    return (a + b + c);
}
*/

/*
dicionario
double a em xmm0
double b em xmm1
double c em xmm2
*/

.text
.globl sum_three
sum_three:
    addsd %xmm1, %xmm0 #faço a+b e salvo em a
    addsd %xmm2, %xmm0 #faço (a+b)+c e salvo em a
    ret

