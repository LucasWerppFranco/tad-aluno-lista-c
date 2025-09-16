#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOME 50

typedef struct {
    int rm;
    char nome[MAX_NOME];
    float nota1;
    float nota2;
    float nota3;
} Aluno;

typedef struct {
    Aluno dados[MAX_ALUNOS];
    int tamanho;
} Lista;

void alterarNota(Aluno *a, float novaNota1, float novaNota2, float novaNota3);

void removerUltimo(Lista *l);

int buscarAlunoPorRM(Lista l, int rm);

float calcularMedia(Lista l);

void listarAlunos(Lista l);

void inserirAluno(Lista *l);

void alterarNotaAluno(Lista *l);

int salvarListaArquivo(Lista l, const char *nomeArquivo);

int carregarListaArquivo(Lista *l, const char *nomeArquivo);

void alterarNota(Aluno *a, float novaNota1, float novaNota2, float novaNota3) {
    a->nota1 = novaNota1;
    a->nota2 = novaNota2;
    a->nota3 = novaNota3;
}

void removerUltimo(Lista *l) {
    if (l->tamanho > 0) {
        l->tamanho--;
        printf("Último aluno removido com sucesso.\n");
    } else {
        printf("Lista vazia, nada para remover.\n");
    }
}

int buscarAlunoPorRM(Lista l, int rm) {
    for (int i = 0; i < l.tamanho; i++) {
        if (l.dados[i].rm == rm) return i;
    }
    return -1;
}

float calcularMedia(Lista l) {
    float soma = 0;
    for (int i = 0; i < l.tamanho; i++) {
        soma += (l.dados[i].nota1 + l.dados[i].nota2 + l.dados[i].nota3) / 3.0f;
    }
    return (l.tamanho > 0) ? soma / l.tamanho : 0;
}

void listarAlunos(Lista l) {
    if (l.tamanho == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    printf("Lista de alunos:\n");
    printf("RM\tNome\t\tNota1\tNota2\tNota3\tMédia\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < l.tamanho; i++) {
        float media = (l.dados[i].nota1 + l.dados[i].nota2 + l.dados[i].nota3) / 3.0f;
        printf("%d\t%-15s\t%.2f\t%.2f\t%.2f\t%.2f\n",
               l.dados[i].rm, l.dados[i].nome,
               l.dados[i].nota1, l.dados[i].nota2, l.dados[i].nota3, media);
    }
}

void inserirAluno(Lista *l) {
    if (l->tamanho >= MAX_ALUNOS) {
        printf("Lista cheia, não é possível adicionar mais alunos.\n");
        return;
    }
    Aluno novo;
    printf("Digite o RM do aluno: ");
    scanf("%d", &novo.rm);
    getchar();
    if (buscarAlunoPorRM(*l, novo.rm) != -1) {
        printf("Aluno com RM %d já existe.\n", novo.rm);
        return;
    }
    printf("Digite o nome do aluno: ");
    fgets(novo.nome, MAX_NOME, stdin);
    size_t len = strlen(novo.nome);
    if (len > 0 && novo.nome[len-1] == '\n') {
        novo.nome[len-1] = '\0';
    }
    printf("Digite a nota 1 do aluno: ");
    scanf("%f", &novo.nota1);
    printf("Digite a nota 2 do aluno: ");
    scanf("%f", &novo.nota2);
    printf("Digite a nota 3 do aluno: ");
    scanf("%f", &novo.nota3);

    l->dados[l->tamanho] = novo;
    l->tamanho++;
    printf("Aluno inserido com sucesso.\n");
}

void alterarNotaAluno(Lista *l) {
    if (l->tamanho == 0) {
        printf("Lista vazia.\n");
        return;
    }
    int rm;
    printf("Digite o RM do aluno para alterar as notas: ");
    scanf("%d", &rm);
    int idx = buscarAlunoPorRM(*l, rm);
    if (idx == -1) {
        printf("Aluno com RM %d não encontrado.\n", rm);
        return;
    }
    float novaNota1, novaNota2, novaNota3;
    printf("Digite a nova nota 1: ");
    scanf("%f", &novaNota1);
    printf("Digite a nova nota 2: ");
    scanf("%f", &novaNota2);
    printf("Digite a nova nota 3: ");
    scanf("%f", &novaNota3);
    alterarNota(&l->dados[idx], novaNota1, novaNota2, novaNota3);
    printf("Notas alteradas com sucesso.\n");
}

int salvarListaArquivo(Lista l, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        perror("Erro ao abrir arquivo para salvar");
        return 0;
    }
    fprintf(f, "%d\n", l.tamanho);
    for (int i = 0; i < l.tamanho; i++) {
        fprintf(f, "%d %.2f %.2f %.2f %s\n",
                l.dados[i].rm,
                l.dados[i].nota1,
                l.dados[i].nota2,
                l.dados[i].nota3,
                l.dados[i].nome);
    }
    fclose(f);
    return 1;
}

int carregarListaArquivo(Lista *l, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) {
        l->tamanho = 0;
        return 0;
    }
    int n;
    if (fscanf(f, "%d\n", &n) != 1) {
        fclose(f);
        return 0;
    }
    if (n < 0 || n > MAX_ALUNOS) {
        fclose(f);
        return 0;
    }
    l->tamanho = n;
    for (int i = 0; i < n; i++) {
        char linha[256];
        if (!fgets(linha, sizeof(linha), f)) {
            l->tamanho = i;
            fclose(f);
            return 0;
        }
        int rm;
        float nota1, nota2, nota3;
        char nome[MAX_NOME];
        int offset = 0;
        if (sscanf(linha, "%d %f %f %f%n", &rm, &nota1, &nota2, &nota3, &offset) < 4) {
            l->tamanho = i;
            fclose(f);
            return 0;
        }
        char *pNome = linha + offset;
        while (*pNome == ' ') pNome++;
        strncpy(nome, pNome, MAX_NOME-1);
        nome[MAX_NOME-1] = '\0';
        size_t len = strlen(nome);
        if (len > 0 && nome[len-1] == '\n') {
            nome[len-1] = '\0';
        }
        l->dados[i].rm = rm;
        l->dados[i].nota1 = nota1;
        l->dados[i].nota2 = nota2;
        l->dados[i].nota3 = nota3;
        strcpy(l->dados[i].nome, nome);
    }
    fclose(f);
    return 1;
}

#endif