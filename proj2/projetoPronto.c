#include <stdio.h>
#include <stdlib.h>

//variavel global das respostas
int resposta[100] = {0};
int counter = 0;

//funçao que usa recursao para fazer todas as combinaçoes possiveis e selecionar apenas as que sao pedidas pela variavel numero
void combinacao(int arr[], int data[], int start, int end, int index, int r, int numero) {
    int i, j, soma=0;

    //caso primario da função que retorna os valores
    if (index == r) {
        //For que soma a combinação para ser comparada mais tarde
        for (j=0; j<r; j++) {
            soma = soma + data[j];
        }
        
        //condicional que verifica se a soma na combinação e igual ao numero
        if (soma == numero) {
            //verificação para salvar na resposta apenas a combinação com o maior valor
            if (resposta[r-1] < data[r-1]) {
                for (j=0; j<r; j++) {
                    //printf("%d ", data[j]);
                    resposta[j] = data[j];    
                }            
            }  
            
            //printf("\n");
            //contador que aumenta o valor de acordo com o tanto de combinações para a resposta
            counter = counter + 1;
        }

        soma = 0; 
        return;
    }
          
    //For que realiza as combinaçoes e as chamadas recursivas
    // para nao dar segment fault Isso é importante para evitar tentativas de acessar elementos fora do intervalo válido do vetor de entrada. 
    for (i=start; i<=end && end-i+1 >= r-index; i++) {
        data[index] = arr[i];
        combinacao(arr, data, i+1, end, index+1, r, numero);
    }
}

//função que aloca um vetor e salva as variaveis para o vetor resposta
void printarCombinacao(int arr[], int n, int r, int numero) {
    int *data;
    data = malloc(r * sizeof(int));
    
    combinacao(arr, data, 0, n-1, 0, r, numero);
}

int main() {
    int i,j,N,M;
    int *vetM,*vetKi;
    //N -> quantidades de numeros a serem decompostos
    //M -> quantidades de numeros que podem serem usados na decomposição
    scanf("%d %d", &N, &M);

    //Alocar dinamicamente o vetor que vai conter osc numeros usados para serem decompostos
    vetM = malloc(M * sizeof(int));
    //Recebe todos os valores dos numeros usados para serem decompostos
    for(i=0;i<M;i++) {
        scanf("%d", &vetM[i]);
    }

    //Alocar dinamicamente o vetor que vai conter os numeros a serem decompostos
    vetKi = malloc(N * sizeof(int));
    //Recebe todos os valores dos numeros a serem decompostos
    for(j=0;j<N;j++) {
        scanf("%d", &vetKi[j]);
    }

    //n = sizeof(vetM)/sizeof(int);
    //v = sizeof(vetKi)/sizeof(int);

    //for para fazer as combinaçoes para cada numero
    for (j=0;j<N; j++) {
        //for para fazer as combinaçoes para todos os valores do vetor
        for(i=2; i<=M; i++) { 
            printarCombinacao(vetM, M, i, vetKi[j]); 
        }  
        
        printf("%d ", counter);
        counter=0;

        //Print da resposta
        for(i=0; i < 100; i++) { 
            if (resposta[i] != 0) {
                printf("%d ", resposta[i]);
                resposta[i] = 0;
            }
        }    

        printf("\n");
    }   
}
