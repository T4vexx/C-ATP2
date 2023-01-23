#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS
typedef struct data {
    int dia, mes, ano;
} Tdata;

/*
Professor(valores editaveis, mas devem ter default)
- Nome do professor(50 carac)
-Quantidade de disciplinas (no max 5 por semestre)*/
typedef struct professor {
    char nome[50];
    int qntd_disciplina;
} Tprof;

/*
Prova e Trabalho
(devem ser editaveis, mas devem ter um default)
-Nome da prova
-Tipo da prova(P=prova, T trabalho, E exame/rec
-Data da prova(livre, igual ou posterior ao inicio do ano e semeste)
-Peso na média(percentual entre 0 e 100)*/
typedef struct structavaliacao {
    char nome_avaliacao[50];
    char tipoAval; //'P' 'T' ou 'E'
    Tdata dataAval;
    int peso;
} Tavaliacao;

/*
Aula
(devem ser editaveis, mas devem ter um default)
-Numero da ordem(livre, comçando do 1)
-Data(livre, igual ou posterior ao inicio do ano e semeste)
-Quantidade de horas da aula(livre, default 2 horas)
-Conteudo(livre, max de 255 carac)*/
typedef struct aula {
    int numero_ordem;
    Tdata data;
    int qntd_horas_ass;
    char conteudo[256];
} Taula;

/*Aluno
Se um aluno ta matriculado em 2 disciplinas ministradas pelo mesmo professor,
seus dados serao armazenados duas vezes (devem ser editaveis, mas devem ter um
default) -Numero (livre, entre 1 e 50) -Nome do aluno(livre, max 50carac) -Nota
obtida em cada prova( entre 0 e 10.0) -Nota na avaliação final(exame/rec)(lvire,
entre 0 e 10.0, nao obrigatoria) -Indicativo de presenca ou falta de cada aula(P
presença, F falta)*/
typedef struct aluno {
    int numero;
    char nome_aluno[50];
    float nota;
    float nota_final;
    float media;
    int presenca;
    float presencaPer;
} Taluno;

typedef struct ano_semestre {
    char opcao;
    int semestre_ano;
} Tsem;

/*
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
*/
typedef struct disciplinaa {
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

/*
INFORMAÇÕES

Interface
-Dialogos simples, deve passar por consistencia, pra evitar erros de execução de
digitação incorreta

Arquivos
-O usuario pode salvar(e posteriormente consultar) todos os dados de cada
disciplina -Cada disciplina deve ser armazenada em um arquivo diferente(mas eh
melhor armazenar todos os dados de uma mesmoa disciplina em um unico arquivo)
*/


//PROTÓTIPOS
void criar_disciplina(disciplina *disc, FILE **fpdisc, FILE *fdiscis, int qntd_disciplina);
void incluir_alunos(int qnt, int ind);
void aula();
void media_freqpercent();
void relatorios();
void a();
void b();
void c();
void d();
void e();

//Função Principal
int main() {
    // Declaração de variáveis
    disciplina disc[50];
    FILE *fpdisc[50], *fdiscis;
    int opt, numero;
    Tprof prof;
    prof.qntd_disciplina = 0;

    // Primeiro funcionamento quando nao tiver disciplinas
    setlocale(LC_ALL, "Portuguese");
    
    if (!fopen("./disciplinas.txt", "r")) {
        fdiscis = fopen("./disciplinas.txt", "a");
        criar_disciplina(disc, fpdisc, fdiscis, prof.qntd_disciplina);
        fclose(fdiscis);
    }

    do {
        // Escolha de opções
        printf("\n\n\n*************MENU************\n");
        printf("Digite a opcao desejada:\n");
        printf("0 - Sair do Programa\n");
        printf("1 - Cotidiano\n");
        printf("2 - Final de semestre\n");
        printf("3 - Relatórios\n");
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
            case 3:
                relatorios();
                break;
        }
    } while (opt);
}

