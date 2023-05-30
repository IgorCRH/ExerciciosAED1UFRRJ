#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[100];
} Alunos;

typedef struct {
    Alunos* dados;
    int tamanho;
    int capacidade;
} ListaSequencial;

void inicializarLista(ListaSequencial* lista, int capacidade) {
    lista->dados = (Alunos*)malloc(capacidade * sizeof(Alunos));
    lista->tamanho = 0;
    lista->capacidade = capacidade;
}

void inserirAluno(ListaSequencial* lista, int matricula, const char* nome) {
    if (lista->tamanho == lista->capacidade) {
        printf("Lista cheia. Não é possível inserir mais elementos.\n");
        return;
    }

    Alunos aluno;
    aluno.matricula = matricula;
    strncpy(aluno.nome, nome, sizeof(aluno.nome));

    lista->dados[lista->tamanho] = aluno;
    lista->tamanho++;
}

void removerRepetidos(ListaSequencial* lista) {
    if (lista->tamanho == 0) {
        printf("Lista vazia. Não há repetidos para remover.\n");
        return;
    }

    int i, j, k; // Variáveis de controle do loop
    for (i = 0; i < lista->tamanho; i++) { // Percorre toda a lista
        for (j = i + 1; j < lista->tamanho; j++) { // Loop para comparar o elemento atual com os elementos seguintes
            if (lista->dados[i].matricula == lista->dados[j].matricula) { // Se a matrícula do atual for igual a do seguinte:
                for (k = j; k < lista->tamanho - 1; k++) { // Loop para deslocar os elementos seguintes para preencher o espaço deixado pela remoção
                    lista->dados[k] = lista->dados[k + 1]; // Desloca o elemento subsequente para preencher a posição atual
                }
                lista->tamanho--; // Decrementa o tamanho da lista para oficializar a remoção
                j--; // Decrementa o valor de j para atualizá-lo para outras comparações
            }
            }
        }
    }
}

void imprimirLista(ListaSequencial* lista) {
    if (lista->tamanho == 0) {
        printf("A lista está vazia.\n");
        return;
    }

    printf("------------\n");
    int i;
    for (i = 0; i < lista->tamanho; i++) {
        printf("Matrícula: %d, Nome: %s\n", lista->dados[i].matricula, lista->dados[i].nome);
    }
}

int contarElementos(ListaSequencial* lista) {
    return lista->tamanho;
}

int main() {
    ListaSequencial lista;
    inicializarLista(&lista, 100);

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

    imprimirLista(&lista);
    removerRepetidos(&lista);
    imprimirLista(&lista);

    int numElementos = contarElementos(&lista);
    printf("A lista possui %d elementos\n", numElementos);

    free(lista.dados);

    return 0;
}
