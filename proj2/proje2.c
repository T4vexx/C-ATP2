#include <stdio.h>
#include <stdlib.h>

int counter=0;

int main() {
    int N,M,i;
    int *vetM,*vetKi;
    //N -> quantidades de numeros a serem decompostos
    //M -> quantidades de numeros que podem serem usados na decomposição
    scanf("%d %d", &N, &M);

    //Alocar dinamicamente o vetor que vai conter os numeros usados para serem decompostos
    vetM = malloc(M * sizeof(int));
    //Recebe todos os valores dos numeros usados para serem decompostos
    for(i=0;i<M;i++) {
        fflush(stdin);
        scanf("%d", &*(vetM + i));
    }

    //Alocar dinamicamente o vetor que vai conter os numeros a serem decompostos
    vetKi = malloc(N * sizeof(int));
    //Recebe todos os valores dos numeros a serem decompostos
    for(i=0;i<N;i++) {
        fflush(stdin);
        scanf("%d", &*(vetKi + i));
    }

    return 0;
}

int combinacao(int n, int combi) { //, int *vetM
    int i,j,tamanho,soma;
    int vetM[] = {1,2,4,5,8,9,10,15,20};

    tamanho = sizeof(vetM) / sizeof(int);
    for (i = 0; i < tamanho; i++) {
        
    }
}

