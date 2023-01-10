#include <stdio.h>
#include <stdlib.h>

void buscar(int linha_m,int coluna_m,int quantos,int M,int chegada,int **matrix) {

    if (linha_m == M - 1 && coluna_m == chegada && matrix[linha_m][coluna_m] == 0) {
        printf("%d\n", quantos);
        exit(0);
    }

    if (validar_movimeto(M, linha_m, coluna_m,matrix) == 0) {
        return;
    }
        
    matrix[linha_m][coluna_m] = 1;
    buscar(linha_m + 1, coluna_m, quantos + 1, M, chegada,matrix);
    buscar(linha_m, coluna_m + 1, quantos + 1, M, chegada,matrix);
    buscar(linha_m, coluna_m -1 , quantos + 1, M, chegada,matrix);
    return;
}

int validar_movimeto(int M,int linha_m,int coluna_m,int **matrix) {
    if(linha_m>=0 && coluna_m >=0 && linha_m < M && coluna_m<M && matrix[linha_m][coluna_m] == 0) {
        return 1;
    } else {
        return 0;
    }    
}

int main() {
    int i,j,M,chegada,comeco,quantos;
    int **mat;

    scanf("%d %d %d", &M, &comeco, &chegada);

    mat = (int **)malloc(M * sizeof(int *));
    for(int i = 0; i < M; i++) {
        mat[i] = (int *)malloc(M * sizeof(int));
    } 

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }


    quantos = 0;
    buscar(0, comeco, quantos, M, chegada,mat);
    printf("-1\n");

    return 0;
}
