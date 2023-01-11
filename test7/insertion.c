#include <stdio.h>
#include <stdlib.h>

void insercao(double *arr, int n) 
{ 
    int i, j;
    double key; 
    for (i = 1; i < n; i++)
    { 
        key = arr[i]; 
        j = i - 1; 
  
        // Move elements of arr[0..i-1],  
        // that are greater than key, to one 
        // position ahead of their 
        // current position
        while (j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
} 
// void insercao(double *vet, int N) {
//     int i,j;
//     double aux;
     
//     for(i=1;i<N;i++){
//         aux=vet[i];
//         j=i;
//         while(j<0 && vet[j-1]>aux) {
//             vet[j]=vet[j-1];
//             j--;
//         }
//         vet[j]=aux;
//     }
// }

int main() {
    int i,N,M;
    double *vet;

    scanf("%d %d",&N,&M);
    vet = malloc(N * sizeof(double));

    for(i=0;i<N;i++) {
        scanf("%lf",&vet[i]);
    }

    insercao(vet,N);

    for(i=0;i<N;i++) {
        printf("%.4lf ", vet[i]);
    }
}