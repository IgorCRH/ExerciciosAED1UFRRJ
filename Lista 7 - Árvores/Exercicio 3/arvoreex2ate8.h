#include <stdio.h>
#include <stdlib.h>
#ifndef ARVOREEX2ATE8_H
#define ARVOREEX2ATE8_H

struct No {
    int dado;
    struct No* esquerda;
    struct No* direita;
};

struct No* criarNo(int dado) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

struct No* inserir(struct No* raiz, int dado) {
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

struct No* encontrarNoMinimo(struct No* no) { // Encontra o n� m�nimo na sub�rvore direita para uso da fun��o de remover
    struct No* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

struct No* removerNo(struct No* raiz, int dado) { // Remove um n� da �rvore
    if (raiz == NULL) {
        return raiz;
    }
    if (dado < raiz->dado) {
        raiz->esquerda = removerNo(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = removerNo(raiz->direita, dado);
    } else {
        if (raiz->esquerda == NULL) { // N� possui apenas filho direito ou nenhum filho
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) { // N� possui apenas filho esquerdo
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        struct No* temp = encontrarNoMinimo(raiz->direita); // N� possui dois filhos
        raiz->dado = temp->dado; // Substitui o dado do n� a ser removido pelo dado do n� m�nimo
        raiz->direita = removerNo(raiz->direita, temp->dado); // Remove o n� m�nimo
    }
    return raiz;
}

struct No* buscarNo(struct No* raiz, int dado) { // Exercicio 4
    while (raiz != NULL) {
        if (dado == raiz->dado) {
            return raiz;
        } else if (dado < raiz->dado) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    return NULL;
}

struct No* encontrarPai(struct No* raiz, int dado) { // Exercicio 5
    struct No* pai = NULL;
    while (raiz != NULL && raiz->dado != dado) {
        pai = raiz;
        if (dado < raiz->dado) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    return pai;
}

struct No* encontrarIrmao(struct No* raiz, int valor) { // Exercicio 2
    struct No* no = buscarNo(raiz, valor);
    if (no == NULL || raiz == NULL) {
        return NULL;  // N� n�o encontrado ou raiz � nula
    }
    struct No* pai = encontrarPai(raiz, valor);
    if (pai == NULL) {
        return NULL;  // N� � a raiz, n�o tem irm�o
    }
    if (pai->esquerda != NULL && pai->esquerda->dado == valor) {
        return pai->direita;  // Retorna o n� direito se o valor est� � esquerda
    } else {
        return pai->esquerda;  // Retorna o n� esquerdo se o valor est� � direita
    }
}


void imprimirCaminho(struct No* raiz, int dado) { // Exercicio 6
    while (raiz != NULL) {
        printf("%d ", raiz->dado);
        if (dado == raiz->dado) {
            break;
        } else if (dado < raiz->dado) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    printf("\n");
}

int contarMaiores(struct No* raiz, int dado) { // Exercicio 7
    if (raiz == NULL) {
        return 0;
    }
    if (raiz->dado <= dado) {
        return contarMaiores(raiz->direita, dado);
    }
    return 1 + contarMaiores(raiz->esquerda, dado) + contarMaiores(raiz->direita, dado);
}

int calcularAltura(struct No* raiz) { // Exercicio 8
    if (raiz == NULL) {
        return 0;
    }
    int alturaEsquerda = calcularAltura(raiz->esquerda);
    int alturaDireita = calcularAltura(raiz->direita);
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
}

void imprimirEmOrdem(struct No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        imprimirEmOrdem(raiz->direita);
    }
}

#endif
