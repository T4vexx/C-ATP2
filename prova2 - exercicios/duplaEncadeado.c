#include <stdio.h>
#include <stdlib.h>

typedef struct dupla {
    int key;
    struct dupla *prox;
    struct dupla *prev;
} Ldupla;

Ldupla *criar() {
    Ldupla *aux;
    aux = (Ldupla *)malloc(sizeof(Ldupla));

    scanf("%d", &aux->key);
    aux->prox = NULL;
    aux->prev = NULL;

    return aux;
}

void listar(Ldupla *h) {
    Ldupla *aux=h;

    do {
        printf("[%d] ", aux->key);
        aux = aux->prox;
    } while(aux != NULL);

    return;
}

void insere_dupla(Ldupla **h, Ldupla **t, Ldupla *elem) {
    Ldupla *atual;

    if (*h==NULL) {
        *h=*t=elem;
        return;
    }

    atual=*h;
    while(atual->prox && elem->key>atual->key) {
        atual=atual->prox;
    }
    if(atual==*h) {
        if(!(elem->key>atual->key)) {
            elem->prox = atual;
            elem->prev = NULL;
            atual->prev = elem;
            *h = elem;
        } else {
            if (*h=*t) {
                *t=elem;
            }
            elem->prox=atual->prox;
            elem->prev=atual;
            atual->prox=elem;
        }
    } else {
        elem->prox = atual;
        elem->prev = atual->prev;
        (atual->prev)->prox = elem;
        atual->prev = elem;
    }
}

void remove_dupla(Ldupla **h, Ldupla **t, int key) {
    Ldupla *atual;
    
    if(!(*h)) {
        printf("Lista vazia\n");
        return;
    }

    atual=(*h);
    while(key>atual->key) {
        atual = atual->prox;
    }
    if(key==atual->key) {
        if(atual==*h) {
            *h=atual->prox;
            (atual->prox)->prev = NULL;
        } else {
            (atual->prev)->prox = atual->prox;
        }
        if(*t==atual) {
            *t=NULL;
        } else {
            (atual->prox)->prev=atual->prev;
        }
        free(atual);
        return;
    }
    printf("Lista vazia\n");
    return;
}

int main() {
    int i,N,aux,remover;
    Ldupla *novo,*dupla_h=NULL,*dupla_t=NULL;

    do {
        scanf("%d",&aux);
        switch (aux) {
            case 1:
                novo = criar();
                insere_dupla(&dupla_h,&dupla_t,novo);
                break;
            case 2:
                scanf("%d",&remover);
                remove_dupla(&dupla_h,&dupla_t,remover);
                listar(dupla_h);
                break;
            case 3: 
                listar(dupla_h);
                break;
        }
    } while (aux < 4);

}