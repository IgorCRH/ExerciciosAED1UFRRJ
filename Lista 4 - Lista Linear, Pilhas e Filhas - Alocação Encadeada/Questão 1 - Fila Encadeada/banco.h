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

typedef struct No {
    TCliente cliente;
    struct No* prox;
} No; // Defini��o da estrutura Node que representa um n� da fila encadeada

typedef struct {
    No* inicio;
    No* fim;
    int quantidade;
} Fila; // Defini��o da estrutura Fila, com os ponteiros inicio e fim para o primeiro e �ltimo n� da fila, respectivamente

void inicializarFila(Fila* fila) { // Inicializa a fila sem elementos
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
}

int filaVazia(Fila* fila) { // Se a fila ainda permanecer vazia:
    return (fila->quantidade == 0);
}

void enfileirar(Fila* fila, TCliente cliente) { // Fun��o que � chamada para inserir elemento
    No* novoNo = (No*)malloc(sizeof(No)); // Aloca mem�ria para um novo n�
    novoNo->cliente = cliente; // Preenche o campo cliente do novo n� com o cliente passado como argumento pelo mainBanco
    novoNo->prox = NULL; // Define o campo prox do novo n� como nulo

    if (filaVazia(fila)) { // Verifica se a fila est� vazia
        fila->inicio = novoNo; // Se estiver, o novo n� � o primeiro
    } else { // Se n�o estiver:
        fila->fim->prox = novoNo; // O campo prox do �ltimo n� da fila aponta para o novo n�, para manter a ordem correta entre o antigo �ltimo n� e o novo
    }

    fila->fim = novoNo; // Atualiza o ponteiro fim para apontar para o novo n�, que agora � o �ltimo n� da fila
    fila->quantidade++; // Incrementa a quantidade de elementos na fila
}

TCliente desenfileirar(Fila* fila) { // Fun��o que pode ser chamada para remover elemento
    if (filaVazia(fila)) { // Verifica se a fila est� vazia
        TCliente clienteVazio; // Se estiver, n�o h� elementos a serem desenfileirados
        clienteVazio.cpf = -1;
        return clienteVazio;
    }
    // Se n�o estiver vazia:
    No* noRemovido = fila->inicio; // Ponteiro noRemovido � criado e aponta para o primeiro n� da fila
    TCliente cliente = noRemovido->cliente; // Cliente do n� removido � atribu�do � vari�vel cliente da struct TCliente
    fila->inicio = fila->inicio->prox; // Ponteiro inicio da fila � atualizado para apontar para o pr�ximo n� da fila, tornando o segundo n� o novo primeiro n�
    fila->quantidade--; // Decrementa o tamanho da fila

    if (fila->inicio == NULL) { // Verifica se a fila n�o estar� agora vazia ap�s a remo��o do �nico elemento.
        fila->fim = NULL; // Nesse caso, o campo fim tamb�m � definido como NULL, indicando que n�o h� mais nenhum elemento na fila.
    }

    free(noRemovido); // Libera a mem�ria alocada para o n� que foi removido
    return cliente;
}

int buscarFila(Fila* fila, int cpf) { // Fun��o de buscar o CPF
    No* noAtual = fila->inicio; // N� noAtual aponta para o primeiro elemento da fila
    int contador = 0;

    while (noAtual != NULL) { // Loop que percorre toda a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            return contador; // Retorna a posi��o dele
        }

        noAtual = noAtual->prox; // Se n�o for encontrado, noAtual j� aponta para o pr�ximo elemento da fila para continua��o da busca
        contador++; // Incrementa a vari�vel para acompanhar a continua��o da busca de forma a ter a posi��o atual correta do cliente
    }

    return -1; // Cliente n�o encontrado
}

int inserirCliente(Fila* fila, TCliente cliente) {
    if (buscarFila(fila, cliente.cpf) != -1) { // Chama a fun��o de busca do CPF para comparar se ele n�o j� est� cadastrado
        return -1; // Cliente j� est� cadastrado
    }

    enfileirar(fila, cliente); // Se n�o for encontrado, chama a fun��o de inserir novo elemento
    return 1;
}

