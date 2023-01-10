#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int d;
    struct lista *prox;
} Pilha;

void push(int);
Pilha *pop(int *);

int main() {
    int quoc,aux;

    scanf("%d", &aux);
    quoc = aux;

    if(quoc == 0) {
        push(0);
    } else {
        while (quoc > 0) {
            push(quoc%2);
            quoc = quoc / 2;
        }
    }

    printf("decimal %d => ",aux);

    while(pop(&aux) != NULL) {
        printf("%d ",aux);
    }
    printf("%d ",aux);
}





