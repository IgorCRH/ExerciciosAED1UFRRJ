#ifndef TABELAHASHQUADRATICA_H
#define TABELAHASHQUADRATICA_H
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

int calcularIndice(int chave, int tamanho, int tentativa) {
    int indice = (chave % tamanho) + tentativa * tentativa;
    return indice % tamanho;
}

void inserir(TabelaHash* tabela, int chave, int valor) {
    int tentativa = 0;
    int indice = calcularIndice(chave, tabela->tamanho, tentativa);

    while (tabela->elementos[indice].chave != -1) {
        tentativa++;
        indice = calcularIndice(chave, tabela->tamanho, tentativa);
    }

    tabela->elementos[indice].chave = chave;
    tabela->elementos[indice].valor = valor;
}

void remover(TabelaHash* tabela, int chave) {
    int tentativa = 0;
    int indice = calcularIndice(chave, tabela->tamanho, tentativa);

    while (tabela->elementos[indice].chave != -1) {
        if (tabela->elementos[indice].chave == chave) {
            tabela->elementos[indice].chave = -1;
            return;
        }

        tentativa++;
        indice = calcularIndice(chave, tabela->tamanho, tentativa);
    }
}

int buscar(TabelaHash* tabela, int chave) {
    int tentativa = 0;
    int indice = calcularIndice(chave, tabela->tamanho, tentativa);

    while (tabela->elementos[indice].chave != -1) {
        if (tabela->elementos[indice].chave == chave) {
            return tabela->elementos[indice].valor;
        }

        tentativa++;
        indice = calcularIndice(chave, tabela->tamanho, tentativa);
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

void trocarPosicaoElementos(TabelaHash* tabela, int chave1, int chave2) {
    int indice1 = -1;
    int indice2 = -1;

    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->elementos[i].chave == chave1) {
            indice1 = i;
        } else if (tabela->elementos[i].chave == chave2) {
            indice2 = i;
        }
    }

    if (indice1 != -1 && indice2 != -1) {
        Elemento temp = tabela->elementos[indice1];
        tabela->elementos[indice1] = tabela->elementos[indice2];
        tabela->elementos[indice2] = temp;
        printf("Elementos trocados de posição com sucesso!\n");
    } else {
        printf("Chaves informadas não foram encontradas na tabela.\n");
    }
}

#endif
