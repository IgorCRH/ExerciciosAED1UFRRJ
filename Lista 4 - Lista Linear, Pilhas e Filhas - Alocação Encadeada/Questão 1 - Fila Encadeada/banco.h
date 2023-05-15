#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cpf;
    char nome[50];
    char endereco[50];
    char tel[10];
    float saldo;
} TCliente; // Defini��o da estrutura TCliente que representa as informa��es dos clientes

typedef struct Node {
    TCliente cliente;
    struct Node* prox; // Ponteiro prox que aponta para o pr�ximo n� da pilha
} Node; // Defini��o da estrutura Node que representa um n� da pilha encadeada

typedef struct {
    Node* topo;
} Pilha; // Defini��o da estrutura da pilha em si, com um �nico campo topo, que � um ponteiro para o topo da pilha

void inicializarPilha(Pilha* pilha) { // Inicializa a pilha, com a pilha sem  elementos, isto �, topo NULL
    pilha->topo = NULL;
}

int empilharCliente(Pilha* pilha, TCliente cliente) { // Fun��o para inserir elemento para um novo cliente
    Node* novoNode = (Node*)malloc(sizeof(Node)); // Aloca��o de mem�ria para o novo n�
    if (novoNode == NULL) { // Verifica se a aloca��o foi bem sucedida
        return 0; // Falha na aloca��o de mem�ria
    }

    novoNode->cliente = cliente; // Preenche o campo ponteiro cliente para a struct TCliente com as informa��es do cliente passado como argumento pela main
    novoNode->prox = pilha->topo; // Ajusta o campo prox para apontar para o n� anterior do topo da pilha, ou seja, o novo n� est� sendo inserido no topo da pilha e seu pr�ximo n� � o n� que anteriormente estava no topo.
    pilha->topo = novoNode; // Atualiza o topo da pilha para o novo n�, que agora � o topo

    return 1; // Cliente inserido com sucesso
}

int desempilharCliente(Pilha* pilha) { // Fun��o para remover cliente(elemento)
    if (pilha->topo == NULL) {
        return 0; // Pilha vazia
    }

    Node* temp = pilha->topo; // N� temp recebe o endere�o do topo da pilha
    pilha->topo = pilha->topo->prox;
    /**
    // Atualiza o ponteiro topo para apontar para o pr�ximo n� da pilha,
    ent�o o campo prox � acessado para entrada na struct TCliente, e coleta das refer�ncias do pr�ximo n� (o que est� abaixo do topo), ent�o o
    n� que estava no topo � removido da pilha, e o n� seguinte passa a ser o novo topo.
    */
    free(temp); // Libera a mem�ria do n� a ser removido da pilha

    return 1; // Cliente removido com sucesso
}

int buscarCliente(Pilha* pilha, int cpf) {
    Node* atual = pilha->topo; // Ponteiro atual recebe o topo da pilha
    int posicao = 1; //  Inicializa-se a vari�vel posicao com o valor 1, que ser� utilizado para armazenar a posi��o do cliente na pilha.

    while (atual != NULL) { // Percorre a pilha at� o final
        if (atual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na pilha, se for encontrado:
            return posicao; // Retorna a posi��o do cliente na pilha (come�ando de 1)
        }
        // Se n�o:
        atual = atual->prox; // Atualiza o ponteiro atual para apontar para o pr�ximo n� na pilha
        posicao++; // Incrementa para acompanhar a ida para o pr�ximo, indicando que passamos para o pr�ximo n� na pilha, e continuar a busca
    }

    return -1; // Cliente n�o encontrado
}

int sacarValor(Pilha* pilha, int cpf, float valor) {
    Node* atual = pilha->topo;

    while (atual != NULL) { // Percorre a pilha at� o final
        if (atual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na pilha, se for encontrado:
            if (atual->cliente.saldo < valor) {
                return -1; // Saldo insuficiente
            }
            // Se cliente tiver saldo dispon�vel:
            atual->cliente.saldo -= valor;
            return 1; // Saque realizado com sucesso
        }

        atual = atual->prox; // Atualiza o ponteiro atual para apontar para o pr�ximo n� na pilha e continuar a busca pelo CPF
    }

    return 0; // Cliente n�o encontrado
}

void imprimirPilha(Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha esta vazia.\n");
    } else {
        printf("Conteudo da pilha:\n");
        Node* atual = pilha->topo; // N� atual recebe o topo da pilha
        int posicao = 1;

        while (atual != NULL) { // Percorre a pilha at� o final
            printf("Cliente %d:\n", posicao); // Imprime as informa��es de cada elemento da pilha, por meio do n� atual da struct No,e o ponteiro campo cliente que entra na struct TCliente
            printf("Nome: %s\n", atual->cliente.nome);
            printf("Endereco: %s\n", atual->cliente.endereco);
            printf("Telefone: %s\n", atual->cliente.tel);
            printf("CPF: %d\n", atual->cliente.cpf);
            printf("Saldo: %.2f\n", atual->cliente.saldo);
            printf("--------------------\n");
        atual = atual->prox; // Atualiza o ponteiro atual para apontar para o pr�ximo n� na pilha e continuar a impress�o
        posicao++; // Incrementa para acompanhar a ida para o pr�ximo, e continuar a impress�o das informa��es
    }
}
}
