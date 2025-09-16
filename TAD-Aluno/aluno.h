#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define ARQUIVO "alunos.txt"

typedef struct {
    char nome[50];
    int rm;        // número de 6 dígitos único
    float nota;
} Aluno;

typedef struct {
    Aluno alunos[MAX_ALUNOS];
    int tamanho;
} Lista;

Lista lista = {.tamanho = 0};

// ---------- Funções de Arquivo ----------
void salvarAlunos() {
    FILE f = fopen(ARQUIVO, "w");
    if (!f) {
        printf("Erro ao salvar alunos.\n");
        return;
    }
    for (int i = 0; i < lista.tamanho; i++) {
        fprintf(f, "%s;%d;%.2f\n", lista.alunos[i].nome,
                                   lista.alunos[i].rm,
                                   lista.alunos[i].nota);
    }
    fclose(f);
}

void carregarAlunos() {
    FILEf = fopen(ARQUIVO, "r");
    if (!f) return;

    while (fscanf(f, "%49[^;];%d;%f\n",
                  lista.alunos[lista.tamanho].nome,
                  &lista.alunos[lista.tamanho].rm,
                  &lista.alunos[lista.tamanho].nota) == 3) {
        lista.tamanho++;
        if (lista.tamanho >= MAX_ALUNOS) break;
    }
    fclose(f);
}

// ---------- Operações ----------
void adicionarAluno(const char *nome, int rm, float nota) {
    if (lista.tamanho >= MAX_ALUNOS) {
        printf("Limite maximo de alunos atingido!\n");
        return;
    }
strcpy(lista.alunos[lista.tamanho].nome, nome);
    lista.alunos[lista.tamanho].rm = rm;
    lista.alunos[lista.tamanho].nota = nota;
    lista.tamanho++;
    salvarAlunos();
    printf("Aluno adicionado com sucesso!\n");
}

void listarAlunos() {
    if (lista.tamanho == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Alunos ---\n");
    for (int i = 0; i < lista.tamanho; i++) {
        printf("%d) Nome: %s | RM: %06d | Nota: %.2f\n",
               i + 1,
               lista.alunos[i].nome,
               lista.alunos[i].rm,
               lista.alunos[i].nota);
    }
    printf("-----------------------\n");
}

void alterarNotaPorRM(int rm, float novaNota) {
    for (int i = 0; i < lista.tamanho; i++) {
        if (lista.alunos[i].rm == rm) {
            lista.alunos[i].nota = novaNota;
            salvarAlunos();
            printf("Nota do aluno %s alterada para %.2f\n",
                   lista.alunos[i].nome, novaNota);
            return;
        }
    }
    printf("Aluno com RM %06d nao encontrado.\n", rm);
}

void removerUltimo(Lista *l) {
    if (l->tamanho > 0) {
        printf("Removendo aluno: %s (RM: %06d)\n",
               l->alunos[l->tamanho - 1].nome,
               l->alunos[l->tamanho - 1].rm);
        l->tamanho--;
        salvarAlunos();
    } else {
        printf("Nao ha alunos para remover.\n");
    }
}

#endif