#ifndef TABELAHASHENCADEAMENTOEXT_H
#define TABELAHASHENCADEAMENTOEXT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento {
    int chave;
    int valor;
    struct Elemento* proximo;
} Elemento;

typedef struct TabelaHash {
    int tamanho;
    Elemento** tabela;
} TabelaHash;

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->tamanho = tamanho;
    tabela->tabela = (Elemento**)calloc(tamanho, sizeof(Elemento*));
    return tabela;
}

int funcaoHash(int chave, int tamanho) {
    return chave % tamanho;
}

void inserir(TabelaHash* tabela, int chave, int valor) {
    Elemento* novoElemento = (Elemento*)malloc(sizeof(Elemento));
    novoElemento->chave = chave;
    novoElemento->valor = valor;
    novoElemento->proximo = NULL;

    int indice = funcaoHash(chave, tabela->tamanho);

    if (tabela->tabela[indice] == NULL) {
        tabela->tabela[indice] = novoElemento;
    } else {
        Elemento* elementoAtual = tabela->tabela[indice];
        while (elementoAtual->proximo != NULL) {
            elementoAtual = elementoAtual->proximo;
        }
        elementoAtual->proximo = novoElemento;
    }
}

void remover(TabelaHash* tabela, int chave) {
    int indice = funcaoHash(chave, tabela->tamanho);

    Elemento* elementoAtual = tabela->tabela[indice];
    Elemento* elementoAnterior = NULL;

    while (elementoAtual != NULL) {
        if (elementoAtual->chave == chave) {
            if (elementoAnterior == NULL) {
                tabela->tabela[indice] = elementoAtual->proximo;
            } else {
                elementoAnterior->proximo = elementoAtual->proximo;
            }
            free(elementoAtual);
            return;
        }
        elementoAnterior = elementoAtual;
        elementoAtual = elementoAtual->proximo;
    }
}

int buscar(TabelaHash* tabela, int chave) {
    int indice = funcaoHash(chave, tabela->tamanho);

    Elemento* elementoAtual = tabela->tabela[indice];

    while (elementoAtual != NULL) {
        if (elementoAtual->chave == chave) {
            return elementoAtual->valor;
        }
        elementoAtual = elementoAtual->proximo;
    }

    return -1;
}

int procurarMaior(TabelaHash* tabela) {
    int maiorValor = INT_MIN;

    for (int i = 0; i < tabela->tamanho; i++) {
        Elemento* elementoAtual = tabela->tabela[i];

        while (elementoAtual != NULL) {
            if (elementoAtual->valor > maiorValor) {
                maiorValor = elementoAtual->valor;
            }
            elementoAtual = elementoAtual->proximo;
        }
    }

    return maiorValor;
}

int procurarMenor(TabelaHash* tabela) {
    int menorValor = INT_MAX;

    for (int i = 0; i < tabela->tamanho; i++) {
        Elemento* elementoAtual = tabela->tabela[i];

        while (elementoAtual != NULL) {
            if (elementoAtual->valor < menorValor) {
            menorValor = elementoAtual->valor;
            }
        elementoAtual = elementoAtual->proximo;
                                      }
}
return menorValor;
}

void trocarPosicaoElementos(TabelaHash* tabela, int chave1, int chave2) {
int indice1 = funcaoHash(chave1, tabela->tamanho);
int indice2 = funcaoHash(chave2, tabela->tamanho);
Elemento* elemento1 = tabela->tabela[indice1];
Elemento* elemento2 = tabela->tabela[indice2];
Elemento* elementoAnterior1 = NULL;
Elemento* elementoAnterior2 = NULL;

while (elemento1 != NULL && elemento1->chave != chave1) {
    elementoAnterior1 = elemento1;
    elemento1 = elemento1->proximo;
}

while (elemento2 != NULL && elemento2->chave != chave2) {
    elementoAnterior2 = elemento2;
    elemento2 = elemento2->proximo;
}

if (elemento1 == NULL || elemento2 == NULL) {
    printf("Um ou ambos os elementos não foram encontrados na tabela.\n");
    return;
}

if (elementoAnterior1 == NULL) {
    tabela->tabela[indice1] = elemento2;
} else {
    elementoAnterior1->proximo = elemento2;
}

if (elementoAnterior2 == NULL) {
    tabela->tabela[indice2] = elemento1;
} else {
    elementoAnterior2->proximo = elemento1;
}

Elemento* temp = elemento1->proximo;
elemento1->proximo = elemento2->proximo;
elemento2->proximo = temp;
}

void imprimirTabelaHash(TabelaHash* tabela) {
printf("\n----- Tabela Hash -----\n");
for (int i = 0; i < tabela->tamanho; i++) {
printf("Indice %d: ", i);
Elemento* elementoAtual = tabela->tabela[i];
while (elementoAtual != NULL) {
printf("[%d, %d] ", elementoAtual->chave, elementoAtual->valor);
elementoAtual = elementoAtual->proximo;
}
printf("\n");
}
printf("-----------------------\n");
}

int contarEspacosVazios(TabelaHash* tabela) {
    int contador = 0;

    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->tabela[i] == NULL) {
            contador++;
        }
    }

    return contador;
}

#endif
