#include <stdio.h>
#include <stdlib.h>

typedef struct circ {
    int key;
    struct circ *prox;
} Lista;

Lista *criar() {
    Lista *aux;
    aux = (Lista *)malloc(sizeof(Lista));

    scanf("%d", &aux->key);
    aux->prox = aux;

    return aux;
}

void listar(Lista *h) {
    Lista *aux=h, *first=h;

    do {
        printf("[%d] ", aux->key);
        aux = aux->prox;
    } while(aux != first);


    return;
}

void insere_circ(Lista **h, Lista *elem) {
    Lista *atual=(*h), *antes=(*h);
    int i=0;

    if (!atual) {
        (*h) = elem;
        return;
    }

    if ((*h)->prox == (*h)) {
        elem->prox = atual;
        atual->prox = elem;
        if (elem->key < atual->key) {
            (*h) = elem;
        }
        return;
    }

    while(antes->prox != (*h) && elem->key>atual->key) {
        antes = atual;
        atual = atual->prox;
    }

    if (atual == (*h) && elem->key<atual->key) {
        while(antes->prox != atual) {
            antes = antes->prox;
        }
        antes->prox = elem;
        elem->prox = atual;
        (*h) = elem;
        return;
    }

    elem->prox = atual;
    antes->prox = elem;
    return;
}

void remove_circ(Lista **h, int key) {
    Lista *atual,*antes;
    
    if ((*h)==NULL) {
        printf("Lista vazia\n");
        return;
    }

    atual=antes=(*h);
    while(atual->prox != (*h) && key>atual->key) {
        antes=atual;
        atual=atual->prox;
    }

    if (key==atual->key) {
        if(atual->prox==atual) {
            *h==NULL;
            free(atual);
            return;
        }
        if(atual==antes) {
            antes = atual->prox;
            while(antes->prox != (*h)) {
                antes=antes->prox;
            }
            antes->prox = atual->prox;
            (*h) = atual->prox;
            free(atual);
            return;
        }
        antes->prox = atual->prox;
        free(atual);
        return;
    }
    printf("%d nao esta na lista\n",key);
    return;
}

int main() {
    int i,N,aux;
    Lista *novo, *circ=NULL;
    
    do {
        scanf("%d",&aux);
        switch (aux) {
            case 1:
                novo = criar();
                insere_circ(&circ,novo);
                break;
            case 2:
                scanf("%d",&aux);
                remove_circ(&circ,aux);
                listar(circ);
                break;
        }
    } while (aux < 4);

}