#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cpf;
    char nome[50];
    char endereco[50];
    char tel[10];
    float saldo;
} TCliente;

typedef struct No {
    TCliente cliente;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
    int quantidade;
} Fila;

void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
}

int filaVazia(Fila* fila) {
    return (fila->quantidade == 0);
}

void enfileirar(Fila* fila, TCliente cliente) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->cliente = cliente;
    novoNo->prox = NULL;

    if (filaVazia(fila)) {
        fila->inicio = novoNo;
    } else {
        fila->fim->prox = novoNo;
    }

    fila->fim = novoNo;
    fila->quantidade++;
}

TCliente desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        TCliente clienteVazio;
        clienteVazio.cpf = -1;
        return clienteVazio;
    }

    No* noRemovido = fila->inicio;
    TCliente cliente = noRemovido->cliente;
    fila->inicio = fila->inicio->prox;
    fila->quantidade--;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(noRemovido);
    return cliente;
}

int buscarFila(Fila* fila, int cpf) {
    No* noAtual = fila->inicio;
    int contador = 0;

    while (noAtual != NULL) {
        if (noAtual->cliente.cpf == cpf) {
            return contador;
        }

        noAtual = noAtual->prox;
        contador++;
    }

    return -1;
}

int inserirCliente(Fila* fila, TCliente cliente) {
    if (buscarFila(fila, cliente.cpf) != -1) {
        return -1;
    }

    enfileirar(fila, cliente);
    return 1;
}

int removerCliente(Fila* fila, int cpf) {
    No* noAnterior = NULL;
    No* noAtual = fila->inicio;

    while (noAtual != NULL) {
        if (noAtual->cliente.cpf == cpf) {
            if (noAnterior == NULL) {
                fila->inicio = noAtual->prox;
            } else {
                noAnterior->prox = noAtual->prox;
            }

            if (noAtual == fila->fim) {
                fila->fim = noAnterior;
            }

            free(noAtual);
            fila->quantidade--;
            return 1;
        }

        noAnterior = noAtual;
        noAtual = noAtual->prox;
    }

    return 0;
}

int sacarFila(Fila* fila, int cpf, float valor) {
    No* noAtual = fila->inicio;

    while (noAtual != NULL) {
        if (noAtual->cliente.cpf == cpf) {
            if (noAtual->cliente.saldo < valor) {
                return -1;
            }

            noAtual->cliente.saldo -= valor;
            return 1;
        }

        noAtual = noAtual->prox;
    }

    return 0;
}

int depositarFila(Fila* fila, int cpf, float valor) {
    No* noAtual = fila->inicio;

    while (noAtual != NULL) {
        if (noAtual->cliente.cpf == cpf) {
            noAtual->cliente.saldo += valor;
            return 1;
        }

        noAtual = noAtual->prox;
    }

    return 0;
}

void imprimirFila(Fila* fila) {
    No* noAtual = fila->inicio;

    while (noAtual != NULL) {
        printf("CPF: %d\n", noAtual->cliente.cpf);
        printf("Nome: %s\n", noAtual->cliente.nome);
        printf("Endereco: %s\n", noAtual->cliente.endereco);
        printf("Telefone: %s\n", noAtual->cliente.tel);
        printf("Saldo: %.2f\n", noAtual->cliente.saldo);
        printf("-----------------\n");

        noAtual = noAtual->prox;
    }
}

void liberarFila(Fila* fila) {
    No* noAtual = fila->inicio;
    No* noRemovido;

    while (noAtual != NULL) {
        noRemovido = noAtual;
        noAtual = noAtual->prox;
        free(noRemovido);
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
}
