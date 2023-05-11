#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

int main() {
    Fila filaClientes;
    int capacidadeInicial = 10; // Capacidade inicial da fila
    inicializarFila(&filaClientes, capacidadeInicial); // Inicializa a fila

    int opcao;
    int cpf;
    float valor;
    TCliente novoCliente;

    do {
        printf("\nDigite a opcao desejada:\n");
        printf("1. Verificar se um cliente esta cadastrado\n");
        printf("2. Fazer retirada de uma determinada quantia de um cliente\n");
        printf("3. Inserir um novo cliente\n");
        printf("4. Retirar um cliente\n");
        printf("5. Imprimir clientes\n");
        printf("6. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o CPF do cliente: ");
                scanf("%d", &cpf);
                if (buscarFila(&filaClientes, cpf) == -1) {
                    printf("Cliente nao cadastrado.\n");
                } else {
                    printf("Cliente cadastrado.\n");
                }
                break;
            case 2:
                printf("Digite o CPF do cliente: ");
                scanf("%d", &cpf);
                printf("Digite o valor a ser sacado: ");
                scanf("%f", &valor);
                int resultadoSaque = sacarFila(&filaClientes, cpf, valor);
                if (resultadoSaque == 0) {
                    printf("Cliente nao encontrado.\n");
                } else if (resultadoSaque == -1) {
                    printf("Saldo insuficiente.\n");
                } else {
                    printf("Saque realizado com sucesso.\n");
                }
                break;
            case 3:
                printf("Digite o CPF do novo cliente: ");
                scanf("%d", &novoCliente.cpf);
printf("Digite o nome do novo cliente: ");
scanf("%s", novoCliente.nome);
fflush(stdin);
printf("Digite o endereco do novo cliente: ");
scanf("%s", novoCliente.endereco);
fflush(stdin);
printf("Digite o telefone do novo cliente: ");
scanf("%s", novoCliente.tel);
fflush(stdin);
printf("Digite o saldo do novo cliente: ");
scanf("%f", &novoCliente.saldo);
            int resultadoInsercao = inserirCliente(&filaClientes, novoCliente);
            if (resultadoInsercao == 0) {
                printf("Fila cheia.\n");
            } else if (resultadoInsercao == -1) {
                printf("Cliente ja cadastrado.\n");
            } else {
                printf("Cliente inserido com sucesso.\n");
            }
            break;
        case 4:
            printf("Digite o CPF do cliente a ser removido: ");
            scanf("%d", &cpf);
            int resultadoRemocao = removerCliente(&filaClientes, cpf);
            if (resultadoRemocao == 0) {
                printf("Cliente nao encontrado.\n");
            } else {
                printf("Cliente removido com sucesso.\n");
            }
            break;
        case 5:
            imprimirFila(&filaClientes);
            break;
        case 6:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
    }

} while (opcao != 6);

free(filaClientes.dados);

return 0;
}
