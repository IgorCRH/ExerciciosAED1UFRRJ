#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cpf;
    char nome[50];
    char endereco[50];
    char tel[10];
    float saldo;
} TCliente; // Definição da estrutura TCliente que representa as informações dos clientes

typedef struct No {
    TCliente cliente;
    struct No* prox;
} No; // Definição da estrutura Node que representa um nó da fila encadeada

typedef struct {
    No* inicio;
    No* fim;
    int quantidade;
} Fila; // Definição da estrutura Fila, com os ponteiros inicio e fim para o primeiro e último nó da fila, respectivamente

void inicializarFila(Fila* fila) { // Inicializa a fila sem elementos
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
}

int filaVazia(Fila* fila) { // Se a fila ainda permanecer vazia:
    return (fila->quantidade == 0);
}

void enfileirar(Fila* fila, TCliente cliente) { // Função que é chamada para inserir elemento
    No* novoNo = (No*)malloc(sizeof(No)); // Aloca memória para um novo nó
    novoNo->cliente = cliente; // Preenche o campo cliente do novo nó com o cliente passado como argumento pelo mainBanco
    novoNo->prox = NULL; // Define o campo prox do novo nó como nulo

    if (filaVazia(fila)) { // Verifica se a fila está vazia
        fila->inicio = novoNo; // Se estiver, o novo nó é o primeiro
    } else { // Se não estiver:
        fila->fim->prox = novoNo; // O campo prox do último nó da fila aponta para o novo nó, para manter a ordem correta entre o antigo último nó e o novo
    }

    fila->fim = novoNo; // Atualiza o ponteiro fim para apontar para o novo nó, que agora é o último nó da fila
    fila->quantidade++; // Incrementa a quantidade de elementos na fila
}

TCliente desenfileirar(Fila* fila) { // Função que pode ser chamada para remover elemento
    if (filaVazia(fila)) { // Verifica se a fila está vazia
        TCliente clienteVazio; // Se estiver, não há elementos a serem desenfileirados
        clienteVazio.cpf = -1;
        return clienteVazio;
    }
    // Se não estiver vazia:
    No* noRemovido = fila->inicio; // Ponteiro noRemovido é criado e aponta para o primeiro nó da fila
    TCliente cliente = noRemovido->cliente; // Cliente do nó removido é atribuído à variável cliente da struct TCliente
    fila->inicio = fila->inicio->prox; // Ponteiro inicio da fila é atualizado para apontar para o próximo nó da fila, tornando o segundo nó o novo primeiro nó
    fila->quantidade--; // Decrementa o tamanho da fila

    if (fila->inicio == NULL) { // Verifica se a fila não estará agora vazia após a remoção do único elemento.
        fila->fim = NULL; // Nesse caso, o campo fim também é definido como NULL, indicando que não há mais nenhum elemento na fila.
    }

    free(noRemovido); // Libera a memória alocada para o nó que foi removido
    return cliente;
}

int buscarFila(Fila* fila, int cpf) { // Função de buscar o CPF
    No* noAtual = fila->inicio; // Nó noAtual aponta para o primeiro elemento da fila
    int contador = 0;

    while (noAtual != NULL) { // Loop que percorre toda a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            return contador; // Retorna a posição dele
        }

        noAtual = noAtual->prox; // Se não for encontrado, noAtual já aponta para o próximo elemento da fila para continuação da busca
        contador++; // Incrementa a variável para acompanhar a continuação da busca de forma a ter a posição atual correta do cliente
    }

    return -1; // Cliente não encontrado
}

int inserirCliente(Fila* fila, TCliente cliente) {
    if (buscarFila(fila, cliente.cpf) != -1) { // Chama a função de busca do CPF para comparar se ele não já está cadastrado
        return -1; // Cliente já está cadastrado
    }

    enfileirar(fila, cliente); // Se não for encontrado, chama a função de inserir novo elemento
    return 1;
}

