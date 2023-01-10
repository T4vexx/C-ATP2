#include <stdio.h>
#include <stdlib.h>

typedef struct fila {
    int key;
    struct fila *prox;
} Lista;

Lista *criar() {
    Lista *aux;
    aux = (Lista *)malloc(sizeof(Lista));

    scanf("%d", &aux->key);
    aux->prox = NULL;

    return aux;
}

void listar(Lista *h) {
    Lista *aux=h;

    do {
        printf("[%d] ", aux->key);
        aux = aux->prox;
    } while(aux != NULL);

    return;
}

void insere_fila(Lista **h, Lista **t, Lista *elem) {
    Lista *atual;

    if(!(*h)) {
        (*h)=(*t)=elem;
        return;
    } 
    (*t)->prox = elem;
    *t = elem;
    return;
}

Lista *remove_fila(Lista **h, Lista **t) {
    Lista *atual;

    if((*h) == NULL) {
        printf("Fila vazia\n");
    }
    if((*h)!=(*t)) {
        atual=(*h);
        (*h)=atual->prox;
    } else {
        *t=*h=NULL;
    }

    return(atual);
}

int main() {
    int i,N,aux;
    Lista *novo, *usage, *fila_h=NULL, *fila_t=NULL;
    
    do {
        scanf("%d",&aux);
        switch (aux) {
            case 1:
                novo = criar();
                insere_fila(&fila_h, &fila_t, novo);
                break;
            case 2:
                usage = remove_fila(&fila_h,&fila_t);
                printf("%d ",usage->key);
                break;
            case 3:
                listar(fila_h);
                break;
        }
    } while (aux < 4);

}