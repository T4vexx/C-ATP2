#include <stdio.h>

typedef struct ender {
    char endereco[50];
    int numero;
    char cidade[20];
    char estado[20];
} TEnder;

typedef struct data {
    int dia;
    int mes;
    int ano;
} TData;

typedef struct disciplina {
    char nome_disciplina[25];
    float nota;
    int freq;
    int condicao,semestre,ano;
} TDisciplina;

typedef struct aluno {
    char nome[50];
    int matricula;
    TEnder endereco;
    TData nascimento;
    int ndis;
    TDisciplina curriculo[100];
} TAluno;

int main() {


    return 0;
}