#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
} Numeros; // Define a estrutura Alunos, com as informações dos elementos

typedef struct No {
    Numeros num;
    struct No* proximo;
} No; // Define a estrutura No, que representa um nó da lista encadeada, aonde cada nó é um elemento (cliente) da lista

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inserirNoFim(ListaEncadeada* lista, int numero) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->num.numero = numero;
    novoNo->proximo = NULL;

    if (lista->primeiro == NULL) {
        lista->primeiro = novoNo;
    } else {
        No* atual = lista->primeiro;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }

    lista->tamanho++;
}

void inserirOrdenado(ListaEncadeada* listaOrdenada, int numero) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->num.numero = numero;
    novoNo->proximo = NULL;

    if (listaOrdenada->primeiro == NULL) {
        listaOrdenada->primeiro = novoNo;
        return;
    }

    if (numero < listaOrdenada->primeiro->num.numero) {
        novoNo->proximo = listaOrdenada->primeiro;
        listaOrdenada->primeiro = novoNo;
        return;
    }

    No* anterior = listaOrdenada->primeiro;
    No* atual = anterior->proximo;

    while (atual != NULL && numero >= atual->num.numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = novoNo;
    novoNo->proximo = atual;
}

void remover(ListaEncadeada* lista, int numero) {
    No* anterior = NULL;
    No* atual = lista->primeiro;

    while (atual != NULL) {
        if (atual->num.numero == numero) {
            if (anterior == NULL) {
                lista->primeiro = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            lista->tamanho--;
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }
}

ListaEncadeada criarListaOrdenada(ListaEncadeada* lista) {
    ListaEncadeada listaOrdenada;
    listaOrdenada.primeiro = NULL;
    listaOrdenada.tamanho = 0;

    No* atual = lista->primeiro;
    while (atual != NULL) {
        inserirOrdenado(&listaOrdenada, atual->num.numero);
        atual = atual->proximo;
    }

    return listaOrdenada;
}

int main() {
    ListaEncadeada lista;
    lista.primeiro = NULL;
    lista.tamanho = 0;

    int numentrada;
    char continuar = 'S', remocao; // Variável para controlar a condição de parada

    printf("Digite os numeros (digite 'N' ou 'n' para parar):\n");

    while (continuar != 'N' && continuar != 'n') {
        printf("Numero: ");
        scanf("%d", &numentrada);

        inserirNoFim(&lista, numentrada);

        printf("Continuar? (S/N): ");
        scanf(" %c", &continuar);
    }
ListaEncadeada listaOrdenada = criarListaOrdenada(&lista);
printf("Lista original:\n");
    No* atualOriginal = lista.primeiro;
    while (atualOriginal != NULL) {
        printf("%d ", atualOriginal->num.numero);
        atualOriginal = atualOriginal->proximo;
    }
        printf("\n\nLista ordenada:\n");
    No* atualOrdenada = listaOrdenada.primeiro;
    while (atualOrdenada != NULL) {
        printf("%d ", atualOrdenada->num.numero);
        atualOrdenada = atualOrdenada->proximo;
    }
    printf("\n");
    printf("Deseja remover algum elemento? (S/N)");
    scanf("%s",&remocao);
    if (remocao == 'S' || remocao == 's') {
    int numremove;
    printf("Numero: ");
    scanf("%d", &numremove);
    remover(&lista, numremove);
    }
    return 0;
}

