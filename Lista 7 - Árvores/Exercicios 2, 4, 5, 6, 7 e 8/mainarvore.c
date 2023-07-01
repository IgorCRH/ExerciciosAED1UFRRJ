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
        printf("3. Buscar um valor (não recursiva)\n");
        printf("4. Encontrar o pai de um nó\n");
        printf("5. Imprimir o caminho até um nó folha\n");
        printf("6. Contar o número de nós maiores que um valor\n");
        printf("7. Encontrar o irmao do no\n");
        printf("8. Calcular a altura da árvore\n");
        printf("9. Imprimir a árvore em ordem\n");
        printf("10. Contar numero de nos da arvore\n");
        printf("11. Imprimir em Pre-Ordem\n");
        printf("12. Imprimir em Pos-Ordem\n");
        printf("13. Imprimir em Ordem Simetrica\n");
        printf("14. Sair\n");
        printf("Escolha uma opção: ");
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
                    printf("Valor encontrado na árvore.\n");
                } else {
                    printf("Valor não encontrado na árvore.\n");
                }
                break;
            case 4:
                printf("Digite o valor do nó para encontrar o pai: ");
                scanf("%d", &valor);
                struct No* pai = encontrarPai(raiz, valor);
                if (pai != NULL) {
                    printf("Pai do nó %d: %d\n", valor, pai->dado);
                } else {
                    printf("Nó não encontrado ou é a raiz.\n");
                }
                break;
            case 5:
                printf("Digite o valor do nó para imprimir o caminho: ");
                scanf("%d", &valor);
                printf("Caminho até o nó %d: ", valor);
                imprimirCaminho(raiz, valor);
                break;
            case 6:
                printf("Digite o valor do nó para contar os maiores: ");
                scanf("%d", &valor);
                int quantidadeMaiores = contarMaiores(raiz, valor);
                printf("Quantidade de nós maiores que %d: %d\n", valor, quantidadeMaiores);
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
                printf("Altura da árvore: %d\n", calcularAltura(raiz));
                break;
            case 9:
                printf("Árvore em ordem: ");
                imprimirEmOrdem(raiz);
                printf("\n");
                break;
            case 10:
                printf("Número de nos na árvore: %d\n", contarNos(raiz));
                contarNos(raiz);
                break;
            case 11:
                printf("Imprimindo a árvore em pre-ordem: ");
                pre_ordem(raiz);
                printf("\n");
                break;
            case 12:
                printf("Imprimindo a árvore em pos-ordem: ");
                pos_ordem(raiz);
                printf("\n");
                break;
            case 13:
                printf("Imprimindo a árvore em ordem simetrica: ");
                sim_ordem(raiz);
                printf("\n");
                break;
            case 14:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 14);

    return 0;
}