int removerCliente(Fila* fila, int cpf) {
    No* noAnterior = NULL;
    No* noAtual = fila->inicio; // noAtual recebe o in�cio da fila.

    while (noAtual != NULL) { // Loop que percorre a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            if (noAnterior == NULL) { // Se noAnterior for NULL, significa que o n� atual � o primeiro n� da fila
                fila->inicio = noAtual->prox; // Ent�o, atualiza-se fila->inicio para apontar para o pr�ximo n�
            } else { // Se n�o: (**->PROX = PULA)
                noAnterior->prox = noAtual->prox; // Atualiza-se o campo prox do n� anterior para apontar para o pr�ximo n�
            }

            if (noAtual == fila->fim) { // Verifica se o n� atual � o �ltimo n� da fila
                fila->fim = noAnterior; // Se for, atualiza-se fila->fim para apontar para o n� anterior
            }

            free(noAtual); // Libera a mem�ria alocada para o n� a ser removido
            fila->quantidade--; // Decrementa a quantidade de elementos na fila
            return 1;
        }

        noAnterior = noAtual;
        noAtual = noAtual->prox; // Continua a busca caso o CPF n�o seja encontrado, e o loop ainda estiver sendo executado
    }

    return 0; // Retorna 0 para indicar que o cliente n�o foi removido.
}

int sacarFila(Fila* fila, int cpf, float valor) {
    No* noAtual = fila->inicio; // noAtual recebe o in�cio da fila

    while (noAtual != NULL) { // Loop que percorre a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            if (noAtual->cliente.saldo < valor) { // Se n�o tiver saldo dispon�vel
                return -1;
            }

            noAtual->cliente.saldo -= valor; // Se tiver, realiza-se o saque
            return 1;
        }

        noAtual = noAtual->prox; // Continua a busca caso o CPF n�o seja encontrado, e o loop ainda estiver sendo executado
    }

    return 0;
}

int depositarFila(Fila* fila, int cpf, float valor) { // Fun��o de dep�sito
    No* noAtual = fila->inicio; // noAtual recebe o in�cio da fila

    while (noAtual != NULL) { // Loop que percorre a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            noAtual->cliente.saldo += valor; // Se for encontrado, realiza-se o dep�sito
            return 1;
        }

        noAtual = noAtual->prox; // Continua a busca caso o CPF n�o seja encontrado, e o loop ainda estiver sendo executado
    }

    return 0;
}

void imprimirFila(Fila* fila) {
    No* noAtual = fila->inicio; // noAtual recebe o in�cio da fila

    while (noAtual != NULL) { // Loop que percorre a fila
        printf("CPF: %d\n", noAtual->cliente.cpf); // Imprime as informa��es de cada elemento da fila, por meio do n� atual da struct No,e o ponteiro campo cliente que entra na struct TCliente
        printf("Nome: %s\n", noAtual->cliente.nome);
        printf("Endereco: %s\n", noAtual->cliente.endereco);
        printf("Telefone: %s\n", noAtual->cliente.tel);
        printf("Saldo: %.2f\n", noAtual->cliente.saldo);
        printf("-----------------\n");

        noAtual = noAtual->prox; // Atualiza o ponteiro atual para apontar para o pr�ximo n� na fila e continuar a impress�o
    }
}

void liberarFila(Fila* fila) { // Remover a fila
    No* noAtual = fila->inicio;
    No* noRemovido;

    while (noAtual != NULL) { // Loop que percorre a fila
        noRemovido = noAtual; // Armazena o ponteiro para o n� atual que ser� removido
        noAtual = noAtual->prox; // Atualiza o ponteiro noAtual para o pr�ximo n�, que tamb�m ser� removido
        free(noRemovido); // Libera a mem�ria ocupada pelo n� removido
    }

    fila->inicio = NULL; // In�cio e FIM s�o redefinidos como NULL, indicando que a fila est� vazia
    fila->fim = NULL;
    fila->quantidade = 0; // Quantidade como 0 para indicar que n�o h� mais elementos na fila
}
