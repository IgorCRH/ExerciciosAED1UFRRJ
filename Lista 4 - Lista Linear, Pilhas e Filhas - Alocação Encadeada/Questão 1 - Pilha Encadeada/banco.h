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

typedef struct Node {
    TCliente cliente;
    struct Node* prox;
} Node;

typedef struct {
    Node* topo;
} Pilha;

void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
}

int empilharCliente(Pilha* pilha, TCliente cliente) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        return 0; // Falha na alocação de memória
    }

    novoNode->cliente = cliente;
    novoNode->prox = pilha->topo;
    pilha->topo = novoNode;

    return 1; // Cliente inserido com sucesso
}

int desempilharCliente(Pilha* pilha) {
    if (pilha->topo == NULL) {
        return 0; // Pilha vazia
    }

    Node* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);

    return 1; // Cliente removido com sucesso
}

int buscarCliente(Pilha* pilha, int cpf) {
    Node* atual = pilha->topo;
    int posicao = 1;

    while (atual != NULL) {
        if (atual->cliente.cpf == cpf) {
            return posicao; // Retorna a posição do cliente na pilha (começando de 1)
        }

        atual = atual->prox;
        posicao++;
    }

    return -1; // Cliente não encontrado
}

int sacarValor(Pilha* pilha, int cpf, float valor) {
    Node* atual = pilha->topo;

    while (atual != NULL) {
        if (atual->cliente.cpf == cpf) {
            if (atual->cliente.saldo < valor) {
                return -1; // Saldo insuficiente
            }

            atual->cliente.saldo -= valor;
            return 1; // Saque realizado com sucesso
        }

        atual = atual->prox;
    }

    return 0; // Cliente não encontrado
}

void imprimirPilha(Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha esta vazia.\n");
    } else {
        printf("Conteudo da pilha:\n");
        Node* atual = pilha->topo;
        int posicao = 1;

        while (atual != NULL) {
            printf("Cliente %d:\n", posicao);
            printf("Nome: %s\n", atual->cliente.nome);
            printf("Endereco: %s\n", atual->cliente.endereco);
            printf("Telefone: %s\n", atual->cliente.tel);
            printf("CPF: %d\n", atual->cliente.cpf);
            printf("Saldo: %.2f\n", atual->cliente.saldo);
            printf("--------------------\n");
        atual = atual->prox;
        posicao++;
    }
}
}
