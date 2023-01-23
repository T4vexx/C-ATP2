#include <stdio.h>
#include <stdlib.h> 

int BinarySearchL(int num,int N,int vet[]){
    int inicio = 0,final = N / 2 - 1, mid;
    if(vet[inicio] == num) 
        return inicio;
    else if(vet[final] == num)
        return final;
    while(inicio <= final && num != vet[mid]){
        mid = (inicio + final) / 2;
        if(vet[mid] < num) 
            inicio = mid + 1;
        else 
            final = mid - 1;   
      }
        if(num == vet[mid]) 
            return mid;
    return -1;
}

int BinarySearchD(int num,int N,int vet[]){
    int inicio=N/2,final=N-1,mid;
    if(vet[inicio] == num) 
        return inicio;
    else if(vet[final] == num)
        return final;
    while(inicio <= final && num != vet[mid]){
        mid = (inicio + final) / 2;
        if(vet[mid] > num) 
            inicio = mid + 1;
        else 
            final = mid - 1;   
    }
    if(num == vet[mid]) 
        return mid;
    return -1;
}

int main() {
    int N,M,*vetValores,aux,i,left,right;    

    scanf("%d",&N);
    vetValores = malloc(N * sizeof(int));

    for(i=0;i<N;i++) {
        scanf("%d ",&vetValores[i]);
    }

    scanf("%d",&M);
    for(i=0;i<M;i++) {
        scanf("%d",&aux); 
        left = BinarySearchL(aux,N,vetValores);
        if(left != -1) {
            printf("%d ", left);
        } else {
            right = BinarySearchD(aux,N,vetValores);
            printf("%d ",right);
        }        
    }
}

