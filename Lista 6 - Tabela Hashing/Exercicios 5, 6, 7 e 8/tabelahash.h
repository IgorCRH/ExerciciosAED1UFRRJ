#ifndef TABELAHASH_H
#define TABELAHASH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int chave;
    int valor;
} Elemento;

typedef struct {
    Elemento* elementos;
    int tamanho;
    int quantidade;
} TabelaHash;

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->elementos = (Elemento*)malloc(tamanho * sizeof(Elemento));
    tabela->tamanho = tamanho;
    tabela->quantidade = 0;

    for (int i = 0; i < tamanho; i++) {
        tabela->elementos[i].chave = -1;
    }

    return tabela;
}

int calcularIndice(int chave, int tamanho) {
    return chave % tamanho;
}

void inserir(TabelaHash* tabela, int chave, int valor) {
    int indice = calcularIndice(chave, tabela->tamanho);

    while (tabela->elementos[indice].chave != -1) {
        indice = (indice + 1) % tabela->tamanho;
    }

    tabela->elementos[indice].chave = chave;
    tabela->elementos[indice].valor = valor;
    tabela->quantidade++;
}

// Exercicio 5
float porcentagemHash(TabelaHash* tabela) {
    return ((float)tabela->quantidade / tabela->tamanho) * 100;
}

// Exercicio 6
void indiceColisao(TabelaHash* tabela) {
    printf("Posicoes da tabela com colisoes:\n");
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->elementos[i].chave != -1) {
            int indice = calcularIndice(tabela->elementos[i].chave, tabela->tamanho);
            if (indice != i) {
                printf("Posicao %d\n", i);
            }
        }
    }
}

// Exercicio 7
int quantidadeColisao(TabelaHash* tabela) {
    int colisoes = 0;
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->elementos[i].chave != -1) {
            int indice = calcularIndice(tabela->elementos[i].chave, tabela->tamanho);
            if (indice != i) {
                colisoes++;
            }
        }
    }
    return colisoes;
}

// Exercicio 8
int quantidadeElementos(TabelaHash* tabela) {
    return tabela->quantidade;
}

#endif