// Função pra cadastrar disciplina
void criar_disciplina(disciplina *disc, FILE **fpdisc, FILE *fdiscis, int qntd_disciplina) {
    char filename[20];
    int i = 1, l, exit = 1;

    //verificação da quantidade de disciplinas
    if(qntd_disciplina > 5){
        printf("Numero de disciplinas máximas ja atingidas!\n");
        return;
    }

    do {
        printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
        printf("Cadastro de Disciplinas\n");

        sprintf(filename, "./disciplina%d.txt", i);
        fpdisc[i] = fopen(filename, "w");

        /*Inserção default*/
        /*Aqui nos inserimos as variaveis default*/
        disc[i].carga_horaria = 60;
        disc[i].nota_min_aprov = 5.0;
        disc[i].percentual_freq = 70.0;

        printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
        printf("Inserir Disciplina:\n");

        printf("Digite o nome da disciplina:\nR:");
        scanf(" %s", disc[i].nome_disc);
        fflush(stdin);
        fprintf(fpdisc[i], "%s ", disc[i].nome_disc);

        printf("Digite o codigo da disciplina:\nR:");
        scanf("%s", disc[i].cod_disc);
        fprintf(fpdisc[i], "%s ", disc[i].cod_disc);

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

        printf("Digite o percentual minimo de frequencia pra aprovação(entre 0 e 100)(baseado na carga horaria prevista):\nR:");
        scanf("%f", &disc[i].percentual_freq);
        fprintf(fpdisc[i], "%.2f ", disc[i].percentual_freq);

        fclose(fpdisc[i]);
        printf("Deseja adicionar mais uma disciplina?[0]Para sair e [1]Para Continuar\nR:");
        scanf("%d", &exit);
        i++;
        qntd_disciplina++;
    } while (exit != 0);

    //imprime o nome da disciplina e o indice no arquivo disciplinas.txt para a facilidade de procura
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

    //Abre o arquivo alunos%d.txt
    sprintf(filename, "./alunos%d.txt", ind);
    incluirAlunos = fopen(filename, "w");

    //for para incluir os dados dos alunos em cada arquivo separado de cada disciplina
    for (i = 1; i <= qnt; i++) {
        printf("Digite o nome do aluno %d:", i);
        scanf("%s", alunos[i].nome_aluno);
        fprintf(incluirAlunos, "%s ", alunos[i].nome_aluno);
        fprintf(incluirAlunos, "%d ", i);
        fprintf(incluirAlunos, "%.2f ", 0.0);
        fprintf(incluirAlunos, "%.2f ", 0.0);
        fprintf(incluirAlunos, "%.2f ", 0.0);
        fprintf(incluirAlunos, "0 ");
        fprintf(incluirAlunos, "%.2f\n", 0.0);
    }

    fprintf(incluirAlunos, "acabou");
    fclose(incluirAlunos);
    return;
}

