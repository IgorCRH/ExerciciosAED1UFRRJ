#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cpf;
    char nome[100];
    char endereco[100];
    char tel[15];
    float saldo;
} TCliente; // Define a estrutura TCliente, ou a das informa��es dos clientes

typedef struct No {
    TCliente cliente;
    struct No* proximo;
} No; // Define a estrutura No, que representa um n� da lista encadeada, aonde cada n� � um elemento (cliente) da lista

/**
Define a estrutura ListaEncadeada, que representa a lista encadeada em si.
Ela possui um ponteiro para o primeiro n� da lista e um inteiro para armazenar o tamanho da lista.
*/

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inicializarLista(ListaEncadeada* lista) { // Inicializa a lista, sem elementos e com tamanho 0, e vai aumentando conforme forem sendo inseridos clientes/elementos
    lista->primeiro = NULL;
    lista->tamanho = 0;
}

/**
Fun��o de busca de um cliente por meio do CPF. Recebe o CPF a partir da main como argumento e compara os armazenados na lista
Percorre os n�s da lista at� encontrar um n� com o CPF correspondente ou at� chegar ao final da lista
Se encontrar, retorna o �ndice, se n�o, retornar� -1
*/

int buscarLista(ListaEncadeada* lista, int cpf) {
    No* atual = lista->primeiro; // Come�a apontando para o primeiro elemento
    int indice = 0;

    while (atual != NULL) { // Loop que percorre a lista enquanto n�o atingir o final dela
        if (atual->cliente.cpf == cpf) { // Compara
            return indice; // Retorna caso o CPF seja encontrado na lista
        }
        atual = atual->proximo; // Atualiza o ponteiro atual para apontar para o pr�ximo n� da lista
        indice++; // Incrementa a vari�vel �ndice para acompanhar a posi��o atual na lista, o que permite mostrar em qual �ndice o cliente com o CPF buscado foi encontrado.
    }

    return -1;
}

int inserirCliente(ListaEncadeada* lista, TCliente cliente) { // Insere novo cliente
    if (buscarLista(lista, cliente.cpf) != -1) { // Chama a fun��o buscarLista para a compara��o do CPF
        return -1; // Cliente j� cadastrado
    }

    No* novoNo = (No*)malloc(sizeof(No)); // Se n�o for encontrado, come�a a inserir o novo cliente, alocando mem�ria para o novo n�(elemento/cliente)
    if (novoNo == NULL) { // Verifica se a aloca��o foi bem sucedida
        return 0; // Falha na aloca��o de mem�ria
    }

    novoNo->cliente = cliente; // Preenche o novo n� com as informa��es do ponteiro cliente (da struct TCliente)
    novoNo->proximo = lista->primeiro;
    /**
    O ponteiro proximo do novo n� � atualizado para apontar para o primeiro n� da lista atual
    Isso significa que o novo n� ser� inserido no in�cio da lista, e o n� anteriormente apontado pelo primeiro n� agora ser� o segundo n�.
    */
    lista->primeiro = novoNo; // O ponteiro primeiro da lista � atualizado para apontar para o novo n�, qie agora ser� o primeiro
    lista->tamanho++; // Tamanho da lista � incrementado.

    return 1; // Cliente cadastrado com sucesso
}

int removerCliente(ListaEncadeada* lista, int cpf) {
    No* atual = lista->primeiro; // Ponteiro atual � inicializado com o primeiro n� da lista
    No* anterior = NULL;

    while (atual != NULL) { // Loop que percorre a lista enquanto n�o atingir o final dela
        if (atual->cliente.cpf == cpf) { // Recebe o CPF por argumento da main e compara com os CPFs armazenados
            if (anterior == NULL) { // Se o n�(elemento) a ser removido � o primeiro da lista, ou seja, n�o h� n�s anteriores:
                lista->primeiro = atual->proximo; // Ponteiro primeiro da lista � atualizado para apontar para o pr�ximo n� (atual->proximo)
            } else { // Se o n�(elemento) a ser removido n�o � o primeiro da lista, e h� n�s anteriores
                anterior->proximo = atual->proximo; // Ponteiro proximo do n� anterior � atualizado para apontar para o pr�ximo n� do n� atual (posi��o atual da lista), pulando o n� a ser removido.
            }
            free(atual); // Libera a mem�ria alocada para o n�(elemento) atual
            lista->tamanho--; // Decrementa o tamanho da lista
            return 1; // Cliente removido com sucesso
        }

        anterior = atual; // Se o CPF n�o for igual, ent�o o ponteiro anterior � atualizado para apontar para o n� atual
        atual = atual->proximo; // Ponteiro atual � movido para o pr�ximo n�, continuando a busca
    }

    return 0; // Cliente n�o encontrado
}

int inserirClienteMeio(ListaEncadeada* lista, TCliente cliente, int posicao) {
    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente j� cadastrado
    }

    if (posicao <= 0 || posicao > lista->tamanho) {
        return 0; // Posi��o inv�lida
    }

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        return 0; // Falha na aloca��o de mem�ria
    }

    novoNo->cliente = cliente;

    if (posicao == 1) {
        novoNo->proximo = lista->primeiro;
        lista->primeiro = novoNo;
    } else {
        No* atual = lista->primeiro;
        int indice = 1;

        while (indice < posicao - 1) {
            atual = atual->proximo;
            indice++;
        }

        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
    }

    lista->tamanho++;

    return 1; // Cliente inserido com sucesso
}

int sacarLista(ListaEncadeada* lista, int cpf, float valor) {
    No* atual = lista->primeiro; // Inicializa o n� atual com o primeiro elemento da lista

    while (atual != NULL) { // Loop que percorre a lista enquanto n�o atingir o final dela
        if (atual->cliente.cpf == cpf) { // Recebe o CPF por argumento da main e compara com os CPFs armazenados, se for encontrado:
            if (atual->cliente.saldo >= valor) { // E se o cliente tiver saldo dispon�vel:
                atual->cliente.saldo -= valor; // Realiza-se o saque
                return 1; // Saque realizado com sucesso
            } else {
                return -1; // Saldo insuficiente
            }
        }
        atual = atual->proximo; // Se o CPF n�o for igual ou encontrado, o ponteiro atual � movido para o pr�ximo n�, continuando assim a busca pelo cliente na lista.
    }

    return 0; // Cliente n�o encontrado
}

void imprimirLista(ListaEncadeada* lista) {
    No* atual = lista->primeiro; // Inicializa o n� atual com o primeiro elemento da lista

    printf("Lista de Clientes:\n");
    while (atual != NULL) { // Loop que percorre a lista enquanto n�o atingir o final dela
        printf("CPF: %d\n", atual->cliente.cpf); // Utiliza ponteiro atual, que aponta para cliente, que � ponteiro da struct TCliente com as informa��es
        printf("Nome: %s\n", atual->cliente.nome);
        printf("Endereco: %s\n", atual->cliente.endereco);
        printf("Telefone: %s\n", atual->cliente.tel);
        printf("Saldo: %.2f\n\n", atual->cliente.saldo);

        atual = atual->proximo; // Continua a busca pelas informa��es para a impress�o na lista at� o fim
    }
}