int removerCliente(Fila* fila, int cpf) {
    No* noAnterior = NULL;
    No* noAtual = fila->inicio; // noAtual recebe o início da fila.

    while (noAtual != NULL) { // Loop que percorre a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            if (noAnterior == NULL) { // Se noAnterior for NULL, significa que o nó atual é o primeiro nó da fila
                fila->inicio = noAtual->prox; // Então, atualiza-se fila->inicio para apontar para o próximo nó
            } else { // Se não: (**->PROX = PULA)
                noAnterior->prox = noAtual->prox; // Atualiza-se o campo prox do nó anterior para apontar para o próximo nó
            }

            if (noAtual == fila->fim) { // Verifica se o nó atual é o último nó da fila
                fila->fim = noAnterior; // Se for, atualiza-se fila->fim para apontar para o nó anterior
            }

            free(noAtual); // Libera a memória alocada para o nó a ser removido
            fila->quantidade--; // Decrementa a quantidade de elementos na fila
            return 1;
        }

        noAnterior = noAtual;
        noAtual = noAtual->prox; // Continua a busca caso o CPF não seja encontrado, e o loop ainda estiver sendo executado
    }

    return 0; // Retorna 0 para indicar que o cliente não foi removido.
}

int sacarFila(Fila* fila, int cpf, float valor) {
    No* noAtual = fila->inicio; // noAtual recebe o início da fila

    while (noAtual != NULL) { // Loop que percorre a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            if (noAtual->cliente.saldo < valor) { // Se não tiver saldo disponível
                return -1;
            }

            noAtual->cliente.saldo -= valor; // Se tiver, realiza-se o saque
            return 1;
        }

        noAtual = noAtual->prox; // Continua a busca caso o CPF não seja encontrado, e o loop ainda estiver sendo executado
    }

    return 0;
}

int depositarFila(Fila* fila, int cpf, float valor) { // Função de depósito
    No* noAtual = fila->inicio; // noAtual recebe o início da fila

    while (noAtual != NULL) { // Loop que percorre a fila
        if (noAtual->cliente.cpf == cpf) { // Compara o CPF passado por argumento pelo mainBanco com os registrados na fila, se for encontrado:
            noAtual->cliente.saldo += valor; // Se for encontrado, realiza-se o depósito
            return 1;
        }

        noAtual = noAtual->prox; // Continua a busca caso o CPF não seja encontrado, e o loop ainda estiver sendo executado
    }

    return 0;
}

void imprimirFila(Fila* fila) {
    No* noAtual = fila->inicio; // noAtual recebe o início da fila

    while (noAtual != NULL) { // Loop que percorre a fila
        printf("CPF: %d\n", noAtual->cliente.cpf); // Imprime as informações de cada elemento da fila, por meio do nó atual da struct No,e o ponteiro campo cliente que entra na struct TCliente
        printf("Nome: %s\n", noAtual->cliente.nome);
        printf("Endereco: %s\n", noAtual->cliente.endereco);
        printf("Telefone: %s\n", noAtual->cliente.tel);
        printf("Saldo: %.2f\n", noAtual->cliente.saldo);
        printf("-----------------\n");

        noAtual = noAtual->prox; // Atualiza o ponteiro atual para apontar para o próximo nó na fila e continuar a impressão
    }
}

void liberarFila(Fila* fila) { // Remover a fila
    No* noAtual = fila->inicio;
    No* noRemovido;

    while (noAtual != NULL) { // Loop que percorre a fila
        noRemovido = noAtual; // Armazena o ponteiro para o nó atual que será removido
        noAtual = noAtual->prox; // Atualiza o ponteiro noAtual para o próximo nó, que também será removido
        free(noRemovido); // Libera a memória ocupada pelo nó removido
    }

    fila->inicio = NULL; // Início e FIM são redefinidos como NULL, indicando que a fila está vazia
    fila->fim = NULL;
    fila->quantidade = 0; // Quantidade como 0 para indicar que não há mais elementos na fila
}
