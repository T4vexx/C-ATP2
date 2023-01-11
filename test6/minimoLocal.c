#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int menorInteiro(int **mat,int alp, int bet);

int main() {
    int i,j,N,M,alp,bet,**mat;

    scanf("%d %d",&N,&M);
    mat = malloc(N*(sizeof(int *)));
    for(i=0;i<N;i++) {
        mat[i] = malloc(N*(sizeof(int)));
    }

    for(i=0;i<N;i++){
        for(j=0;j<N;j++) {
            scanf(" %d",&mat[i][j]);
        }
    }

    for(i=0;i<M;i++) {
        scanf("%d %d",&alp,&bet);
        printf("%d \n",menorInteiro(mat,alp,bet));
    }
    return 0;
}

int menorInteiro(int **mat,int alp, int bet) {
    int k,j,menor=INT_MAX;
    for (j = alp-1; j <= bet-1; j++) {
        for (k = alp-1; k <= bet-1; k++) {
            if(mat[j][k] < menor) {
                menor = mat[j][k];
            }
        } 
    }
        
    return menor;
}