#include <stdio.h>
#include <stdlib.h>
#include "arvoreex2ate8.h"

int main() {
    struct No* raiz = NULL;
    int opcao, valor;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir um valor\n");
        printf("2. Remover um valor\n");
        printf("3. Buscar um valor (n�o recursiva)\n");
        printf("4. Encontrar o pai de um n�\n");
        printf("5. Imprimir o caminho at� um n� folha\n");
        printf("6. Contar o n�mero de n�s maiores que um valor\n");
        printf("7. Encontrar o irmao do no\n");
        printf("8. Calcular a altura da �rvore\n");
        printf("9. Imprimir a �rvore em ordem\n");
        printf("10. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = removerNo(raiz, valor);
                break;
            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                struct No* encontrado = buscarNo(raiz, valor);
                if (encontrado != NULL) {
                    printf("Valor encontrado na �rvore.\n");
                } else {
                    printf("Valor n�o encontrado na �rvore.\n");
                }
                break;
            case 4:
                printf("Digite o valor do n� para encontrar o pai: ");
                scanf("%d", &valor);
                struct No* pai = encontrarPai(raiz, valor);
                if (pai != NULL) {
                    printf("Pai do n� %d: %d\n", valor, pai->dado);
                } else {
                    printf("N� n�o encontrado ou � a raiz.\n");
                }
                break;
            case 5:
                printf("Digite o valor do n� para imprimir o caminho: ");
                scanf("%d", &valor);
                printf("Caminho at� o n� %d: ", valor);
                imprimirCaminho(raiz, valor);
                break;
            case 6:
                printf("Digite o valor do n� para contar os maiores: ");
                scanf("%d", &valor);
                int quantidadeMaiores = contarMaiores(raiz, valor);
                printf("Quantidade de n�s maiores que %d: %d\n", valor, quantidadeMaiores);
                break;
            case 7:
               printf("Digite o valor do no: ");
               scanf("%d", &valor);
               struct No* no = encontrarIrmao(raiz, valor);
                 if (no != NULL) {
                   printf("O irmao do no %d e: %d\n", valor, no->dado);
                 } else {
                   printf("O no %d nao possui irmao.\n", valor);
                 }
                break;
            case 8:
                printf("Altura da �rvore: %d\n", calcularAltura(raiz));
                break;
            case 9:
                printf("�rvore em ordem: ");
                imprimirEmOrdem(raiz);
                printf("\n");
                break;
            case 10:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Op��o inv�lida.\n");
                break;
        }
    } while (opcao != 10);

    return 0;
}
