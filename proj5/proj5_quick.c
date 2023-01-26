#include <stdio.h>
#include <stdlib.h>

//Constantes
#define MAX 200000

//Define o tipo do BigInt
typedef struct biggo {
    int high; 
    int low; 
} BigInt;

//Protótipo das funções a serem executadas
int mediana3(BigInt *v,int i, int j, int k);
void troca(BigInt *biggo,int troca1,int troca2);
void quicksort(BigInt *biggo, int lo, int hi);

int main() {
    //Declaração de variáveis 
    int i=0;
    BigInt biggo[MAX];
    FILE *ints,*quick;

    //Abertura e leitura dos dados necessários para o prigrama
    ints = fopen("./bigint.dat","r");
    do {
        fscanf(ints,"%d %d",&biggo[i].high,&biggo[i].low);
        i++;
    } while(!feof(ints));
    
    //Uso da função passando o primeiro indece do vetor e o ultimo
    quicksort(biggo,0,MAX-1);

    //Abertura e impressão dos dados no arquivo de saida
    quick = fopen("./quick.dat","w");
    for(i=0;i<MAX;i++) {
        fprintf(quick,"%d %d\n",biggo[i].high,biggo[i].low);
    }


    //Fechamento dos arquivos
    fclose(ints);
    fclose(quick);
}

//Função que executa os calculos da mediana de 3
int mediana3(BigInt *v,int i, int j, int k){
    //calcula do valor da mediana para saber qual melhor pivo
    if((v[i].high > v[j].high && v[i].high < v[k].high) || (v[i].high < v[j].high && v[i].high > v[k].high)) {
        return i;
    } else if((v[j].high > v[i].high && v[j].high < v[k].high) || (v[j].high < v[i].high && v[j].high > v[k].high)) {
        return j;
    } else {
        return k;
    }  
}

//Função que troca dos ints de lugar porem usando as posições deles na struct
void troca(BigInt *biggo,int troca1,int troca2) {
    int aux,aux2;
    aux = biggo[troca1].high;
    aux2 = biggo[troca1].low;

    biggo[troca1].high = biggo[troca2].high;
    biggo[troca1].low  = biggo[troca2].low;
    biggo[troca2].high = aux;
    biggo[troca2].low  = aux2;
}

//Função do quicksort diferente usando ao invés de ints um tipo para comparação
void quicksort(BigInt *biggo, int lo, int hi){
    int i,pivo,bigger;
    //hi eh o pivo, que deixa sempre em último

    if(lo<hi){ //indice da primeira e ultima posição
        pivo = mediana3(biggo,lo,(lo+hi)/2, hi); //retorna o indice da mediana
        troca(biggo,pivo,hi); //função que troca o ultimo com o melhor pivo
        bigger=lo;

        //troca os valores menores com os maiores em seus devidos lugares
        for(i=bigger;i<hi;i++){  
            if(biggo[i].high < biggo[hi].high){
                troca(biggo,i,bigger);
                bigger++;
            } else if (biggo[i].high == biggo[hi].high) {
                if(biggo[i].low < biggo[hi].low && biggo[i].high > 0) {
                    troca(biggo,i,bigger);
                    bigger++;
                } else if(biggo[i].low > biggo[hi].low && biggo[i].high < 0) {
                    troca(biggo,i,bigger);
                    bigger++;
                }
            }
        }

        troca(biggo,i,bigger); //troca o pivo com o bigger(pra colcoar o pivo bem no meio
        
        quicksort(biggo, lo, bigger-1); //Re-faz o quicksorte para o lado esquerdo
        quicksort(biggo,bigger+1,hi); //Re-faz o quicksorte para o lado direito
        //Testa se chegou ao fim(ordenado)
        //escolher um pivo que todos menor que ele ficam a esquerda e os maiores ficam a direita
        //senao prepara pra recursao
        //faz a recursao(a cada recursao escolhe um pivo)
    }
}