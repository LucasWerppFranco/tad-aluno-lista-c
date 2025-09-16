#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define ARQUIVO "alunos.txt"

typedef struct {
    char nome[50];
    int rm;
    float nota;
} Aluno;

Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;

void salvarAlunos() {
    FILE *f = fopen(ARQUIVO, "w");
    if (!f) {
        printf("Erro ao salvar alunos.\n");
        return;
    }
    for (int i = 0; i < totalAlunos; i++) {
        fprintf(f, "%s;%d;%.2f\n", alunos[i].nome, alunos[i].rm, alunos[i].nota);
    }
    fclose(f);
}

void carregarAlunos() {
    FILE *f = fopen(ARQUIVO, "r");
    if (!f) return; 

    while (fscanf(f, "%49[^;];%d;%f\n",
                  alunos[totalAlunos].nome,
                  &alunos[totalAlunos].rm,
                  &alunos[totalAlunos].nota) == 3) {
        totalAlunos++;
        if (totalAlunos >= MAX_ALUNOS) break;
    }
    fclose(f);
}

void adicionarAluno(const char *nome, int rm, float nota) {
    if (totalAlunos >= MAX_ALUNOS) {
        printf("Limite maximo de alunos atingido!\n");
        return;
    }
    strcpy(alunos[totalAlunos].nome, nome);
    alunos[totalAlunos].rm = rm;
    alunos[totalAlunos].nota = nota;
    totalAlunos++;
    salvarAlunos();
    printf("Aluno adicionado com sucesso!\n");
}

void listarAlunos() {
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Alunos ---\n");
    for (int i = 0; i < totalAlunos; i++) {
        printf("%d) Nome: %s | RM: %06d | Nota: %.2f\n",
               i + 1, alunos[i].nome, alunos[i].rm, alunos[i].nota);
    }
    printf("-----------------------\n");
}

void alterarNotaPorRM(int rm, float novaNota) {
    for (int i = 0; i < totalAlunos; i++) {
        if (alunos[i].rm == rm) {
            alunos[i].nota = novaNota;
            salvarAlunos();
            printf("Nota do aluno %s alterada para %.2f\n", alunos[i].nome, novaNota);
            return;
        }
    }
    printf("Aluno com RM %06d nao encontrado.\n", rm);
}

#endif

