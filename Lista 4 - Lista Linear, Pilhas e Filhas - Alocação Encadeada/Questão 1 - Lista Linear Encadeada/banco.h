#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cpf;
    char nome[100];
    char endereco[100];
    char tel[15];
    float saldo;
} TCliente;

typedef struct No {
    TCliente cliente;
    struct No* proximo;
} No;

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inicializarLista(ListaEncadeada* lista) {
    lista->primeiro = NULL;
    lista->tamanho = 0;
}

int buscarLista(ListaEncadeada* lista, int cpf) {
    No* atual = lista->primeiro;
    int indice = 0;

    while (atual != NULL) {
        if (atual->cliente.cpf == cpf) {
            return indice;
        }
        atual = atual->proximo;
        indice++;
    }

    return -1;
}

int inserirCliente(ListaEncadeada* lista, TCliente cliente) {
    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        return 0; // Falha na alocação de memória
    }

    novoNo->cliente = cliente;
    novoNo->proximo = lista->primeiro;
    lista->primeiro = novoNo;
    lista->tamanho++;

    return 1; // Cliente cadastrado com sucesso
}

int removerCliente(ListaEncadeada* lista, int cpf) {
    No* atual = lista->primeiro;
    No* anterior = NULL;

    while (atual != NULL) {
        if (atual->cliente.cpf == cpf) {
            if (anterior == NULL) {
                lista->primeiro = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            lista->tamanho--;
            return 1; // Cliente removido com sucesso
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0; // Cliente não encontrado
}

int sacarLista(ListaEncadeada* lista, int cpf, float valor) {
    No* atual = lista->primeiro;

    while (atual != NULL) {
        if (atual->cliente.cpf == cpf) {
            if (atual->cliente.saldo >= valor) {
                atual->cliente.saldo -= valor;
                return 1; // Saque realizado com sucesso
            } else {
                return -1; // Saldo insuficiente
            }
        }
        atual = atual->proximo;
    }

    return 0; // Cliente não encontrado
}

void imprimirLista(ListaEncadeada* lista) {
    No* atual = lista->primeiro;

    printf("Lista de Clientes:\n");
    while (atual != NULL) {
        printf("CPF: %d\n", atual->cliente.cpf);
        printf("Nome: %s\n", atual->cliente.nome);
        printf("Endereco: %s\n", atual->cliente.endereco);
        printf("Telefone: %s\n", atual->cliente.tel);
        printf("Saldo: %.2f\n\n", atual->cliente.saldo);

        atual = atual->proximo;
    }
}
