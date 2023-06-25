#include <stdio.h>
#include <stdlib.h>
#ifndef ABBEX1_H
#define ABBEX1_H

struct No {
    int dado;
    struct No* esquerda;
    struct No* direita;
};

struct No* criarNo(int dado) { // Cria o nó da árvore
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

struct No* inserir(struct No* raiz, int dado) { // Insere elemento na árvore
    if (raiz == NULL) {
        return criarNo(dado);
    }
    if (dado < raiz->dado) {
        raiz->esquerda = inserir(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = inserir(raiz->direita, dado);
    }
    return raiz;
}

struct No* encontrarNoMinimo(struct No* no) { // Encontra o nó mínimo na subárvore direita
    struct No* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

struct No* removerNo(struct No* raiz, int dado) { // Remove um nó da árvore
    if (raiz == NULL) {
        return raiz;
    }
    if (dado < raiz->dado) {
        raiz->esquerda = removerNo(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = removerNo(raiz->direita, dado);
    } else {
        if (raiz->esquerda == NULL) { // Nó possui apenas filho direito ou nenhum filho
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) { // Nó possui apenas filho esquerdo
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        struct No* temp = encontrarNoMinimo(raiz->direita); // Nó possui dois filhos
        raiz->dado = temp->dado; // Substitui o dado do nó a ser removido pelo dado do nó mínimo
        raiz->direita = removerNo(raiz->direita, temp->dado); // Remove o nó mínimo
    }
    return raiz;
}

void imprimirEmOrdem(struct No* raiz) { // Imprime os elementos em ordem
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        imprimirEmOrdem(raiz->direita);
    }
}

#endif
