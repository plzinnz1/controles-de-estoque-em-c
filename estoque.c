#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char nomes[100][100];
    int quant[100];
    int total = 0;
    int opcao, qtd, pos;
    char nome[100];
    FILE *arquivo;

    arquivo = fopen("inventory.txt", "r");

    if (arquivo != NULL){
        while (fscanf(arquivo, " %99[^\n]", nomes[total]) == 1){
            if (fscanf(arquivo, "%d", &quant[total]) != 1){
            break;
            }

            total++;

            if (total == 100){
            break;
            }
        }

        fclose(arquivo);
    }

    do {
        printf("\n1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Estoque\n");
        printf("4. Sair\n");
        printf("Opção: ");

        if (scanf("%d", &opcao) != 1){
            printf("Opção inválida! Tente novamente.\n");

            while (getchar() != '\n'){
            }

            continue;
        }

        if (opcao < 1 || opcao > 4){
            printf("Opção inválida! Tente novamente.\n");
        }else if (opcao == 1){
            printf("Nome do item: ");
            scanf(" %99[^\n]", nome);

            printf("Quantidade: ");
            scanf("%d", &qtd);

            pos = -1;

            for (int i = 0; i < total; i++){
                if (strcmp(nomes[i], nome) == 0){
                    pos = i;
                }
            }

            if (pos == -1 && total < 100){
                strcpy(nomes[total], nome);
                quant[total] = qtd;
                total++;
            }else if (pos != -1){
                quant[pos] += qtd;
            }

            arquivo = fopen("inventory.txt", "w");

            if (arquivo != NULL){
                for (int i = 0; i < total; i++){
                 fprintf(arquivo, "%s\n%d\n", nomes[i], quant[i]);
                }

                fclose(arquivo);
            }

            printf("Item adicionado!\n");

        }else if (opcao == 2) {
            printf("Nome do item: ");
            scanf(" %99[^\n]", nome);

            printf("Quantidade a remover: ");
            scanf("%d", &qtd);

            pos = -1;

            for (int i = 0; i < total; i++){
                if (strcmp(nomes[i], nome) == 0){
                  pos = i;
                }
            }

            if (pos == -1){
                printf("Item não encontrado.\n");
            }else if (qtd >= quant[pos]) {
                for (int i = pos; i < total - 1; i++){
                    strcpy(nomes[i], nomes[i + 1]);
                    quant[i] = quant[i + 1];
                }

                total--;
                printf("Item removido do estoque!\n");
            }else{
                quant[pos] -= qtd;
                printf("Quantidade atualizada!\n");
            }

            arquivo = fopen("inventory.txt", "w");

            if (arquivo != NULL){
                for (int i = 0; i < total; i++){
                 fprintf(arquivo, "%s\n%d\n", nomes[i], quant[i]);
                }

                 fclose(arquivo);
            }

        }else if (opcao == 3){
            printf("==============================\n");
            printf("        Estoque Atual\n");
            printf("==============================\n");

            if (total == 0){
                printf("O estoque está vazio.\n");
            }

            for (int i = 0; i < total; i++){
                printf("Nome: %s\n", nomes[i]);
                printf("Quantidade: %d\n\n", quant[i]);
            }
        }

    } while (opcao != 4);

    printf("Até a próxima!\n");

    return 0;
}