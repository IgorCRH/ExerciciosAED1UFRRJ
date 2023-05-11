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
    int inicio; // �ndice do primeiro elemento da fila
    int fim; // �ndice do �ltimo elemento da fila
    int quantidade; // Quantidade de elementos na fila
} Fila;

void inicializarFila(Fila* fila, int capacidade) { // Fila e Capacidade s�o passadas por argumento pela main
    // Vari�veis s�o inicializadas
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
    return (fila->quantidade == fila->capacidade); // Se a quantidade de elementos da fila estiver igual a sua capacidade, ela est� cheia
}

void enfileirar(Fila* fila, TCliente cliente) { // Fun��o usada para inserir elementos
    if (filaCheia(fila)) {
        printf("Erro: fila cheia\n");
        return;
    }

// fila->fim +1 incrementa o valor do �ndice fim para representar a inser��o do novo elemento
    fila->fim = (fila->fim + 1) % fila->capacidade; // Avan�a o �ndice circularmente de forma modular, garantindo que o �ndice seja atualizado dentro dos limites da capacidade da fila
    fila->dados[fila->fim] = cliente; //  atribui o objeto cliente e seus dados � posi��o indicada pelo �ndice fim na lista de dados da fila.
    fila->quantidade++; // Incrementa o contador da quantidade de elementos na fila
}

TCliente desenfileirar(Fila* fila) { // Fun��o usada para remo��o de elementos
    if (filaVazia(fila)) { // Verifica se a fila est� vazia
        printf("Erro: fila vazia\n");
        TCliente clienteVazio;
        clienteVazio.cpf = -1; // CPF inv�lido para indicar erro
        return clienteVazio;
    }

    TCliente cliente = fila->dados[fila->inicio]; // Armazena na vari�vel cliente, o que est� no in�cio da fila
    fila->inicio = (fila->inicio + 1) % fila->capacidade; // Avan�a o �ndice circularmente para indicar o novo in�cio da fila
    fila->quantidade--; // Decrementa o contador da quantidade de elementos na fila

    return cliente; // Retorna o cliente removido da fila
}

int buscarFila(Fila* fila, int cpf) {
    if (filaVazia(fila)) {
        return -1; // Fila vazia, cliente n�o encontrado
    }

    int posicao = fila->inicio; // Conta a partir do in�cio da fila, inicializando o contador posi��o como tal
    int contador = 0; // Inicializa o contador para controlar a quantidade de itera��es

    while (contador < fila->quantidade) { // Enquanto a quantidade de elementos da fila n�o for alcan�ada, o loop ser� executado, para percorrer a fila
        if (fila->dados[posicao].cpf == cpf) {
            return contador;
        }

        posicao = (posicao + 1) % fila->capacidade; // Avan�a o �ndice circularmente (com o m�dulo para manter a atualiza��o dentro dos limites da capacidade da linha) para obter o pr�ximo elemento na fila
        contador++; // Incrementa o contador para controlar a quantidade de itera��es
    }

    return -1; // Cliente n�o encontrado
}

int inserirCliente(Fila* fila, TCliente cliente) {
    if (filaCheia(fila)) {
        return 0; // Fila cheia, n�o � poss�vel cadastrar
    }

    if (buscarFila(fila, cliente.cpf) != -1) {
        return -1; // Cliente j� cadastrado
    }

    enfileirar(fila, cliente); // Chama a fun��o enfileirar para inserir novo elemento
    return 1; // Cliente cadastrado com sucesso
}

int removerCliente(Fila* fila, int cpf) {
    if (filaVazia(fila)) {
        return 0; // Fila vazia, cliente n�o encontrado
    }

    int posicao = buscarFila(fila, cpf); // Busca a posi��o do cliente na fila pelo CPF
    if (posicao == -1) {
        return 0; // Cliente n�o encontrado (CPF n�o est� cadastrado)
    }

    // Movendo os elementos para frente para preencher o espa�o vazio
    int posicaoAtual = (fila->inicio + posicao) % fila->capacidade; // Posi��o atual do cliente na fila
    int proximaPosicao = (posicaoAtual + 1) % fila->capacidade; // Calcula a pr�xima posi��o a ser movida
    /**
    // Loop � executado enquanto a proximaPosicao n�o atingir o valor correspondente � posi��o do �ltimo elemento da fila, ou seja,
    at� que todos os elementos tenham sido movidos adequadamente.
    */
    while (proximaPosicao != (fila->fim + 1) % fila->capacidade) {
 // (fila->fim + 1) % fila->capacidade para garantir que o resultado esteja dentro dos limites da capacidade da fila
        fila->dados[posicaoAtual] = fila->dados[proximaPosicao]; // Copia o elemento da proximaPosicao para a posicaoAtual, movendo-o uma posi��o para tr�s
        posicaoAtual = proximaPosicao; // Atualiza a posi��o atual
        proximaPosicao = (proximaPosicao + 1) % fila->capacidade; // Calcula a pr�xima posi��o a ser movida NOVAMENTE
    }

    fila->fim = (fila->fim - 1 + fila->capacidade) % fila->capacidade; // Atualiza o �ndice do �ltimo elemento
    fila->quantidade--; // Decrementa a quantidade de elementos na fila

    return 1; // Cliente removido com sucesso
}


int sacarFila(Fila* fila, int cpf, float valor) {
    if (filaVazia(fila)) {
        return 0; // Fila vazia, cliente n�o encontrado
    }

    int posicao = buscarFila(fila, cpf);
    if (posicao == -1) {
        return 0; // Cliente n�o encontrado
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

