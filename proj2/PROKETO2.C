#include <stdio.h>

int resposta[1000] = {0};

int combinationUtil(int arr[], int data[], int start, int end, int index, int r, int numero) {
    int i, j, soma=0,counter=0;

    if (index == r) {
        for (j=0; j<r; j++) {
            soma = soma + data[j];
        }

        if (soma == numero) {
            for (j=0; j<r; j++) {
               //printf("%d ", data[j]);
               resposta[j] = data[j];
            }
        
            counter++;
        }
        
        soma = 0; 
        return counter;
    }
          
    for (i=start; i<=end && end-i+1 >= r-index; i++) {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r, numero);
    }
}

int printCombination(int arr[], int n, int r, int numero) {
    int data[r],resp;
    
    resp = combinationUtil(arr, data, 0, n-1, 0, r, numero);
    return resp;
}
 

int main() {
    int arr[] = {1, 10, 11, 21, 27, 33, 34, 46, 49, 61, 62, 67, 73, 77, 79};
    int vet[] = {148, 206, 14};
    int i,j,n,v;

    n = sizeof(arr)/sizeof(int);
    v = sizeof(vet)/sizeof(int);

    for (j=0;j<v; j++) {
        for(i=2; i<=n; i++) { 
            printCombination(arr, n, i, vet[j]); 
        }  

        for(i=0; i<= 7; i++) { 
            printf("%d ", resposta[i]);
            resposta[i] = 0;
        }    
        printf("\n");
    }   
}