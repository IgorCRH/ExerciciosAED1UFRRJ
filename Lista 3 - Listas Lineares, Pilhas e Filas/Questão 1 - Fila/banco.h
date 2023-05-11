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

typedef struct { // Struct Fila para o programa em tipo Fila
    int capacidade;
    TCliente* dados;
    int inicio; // Índice do primeiro elemento da fila
    int fim; // Índice do último elemento da fila
    int quantidade; // Quantidade de elementos na fila
} Fila;

void inicializarFila(Fila* fila, int capacidade) { // Fila e Capacidade são passadas por argumento pela main
    // Variáveis são inicializadas
    fila->capacidade = capacidade;
    fila->dados = (TCliente*)malloc(capacidade * sizeof(TCliente));
    fila->inicio = 0;
    fila->fim = -1;
    fila->quantidade = 0;
}

int filaVazia(Fila* fila) {
    return (fila->quantidade == 0); // Se a fila estiver vazia
}

int filaCheia(Fila* fila) {
    return (fila->quantidade == fila->capacidade); // Se a quantidade de elementos da fila estiver igual a sua capacidade, ela está cheia
}

void enfileirar(Fila* fila, TCliente cliente) { // Função usada para inserir elementos
    if (filaCheia(fila)) {
        printf("Erro: fila cheia\n");
        return;
    }

// fila->fim +1 incrementa o valor do índice fim para representar a inserção do novo elemento
    fila->fim = (fila->fim + 1) % fila->capacidade; // Avança o índice circularmente de forma modular, garantindo que o índice seja atualizado dentro dos limites da capacidade da fila
    fila->dados[fila->fim] = cliente; //  atribui o objeto cliente e seus dados à posição indicada pelo índice fim na lista de dados da fila.
    fila->quantidade++; // Incrementa o contador da quantidade de elementos na fila
}

TCliente desenfileirar(Fila* fila) { // Função usada para remoção de elementos
    if (filaVazia(fila)) { // Verifica se a fila está vazia
        printf("Erro: fila vazia\n");
        TCliente clienteVazio;
        clienteVazio.cpf = -1; // CPF inválido para indicar erro
        return clienteVazio;
    }

    TCliente cliente = fila->dados[fila->inicio]; // Armazena na variável cliente, o que está no início da fila
    fila->inicio = (fila->inicio + 1) % fila->capacidade; // Avança o índice circularmente para indicar o novo início da fila
    fila->quantidade--; // Decrementa o contador da quantidade de elementos na fila

    return cliente; // Retorna o cliente removido da fila
}

int buscarFila(Fila* fila, int cpf) {
    if (filaVazia(fila)) {
        return -1; // Fila vazia, cliente não encontrado
    }

    int posicao = fila->inicio; // Conta a partir do início da fila, inicializando o contador posição como tal
    int contador = 0; // Inicializa o contador para controlar a quantidade de iterações

    while (contador < fila->quantidade) { // Enquanto a quantidade de elementos da fila não for alcançada, o loop será executado, para percorrer a fila
        if (fila->dados[posicao].cpf == cpf) {
            return contador;
        }

        posicao = (posicao + 1) % fila->capacidade; // Avança o índice circularmente (com o módulo para manter a atualização dentro dos limites da capacidade da linha) para obter o próximo elemento na fila
        contador++; // Incrementa o contador para controlar a quantidade de iterações
    }

    return -1; // Cliente não encontrado
}

int inserirCliente(Fila* fila, TCliente cliente) {
    if (filaCheia(fila)) {
        return 0; // Fila cheia, não é possível cadastrar
    }

    if (buscarFila(fila, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    enfileirar(fila, cliente); // Chama a função enfileirar para inserir novo elemento
    return 1; // Cliente cadastrado com sucesso
}

int removerCliente(Fila* fila, int cpf) {
    if (filaVazia(fila)) {
        return 0; // Fila vazia, cliente não encontrado
    }

    int posicao = buscarFila(fila, cpf); // Busca a posição do cliente na fila pelo CPF
    if (posicao == -1) {
        return 0; // Cliente não encontrado (CPF não está cadastrado)
    }

    // Movendo os elementos para frente para preencher o espaço vazio
    int posicaoAtual = (fila->inicio + posicao) % fila->capacidade; // Posição atual do cliente na fila
    int proximaPosicao = (posicaoAtual + 1) % fila->capacidade; // Calcula a próxima posição a ser movida
    /**
    // Loop é executado enquanto a proximaPosicao não atingir o valor correspondente à posição do último elemento da fila, ou seja,
    até que todos os elementos tenham sido movidos adequadamente.
    */
    while (proximaPosicao != (fila->fim + 1) % fila->capacidade) {
 // (fila->fim + 1) % fila->capacidade para garantir que o resultado esteja dentro dos limites da capacidade da fila
        fila->dados[posicaoAtual] = fila->dados[proximaPosicao]; // Copia o elemento da proximaPosicao para a posicaoAtual, movendo-o uma posição para trás
        posicaoAtual = proximaPosicao; // Atualiza a posição atual
        proximaPosicao = (proximaPosicao + 1) % fila->capacidade; // Calcula a próxima posição a ser movida NOVAMENTE
    }

    fila->fim = (fila->fim - 1 + fila->capacidade) % fila->capacidade; // Atualiza o índice do último elemento
    fila->quantidade--; // Decrementa a quantidade de elementos na fila

    return 1; // Cliente removido com sucesso
}


int sacarFila(Fila* fila, int cpf, float valor) {
    if (filaVazia(fila)) {
        return 0; // Fila vazia, cliente não encontrado
    }

    int posicao = buscarFila(fila, cpf);
    if (posicao == -1) {
        return 0; // Cliente não encontrado
    }

    if (fila->dados[posicao].saldo < valor) {
        return -1; // Saldo insuficiente
    }

    fila->dados[posicao].saldo -= valor;
    return 1; // Saque realizado com sucesso
}

void imprimirFila(Fila *fila) {
    printf("Fila de Clientes:\n");
    for (int i = fila->inicio; i <= fila->fim; i++) {
            printf("Cliente %d:\n", i+1);
            printf("Nome: %s\n", fila->dados[i].nome);
            printf("Endereco: %s\n", fila->dados[i].endereco);
            printf("Telefone: %s\n", fila->dados[i].tel);
            printf("CPF: %d\n", fila->dados[i].cpf);
            printf("Saldo: %.2f\n", fila->dados[i].saldo);
            printf("--------------------\n");
    }
}

