#include <stdio.h>
#include <stdlib.h>
// Protótipos:
void pegaMatrix(int *, int);
void imprimeMatriz(int *, int);
int espiralHorario(int *, int);

int main(void) {
  int **matriz;
  int N, i, j, resp;
  printf("Digite a ordem da matriz quadrada:\n");
  scanf("%d", &N);
  matriz = malloc(N * sizeof(int *));
  for (i = 0; i < N; i++) {
    matriz[i] = malloc(N * sizeof(int));
  }
  pegaMatrix(&matriz[0][0], N);
  imprimeMatriz(&matriz[0][0], N);
  resp = espiralHorario(&matriz[0][0], N);
  printf("\nA resp é = %d", resp);
  return 0;
}

void pegaMatrix(int *matriz, int N) {
  int i;
  for (i = 0; i < N * N; i++) {
    printf("\nDigite o elemento na respectiva posição\n");
    scanf("%d", &(*matriz));
    matriz++;
  }
}

void imprimeMatriz(int *matriz, int N) {
  printf("\t----> MATRIZ <----\n");
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("[ %d ]", *matriz);
      matriz++;
    }
    printf("\n");
  }
}

int espiralHorario(int *matriz, int N) {
  int resp = N, i, j,origem = 0, auxiliar = N, flag = N;
  int **aux;
  aux = malloc(N * sizeof(int *));
  for (i = 0; i < N; i++) {
    aux[i] = malloc(N * sizeof(int));
  }
  
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      aux[i][j] = *matriz;
      matriz++;
    }
  }
  do {

    for (i = origem; i < auxiliar - 1; i++) {
      if (aux[origem][i] + 1 != aux[origem][i + 1]) {
        return 0;
      }
    }

    for (i = origem; i < auxiliar - 1; i++) {
      if (aux[i][auxiliar - 1] + 1 != aux[i + 1][auxiliar - 1]) {
        return 0;
      }
    }

    for (i = auxiliar - 1; i > origem; i--) {
      if (aux[auxiliar - 1][i] + 1 != aux[auxiliar - 1][i - 1]) {
        return 0;
      }
    }

    for (i = auxiliar - 1; i > origem + 1; i--) {
      if (aux[i][origem] + 1 != aux[i - 1][origem]) {
        return 0;
      }
    }

    if(N % 2 == 0){
      flag = flag / 2;
    }else{
      flag = flag - 2;
    }
    auxiliar --;
    origem ++;
  }while(flag != 1);

  if(N % 2 && aux[N/2][N/2] != aux[N/2][(N/2) - 1] + 1){
    return 0;
  }  

  return(resp);
}