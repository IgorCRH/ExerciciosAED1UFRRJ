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

// Fun��es
void inicializarLista(Lista *lista, int capacidade) { // Inicializa a Lista
    lista->capacidade = capacidade; // Passa e determina a capacidade por par�metro a partir da main
    lista->dados = (TCliente*) malloc(capacidade * sizeof(TCliente)); // Aloca��o din�mica dos dados da struct, que no caso s�o os dos clientes
    lista->ultimo = -1; // Define que a lista est� vazia antes de ter algu�m cadastrado
}

int buscarLista(Lista *lista, int cpf) { // Busca CPF do cliente pela lista
    for (int i = 0; i <= lista->ultimo; i++) { // For que vai do 0 at� a posi��o do �ltimo cliente da lista
        if (lista->dados[i].cpf == cpf) { // Se encontrar o CPF, comparando o CPF da struct Lista com o que � passado pela main, retorna o �ndice do elemento na lista
            return i;
        }
    }
    return -1; // Caso contr�rio, retorna -1 indicando que o elemento n�o foi encontrado
}

int inserirCliente(Lista* lista, TCliente cliente) {
    if (lista->ultimo == lista->capacidade - 1) {
        return 0; // Lista cheia
    }

    if (buscarLista(lista, cliente.cpf) != -1) {
        return -1; // Cliente j� cadastrado
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
        return -1; // Cliente j� cadastrado
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
        return -1; // Cliente j� cadastrado
    }

    if (posicao <= 0 || posicao > lista->ultimo + 2) {
        return 0; // Posi��o inv�lida
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
        return -1; // Cliente j� cadastrado
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
    int posicao = buscarLista(lista, cpf); // Posicao chama a fun��o buscar CPF na lista (sistema)
    if (posicao == -1) { // Se buscar lista encontrar o CPF, retornar� -1, ent�o:
        return 0; // cliente n�o encontrado
    }
    for (int i = posicao; i < lista->ultimo; i++) { // Caso ele seja encontrado, o for � executado da posi��o do cliente a ser removido at� o �ltimo
        lista->dados[i] = lista->dados[i + 1]; // Copia cada cliente posterior a ele, para a posi��o anterior
    }
    lista->ultimo--; // Decrementa o �ndice do �ltimo cliente inserido na lista, indicando que a lista agora cont�m um cliente a menos
    return 1; // Cliente foi removido
}

int sacarLista(Lista *lista, int cpf, float valor) { // Fun��o de saque
    int posicao = buscarLista(lista, cpf); // Posicao chama a fun��o buscar CPF na lista (sistema)
    if (posicao == -1) { // Se buscar lista encontrar o CPF, retornar� -1, ent�o:
        return 0; // cliente n�o encontrado
    }
    if (lista->dados[posicao].saldo < valor) { // Se for encontrado, e o saldo for menor que a quantia:
        return -1; // saldo insuficiente
    }
    lista->dados[posicao].saldo -= valor; // Se o saldo for maior, ent�o realiza-se o saque
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
