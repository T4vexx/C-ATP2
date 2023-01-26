#include <stdio.h>
#include <stdlib.h>

void mergesort(int i,int j,int *a, int *aux) {
  int K,mid,ptr_dir,ptr_esq;
  if(j<=i) return;
  mid=(i+j)/2;
  mergesort(i,mid,a,aux);
  mergesort(mid+1,j,a,aux);
  ptr_esq=i;
  ptr_dir=mid+1;
  K=0;
  while(ptr_esq<=mid&&ptr_dir<=j) {
    if(a[ptr_esq] < a[ptr_dir]) {
      aux[K]=a[ptr_esq];
      ptr_esq++;
    } else {
      aux[K]=a[ptr_dir];
      ptr_dir++;
    }
    K++;
  }
  if(ptr_esq>mid) {
    while(ptr_dir<=j) {
      aux[K]=a[ptr_dir];
      K++;
      ptr_dir++;
    }
  } else {
    while(ptr_esq<=mid){
      aux[K]=a[ptr_esq];
      K++;
      ptr_esq++;
    }
  }
  for(K=i;K<=j;K++){
    a[K]=aux[K-i];
  }
}

int mediana(int *vet,int i,int j,int k)  {
  int numero;
  if(vet[i]<vet[j]&&vet[j]<vet[k]) {
    return j;
  } else if(vet[j]<vet[i]&&vet[i]<vet[k]){
    return i;
  } else {
    return k;
  }
}

int troca(int *a,int *b) {
  int aux;
  aux=*a;
  *a=*b;
  *b=aux;
}

void quicksort(int *vet, int lo, int hi){
int i, pivo,bigger;

//hi eh o pivo, que deuxa sempre em ultimo

if(lo<hi){// indice da primeira e ultima posicak)
pivo=mediana(vet,lo,(lo+hi)/2, hi); //retorna o indice da mediana
troca(&vet[pivo],&vet[hi]);
bigger=lo;

for(i=bigger;i<hi;i++){  
 if(vet[i]<vet[hi]){
  troca(&vet[i],&vet[bigger]);
  bigger++;
 }
}
troca(&vet[i],&vet[bigger]);//troca o pivo com o bigger(pra colcoar o pivo bem no meio
quicksort(vet, lo, bigger-1);
quicksort(vet,bigger+1,hi);

//Testa se chegou ao fim(ordenado)
//escolher um pivo que todos menor wue ele ficam a eswuerda e os maiores ficam a direita

//senao prepara pra recursao
//faz a recursao( a cada recursao escolhe um pivo)

}
}



int main(void) {
  int *vet,*aux;
  vet = malloc(100 * sizeof(int));
  aux = malloc(100 * sizeof(int));

  for(int i=0;i<100;i++) 
    vet[i]=rand()%999+1;

  quicksort(vet,0,99);
  for(int i=0;i<100;i++) 
    printf("%d ",vet[i]);
  
  return 0;
}