#include <stdio.h>
#include <stdlib.h>

typedef struct simples {
    int key;
    struct simples *prox;
} Lsimples;

Lsimples *criar() {
    Lsimples *aux;
    aux = (Lsimples *)malloc(sizeof(Lsimples));

    scanf("%d", &aux->key);
    aux->prox = NULL;

    return aux;
}

void listar(Lsimples *h) {
    Lsimples *aux=h;

    do {
        printf("[%d] ", aux->key);
        aux = aux->prox;
    } while(aux != NULL);

    return;
}

void insere_simples(Lsimples **h, Lsimples *elem) {
    Lsimples *atual,*antes;

    if(!(*h)) {
        (*h) = elem;
        return;
    }

    antes=atual=*h;
    while(atual->prox && elem->key>atual->key) {
        antes=atual;
        atual=atual->prox;
    }

    if(atual==(*h)) {
        if (elem->key<atual->key) {
            elem->prox = (*h);
            (*h) = elem;
            return;
        }
    }

    if(elem->key<atual->key) {
        elem->prox = atual;
        antes->prox = elem;
        return;
    } else {
        atual->prox = elem;
        return;
    }
        

}

// void remove_simples(Lsimples **h, Lsimples **t, int key) {
//     Lsimples *atual;
// }

int main() {
    int i,N,aux,remover;
    Lsimples *novo,*simples_h=NULL;

    do {
        scanf("%d",&aux);
        switch (aux) {
            case 1:
                novo = criar();
                insere_simples(&simples_h,novo);
                break;
            case 2:
                scanf("%d",&remover);
                //remove_simples(&simples_h,remover);
                listar(simples_h);
                break;
            case 3: 
                listar(simples_h);
                break;
        }
    } while (aux < 4);

}