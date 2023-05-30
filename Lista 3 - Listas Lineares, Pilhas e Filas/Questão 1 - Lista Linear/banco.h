#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // Struct Lista passadas pelo enunciado
    int cpf;
    char nome[50];
    char endereco[50];
    char tel[10];
    float saldo;
} TCliente;

typedef struct {
    int capacidade;
    TCliente* dados;
    int ultimo;
} Lista;

// Funções
void inicializarLista(Lista *lista, int capacidade) { // Inicializa a Lista
    lista->capacidade = capacidade; // Passa e determina a capacidade por parâmetro a partir da main
    lista->dados = (TCliente*) malloc(capacidade * sizeof(TCliente)); // Alocação dinâmica dos dados da struct, que no caso são os dos clientes
    lista->ultimo = -1; // Define que a lista está vazia antes de ter alguém cadastrado
}

int buscarLista(Lista *lista, int cpf) { // Busca CPF do cliente pela lista
    for (int i = 0; i <= lista->ultimo; i++) { // For que vai do 0 até a posição do último cliente da lista
        if (lista->dados[i].cpf == cpf) { // Se encontrar o CPF, comparando o CPF da struct Lista com o que é passado pela main, retorna o índice do elemento na lista
            return i;
        }
    }
    return -1; // Caso contrário, retorna -1 indicando que o elemento não foi encontrado
}

int inserirCliente(Lista* lista, TCliente cliente) {
    if (lista->ultimo == lista->capacidade - 1) {
        return 0; // Lista cheia
    }

    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    lista->ultimo++;
    lista->dados[lista->ultimo] = cliente;

    return 1; // Cliente inserido com sucesso
}

int inserirClienteInicio(Lista* lista, TCliente cliente) {
    if (lista->ultimo == lista->capacidade - 1) {
        return 0; // Lista cheia
    }

    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    for (int i = lista->ultimo; i >= 0; i--) {
        lista->dados[i + 1] = lista->dados[i];
    }

    lista->dados[0] = cliente;
    lista->ultimo++;

    return 1; // Cliente inserido com sucesso
}

int inserirClienteMeio(Lista* lista, TCliente cliente, int posicao) {
    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    if (posicao <= 0 || posicao > lista->ultimo + 2) {
        return 0; // Posição inválida
    }

    if (lista->ultimo == lista->capacidade - 1) {
        return 0; // Lista cheia
    }

    for (int i = lista->ultimo; i >= posicao; i--) {
        lista->dados[i + 1] = lista->dados[i];
    }

    lista->dados[posicao - 1] = cliente;
    lista->ultimo++;

    return 1; // Cliente inserido com sucesso
}

int inserirClienteTermodoMeio(Lista* lista, TCliente cliente) {
    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente já cadastrado
    }

    int posicao = (lista->ultimo + 2) / 2;

    if (lista->ultimo == lista->capacidade - 1) {
        return 0; // Lista cheia
    }

    for (int i = lista->ultimo; i >= posicao; i--) {
        lista->dados[i + 1] = lista->dados[i];
    }

    lista->dados[posicao - 1] = cliente;
    lista->ultimo++;

    return 1; // Cliente inserido com sucesso
}

int removerCliente(Lista *lista, int cpf) { // Remove cliente do sistema
    int posicao = buscarLista(lista, cpf); // Posicao chama a função buscar CPF na lista (sistema)
    if (posicao == -1) { // Se buscar lista encontrar o CPF, retornará -1, então:
        return 0; // cliente não encontrado
    }
    for (int i = posicao; i < lista->ultimo; i++) { // Caso ele seja encontrado, o for é executado da posição do cliente a ser removido até o último
        lista->dados[i] = lista->dados[i + 1]; // Copia cada cliente posterior a ele, para a posição anterior
    }
    lista->ultimo--; // Decrementa o índice do último cliente inserido na lista, indicando que a lista agora contém um cliente a menos
    return 1; // Cliente foi removido
}

int sacarLista(Lista *lista, int cpf, float valor) { // Função de saque
    int posicao = buscarLista(lista, cpf); // Posicao chama a função buscar CPF na lista (sistema)
    if (posicao == -1) { // Se buscar lista encontrar o CPF, retornará -1, então:
        return 0; // cliente não encontrado
    }
    if (lista->dados[posicao].saldo < valor) { // Se for encontrado, e o saldo for menor que a quantia:
        return -1; // saldo insuficiente
    }
    lista->dados[posicao].saldo -= valor; // Se o saldo for maior, então realiza-se o saque
    return 1; // saque realizado com sucesso
}

void imprimirLista(Lista* lista) {
    if (lista->ultimo == -1) {
        printf("Lista vazia.\n");
        return;
    }

    printf("CPF|Nome|Endereco|Telefone|Saldo\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i <= lista->ultimo; i++) {
        TCliente cliente = lista->dados[i];
        printf("%d\t%s\t%s\t%s\t%.2f\n", cliente.cpf, cliente.nome, cliente.endereco, cliente.tel, cliente.saldo);
    }

    printf("------------------------------------------------------------\n");
}