// Função para adicionar aulas/trabalhos/provas/exame
// Cotidiano
// -A cada aula, o prof faz a lista de presença
// Avaliações
// -Se a aula eh uma avaliação, alem dos dados comuns, as notas dos alunos devem
// ser informadas
void aula() {
    Taula aula_dada, aulanull;
    disciplina disciplinaSub;
    Tavaliacao prova_dada;
    Taluno aluno[50];
    char nomedisc[20], busca[20], filename[20], filename2[20], busca3[20], busca5,testacabou[20];
    int i = 1, j = 1, exit = 1, opcao, busca2, busca4, notaProva;
    FILE *materias, *aula, *alunos;
    int buscaint;

    printf("\nDigite o nome da disciplina ministrada:\nR: ");
    scanf("%s", nomedisc);
    materias = fopen("disciplinas.txt", "r");

    //Abre o aqruivo disciplinas.txt e procura pela disciplina desejada, alem de pegar seu indice
    while (exit) {
        fscanf(materias, "%s %d ", busca, &busca2);
        if (strcmp(busca, nomedisc) == 0) {
            exit = 0;
        }
    }

    //Abre o aqruivo aulas%d.txt
    sprintf(filename, "./aulas%d.txt", busca2);
    aula = fopen(filename, "a");

    //Abre o aqruivo alunos%d.txt em modo de leitura
    sprintf(filename2, "./alunos%d.txt", busca2);
    if (fopen(filename2, "r") == NULL) {
        alunos = fopen(filename2, "w");
        fclose(alunos);
    } else {
        alunos = fopen(filename2, "r");
    }
    
    //Função para scanear e armazenar temporariamente os dados dos alunos dos arquivos numa struct do programa 
    do {
        fflush(stdin);
        fscanf(alunos, "%s", testacabou);
        if (strcmp(testacabou, "acabou") != 0) {
            strcpy(aluno[j].nome_aluno, testacabou);
            fscanf(alunos, " %d %f %f %f %d %f", &aluno[j].numero, &aluno[j].nota,&aluno[j].nota_final, &aluno[j].media, &aluno[j].presenca,&aluno[j].presencaPer);
            j++;
        }
    } while (strcmp(testacabou, "acabou") != 0);
    fclose(alunos);

    printf("\nQue tipo de ação cotidiana é:\n");
    printf("1-Inserção de aula:\n");
    printf("2-Inserção de Prova:\nR: ");
    scanf("%d", &opcao);

    printf("\nDigite o número de ordem:\nR: ");
    scanf("%d", &aula_dada.numero_ordem);
    fprintf(aula, "%d ", aula_dada.numero_ordem);

    printf("Digite a data da aula:\nR: ");
    scanf("%d/%d/%d", &aula_dada.data.dia, &aula_dada.data.mes,&aula_dada.data.ano);
    fprintf(aula, "%d/%d/%d ", aula_dada.data.dia, aula_dada.data.mes,aula_dada.data.ano);

    printf("Digite a quantidade de horas associadas a disciplina:\nR: ");
    scanf("%d", &aula_dada.qntd_horas_ass);
    fprintf(aula, "%d ", aula_dada.qntd_horas_ass);

    //Adicionar prova ou trabalho
    if (opcao == 2) {
        fprintf(aula, "prova/trabalho ");

        printf("Digite o nome da avaliação/trabalho:\nR: ");
        scanf("%s", prova_dada.nome_avaliacao);
        fprintf(aula, "%s ", prova_dada.nome_avaliacao);

        printf("Digite o tipo da avaliação/trabalho(P - para prova - T para trabalho - E para exames finais):\nR: ");
        scanf(" %c", &prova_dada.tipoAval);
        fprintf(aula, "%c ", prova_dada.tipoAval);

        prova_dada.dataAval.dia = aula_dada.data.dia;
        prova_dada.dataAval.mes = aula_dada.data.mes;
        prova_dada.dataAval.ano = aula_dada.data.ano;

        printf("Digite o peso da avaliação/trabalho(Ex. 2 para prova com peso 2):\nR: ");
        scanf("%d", &prova_dada.peso);
        fprintf(aula, "%d", prova_dada.peso);

    
    } else if (opcao == 1) { //Adicionar aula
        printf("Digite qual o conteudo ministrado na aula:\nR: ");
        fflush(stdin);
        scanf("%s", aula_dada.conteudo);
        fprintf(aula, "%s ", aula_dada.conteudo);
    }

    //Frequencia na prova/aula
    for (i = 1; i < j; i++) {
        printf("Digite a frequencia nas aulas(P - presença e F - falta) para o aluno %s:\nR: ",aluno[i].nome_aluno);
        scanf(" %c", &busca5);
        fflush(stdin);
        if (busca5 == 'P') {
            aluno[i].presenca = aluno[i].presenca + 1;
            if (opcao == 2) {
                if (prova_dada.tipoAval == 'P' || prova_dada.tipoAval == 'p' || prova_dada.tipoAval == 't' || prova_dada.tipoAval == 'T') {
                    printf("Digite a nota para o aluno %s na avaliação/trabalho %s:\nR: ",aluno[i].nome_aluno, prova_dada.nome_avaliacao);
                    scanf("%d", &notaProva);
                    aluno[i].nota = aluno[i].nota + notaProva * prova_dada.peso;
                } else {
                    printf("Digite a nota para o aluno %s no exame final:\nR: ",aluno[i].nome_aluno);
                    scanf("%d", &notaProva);
                    aluno[i].nota_final = aluno[i].nota_final + notaProva;
                }
            }
        }
    }
    fprintf(aula, "\n");

    //Função para scanear e armazenar temporariamente os dados dos alunos dos arquivos numa struct do programa 
    sprintf(filename2, "./alunos%d.txt", busca2);
    alunos = fopen(filename2, "w");
    for (i = 1; i < j; i++) {
        fprintf(alunos, "%s %d %.2f %.2f %.2f %d %.2f\n", aluno[i].nome_aluno,aluno[i].numero, aluno[i].nota, aluno[i].nota_final, aluno[i].media,aluno[i].presenca, aluno[i].presencaPer);
    }
    fprintf(alunos, "acabou"); //palavra usada para controlar o fim do arquivo

    fclose(aula);
    fclose(alunos);
    fclose(materias);

    return;
}


