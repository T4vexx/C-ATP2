#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_sort(char **vet, int size) {
    int i,j,g,value;
    int gap = 1;
  
    do {
        gap = gap*2;
    } while(gap <= size/4);
  
    do {
        gap /= 2;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i - gap;
    
            while (j >= 0 && strcmp(value,vet[j]) < 0) {
                vet[j + gap] = vet[j];
                j -= gap;
            }
            vet[j + gap] = value;
        }

        for(g=0;g<size;g++) {
            printf("%s ",vet[g]);
        }
        printf("\n");
    }while(gap > 1);
}



int main() {
    int i,N;
    char **mat;

    scanf("%d",&N);

    mat = malloc(N * sizeof(char *));
    for(i=0;i<N;i++) {
        mat[i] = malloc(50 * sizeof(char));
    }

    for(i=0;i<N;i++) {
        scanf("%s", mat[i]);
    }

    shell_sort(mat,N);
}