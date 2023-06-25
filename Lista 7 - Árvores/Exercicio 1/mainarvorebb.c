#include <stdio.h>
#include "abbex1.h"

int main() {
    struct No* raiz = NULL;

    // Dados de entrada
    int numeros[] = {14, 10, 20, 5, 40, 18, 50, 30, 25, 33, 37, 36, 3, 12};
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);

    // Inserir os elementos na árvore
    for (int i = 0; i < tamanho; i++) {
        raiz = inserir(raiz, numeros[i]);
    }

    // Remover os elementos especificados
    raiz = removerNo(raiz, 3);
    raiz = removerNo(raiz, 10);
    raiz = removerNo(raiz, 20);
    raiz = removerNo(raiz, 33);
    raiz = removerNo(raiz, 40);

    // Imprimir a árvore resultante em ordem
    printf("Arvore resultante em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    return 0;
}
