#include <stdio.h>
#include "aluno.h"

int main() {
    carregarAlunos(); 
    int opcao;

    do {
        printf("\n===== Sistema de Alunos =====\n");
        printf("1 - Adicionar aluno\n");
        printf("2 - Alterar nota\n");
        printf("3 - Listar alunos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            char nome[50];
            int rm;
            float nota;
            printf("Digite o nome do aluno: ");
            getchar(); 
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0; 
            printf("Digite o RM (6 digitos): ");
            scanf("%d", &rm);
            printf("Digite a nota: ");
            scanf("%f", &nota);
            adicionarAluno(nome, rm, nota);

        } else if (opcao == 2) {
            int rm;
            float novaNota;
            printf("Digite o RM do aluno: ");
            scanf("%d", &rm);
            printf("Digite a nova nota: ");
            scanf("%f", &novaNota);
            alterarNotaPorRM(rm, novaNota);

        } else if (opcao == 3) {
            listarAlunos();

        } else if (opcao == 0) {
            printf("Saindo...\n");

        } else {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;


}
