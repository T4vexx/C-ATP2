#include <stdio.h>
#include <stdlib.h>

int crescente(int buscados, int N, int v[]);
int decrescente(int buscados, int N, int v[]);

int main(){
    int N, M, i, buscados, key;
    scanf("%d", &N);
    int a[N];
    for(i = 0; i < N; i++){
        scanf("%d ", &a[i]);
    }
    scanf("%d", &M);
    for(i = 0; i < M; i++){
        scanf("%d", &buscados);
        key = crescente(buscados, N, a);
        if(key != -1)
            printf("%d ", key);
        else{
            key = decrescente(buscados, N, a);
            printf("%d ", key);
        }
    }
}

int crescente(int buscados, int N, int v[]){
    int min = 0, max = N / 2 - 1, mid;
    if(v[min] == buscados) 
        return min;
    else if(v[max] == buscados)
        return max;
    while(min <= max && buscados != v[mid]){
        mid = (min + max) / 2;
        if(v[mid] < buscados)
            min = mid + 1;
        else 
            max = mid - 1;
      }
        if(buscados == v[mid])
            return mid;
    return -1;
}

int decrescente(int buscados, int N, int v[]){
    int min = N / 2, max = N - 1, mid;
    if(v[min] == buscados)
        return min;
    else if(v[max] == buscados)
        return max;
    while(min <= max && buscados != v[mid]){
        mid = (min + max) / 2;
        if(v[mid] > buscados)
            min = mid + 1;
        else 
            max = mid - 1;
      }
        if(buscados == v[mid])
            return mid;
    return -1;
}