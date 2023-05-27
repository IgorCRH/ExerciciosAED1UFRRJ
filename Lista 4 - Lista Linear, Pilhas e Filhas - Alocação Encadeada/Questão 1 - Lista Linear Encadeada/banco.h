#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cpf;
    char nome[100];
    char endereco[100];
    char tel[15];
    float saldo;
} TCliente; // Define a estrutura TCliente, ou a das informações dos clientes

typedef struct No {
    TCliente cliente;
    struct No* proximo;
} No; // Define a estrutura No, que representa um nó da lista encadeada, aonde cada nó é um elemento (cliente) da lista

/**
Define a estrutura ListaEncadeada, que representa a lista encadeada em si.
Ela possui um ponteiro para o primeiro nó da lista e um inteiro para armazenar o tamanho da lista.
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
Função de busca de um cliente por meio do CPF. Recebe o CPF a partir da main como argumento e compara os armazenados na lista
Percorre os nós da lista até encontrar um nó com o CPF correspondente ou até chegar ao final da lista
Se encontrar, retorna o índice, se não, retornará -1
*/

int buscarLista(ListaEncadeada* lista, int cpf) {
    No* atual = lista->primeiro; // Começa apontando para o primeiro elemento
    int indice = 0;

    while (atual != NULL) { // Loop que percorre a lista enquanto não atingir o final dela
        if (atual->cliente.cpf == cpf) { // Compara
            return indice; // Retorna caso o CPF seja encontrado na lista
        }
        atual = atual->proximo; // Atualiza o ponteiro atual para apontar para o próximo nó da lista
        indice++; // Incrementa a variável índice para acompanhar a posição atual na lista, o que permite mostrar em qual índice o cliente com o CPF buscado foi encontrado.
    }

    return -1;
}

int inserirCliente(ListaEncadeada* lista, TCliente cliente) { // Insere novo cliente
    if (buscarLista(lista, cliente.cpf) != -1) { // Chama a função buscarLista para a comparação do CPF
        return -1; // Cliente já cadastrado
    }

    No* novoNo = (No*)malloc(sizeof(No)); // Se não for encontrado, começa a inserir o novo cliente, alocando memória para o novo nó(elemento/cliente)
    if (novoNo == NULL) { // Verifica se a alocação foi bem sucedida
        return 0; // Falha na alocação de memória
    }

    novoNo->cliente = cliente; // Preenche o novo nó com as informações do ponteiro cliente (da struct TCliente)
    novoNo->proximo = lista->primeiro;
    /**
    O ponteiro proximo do novo nó é atualizado para apontar para o primeiro nó da lista atual
    Isso significa que o novo nó será inserido no início da lista, e o nó anteriormente apontado pelo primeiro nó agora será o segundo nó.
    */
    lista->primeiro = novoNo; // O ponteiro primeiro da lista é atualizado para apontar para o novo nó, qie agora será o primeiro
    lista->tamanho++; // Tamanho da lista é incrementado.

    return 1; // Cliente cadastrado com sucesso
}

int removerCliente(ListaEncadeada* lista, int cpf) {
    No* atual = lista->primeiro; // Ponteiro atual é inicializado com o primeiro nó da lista
    No* anterior = NULL;

    while (atual != NULL) { // Loop que percorre a lista enquanto não atingir o final dela
        if (atual->cliente.cpf == cpf) { // Recebe o CPF por argumento da main e compara com os CPFs armazenados
            if (anterior == NULL) { // Se o nó(elemento) a ser removido é o primeiro da lista, ou seja, não há nós anteriores:
                lista->primeiro = atual->proximo; // Ponteiro primeiro da lista é atualizado para apontar para o próximo nó (atual->proximo)
            } else { // Se o nó(elemento) a ser removido não é o primeiro da lista, e há nós anteriores
                anterior->proximo = atual->proximo; // Ponteiro proximo do nó anterior é atualizado para apontar para o próximo nó do nó atual (posição atual da lista), pulando o nó a ser removido.
            }
            free(atual); // Libera a memória alocada para o nó(elemento) atual
            lista->tamanho--; // Decrementa o tamanho da lista
            return 1; // Cliente removido com sucesso
        }

        anterior = atual; // Se o CPF não for igual, então o ponteiro anterior é atualizado para apontar para o nó atual
        atual = atual->proximo; // Ponteiro atual é movido para o próximo nó, continuando a busca
    }

    return 0; // Cliente não encontrado
}

int inserirClienteMeio(ListaEncadeada* lista, TCliente cliente, int posicao) {
    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    if (posicao <= 0 || posicao > lista->tamanho) {
        return 0; // Posição inválida
    }

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        return 0; // Falha na alocação de memória
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
    No* atual = lista->primeiro; // Inicializa o nó atual com o primeiro elemento da lista

    while (atual != NULL) { // Loop que percorre a lista enquanto não atingir o final dela
        if (atual->cliente.cpf == cpf) { // Recebe o CPF por argumento da main e compara com os CPFs armazenados, se for encontrado:
            if (atual->cliente.saldo >= valor) { // E se o cliente tiver saldo disponível:
                atual->cliente.saldo -= valor; // Realiza-se o saque
                return 1; // Saque realizado com sucesso
            } else {
                return -1; // Saldo insuficiente
            }
        }
        atual = atual->proximo; // Se o CPF não for igual ou encontrado, o ponteiro atual é movido para o próximo nó, continuando assim a busca pelo cliente na lista.
    }

    return 0; // Cliente não encontrado
}

void imprimirLista(ListaEncadeada* lista) {
    No* atual = lista->primeiro; // Inicializa o nó atual com o primeiro elemento da lista

    printf("Lista de Clientes:\n");
    while (atual != NULL) { // Loop que percorre a lista enquanto não atingir o final dela
        printf("CPF: %d\n", atual->cliente.cpf); // Utiliza ponteiro atual, que aponta para cliente, que é ponteiro da struct TCliente com as informações
        printf("Nome: %s\n", atual->cliente.nome);
        printf("Endereco: %s\n", atual->cliente.endereco);
        printf("Telefone: %s\n", atual->cliente.tel);
        printf("Saldo: %.2f\n\n", atual->cliente.saldo);

        atual = atual->proximo; // Continua a busca pelas informações para a impressão na lista até o fim
    }
}
