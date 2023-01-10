#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int d;
    struct lista *prox;
} Pilha;

void movimenta(int disco, Pilha **poste_orig, Pilha **poste_dest) {
    Pilha *aux;
    int d;

    (*poste_orig)->d = d;
    if(d != disco) {
        printf("Disco Errado\n");
        return;
    }

    aux = (*poste_orig)->prox;
    free(*poste_orig);
    *poste_orig = aux;
    aux = (Pilha *)malloc(sizeof(Pilha));
    aux->d = disco;
    aux->prox = (*poste_dest);
    *poste_dest = aux;
    return;
}
