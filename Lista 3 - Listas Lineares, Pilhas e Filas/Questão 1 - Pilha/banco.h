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

typedef struct { // Usando a struct de Pilha, para a vers�o Pilha
    int capacidade;
    TCliente* dados;
    int topo;
} Pilha;

// Implementa��o das fun��es

/**
Inicializa a pilha, aonde o ponteiro do tipo pilha e a capacidade s�o passados por argumento pela main para dentro dessa fun��o.
E ent�o s�o alocados as vari�veis da struct pilha para inicializ�-la.
*/

void inicializarPilha(Pilha* pilha, int capacidade) {
    pilha->capacidade = capacidade;
    pilha->dados = (TCliente*)malloc(capacidade * sizeof(TCliente));
    pilha->topo = -1;
}

/**
Fun��o para cadastro de clientes. Os novos clientes, conforme v�o sendo cadastrados, s�o empilhados um em cima do outro.
Aonde o mais recente � o mais novo, portanto o topo.
*/

int empilharCliente(Pilha* pilha, TCliente cliente) {
    if (pilha->topo == pilha->capacidade - 1) { // Capacidade -1 pois vai de 0 at� o tamanho da pilha (capacidade)/n�mero de lugares
        return 0;  // Pilha cheia
    }

    if (buscarCliente(pilha, cliente.cpf) != -1) {
        return -1; // Cliente j� cadastrado
    }

    pilha->topo++;
    pilha->dados[pilha->topo] = cliente;
    return 1; // Cliente inserido com sucesso
}

/**
Fun��o para remo��o de clientes. Os novos clientes, conforme v�o sendo cadastrados, s�o empilhados um em cima do outro.
Aonde o mais recente � o mais novo, portanto o topo.
*/

int desempilharCliente(Pilha* pilha) {
    if (pilha->topo == -1) {
        return 0; // Pilha vazia
    }

    pilha->topo--; // Decrementa o valor do campo topo da estrutura Pilha para indicar que o elemento do topo est� sendo removido.
    return 1; // Cliente removido com sucesso
}

int buscarCliente(Pilha* pilha, int cpf) { // Busca cliente por CPF
    for (int i = 0; i <= pilha->topo; i++) { // Percorre a posi��o 0 at� o topo da pilha
        if (pilha->dados[i].cpf == cpf) { // Compara o CPF guardado na struct pilha com o que � passado por argumento
            return i; // Guarda e retorna o �ndice do cliente na pilha do CPF digitado
        }
    }
    return -1; // CPF n�o registrado, portanto cliente n�o foi encontrado
}

int sacarValor(Pilha* pilha, int cpf, float valor) {
    int posicao = buscarCliente(pilha, cpf); // Faz chamada a fun��o de busca do CPF para ver se esse cliente est� cadastrado
    if (posicao == -1) { // buscarCliente retorna -1 se o CPF n�o for encontrado, ent�o:
        return 0; // Cliente n�o encontrado
    }

    if (pilha->dados[posicao].saldo < valor) { // Se for encontrado, mas a quantia for maior que o saldo do cliente, ent�o:
        return -1; // Saldo insuficiente
    }

    pilha->dados[posicao].saldo -= valor; // Se for encontrado, e houver saque dispon�vel, realiza o saque
    return 1; // Saque realizado com sucesso
}

void imprimirPilha(Pilha* pilha) {
    if (pilha->topo == -1) {
        printf("A pilha esta vazia.\n");
    } else {
        printf("Conteudo da pilha:\n");
        for (int i = pilha->topo; i >= 0; i--) { // Percorre a pilha do topo at� o final pelo uso do apontador pilha
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
