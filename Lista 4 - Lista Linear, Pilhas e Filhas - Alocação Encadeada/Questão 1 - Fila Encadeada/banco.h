#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cpf;
    char nome[50];
    char endereco[50];
    char tel[10];
    float saldo;
} TCliente; // Definição da estrutura TCliente que representa as informações dos clientes

typedef struct Node {
    TCliente cliente;
    struct Node* prox; // Ponteiro prox que aponta para o próximo nó da pilha
} Node; // Definição da estrutura Node que representa um nó da pilha encadeada

typedef struct {
    Node* topo;
} Pilha; // Definição da estrutura da pilha em si, com um único campo topo, que é um ponteiro para o topo da pilha

void inicializarPilha(Pilha* pilha) { // Inicializa a pilha, com a pilha sem  elementos, isto é, topo NULL
    pilha->topo = NULL;
}

int empilharCliente(Pilha* pilha, TCliente cliente) { // Função para inserir elemento para um novo cliente
    Node* novoNode = (Node*)malloc(sizeof(Node)); // Alocação de memória para o novo nó
    if (novoNode == NULL) { // Verifica se a alocação foi bem sucedida
        return 0; // Falha na alocação de memória
    }

    novoNode->cliente = cliente; // Preenche o campo ponteiro cliente para a struct TCliente com as informações do cliente passado como argumento pela main
    novoNode->prox = pilha->topo; // Ajusta o campo prox para apontar para o nó anterior do topo da pilha, ou seja, o novo nó está sendo inserido no topo da pilha e seu próximo nó é o nó que anteriormente estava no topo.
    pilha->topo = novoNode; // Atualiza o topo da pilha para o novo nó, que agora é o topo

    return 1; // Cliente inserido com sucesso
}

int desempilharCliente(Pilha* pilha) { // Função para remover cliente(elemento)
    if (pilha->topo == NULL) {
        return 0; // Pilha vazia
    }

    Node* temp = pilha->topo; // Nó temp recebe o endereço do topo da pilha
    pilha->topo = pilha->topo->prox;
    /**
    // Atualiza o ponteiro topo para apontar para o próximo nó da pilha,
    então o campo prox é acessado para entrada na struct TCliente, e coleta das referências do próximo nó (o que está abaixo do topo), então o
    nó que estava no topo é removido da pilha, e o nó seguinte passa a ser o novo topo.
    */
    free(temp); // Libera a memória do nó a ser removido da pilha

    return 1; // Cliente removido com sucesso
}

int buscarCliente(Pilha* pilha, int cpf) {
    Node* atual = pilha->topo; // Ponteiro atual recebe o topo da pilha
    int posicao = 1; //  Inicializa-se a variável posicao com o valor 1, que será utilizado para armazenar a posição do cliente na pilha.

    while (atual != NULL) { // Percorre a pilha até o final
        if (atual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na pilha, se for encontrado:
            return posicao; // Retorna a posição do cliente na pilha (começando de 1)
        }
        // Se não:
        atual = atual->prox; // Atualiza o ponteiro atual para apontar para o próximo nó na pilha
        posicao++; // Incrementa para acompanhar a ida para o próximo, indicando que passamos para o próximo nó na pilha, e continuar a busca
    }

    return -1; // Cliente não encontrado
}

int sacarValor(Pilha* pilha, int cpf, float valor) {
    Node* atual = pilha->topo;

    while (atual != NULL) { // Percorre a pilha até o final
        if (atual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na pilha, se for encontrado:
            if (atual->cliente.saldo < valor) {
                return -1; // Saldo insuficiente
            }
            // Se cliente tiver saldo disponível:
            atual->cliente.saldo -= valor;
            return 1; // Saque realizado com sucesso
        }

        atual = atual->prox; // Atualiza o ponteiro atual para apontar para o próximo nó na pilha e continuar a busca pelo CPF
    }

    return 0; // Cliente não encontrado
}

void imprimirPilha(Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha esta vazia.\n");
    } else {
        printf("Conteudo da pilha:\n");
        Node* atual = pilha->topo; // Nó atual recebe o topo da pilha
        int posicao = 1;

        while (atual != NULL) { // Percorre a pilha até o final
            printf("Cliente %d:\n", posicao); // Imprime as informações de cada elemento da pilha, por meio do nó atual da struct No,e o ponteiro campo cliente que entra na struct TCliente
            printf("Nome: %s\n", atual->cliente.nome);
            printf("Endereco: %s\n", atual->cliente.endereco);
            printf("Telefone: %s\n", atual->cliente.tel);
            printf("CPF: %d\n", atual->cliente.cpf);
            printf("Saldo: %.2f\n", atual->cliente.saldo);
            printf("--------------------\n");
        atual = atual->prox; // Atualiza o ponteiro atual para apontar para o próximo nó na pilha e continuar a impressão
        posicao++; // Incrementa para acompanhar a ida para o próximo, e continuar a impressão das informações
    }
}
}
