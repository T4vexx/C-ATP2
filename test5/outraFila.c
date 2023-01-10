#include <stdio.h>
#include <stdlib.h>

typedef struct simples {
    int TJ;
    int IJ;
    struct simples *prox;
} Lsimples;

Lsimples *criar() {
    int IJ,TJ;
    Lsimples *aux;
    aux = (Lsimples *)malloc(sizeof(Lsimples));
    scanf("%d %d", &aux->IJ,&aux->TJ);
    aux->prox = NULL;

    return aux;
}

void listar(Lsimples *h) {
    Lsimples *aux=h;

    while (aux != NULL) {
        printf("%d ", aux->IJ);
        aux = aux->prox;
    }
    printf("\n");
    return;
}

void insere_simples(Lsimples **h, Lsimples **t, Lsimples *elem) {
    Lsimples *atual,*antes;

    if(!(*h)) {
        (*h) = elem;
        (*t) = elem;
        return;
    }

    if (elem->TJ < (*h)->TJ || (elem->TJ == (*h)->TJ && elem->IJ > 59 && elem->IJ > (*h)->IJ)) {
        elem->prox = *h;
        *h = elem;
        return;
    }

    if (elem->TJ > (*t)->TJ) {
        elem->prox = NULL;
        (*t)->prox = elem;
        *t = elem;
        return;
    }

    antes=*h;
    atual=(*h)->prox;
    while(atual!=NULL) {
        if (elem->TJ < atual->TJ || (elem->TJ == atual->TJ && elem->IJ > 59 && elem->IJ > atual->IJ)) {
            antes->prox = elem;
            elem->prox = atual;
            return;
        }
        antes=atual;
        atual=atual->prox;
    }

    if (elem->TJ == (*h)->TJ && ((*h)->prox == NULL || (*h)->prox->TJ != elem->TJ)) {
        elem->prox = (*h)->prox;
        (*h)->prox = elem;
        return;
    }

    atual = (*h)->prox;
    while (atual != NULL) {
        if (elem->TJ == atual->TJ && (atual->prox == NULL || atual->prox->TJ != elem->TJ)) {
            elem->prox = atual->prox;
            atual->prox = elem;
            if (elem->prox == NULL) {
                *t = elem;
            } 
            return;
        }
        atual = atual->prox;
    }

}

void insere_Lfila(Lsimples **h, Lsimples **t, int idade, int tempo) {
    Lsimples *novo,*aux,*aux_anterior;
    novo = (Lsimples *)malloc(sizeof(Lsimples));
    novo->IJ = idade;
    novo->TJ = tempo;

    if ((*h)==NULL) {
        *h = novo;
        *t = novo;
        novo->prox = NULL;
        return;
    }

    if (novo->IJ > 59) {
        if (novo->IJ > (*h)->IJ) {
            novo->prox = *h;
            *h = novo;
            return;
        }

        aux = (*h)->prox;
        aux_anterior = (*h);

        while(aux!=NULL){
            if (novo->IJ>aux->IJ) {
                aux_anterior->prox = novo;
                novo->prox = aux;
                return;
            }
            aux_anterior = aux;
            aux = aux->prox;
        }

        
    }

    (*t)->prox = novo;
    novo->prox = NULL;
    *t = novo;
}

void remover_filaToLfila(Lsimples **h, Lsimples **t) {
    Lsimples *aux = *h;

    if (*h == NULL) {
        return;
    }
    if ((*h)->prox == NULL) {
        free(*h);
        *h = NULL;
        *t = NULL;
        return;
    }
    if ((*h)->prox == *t) {
        free(*h);
        *h=*t;
        return;
    }
    
    *h=(*h)->prox;
    free(aux);
}

int main() {
    int N,i,tempo_i,idade_a,tempo_atual=3,inseriu=1;
    Lsimples *novo,*simples_h=NULL,*simples_t=NULL,*fila_h=NULL,*fila_t=NULL;


    scanf("%d",&N);
    for(i=0;i<N;i++) {
       novo = criar();
       insere_simples(&simples_h,&simples_t,novo);
    }

    // primeiro bloco de para adicionar o primeiro caso
    tempo_i = simples_h->TJ;
    idade_a = simples_h->IJ;
    insere_Lfila(&fila_h,&fila_t,simples_h->IJ,simples_h->TJ);
    remover_filaToLfila(&simples_h,&simples_t);

    // Resolução dos demais casos
    while (simples_h!=NULL || fila_h!=NULL) {
        if (tempo_atual>=3) {
            tempo_atual = 0;
            if (fila_h==NULL) {
                insere_Lfila(&fila_h,&fila_t,simples_h->IJ,simples_h->TJ);
                tempo_i = simples_h->TJ;
                remover_filaToLfila(&simples_h,&simples_t);
                inseriu = 1;
            }
            idade_a = fila_h->IJ;
            remover_filaToLfila(&fila_h,&fila_t);
        }

        while (simples_h!=NULL && tempo_i>=simples_h->TJ) {
            insere_Lfila(&fila_h,&fila_t,simples_h->IJ,simples_h->TJ);
            remover_filaToLfila(&simples_h,&simples_t);
            inseriu = 1;
        }

        if (inseriu) {
            printf("%d ",idade_a);
            listar(fila_h);
        }

        tempo_atual++;
        tempo_i++;
        inseriu = 0;
    }
}