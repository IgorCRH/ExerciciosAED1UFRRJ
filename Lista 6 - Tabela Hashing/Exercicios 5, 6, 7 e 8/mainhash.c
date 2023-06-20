#include <stdio.h>
#include "tabelahash.h"

int main() {
    int tamanhoTabela;
    printf("Digite o tamanho da tabela hash: ");
    scanf("%d", &tamanhoTabela);
    TabelaHash* tabela = criarTabelaHash(tamanhoTabela);

    int opcao = 0;
    int chave, chave1, chave2, valor;

    while (opcao != 5) {
        printf("\n----- Menu -----\n");
        printf("1. Inserir elemento\n");
        printf("2. Porcentagem Hash\n");
        printf("3. Indice das Colisoes\n");
        printf("4. Quantidade de Colisoes\n");
        printf("5. Quantidade de Elementos\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserir(tabela, chave, valor);
                printf("Elemento inserido com sucesso!\n");
                break;
            case 2:
                printf("Porcentagem da tabela hash: %.2f%%\n", porcentagemHash(tabela));
                break;
            case 3:
                printf("Indices das colisoes:\n");
                indiceColisao(tabela);
                break;
            case 4:
                printf("Quantidade de colisoes: %d\n", quantidadeColisao(tabela));
                break;
            case 5:
                printf("Quantidade de elementos: %d\n", quantidadeElementos(tabela));
                break;
            case 6:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