// Função para fazer calculo de media e do percentual de frequencia
// Final do Semestre
// -Calcular média e percentual de frequencia
void media_freqpercent() {
    char nomedisc[20], busca[20], filename[20], testacabou[20];
    int busca2, i, j = 1, exit = 1, k = 0, pesoCounter = 0, test2 = 1;
    Taluno aluno[50];
    Taula aula_dada[60];
    Tavaliacao prova_dada[20];
    FILE *materias, *alunos, *aulas, *fpdisc;
    disciplina disc;

    printf("\nDigite o nome da disciplina a ser calculada a media e o percentual de frequência:\nR: ");
    scanf(" %s", nomedisc);

    //Abre o aqruivo disciplinas.txt e procura pela disciplina desejada, alem de pegar seu indice
    materias = fopen("disciplinas.txt", "r");
    while (exit) {
        fscanf(materias, "%s %d ", busca, &busca2);
        if (strcmp(busca, nomedisc) == 0) {
        exit = 0;
        }
    }

    // calcular a soma dos pesos e da frequencia por disciplinas
    sprintf(filename, "./aulas%d.txt", busca2);
    aulas = fopen(filename, "r");

    // Abriu arquivos disciplina%d para ver a nota minima e frequencia minima
    sprintf(filename, "./disciplina%d.txt", busca2);
    fpdisc = fopen(filename, "r");
    fscanf(fpdisc, "%s %c %d %c %d %d %d %d %d %f %f", disc.nome_disc,&disc.cod_disc, &disc.qntd_aluno, &disc.sem_ano.opcao,&disc.sem_ano.semestre_ano, &disc.qntd_provas, &disc.qntd_trabalhos,&disc.carga_horaria, &disc.carga_realizada, &disc.nota_min_aprov,&disc.percentual_freq);
    
    //Função para scanear e armazenar temporariamente os dados das aulas dos arquivos numa struct do programa
    do {
        fscanf(aulas, "%d", &aula_dada[k].numero_ordem);
        fscanf(aulas, "%d/%d/%d %d", &aula_dada[k].data.dia, &aula_dada[k].data.mes,&aula_dada[k].data.ano, &aula_dada[k].qntd_horas_ass);
        fscanf(aulas, "%s", aula_dada[k].conteudo);
        if (strcmp(aula_dada[k].conteudo, "prova/trabalho") == 0) {
            fscanf(aulas, "%s %c %d", prova_dada[k].nome_avaliacao,&prova_dada[k].tipoAval, &prova_dada[k].peso);
            pesoCounter = pesoCounter + prova_dada[k].peso;
        }
        k++;
    } while (!feof(aulas));

    //Função para scanear e armazenar temporariamente os dados dos alunos dos arquivos numa struct do programa
    sprintf(filename, "./alunos%d.txt", busca2);
    alunos = fopen(filename, "r");
    do {
        fscanf(alunos, "%s", testacabou);
        if (strcmp(testacabou, "acabou") != 0) {
            strcpy(aluno[j].nome_aluno, testacabou);
            fscanf(alunos, " %d %f %f %f %d %f", &aluno[j].numero, &aluno[j].nota,&aluno[j].nota_final, &aluno[j].media, &aluno[j].presenca,&aluno[j].presencaPer);
            if (aluno[j].nota != 0) {
                aluno[j].media = aluno[j].nota / pesoCounter;
            }
            if (aluno[j].presenca != 0) {
                aluno[j].presencaPer = (aluno[j].presenca * 100) / (k - 1);
            }
            j++;
        }
    } while (strcmp(testacabou, "acabou") != 0);
    fclose(alunos);


    /*Recuperação
    -Se a frequencia passou mas a nota nao, ele tem direito a uma prova
    final(chamada exame ou recuperacao) A nota obtida sera somada com a media atual
    e dividida por 2*/
    //faz os calculos das medias e frequencias com os dados obtidos
    alunos = fopen(filename, "w");
    printf("\n");
    for (i = 1; i < j; i++) {
        aluno[i].nota_final = 0;
        fprintf(alunos, "%s ", aluno[i].nome_aluno);
        fprintf(alunos, "%d ", aluno[i].numero);
        fprintf(alunos, "%.2f ", aluno[i].nota);
        if (aluno[i].media < disc.nota_min_aprov && aluno[i].presencaPer >= disc.percentual_freq) {
            printf("O aluno %s obteve média das notas:%.2f e precisa de %.2f para passar\n",aluno[i].nome_aluno, aluno[i].media,(disc.nota_min_aprov * 2) - aluno[i].media);
            printf("Qual foi a nota obtida na recuperação?\n");

            scanf("%f", &aluno[i].nota_final);
            fprintf(alunos, "%.2f ", aluno[i].nota_final);

            aluno[i].media = (aluno[i].nota_final + aluno[i].media) / 2;
            fprintf(alunos, "%.2f ", aluno[i].media); // calcula media
        } else {
            fprintf(alunos, "%.2f ", aluno[i].nota_final);
            fprintf(alunos, "%.2f ", aluno[i].media);
        }
        printf("O aluno %s e obteve media:%.2f e frequência:%.2f\n",aluno[i].nome_aluno, aluno[i].media, aluno[i].presencaPer);
        fprintf(alunos, "%d ", aluno[i].presenca);
        fprintf(alunos, "%.2f\n", aluno[i].presencaPer);
        // Procura no arquivo disciplina, a media e frequencia especifica da
        // disciplina
    }
    fprintf(alunos, "acabou");

    printf("\nMédia e frequêcia calculada com sucesso!");

    fclose(aulas);
    fclose(alunos);
    fclose(materias);
    fclose(fpdisc);
    return;
}

/*
Relatórios 
-O sistema deve fornecer relatorios em tela ou impressos, a escolha do usuario,
eles devem ser possiveis(no minimo): -situacao individual de cada
aluno(quantidade e percentual de faltas, notas e situacao) -Listagem geral da
turma de uma disciplina(quantidade e percentual de faltas, notas e situação)
        -Notas minima, media e maxima da turma
        -Relação dos alunos que devem realizar a avaliacao final, assim como a
nota necessaria pra cada um deles -Relação dos aprovados ou dos reprovados da
turma, indicando se eh por frequencia ou por nota
*/
void relatorios() {
    char opt;
    do {
        // Escolha de opções
        printf("\n\n\n*************Cotidiano************\n");
        printf("Digite a opcao desejada:\n");
        printf("a - Situação individual de cada aluno\n");
        printf("b - Listagem geral da turma de uma disciplina\n");
        printf("c - Notas mínima, média e máxima de cada turma\n");
        printf("d - Alunos de exame e nota necessaria para passar\n");
        printf("e - Relações dos aprovados ou dos reprovados de uma turma\n");
        printf("f - Sair\n");
        scanf(" %c", &opt);

        switch (opt) {
            case 'a':
                a();
                break;
            case 'b':
                b();
                break;
            case 'c':
                c();
                break;
            case 'd':
                d();
                break;
            case 'e':
                e();
                break;
            case 'f':
                system("clear");
                break;
        }
    } while (opt != 'f');
}

