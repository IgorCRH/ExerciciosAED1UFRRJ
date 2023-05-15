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

void exibirListaInversa(No* atual) {
    if (atual == NULL) { // Verifica se chegamos ao final da lista
        return;  // Se chegarmos ao final da lista (nó atual é NULL), retorna
    }
    exibirListaInversa(atual->proximo);  // Caso ainda não chegar ao final, faz chamada recursiva para a própria função e o próximo nó, ou seja o último nó é chamado primeiro
    printf("Matrícula: %d, Nome: %s\n", atual->aluno.matricula, atual->aluno.nome);
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
printf("Exibindo a lista em ordem inversa:\n");
exibirListaInversa(lista.primeiro);


    return 0;
}
