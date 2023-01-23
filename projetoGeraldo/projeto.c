#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/*
Professor(valores editaveis, mas devem ter default)
- Nome do professor(50 carac)
-Quantidade de disciplinas (no max 5 por semestre)

Disciplina
(Os dados de cada disciplina devem ser informados pelo prof)
(devem ser editaveis, mas devem ter um default)
-Codigo da disciplina(10CHAR)
-Nome da disciplina(50char)
-Ano/semetre(2013 a 2020/ 1 ou 2)
-Quantidade de alunos matriculados(50 alunos por disciplina)
-Quantidade de provas(teoricas)(max de 4)
-Quantidade de trablahos(max de 10)
-Carga horaria prevista(livre, default 60 horas)
-Carga horaria realizada(livre)
-Nota minima pra aprovação(entre 0 e 10), default(5)
-Percentual minimo de frequencia pra aprovação(entre 0 e 100, default
70%)(calculado na carga horaria prevista, nao realizada)

Prova e Trabalho
(devem ser editaveis, mas devem ter um default)
-Nome da prova
-Tipo da prova(P=prova, T trabalho, E exame/rec
-Data da prova(livre, igual ou posterior ao inicio do ano e semeste)
-Peso na média(percentual entre 0 e 100)

Aula
(devem ser editaveis, mas devem ter um default)
-Numero da ordem(livre, comçando do 1)
-Data(livre, igual ou posterior ao inicio do ano e semeste)
-Quantidade de horas da aula(livre, default 2 horas)
-Conteudo(livre, max de 255 carac)

Aluno
Se um aluno ta matriculado em 2 disciplinas ministradas pelo mesmo professor,
seus dados serao armazenados duas vezes (devem ser editaveis, mas devem ter um
default) -Numero (livre, entre 1 e 50) -Nome do aluno(livre, max 50carac) -Nota
obtida em cada prova( entre 0 e 10.0) -Nota na avaliação final(exame/rec)(lvire,
entre 0 e 10.0, nao obrigatoria) -Indicativo de presenca ou falta de cada aula(P
presença, F falta)

*/
typedef struct data {
  int dia, mes, ano;
} Tdata;

typedef struct professor {
  char nome[50];
  int qntd_disciplina;
} Tprof;

typedef struct structavaliacao {
  char nome_avaliacao[50];
  char tipoAval; //'P' 'T' ou 'E'
  Tdata dataAval;
  int peso;
} Tavalicao;

typedef struct aula {
  int numero_ordem;
  Tdata data;
  int qntd_horas_ass;
  char conteudo[256];
} Taula;

typedef struct aluno {
  int numero;
  char nome_aluno[50];
  float nota;
  float nota_final;
  float media;
  int presenca;
  float precencaPer;
} Taluno;

typedef struct ano_semestre {
  char opcao;
  int semestre_ano;
} Tsem;

typedef struct disciplina {
  Tprof professor;
  char cod_disc[10];
  char nome_disc[50];
  Tsem sem_ano;
  int qntd_aluno;
  int qntd_provas;
  int qntd_trabalhos;
  int carga_horaria;
  int carga_realizada;
  float nota_min_aprov;
  float percentual_freq;
} disciplina;

// Criar funcao para verificação

/*
Cotidiano
-A cada aula, o prof faz a lista de presença

Avaliações
-Se a aula eh uma avaliação, alem dos dados comuns, as notas dos alunos devem
ser informadas

Final do Semestre
-Calcular média e percentual de frequencia

Recuperação
-Se a frequencia passou mas a nota nao, ele tem direito a uma prova
final(chamada exame ou recuperacao) A nota obtida sera somada com a media atual
e dividida por 2

Relatorios MUITO DIFICL
-O sistema deve fornecer relatorios em tela ou impressos, a escolha do usuario,
eles devem ser possiveis(no minimo): -situacao individual de cada
aluno(quantidade e percentual de faltas, notas e situacao) -Listagem geral da
turma de uma disciplina(quantidade e percentual de faltas, notas e situação)
        -Notas minima, media e maxima da turma
        -Relação dos alunos que devem realizar a avaliacao final, assim como a
nota necessaria pra cada um deles -Relação dos aprovados ou dos reprovados da
turma, indicando se eh por frequencia ou por nota

Interface
-Dialogos simples, deve passar por consistencia, pra evitar erros de execução de
digitação incorreta

Arquivos
-O usuario pode salvar(e posteriormente consultar) todos os dados de cada
disciplina -Cada disciplina deve ser armazenada em um arquivo diferente(mas eh
melhor armazenar todos os dados de uma mesmoa disciplina em um unico arquivo)
*/

void criar_disciplina(disciplina *disc, FILE **fpdisc, FILE *fdiscis);
void incluir_alunos(int qnt, int ind);
void aula();
void media_freqpercent();

int main() {
    // Declaração de variáveis
    disciplina disc[50];
    FILE *fpdisc[50], *fdiscis;
    int opt, numero;

    // Primeiro funcionamento quando nao tiver disciplinas
    setlocale(LC_ALL, "Portuguese");
    if (!fopen("./disciplinas.txt", "r")) {
        fdiscis = fopen("./disciplinas.txt", "a");
        criar_disciplina(disc, fpdisc, fdiscis);
        fclose(fdiscis);
    }

    
    do{
        // Escolha de opções
        printf("\n\n\n*************Cotidiano************\n");
        printf("Digite a opcao desejada:\n");
        printf("1 - Cotidiano\n");
        printf("2 - Final de semestre\n");
        scanf("%d", &opt);

        switch (opt) {
            case 0:
                break;
            case 1:
                aula();
                break;
            case 2:
                media_freqpercent();
                break;
        }
    } while (opt);
}

// Função pra cadastrar disciplina
void criar_disciplina(disciplina *disc, FILE **fpdisc, FILE *fdiscis) {
    char filename[20];
    int ndisc, i = 1, l, exit = 1;

    do {
        printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
        printf("Cadastro de Disciplinas\n");

        sprintf(filename, "./disciplina%d.txt", i);
        fpdisc[i] = fopen(filename, "w");

        /*Inserção default*/
        disc[i].carga_horaria = 60;
        disc[i].nota_min_aprov = 5.0;
        disc[i].percentual_freq = 70.0;

        printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
        printf("Inserir Disciplina:\n");
        printf("Digite o codigo da disciplina:\nR:");
        scanf("%s", disc[i].cod_disc);
        fprintf(fpdisc[i], "%s ", disc[i].cod_disc);

        printf("Digite o nome da disciplina:\nR:");
        scanf(" %s", disc[i].nome_disc);
        fflush(stdin);
        fprintf(fpdisc[i], "%s ", disc[i].nome_disc);

        printf("Digite a quantidade de alunos:\nR:");
        scanf("%d", &disc[i].qntd_aluno);
        fprintf(fpdisc[i], "%d ", disc[i].qntd_aluno);
        incluir_alunos(disc[i].qntd_aluno, i);

        printf("Anual ou semestral?([a] para anual e [s] para semestral):\nR:");
        scanf(" %c", &disc[i].sem_ano.opcao);
        fprintf(fpdisc[i], "%c ", disc[i].sem_ano.opcao);

        if (disc[i].sem_ano.opcao == 'a' || disc[i].sem_ano.opcao == 'A') {
        printf("Digite o ano da disciplina:\nR:");
        scanf("%d", &disc[i].sem_ano.semestre_ano);
        fprintf(fpdisc[i], "%d ", disc[i].sem_ano.semestre_ano);
        } else if (disc[i].sem_ano.opcao == 's' || disc[i].sem_ano.opcao == 'S') {
        printf("Digite o semestre da disciplina(ex:1 ou 2):\nR:");
        scanf("%d", &disc[i].sem_ano.semestre_ano);
        fprintf(fpdisc[i], "%d ", disc[i].sem_ano.semestre_ano);
        }

        printf("Digite a quantidade de provas:\nR:");
        scanf("%d", &disc[i].qntd_provas);
        fprintf(fpdisc[i], "%d ", disc[i].qntd_provas);

        printf("Digite a quantidade de trabalhos:\nR:");
        scanf("%d", &disc[i].qntd_trabalhos);
        fprintf(fpdisc[i], "%d ", disc[i].qntd_trabalhos);

        printf("Digite a quantidade de horas previstas(Carga Horaria):\nR:");
        scanf("%d", &disc[i].carga_horaria);
        fprintf(fpdisc[i], "%d ", disc[i].carga_horaria);

        printf("Digite a quantidade de horas realizada(Carga Horaria):\nR:");
        scanf("%d", &disc[i].carga_realizada);
        fprintf(fpdisc[i], "%d ", disc[i].carga_realizada);

        printf("Digite a nota minima para aprovacao(entre 0.0 e 10.0):\nR:");
        scanf("%f", &disc[i].nota_min_aprov);
        fprintf(fpdisc[i], "%.2f ", disc[i].nota_min_aprov);

        printf("Digite o percentual minimo de frequencia pra aprovação(entre 0 e "
            "100)(baseado na carga horaria prevista):\nR:");
        scanf("%f", &disc[i].percentual_freq);
        fprintf(fpdisc[i], "%.2f ", disc[i].percentual_freq);

        fclose(fpdisc[i]);
        printf("Deseja adicionar mais uma disciplina?[0]Para sair e [1]Para "
            "Continuar\nR:");
        scanf("%d", &exit);
        i++;
    } while (exit != 0);

    for (l = 1; l < i; l++) {
        fprintf(fdiscis, "%s %d ", disc[l].nome_disc, l);
    }
    return;
}

// Função para criar alunos para determinada disciplina
void incluir_alunos(int qnt, int ind) {
    FILE *incluirAlunos;
    Taluno alunos[qnt];
    char filename[20];
    int i;

    sprintf(filename, "./alunos%d.txt", ind);
    incluirAlunos = fopen(filename, "w");

    for (i = 1; i <= qnt; i++) {
        printf("Digite o nome do aluno %d:", i);
        scanf("%s", alunos[i].nome_aluno);
        fprintf(incluirAlunos, "%s ", alunos[i].nome_aluno);
        fprintf(incluirAlunos, "%d ", i);
        fprintf(incluirAlunos, "0,00 ");
        fprintf(incluirAlunos, "0,00 ");
        fprintf(incluirAlunos, "0,00 ");
        fprintf(incluirAlunos, "0 ");
        fprintf(incluirAlunos, "0,00\nacabou");
    }
    fclose(incluirAlunos);
    return;
}

// Função para adicionar aulas/trabalhos/provas/exame
void aula() {
    Taula aula_dada;
    disciplina disciplinaSub;
    Tavalicao prova_dada;
    Taluno aluno[50];
    char bonhon[20],busca[20],filename[20],filename2[20],busca3[20],busca5,testacabou[20];
    int i=1,j=1,exit=1,opcao,busca2,busca4,notaProva;
    FILE *materias, *aula, *alunos;
    int buscaint;

    printf("\nDigite o nome da disciplina ministrada:\nR: ");
    scanf("%s", bonhon);
    materias = fopen("disciplinas.txt", "r");

    while (exit) {
        fscanf(materias, "%s %d ", busca, &busca2);
        if (strcmp(busca, bonhon) == 0) {
            exit = 0;
        }
    }

    printf("\nQue tipo de ação cotidiana é:\nR: ");
    printf("1-Inserção de aula:\n");
    printf("2-Inserção de Prova:\n");
    scanf("%d", &opcao);

        sprintf(filename, "./aulas%d.txt", busca2);
        aula = fopen(filename, "a");
        sprintf(filename2, "./alunos%d.txt", busca2);
        alunos = fopen(filename2, "r");

        do {
            fflush(stdin);
            fscanf(alunos, "%s", testacabou);
            if (strcmp(testacabou, "acabou") != 0) {
                strcpy(aluno[j].nome_aluno, testacabou);
                fscanf(alunos, " %d %f %f %f %d %f", &aluno[j].numero, &aluno[j].nota,&aluno[j].nota_final,&aluno[j].media,&aluno[j].presenca,&aluno[j].precencaPer);
                j++;
            }
    } while (strcmp(testacabou, "acabou") != 0);
        fclose(alunos);

        printf("\nDigite o número de ordem:\nR: ");
        scanf("%d", &aula_dada.numero_ordem);
        fprintf(aula, "%d ", aula_dada.numero_ordem);

        printf("Digite a data da aula:\nR: ");
        scanf("%d/%d/%d", &aula_dada.data.dia, &aula_dada.data.mes,&aula_dada.data.ano);
        fprintf(aula, "%d/%d/%d ", aula_dada.data.dia, aula_dada.data.mes,aula_dada.data.ano);

        printf("Digite a quantidade de horas associadas a disciplina:\nR: ");
        scanf("%d", &aula_dada.qntd_horas_ass);
        fprintf(aula, "%d ", aula_dada.qntd_horas_ass);

        if (opcao == 2) {
            fprintf(aula, "prova/trabalho ");

            printf("Digite o nome da avaliação/trabalho:\nR: ");
            scanf("%s", prova_dada.nome_avaliacao);
            fprintf(aula, "%s ", prova_dada.nome_avaliacao);

            printf("Digite o tipo da avaliação/trabalho(P para prova - T para trabalho - E para exames finais):\nR: ");
            scanf(" %c", &prova_dada.tipoAval);
            fprintf(aula, "%c ", prova_dada.tipoAval);

            prova_dada.dataAval.dia = aula_dada.data.dia;
            prova_dada.dataAval.mes = aula_dada.data.mes;
            prova_dada.dataAval.ano = aula_dada.data.ano;

            printf("Digite o peso da avaliação/trabalho(Ex. 2 para prova com peso 2):\nR: ");
            scanf("%d", &prova_dada.peso);
            fprintf(aula, "%d", prova_dada.peso);
        } else if (opcao == 1) {
            printf("Digite qual o conteudo ministrado na aula:\nR: ");
            fflush(stdin);
            scanf("%s", aula_dada.conteudo);
            fprintf(aula, "%s ", aula_dada.conteudo);
        }
        fprintf(aula,"\n-1");
        for (i = 1; i < j; i++) {
            printf("Digite a frequencia nas aulas(P - presença e F - falta) para o aluno %s:\nR: ", aluno[i].nome_aluno);
            scanf(" %c", &busca5);
            fflush(stdin);
            if (busca5 == 'P') {
                aluno[i].presenca = aluno[i].presenca + 1;
                if(opcao == 2) {
                    if(prova_dada.tipoAval == 'P' || prova_dada.tipoAval == 'T') {
                        printf("Digite a nota para o aluno %s na avaliação/trabalho %s:\nR: ", aluno[i].nome_aluno,prova_dada.nome_avaliacao);
                        scanf("%d",&notaProva);
                        aluno[i].nota = aluno[i].nota + notaProva * prova_dada.peso;
                    } else {
                        printf("Digite a nota para o aluno %s no exame final:\nR: ", aluno[i].nome_aluno);
                        scanf("%d",&notaProva);
                        aluno[i].nota_final = aluno[i].nota_final + notaProva;
                    }
                }
            }
        }

        sprintf(filename2, "./alunos%d.txt", busca2);
        alunos = fopen(filename2, "w");
        for (i = 1; i < j; i++) {
            fprintf(alunos, "%s %d %.2f %.2f %.2f %d %.2f\n", aluno[i].nome_aluno,aluno[i].numero,aluno[i].nota,aluno[i].nota_final,aluno[i].media,aluno[i].presenca,aluno[i].precencaPer);
        }
        fprintf(alunos, "acabou");
        
        fclose(aula);
        fclose(alunos);
        fclose(materias);

    return;
}

// Função para fazer calculo de media e do percentual de frequencia
void media_freqpercent() {
    char bonhon[20],busca[20],filename[20],testacabou[20];
    int busca2,i,j=1,exit=1,k=0,pesoCounter=0,test2=1;
    Taluno aluno[50];
    Taula aula_dada[60];
    Tavalicao prova_dada[20];
    FILE  *materias,*alunos,*aulas;

    printf("\nDigite o nome da disciplina a ser calculada a media e o percentual de frequência:\nR: ");
    scanf("%s", bonhon);
    materias = fopen("disciplinas.txt", "r");

    while (exit) {
        fscanf(materias, "%s %d ", busca, &busca2);
        if (strcmp(busca, bonhon) == 0) {
            exit = 0;
        }
    }
    
    //calcular a soma dos pesos e da frequencia por disciplinas
    sprintf(filename, "./aulas%d.txt", busca2);
    aulas = fopen(filename, "r");

    do {
        fscanf(aulas,"%d",&test2);
        if (test2 != -1) {
            aula_dada[k].numero_ordem = test2;
            fscanf(aulas,"%d/%d/%d %d",&aula_dada[k].data.dia,&aula_dada[k].data.mes,&aula_dada[k].data.ano,&aula_dada[k].qntd_horas_ass);
            fscanf(aulas,"%s",aula_dada[k].conteudo);
            if (strcmp(aula_dada[k].conteudo,"prova/trabalho") == 0) {
                fscanf(aulas,"%s %c %d",prova_dada[k].nome_avaliacao,&prova_dada[k].tipoAval,&prova_dada[k].peso);
                pesoCounter = pesoCounter + prova_dada[k].peso;
            }
            k++;
        }
    } while (!feof(aulas));

    sprintf(filename, "./alunos%d.txt", busca2);
    alunos = fopen(filename, "r");
    do {
        fscanf(alunos, "%s", testacabou);
        if (strcmp(testacabou, "acabou") != 0) {
            strcpy(aluno[j].nome_aluno, testacabou);
            fscanf(alunos, " %d %f %f %f %d %f", &aluno[j].numero, &aluno[j].nota,&aluno[j].nota_final,&aluno[j].media,&aluno[j].presenca,&aluno[j].precencaPer);
            if(aluno[j].nota != 0) {
                aluno[j].media = aluno[j].nota/pesoCounter;
            }
            if(aluno[j].presenca != 0) {
                aluno[j].precencaPer = (aluno[j].presenca*100)/k;
            }
            j++;
        }
    } while (strcmp(testacabou, "acabou") != 0);
    fclose(alunos);

    alunos = fopen(filename, "w");
    for(i=1;i<j;i++) {
        fprintf(alunos, "%s ", aluno[i].nome_aluno);
        fprintf(alunos, "%d ",  aluno[i].numero);
        fprintf(alunos, "%.2f ", aluno[i].nota);
        fprintf(alunos, "%.2f ", aluno[i].nota_final);
        fprintf(alunos, "%.2f ", aluno[i].media);
        fprintf(alunos, "%d ", aluno[i].presenca);
        fprintf(alunos, "%.2f\n", aluno[i].precencaPer);
    }
    fprintf(alunos, "acabou");
    
    printf("\nMédia e frequêcia calculada com sucesso");

    fclose(aulas);
    fclose(alunos);
    fclose(materias);

    return;
}

void c() {
    
}