//Relatório (a) mostra a situação individual de cada aluno(quantidade e porcentagem de faltas, notas e situação)
void a() {
    FILE *alunos, *relatorio_a, *fpdisc, *aulas, *fpdiscs;
    int i = 1, j = 1, test2, faltas, n_aulas = -1, exit = 1, indicedisc;
    float porc_faltas;
    char opt, nomealuno[30], busca[20], filename[20], situacao;
    Taluno aluno;
    Taula aula;
    disciplina disc;
    Tavaliacao prova_dada;

    relatorio_a = fopen("RelatorioA.txt", "w");

    printf("\nDigite o nome do aluno a ser listado:\nR: ");
    scanf(" %s", nomealuno);
    fpdiscs = fopen("disciplinas.txt", "r");

    printf("Deseja obter o relatório na tela ou no arquivo?(T-Tela e A para arquivo)\nR: ");
    scanf(" %c", &opt);
    printf("\n");

    do {
        fscanf(fpdiscs, "%s %d ", busca, &indicedisc);
        
        // Abrir o disciplina%d e armazena temporariamente os dados da disciplina no programa
        sprintf(filename, "./disciplina%d.txt", indicedisc);
        fpdisc = fopen(filename, "r");
        fscanf(fpdisc, "%s ", disc.nome_disc);
        fscanf(fpdisc, "%c %d %c %d %d %d %d %d %f %f", &disc.cod_disc,&disc.qntd_aluno, &disc.sem_ano.opcao, &disc.sem_ano.semestre_ano,&disc.qntd_provas, &disc.qntd_trabalhos, &disc.carga_horaria,&disc.carga_realizada, &disc.nota_min_aprov, &disc.percentual_freq);
        // Abrir o alunos%d
        sprintf(filename, "./alunos%d.txt", indicedisc);
        alunos = fopen(filename, "r");
        // Abrir o aulas%d
        sprintf(filename, "./aulas%d.txt", indicedisc);
        aulas = fopen(filename, "r");
        
        // Armazena temporariamente os dados da disciplina no programa
        while (!feof(aulas)) {
            fscanf(aulas, "%d", &aula.numero_ordem);
            fscanf(aulas, "%d/%d/%d %d %s", &aula.data.dia, &aula.data.mes,&aula.data.ano, &aula.qntd_horas_ass, aula.conteudo);
            if (strcmp(aula.conteudo, "prova/trabalho") == 0) {
                fscanf(aulas, "%s %c %d", prova_dada.nome_avaliacao,&prova_dada.tipoAval, &prova_dada.peso);
            }
            n_aulas++;//calcula o numero de aulas 
        }
        // Armazena temporariamente os dados dos alunos no programa
        while (!feof(alunos)) {
            fscanf(alunos, "%s %d %f %f %f %d %f", aluno.nome_aluno, &aluno.numero, &aluno.nota, &aluno.nota_final, &aluno.media, &aluno.presenca, &aluno.presencaPer);
            if (strcmp(nomealuno, aluno.nome_aluno) == 0) {
                faltas = (n_aulas - aluno.presenca);
                if (aluno.media >= disc.nota_min_aprov && aluno.presencaPer >= disc.percentual_freq) situacao = 'A';
                else situacao = 'R';
                if (opt == 'T') {
                    printf("Disc     /Qtde Faltas/Percent Faltas/Notas/Situação:\n");
                    printf("%s     %d        %.2f        %.2f       %c\n", disc.nome_disc,faltas, (100 - aluno.presencaPer), aluno.media, situacao);
                } else if (opt == 'A') {
                    fprintf(relatorio_a, "%s %d %.2f %.2f %c\n", disc.nome_disc, faltas, (100 - aluno.presencaPer), aluno.media, situacao);        
                }
            }
        }

        n_aulas = -1;
    } while (!feof(fpdiscs));

    fclose(alunos);
    fclose(relatorio_a);
    fclose(fpdiscs);
    fclose(fpdisc);
    fclose(aulas);
}
//Relatório (b) lista a turma por disciplina, com a quantidade e porcentagem de faltas, notas e situação de todos os alunos da turma
void b() {
    FILE *fpdisc, *fprel, *alunos, *aulas, *fpdisciplina;
    int qtdefaltas, exit = 1, indicedisc, n_aulas = -1, n_alunos = 0;
    float faltasper, notas, percentfaltas;
    char situacao, nomedisc[20], busca[20], opt, filename[20];
    Taluno aluno;
    Taula aula;
    Tavaliacao prova;
    disciplina disc;

    // Pegar o indice da disciplina
    printf("\nDigite o nome da disciplina a ser listada:\nR: ");
    scanf(" %s", nomedisc);

    fpdisc = fopen("disciplinas.txt", "r");
    while (exit) {
        fscanf(fpdisc, "%s %d ", busca, &indicedisc);
        if (strcmp(busca, nomedisc) == 0) {
        exit = 0;
        }
    }

    // Abrir o alunos%d
    sprintf(filename, "./alunos%d.txt", indicedisc);
    alunos = fopen(filename, "r");

    // Abrir o disciplina%d
    sprintf(filename, "./disciplina%d.txt", indicedisc);
    fpdisciplina = fopen(filename, "r");

    // Le o arquivo disciplinas pra pegar a nota mina aprovacçao e percentual
    // frequencia
    fscanf(fpdisciplina, "%s ", disc.nome_disc);
    fscanf(fpdisciplina, "%c %d %c %d %d %d %d %d %f %f", &disc.cod_disc,&disc.qntd_aluno, &disc.sem_ano.opcao, &disc.sem_ano.semestre_ano,&disc.qntd_provas, &disc.qntd_trabalhos, &disc.carga_horaria,&disc.carga_realizada, &disc.nota_min_aprov, &disc.percentual_freq);

    // Abrir aulas%d pra pegar a quantidade de aulas
    sprintf(filename, "./aulas%d.txt", indicedisc);
    aulas = fopen(filename, "r");

    // Pega a quantidade de aulas
    while (!feof(aulas)) {
        fscanf(aulas, "%d", &aula.numero_ordem);
        fscanf(aulas, "%d/%d/%d %d   %s", &aula.data.dia, &aula.data.mes,&aula.data.ano, &aula.qntd_horas_ass, aula.conteudo);
        if (strcmp(aula.conteudo, "prova/trabalho") == 0) {
            fscanf(aulas, "%s %c %d", prova.nome_avaliacao, &prova.tipoAval,&prova.peso);
        }
        n_aulas++;
    }
    printf("Deseja obter o relatório na tela ou no arquivo?(T-Tela e A para arquivo)\nR: ");
    scanf(" %c", &opt);
    fprel = fopen("RelatorioB.txt", "w");
    //printa na tela os dados dos alunos
    if (opt == 'T') {
        while (strcmp("acabou", aluno.nome_aluno) != 0) {
            fscanf(alunos, "%s ", aluno.nome_aluno);
            if (strcmp("acabou", aluno.nome_aluno) == 0)
                break;

            fscanf(alunos, "%d %f %f %f %d %f", &aluno.numero, &aluno.nota,&aluno.nota_final, &aluno.media, &aluno.presenca,&aluno.presencaPer);
            n_alunos++;

            qtdefaltas = (n_aulas - aluno.presenca);
            percentfaltas = 100.00 - aluno.presencaPer;
            if (aluno.media >= disc.nota_min_aprov && aluno.presencaPer >= disc.percentual_freq)
                situacao = 'A';
            else
                situacao = 'R';
            printf("Nome/Numero/Qtde Faltas/Percent Faltas/Notas/Situação:\n");
            printf("%s  %d      %d        %.2f        %.2f       %c\n",aluno.nome_aluno, aluno.numero, qtdefaltas, percentfaltas,aluno.media, situacao);
        }
    }
    //printa no arquivo os dados dos alunos
    else if (opt == 'A') {
        while (strcmp("acabou", aluno.nome_aluno) != 0) {
        fscanf(alunos, "%s ", aluno.nome_aluno);
        if (strcmp("acabou", aluno.nome_aluno) == 0)
            break;
        fscanf(alunos, "%d %f %f %f %d %f", &aluno.numero, &aluno.nota,&aluno.nota_final, &aluno.media, &aluno.presenca,&aluno.presencaPer);
        n_alunos++;

        qtdefaltas = (n_aulas - aluno.presenca);
        percentfaltas = 100.00 - aluno.presencaPer;
        if (aluno.media >= disc.nota_min_aprov && aluno.presencaPer >= disc.percentual_freq)
            situacao = 'A';
        else
            situacao = 'R';
        fprintf(fprel, "%s %d %d %.2f %.2f %c\n", aluno.nome_aluno, aluno.numero,qtdefaltas, percentfaltas, aluno.media, situacao);
        }
    }
    fclose(alunos);
    fclose(fprel);
    fclose(fpdisc);
    fclose(fpdisciplina);
    fclose(aulas);
}
//Relatório (c) exibe as notas mínimas, médias e máximas de cada turma
void c() {
    char testacabou[20], filename[20], filename2[20], disciplina[20], busca[20],opt;
    int i = 1, j = 0, l = 0, busca2;
    float min = 10, max = 1, media = 0;
    Taluno aluno[50];
    FILE *alunos, *disc, *relatorio, *materias;

    relatorio = fopen("./RelatorioC.txt", "a");
    materias = fopen("./disciplinas.txt", "r");

    printf("Deseja obter o relatório na tela ou no arquivo?(T - Tela e A - para arquivo)\nR: ");
    scanf(" %c", &opt);
    printf("\n");

    //for para ver o tanto de materias
    do {
        fscanf(materias, "%s %d ", busca, &busca2);
        l++;
    } while (!feof(materias));
    fclose(materias);

    //for para abrir os arquivos alunos e disciplina e calcular a media
    for (i = 1; i <= l; i++) {
        sprintf(filename, "./alunos%d.txt", i);
        sprintf(filename2, "./disciplina%d.txt", i);

        FILE *alunos = fopen(filename, "r"), *disc = fopen(filename2, "r");

        if (!alunos && !disc) {
            break;
        }

        fscanf(disc, "%s", disciplina);

        do {
            fscanf(alunos, "%s", testacabou);
            if (strcmp(testacabou, "acabou") != 0) {
                strcpy(aluno[j].nome_aluno, testacabou);
                //leitura do conteúdo dos arquivos alunos%d
                fscanf(alunos, "%d %f %f %f %d %f", &aluno[j].numero, &aluno[j].nota,&aluno[j].nota_final, &aluno[j].media, &aluno[j].presenca,&aluno[j].presencaPer);

                if (aluno[j].media < min) {
                    min = aluno[j].media;
                }
                if (aluno[j].media > max) {
                    max = aluno[j].media;
                }
                    media = media + aluno[j].media;
                j++;
            }
        } while (strcmp(testacabou, "acabou") != 0);

        if (opt == 'T') { //escolhe a opção para exibir o relatório na tela
            printf("Nota Mínima/Nota Máxima/Nota Média - %s:\n", disciplina);
            printf("%.2f        %.2f           %.2f\n", min, max, media / j);
            printf("\n\n");
        } else if (opt == 'A') { //escolhe a opção para exibir o relatório no arquivo
            fprintf(relatorio, "Nota Mínima/Nota Máxima/Nota Média - %s:\n", disciplina);
            fprintf(relatorio, "%.2f       %.2f           %.2f\n", min, max, media / j);
            fprintf(relatorio, "\n");
        }

        fclose(alunos);
        fclose(disc);
        // reset das variaveis maximas e minimas
        min = 11;
        max = -1;
        media = 0;
        j = 0;
    }
    //fechamento dos arquivos
    fclose(relatorio);
    return;
    fclose(alunos);
    fclose(relatorio);
    fclose(disc);
    fclose(materias);
}
//Relatório (d) relaciona os alunos que devem realizar a avaliação final e a nota necessária para cada um deles conseguir ser aprovado
void d() {
    FILE *alunos, *fpdisciplina, *fpdisc, *relatorio_d;
    char opt, busca[20], filename[20], nomedisc[20];
    int indicedisc, exit = 1, n_alunos, n_aulas;
    float nota, percentfaltas;
    Taluno aluno;
    disciplina disc;

    printf("Deseja obter o relatório na tela ou no arquivo?(T-Tela e A para arquivo)\nR: ");
    scanf(" %c", &opt);
    printf("\n");

    fpdisc = fopen("disciplinas.txt", "r");
    relatorio_d = fopen("./RelatorioD.txt", "a");

    do {
        //leitura do nome do aluno a ser buscado e o índice da disciplina
        fscanf(fpdisc, "%s %d ", busca, &indicedisc);
        sprintf(filename, "./disciplina%d.txt", indicedisc);
        fpdisciplina = fopen(filename, "r");
        //leitura do conteúdo do arquivo disciplina
        fscanf(fpdisciplina, "%s %s %d %c %d %d %d %d %d %f %f", disc.nome_disc,&disc.cod_disc, &disc.qntd_aluno, &disc.sem_ano.opcao,&disc.sem_ano.semestre_ano, &disc.qntd_provas, &disc.qntd_trabalhos,&disc.carga_horaria, &disc.carga_realizada, &disc.nota_min_aprov,&disc.percentual_freq);

        sprintf(filename, "./alunos%d.txt", indicedisc);
        alunos = fopen(filename, "r");
        strcpy(aluno.nome_aluno, "banana");

        while (strcmp("acabou", aluno.nome_aluno) != 0) {
            fscanf(alunos, "%s ", aluno.nome_aluno);
            if (strcmp("acabou", aluno.nome_aluno) == 0)//verifica se chegou ao final do arquivo alunos
                break;
            //leitura do conteúdo do arquivo alunos
            fscanf(alunos, "%d %f %f %f %d %f", &aluno.numero, &aluno.nota,&aluno.nota_final, &aluno.media, &aluno.presenca,&aluno.presencaPer);
            nota = (disc.nota_min_aprov * 2) - aluno.media;

            if (aluno.media < disc.nota_min_aprov) { //verifica se a média do aluno é menor que nota mínima para ser aprovado
                if (opt == 'T') {  //escolhe a opção para exibir o relatório na tela
                    printf("Nome/   Disciplina/Nota Necessaria:\n");
                    printf("%s   %s        %.2f \n", aluno.nome_aluno, disc.nome_disc, nota);
                } else if (opt == 'A') {  //escolhe a opção para exibir o relatório no arquivo
                    fprintf(relatorio_d, "Nome/  Disciplina/Nota Necessaria:\n");
                    fprintf(relatorio_d, "%s  %s         %.2f \n", aluno.nome_aluno, disc.nome_disc, nota);
                }
            }
        }
        //fechamento dos arquivos
        fclose(alunos);
        fclose(fpdisciplina);
    }while (!feof(fpdisc)); //sai do loop se chega no final do arquivo fpdisc

    fclose(fpdisc);
    fclose(relatorio_d);
}
//Relatório (e) relaciona a aprovação ou reprovação dos alunos, especificando se o aluno foi reprovado por frequência ou nota
void e() {
    int indices, j = 0;
    char buscar2[20], filename[20], testacabou[20], filename2[20], opt;
    Taluno aluno[50];
    disciplina disc;
    FILE *fpdisc, *alunos, *fpdisciplina, *relatorio;

    fpdisc = fopen("./disciplinas.txt", "r");
    relatorio = fopen("./RelatorioE.txt", "w");
    printf("Deseja obter o relatório na tela ou no arquivo?(T - Tela e A - para arquivo)\nR: ");
    scanf(" %c", &opt);

    printf("\n");

    do {
        fscanf(fpdisc, "%s %d ", buscar2, &indices);
        sprintf(filename, "./alunos%d.txt", indices);
        sprintf(filename2, "./disciplina%d.txt", indices);
        alunos = fopen(filename, "r");
        fpdisciplina = fopen(filename2, "r");
        //leitura das variaveis do arquivo da disciplina para verificação
        fscanf(fpdisciplina, "%s %s %d %c %d %d %d %d %d %f %f", disc.nome_disc,&disc.cod_disc, &disc.qntd_aluno, &disc.sem_ano.opcao,&disc.sem_ano.semestre_ano, &disc.qntd_provas, &disc.qntd_trabalhos,&disc.carga_horaria, &disc.carga_realizada, &disc.nota_min_aprov,&disc.percentual_freq);
        if (opt == 'T') { //escolhe a opção para exibir o enunciado do relatório na tela
            printf("Nome/   Média(>%.2f)/Percentual Faltas(%.2f%)/Situação - %s:\n", disc.nota_min_aprov, disc.percentual_freq, disc.nome_disc);
        } else if (opt == 'A') { //escolhe a opção para exibir o enunciado do relatório no arquivo
            fprintf(relatorio,"Nome/   Média(>%.2f)/Percentual Faltas(%.2f%)/Situação - %s:\n", disc.nota_min_aprov, disc.percentual_freq, disc.nome_disc);
        }

        do {
            fscanf(alunos, "%s", testacabou);
            if (strcmp(testacabou, "acabou") != 0) {
                strcpy(aluno[j].nome_aluno, testacabou);
                //leitura do conteúdo do arquivo alunos
                fscanf(alunos, "%d %f %f %f %d %f", &aluno[j].numero, &aluno[j].nota,&aluno[j].nota_final, &aluno[j].media, &aluno[j].presenca,&aluno[j].presencaPer);
                //verifica se o aluno está nas condições para ser reprovado
                if (aluno[j].presencaPer < disc.percentual_freq ||
                    aluno[j].media < disc.nota_min_aprov) {
                    if (opt == 'T') { //escolhe a opção para exibir o conteúdo do relatório na tela
                        printf("%s     %.2f              %.2f             Reprovado\a\n",aluno[j].nome_aluno, aluno[j].media, aluno[j].presencaPer);
                    } else { //senão exibe no arquivo
                        fprintf(relatorio,"%s     %.2f              %.2f             Reprovado\n",aluno[j].nome_aluno, aluno[j].media, aluno[j].presencaPer);
                    }
                } else {
                //senão o aluno está nas condições para ser aprovado
                    if (opt == 'T') {//escolhe a opção para exibir o conteúdo do relatório na tela
                        printf("%s     %.2f              %.2f             Aprovado\n",aluno[j].nome_aluno, aluno[j].media, aluno[j].presencaPer);
                    } else { //senão exibe no arquivo
                        fprintf(relatorio,"%s     %.2f              %.2f             Aprovado\n",aluno[j].nome_aluno, aluno[j].media, aluno[j].presencaPer);
                    }
                }

                j++;
            }
        } while (strcmp(testacabou, "acabou") != 0);

        //fechamento de arquivos
        fclose(alunos);
        fclose(fpdisciplina);
        j = 0;
    } while (!feof(fpdisc));

    fclose(relatorio);
    fclose(fpdisc);
    
    return;
}