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

typedef struct { // Usando a struct de Pilha, para a versão Pilha
    int capacidade;
    TCliente* dados;
    int topo;
} Pilha;

// Implementação das funções

/**
Inicializa a pilha, aonde o ponteiro do tipo pilha e a capacidade são passados por argumento pela main para dentro dessa função.
E então são alocados as variáveis da struct pilha para inicializá-la.
*/

void inicializarPilha(Pilha* pilha, int capacidade) {
    pilha->capacidade = capacidade;
    pilha->dados = (TCliente*)malloc(capacidade * sizeof(TCliente));
    pilha->topo = -1;
}

/**
Função para cadastro de clientes. Os novos clientes, conforme vão sendo cadastrados, são empilhados um em cima do outro.
Aonde o mais recente é o mais novo, portanto o topo.
*/

int empilharCliente(Pilha* pilha, TCliente cliente) {
    if (pilha->topo == pilha->capacidade - 1) { // Capacidade -1 pois vai de 0 até o tamanho da pilha (capacidade)/número de lugares
        return 0;  // Pilha cheia
    }

    if (buscarCliente(pilha, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    pilha->topo++;
    pilha->dados[pilha->topo] = cliente;
    return 1; // Cliente inserido com sucesso
}

/**
Função para remoção de clientes. Os novos clientes, conforme vão sendo cadastrados, são empilhados um em cima do outro.
Aonde o mais recente é o mais novo, portanto o topo.
*/

int desempilharCliente(Pilha* pilha) {
    if (pilha->topo == -1) {
        return 0; // Pilha vazia
    }

    pilha->topo--; // Decrementa o valor do campo topo da estrutura Pilha para indicar que o elemento do topo está sendo removido.
    return 1; // Cliente removido com sucesso
}

int buscarCliente(Pilha* pilha, int cpf) { // Busca cliente por CPF
    for (int i = 0; i <= pilha->topo; i++) { // Percorre a posição 0 até o topo da pilha
        if (pilha->dados[i].cpf == cpf) { // Compara o CPF guardado na struct pilha com o que é passado por argumento
            return i; // Guarda e retorna o índice do cliente na pilha do CPF digitado
        }
    }
    return -1; // CPF não registrado, portanto cliente não foi encontrado
}

int sacarValor(Pilha* pilha, int cpf, float valor) {
    int posicao = buscarCliente(pilha, cpf); // Faz chamada a função de busca do CPF para ver se esse cliente está cadastrado
    if (posicao == -1) { // buscarCliente retorna -1 se o CPF não for encontrado, então:
        return 0; // Cliente não encontrado
    }

    if (pilha->dados[posicao].saldo < valor) { // Se for encontrado, mas a quantia for maior que o saldo do cliente, então:
        return -1; // Saldo insuficiente
    }

    pilha->dados[posicao].saldo -= valor; // Se for encontrado, e houver saque disponível, realiza o saque
    return 1; // Saque realizado com sucesso
}

void imprimirPilha(Pilha* pilha) {
    if (pilha->topo == -1) {
        printf("A pilha esta vazia.\n");
    } else {
        printf("Conteudo da pilha:\n");
        for (int i = pilha->topo; i >= 0; i--) { // Percorre a pilha do topo até o final pelo uso do apontador pilha
            printf("Cliente %d:\n", i+1);
            printf("Nome: %s\n", pilha->dados[i].nome);
            printf("Endereco: %s\n", pilha->dados[i].endereco);
            printf("Telefone: %s\n", pilha->dados[i].tel);
            printf("CPF: %d\n", pilha->dados[i].cpf);
            printf("Saldo: %.2f\n", pilha->dados[i].saldo);
            printf("--------------------\n");
        }
    }
}
