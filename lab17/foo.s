/* 
double foo (double a, int b) {
  return a * (-b);
}
*/

/*
dicionario

double a tá em xmm0
int b tá em edi

*/

.text
.globl foo
foo:
    neg %edi
    cvtsi2sd %edi, %xmm1
    mulsd %xmm1, %xmm0
    ret