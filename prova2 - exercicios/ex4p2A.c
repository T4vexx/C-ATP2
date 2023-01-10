#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct circular {
    char um_nome[40];
    struct circular *prox;
} CIRC;

CIRC *inic, *fim;

CIRC *insere(CIRC *inic, CIRC *fim, char novo[40]) {
    CIRC *aux;

    if(vazia(inic,fim)) {
        strcpy(inic->um_nome,novo);
        return(aux);
    }

    aux = (CIRC *)malloc(sizeof(CIRC));
    strcpy(aux->um_nome,novo);
    aux->prox = fim;
    inic->prox = aux;
    return(aux);
}

CIRC *Remove (CIRC *inic, CIRC *fim, char *ret) {
    if(!vazia(inic,fim)) {
        if (inic == fim) {
            strcpy(inic->um_nome,"NULL");
            return(fim);
        }
        inic->prox = fim->prox;
        free(fim);
        return(inic->prox);
    }
}

int vazia(CIRC *inic, CIRC *fim) {
    if(inic != fim || strcmp(inic->um_nome, "NULL")) {
        return 0;
    } else {
        return 1;
    }
}

