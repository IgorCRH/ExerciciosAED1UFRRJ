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
} TabelaHash;

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->elementos = (Elemento*)malloc(tamanho * sizeof(Elemento));
    tabela->tamanho = tamanho;

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
}

void remover(TabelaHash* tabela, int chave) {
    int indice = calcularIndice(chave, tabela->tamanho);

    while (tabela->elementos[indice].chave != -1) {
        if (tabela->elementos[indice].chave == chave) {
            tabela->elementos[indice].chave = -1;
            return;
        }
        indice = (indice + 1) % tabela->tamanho;
    }
}

int buscar(TabelaHash* tabela, int chave) {
    int indice = calcularIndice(chave, tabela->tamanho);

    while (tabela->elementos[indice].chave != -1) {
        if (tabela->elementos[indice].chave == chave) {
            return tabela->elementos[indice].valor;
        }
        indice = (indice + 1) % tabela->tamanho;
    }

    return -1;
}

int procurarMaior(TabelaHash* tabela) {
    int maiorValor = -1;

    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->elementos[i].chave != -1) {
            if (maiorValor == -1 || tabela->elementos[i].valor > maiorValor) {
                maiorValor = tabela->elementos[i].valor;
            }
        }
    }

    return maiorValor;
}

int procurarMenor(TabelaHash* tabela) {
    int menorValor = -1;

    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->elementos[i].chave != -1) {
            if (menorValor == -1 || tabela->elementos[i].valor < menorValor) {
                menorValor = tabela->elementos[i].valor;
            }
        }
    }

    return menorValor;
}

void imprimirTabelaHash(TabelaHash* tabela) {
    printf("----- Tabela Hash -----\n");

    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->elementos[i].chave != -1) {
            printf("Posicao %d: Chave = %d, Valor = %d\n", i, tabela->elementos[i].chave, tabela->elementos[i].valor);
        }
    }

    printf("-----------------------\n");
}

#endif
