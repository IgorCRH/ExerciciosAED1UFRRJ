#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
} Numeros;

typedef struct No {
    Numeros num;
    struct No* proximo;
} No;

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inserirNumero(ListaEncadeada* lista, int numentrada) {
    No* novoNo = (No*)malloc(sizeof(No)); // Aloca a memória para o novo nó, o novo número
    novoNo->num.numero = numentrada; // Preenche o campo numero com o valor numentrada pela main
    novoNo->proximo = NULL; // Como há um novo nó, o próximo ainda não foi definido
    /**
    Isso é importante porque, ao percorrer a lista encadeada posteriormente, o programa pode verificar se
    o ponteiro proximo é NULL, o que indica que o nó atual é o último nó da lista e não há mais nós a seguir.
    */

    if (lista->primeiro == NULL) { // Se a lista estiver vazia, o novo nó se torna o primeiro
        lista->primeiro = novoNo;
    } else {
        No* atual = lista->primeiro; // Se não, percorre a lista até o último nó
        while (atual->proximo != NULL) { // Percorre a lista encadeada
            atual = atual->proximo; // Se não for NULL, avança para o próximo nó, atualizando o ponteiro atual
            // Atualiza o ponteiro atual para apontar para o próximo nó na lista a cada iteração, até o último nó da lista ser alcançado
        }
        // Adicionar o novo nó no final da lista
        atual->proximo = novoNo;
    }
    // Incrementar o tamanho da lista
    lista->tamanho++;
}

void inserirNumeroInverso(ListaEncadeada* lista, int numentrada) { // Cria a segunda lista que será preenchida com a ordem inversa da primeira
    No* novoNo = (No*)malloc(sizeof(No)); // Aloca a memória para os elementos que virão
    novoNo->num.numero = numentrada; // Preenche
    novoNo->proximo = lista->primeiro; // Define o próximo nó do novo nó como o primeiro nó da lista atual

    lista->primeiro = novoNo; // Define o novo nó como o primeiro nó da lista atual, tornando-o o novo início da lista

    lista->tamanho++; // Incrementa
}

void exibirLista(No* atual) { // Exibe a lista original percorrendo por meio do while
    while (atual != NULL) {
        printf("%d\n", atual->num.numero);
        atual = atual->proximo; // Avança para o próximo a cada iteração para a impressão, até chegar ao final
    }
}

void exibirListaInversa(No* atual) { // Exibe a lista original, só que inversa em nova lista
    if (atual == NULL) { // Verifica se chegamos ao final da lista
        return; // Se chegarmos ao final da lista (nó atual NULL), retorna
    }
    exibirListaInversa(atual->proximo); // Caso ainda não chegar ao final, faz chamada recursiva para a própria função e o próximo nó, ou seja o último nó é chamado primeiro
    printf("%d\n", atual->num.numero);
}

int main() {
    ListaEncadeada lista;
    lista.primeiro = NULL;
    lista.tamanho = 0;

    int numentrada;
    char continuar = 'S';

    printf("Digite os numeros (digite 'N' ou 'n' para parar):\n");

    while (continuar != 'N' && continuar != 'n') {
        printf("Numero: ");
        scanf("%d", &numentrada);

        inserirNumero(&lista, numentrada);

        printf("Continuar? (S/N): ");
        scanf(" %c", &continuar);
    }

    printf("Primeira lista:\n");
    exibirLista(lista.primeiro);

    ListaEncadeada segundaLista;
    segundaLista.primeiro = NULL;
    segundaLista.tamanho = 0;

    No* atual = lista.primeiro;
    while (atual != NULL) {
        inserirNumeroInverso(&segundaLista, atual->num.numero);
        atual = atual->proximo;
    }

    printf("Segunda lista (ordem inversa):\n");
    exibirLista(segundaLista.primeiro);

    return 0;
}
