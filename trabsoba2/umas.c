int minha_funcao() {
    // Declaração de uma variável local (que irá para a pilha, ex: -4(%rbp) )
    int a = 123; 
    
    // Instrução 1: Mova a variável 'a' (memória) para %eax (registrador)
    // O compilador gera: movl -offset(%rbp), %eax
    return a;
}

// Para que o compilador não otimize demais a função:
int main() {
    return minha_funcao();
}