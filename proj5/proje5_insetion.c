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
void insertionSort(BigInt *biggo,int limit);

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
    insertionSort(biggo,MAX);

    //Abertura e impressão dos dados no arquivo de saida
    quick = fopen("./insertion.dat","w");
    for(i=0;i<MAX;i++) {
        fprintf(quick,"%d %d\n",biggo[i].high,biggo[i].low);
    }


    //Fechamento dos arquivos
    fclose(ints);
    fclose(quick);
}

//Função do insertion porém usando struct como tipo de dado
void insertionSort(BigInt *biggo,int limit) {
    int i, j;
    BigInt aux;
    
    //Logica do insertion de comparação, só que agora usando os dados da struct
    for (i = 1; i < limit; i++) {
        aux =  biggo[i];
        j = i;
        while(j > 0 && ((biggo[j-1].high > aux.high) || (aux.high == biggo[j-1].high && biggo[j-1].low > aux.low) || (aux.high == biggo[j-1].high && aux.high < 0 && biggo[j-1].low < aux.low ))) { 
            biggo[j] = biggo[j-1]; 
            j--; 
        }
        biggo[j] = aux;

    }
}