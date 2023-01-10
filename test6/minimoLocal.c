#include <stdio.h>
#include <stdlib.h>

int main() {
    int i,j,N,M;
    int **mat;

    scanf("%d %d",&N,&M);
    mat = malloc(N*(sizeof(int *)));
    for(i=0;i<N;i++) {
        mat[i] = malloc(N*(sizeof(int)));
    }

    for(i=0;i<N;i++){
        for(j=0;j<N;j++) {
            scanf("%d",&mat[i][j]);
        }
    }

    
}