#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

TAluno cadastros[10000];

int ler_cadastros(TAluno cadastros[10000]) {
    int i=0,j=0;
    FILE *fp;

    while (!(fp = fopen("./dados.dat", "r"))) {
        return 0;
    }

    while (!feof(fp)) {
        fscanf(fp, "%[^\n] %d", cadastros[i].nome, &cadastros[i].matricula);
        fscanf(fp,"%[^\n] %d %[^\n] %[^\n]", cadastros[i].endereco.endereco, &cadastros[i].endereco.numero,cadastros[i].endereco.cidade,cadastros[i].endereco.estado);
        fscanf(fp,"%d %d %d", &cadastros[i].nascimento.dia, &cadastros[i].nascimento.mes, &cadastros[i].nascimento.ano);
        fscanf(fp,"%d", &cadastros[i].ndis);
        for (j = 0; j < cadastros[i].ndis; j++) {
            fscanf(fp,"%[^\n]", cadastros[i].curriculo[j].nome_disciplina);
            fscanf(fp,"%f %d %d %d %d", cadastros[i].curriculo[j].nota,cadastros[i].curriculo[j].freq, cadastros[i].curriculo[j].condicao,cadastros[i].curriculo[j].semestre, cadastros[i].curriculo[j].ano);
        }
        i++;
    }
    fclose(fp);
}

void alterar_dados(TAluno cadastros[10000], char aluno[50]) {
    int i=0,j=0;
    float nota;
    char disciplina[25];

    while(strcmp(aluno,cadastros[i].nome)) {
        i++;
    }
    puts("Qual disciplina será alterada?\n");
    scanf("%s",disciplina);
    while(strcmp(disciplina,cadastros[i].curriculo[j].nome_disciplina)) {
        j++;
    }
    puts("Qual é a nova nota?\n");
    scanf("%f",cadastros[i].curriculo[j].nota);
}

void salvar_dados(TAluno cadastros[10000],char disciplina[25], int n) {
    int i=0,j=0;
    FILE *fp;

    fp = fopen(disciplina, "w");
    for(i=0; i<n; i++) {
        for(j=0;j< cadastros[i].ndis; j++) {
            if(!strcmp(disciplina,cadastros[i].curriculo[j].nome_disciplina)) {
                if(cadastros[i].curriculo[j].condicao == 1) {
                    printf("%s\n",cadastros[i].nome);
                    fprintf("%s\n",cadastros[i].nome);
                } 
            }
        }
    }

    fclose(fp);
}


