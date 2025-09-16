#include <stdio.h>
#include "aluno.h"

#define ARQUIVO "alunos.txt"

int main() {
    Lista lista;
    if (carregarListaArquivo(&lista, ARQUIVO)) {
        printf("Dados carregados de %s.\n", ARQUIVO);
    } else {
        printf("Nenhum dado encontrado, iniciando lista vazia.\n");
        lista.tamanho = 0;
    }

    int opcao;

    do {
        printf("\n=== Gerenciador de Alunos ===\n");
        printf("1. Inserir aluno\n");
        printf("2. Alterar notas\n");
        printf("3. Remover último aluno\n");
        printf("4. Buscar aluno por RM\n");
        printf("5. Calcular média das médias\n");
        printf("6. Listar todos os alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirAluno(&lista);
                break;
            case 2:
                alterarNotaAluno(&lista);
                break;
            case 3:
                removerUltimo(&lista);
                break;
            case 4: {
                int rm;
                printf("Digite o RM para buscar: ");
                scanf("%d", &rm);
                int idx = buscarAlunoPorRM(lista, rm);
                if (idx == -1) {
                    printf("Aluno com RM %d não encontrado.\n", rm);
                } else {
                    Aluno a = lista.dados[idx];
                    float media = (a.nota1 + a.nota2 + a.nota3) / 3.0f;
                    printf("Aluno encontrado: RM: %d, Nome: %s, Nota1: %.2f, Nota2: %.2f, Nota3: %.2f, Média: %.2f\n",
                           a.rm, a.nome, a.nota1, a.nota2, a.nota3, media);
                }
                break;
            }
            case 5: {
                float media = calcularMedia(lista);
                printf("Média das médias dos alunos: %.2f\n", media);
                break;
            }
            case 6:
                listarAlunos(lista);
                break;
            case 0:
                printf("Salvando dados e saindo...\n");
                if (salvarListaArquivo(lista, ARQUIVO)) {
                    printf("Dados salvos em %s.\n", ARQUIVO);
                } else {
                    printf("Erro ao salvar dados.\n");
                }
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}