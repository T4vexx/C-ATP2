#include <stdio.h>
#include <stdlib.h>

void insercao(double *arr, int n, int full) { 
    int i, j;
    double key; 

    for (i = 1; i <= n; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    }

    for (i = n+1; i < full; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && arr[j] < key)
        { 
            arr[j + 1] = arr[j]; 
            --j; 
        } 
        arr[j + 1] = key; 
    }
    
} 

int main() {
    int i,N,M;
    double *vet;

    scanf("%d %d",&N,&M);
    vet = malloc(N * sizeof(double));

    for(i=0;i<N;i++) {
        scanf("%lf",&vet[i]);
    }

    insercao(vet,M,N);

    for(i=0;i<N;i++) {
        printf("%.3lf ", vet[i]);
    }
}