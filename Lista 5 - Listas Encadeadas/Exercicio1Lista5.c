#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[100];
} Alunos; // Define a estrutura Alunos, com as informações dos elementos

typedef struct No {
    Alunos aluno;
    struct No* proximo;
} No; // Define a estrutura No, que representa um nó da lista encadeada, aonde cada nó é um elemento (cliente) da lista

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inserirAluno(ListaEncadeada* lista, int matricula, const char* nome) { // Inserir Elementos
    // Aloca a memória para o novo nó, o novo aluno
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->aluno.matricula = matricula; // Preenche as informações do novo aluno
    strncpy(novoNo->aluno.nome, nome, sizeof(novoNo->aluno.nome)); // Recebe a variável nome da main e a aloca no campo nome do Aluno
    novoNo->proximo = NULL; // Como há um novo nó, o próximo ainda não foi definido
    /**
    Isso é importante porque, ao percorrer a lista encadeada posteriormente, o programa pode verificar se
    o ponteiro proximo é NULL, o que indica que o nó atual é o último nó da lista e não há mais nós a seguir.
    */

    // Se a lista estiver vazia, o novo nó se torna o primeiro
    if (lista->primeiro == NULL) {
        lista->primeiro = novoNo;
    } else {
        // Percorrer a lista até o último nó
        No* atual = lista->primeiro;
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


int contarElementos(ListaEncadeada* lista) {
    int contador = 0;
    No* atual = lista->primeiro; // Começa apontando para o primeiro elemento
    while (atual != NULL) { // Percorre a lista
        contador++; // Incrementa conforme os nós foram sendo apontados
        atual = atual->proximo; // Atualiza o ponteiro atual para apontar para o próximo nó na lista a cada iteração, até o último nó da lista ser alcançado
    }
    return contador;
}

int main() {
    ListaEncadeada lista;
    lista.primeiro = NULL; // Inicializar a lista vazia
    lista.tamanho = 0;

    int continuar = 1;
    while (continuar) {
        int matricula;
        char nome[100];

        printf("Digite a matricula do aluno (ou 0 para parar): ");
        scanf("%d", &matricula);

        if (matricula == 0) {
            continuar = 0;
        } else {
            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]", nome);

            inserirAluno(&lista, matricula, nome);
        }
    }

    int numElementos = contarElementos(&lista);
    printf("A lista possui %d elementos\n", numElementos);

    // Liberar a memória alocada para os nós da lista
    No* atual = lista.primeiro;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
