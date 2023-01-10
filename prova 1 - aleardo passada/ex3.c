#include <stdio.h>
#include <stdlib.h>

void pegaMatrix(int *, int);
void imprimeMatrix(int *, int);
int espiralHorario(int *, int);

int main() {
    int N,i,result;
    int **matrix;

    printf("Digite o numero da matriz: \n");
    scanf("%d", &N); 
    matrix = malloc(N * sizeof(int *));
    for(i=0;i<N;i++) {
        matrix[i] = malloc(N * sizeof(int *));
    }

    pegaMatrix(&matrix[0][0],N);
    imprimeMatrix(&matrix[0][0],N);
    result = espiralHorario(&matrix[0][0],N);

    printf("\nO resultado é = %d", result);

    free(matrix);
    for(i=0;i<N;i++) {
        free(matrix[i]);
    }
}

void pegaMatrix(int *matrix, int N) {
    int i;

    printf("Digite a matriz em ordem: \n");
    for (i = 0; i < N*N; i++) {
        scanf("%d",&(*matrix));
        matrix++;
    }
}

void imprimeMatrix(int *matrix, int N) {
    printf("----> MATRIZ <----\n");
    int i,j;

    for(i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("[%d] ", *matrix);
            matrix++;
        }
        printf("\n");
    }

    printf("\n");
}

int espiralHorario(int *matrix, int N) {
    int i,j,flag=N,origem=0,auxiliar=N;
    int **aux;

    aux = malloc(N * sizeof(int *));
    for(i = 0; i < N; i++) {
        aux[i] = malloc(N * sizeof(int *));
    }
    for(i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            aux[i][j] = *matrix;
            matrix++;
        }
    }

    do {
        for (i = origem; i < auxiliar - 1; i++) {
            if (aux[origem][i] + 1 != aux[origem][i + 1]) {
                return 0;
            }
        }

        for (i = origem; i < auxiliar - 1; i++) {
            if (aux[i][auxiliar - 1] + 1 != aux[i + 1][auxiliar - 1]) {
                return 0;
            }
        }

        for (i = auxiliar - 1; i > origem ; i--) {
            if (aux[auxiliar - 1][i] + 1 != aux[auxiliar - 1][i - 1]) {
                return 0;
            }
        }

        for (i = auxiliar - 1; i > origem + 1; i--) {
            if (aux[i][origem] + 1 != aux[i - 1][origem]) {
                return 0;
            }
        }

        if (N%2 == 0) {
            flag = flag/2;
        } else {
            flag = flag - 2;
        }

        auxiliar--;
        origem++;
    }while(flag != 1);

    if(N%2 && aux[N/2][N/2] != aux[N/2][(N/2) - 1] + 1) {
        return 0;
    }


    return N;
}


