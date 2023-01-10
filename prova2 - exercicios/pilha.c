#include <stdio.h>
#include <stdlib.h>

typedef struct pilha {
    int key;
    struct pilha *prox;
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
        printf("[%d]\n", aux->key);
        aux = aux->prox;
    } while(aux != NULL);

    return;
}

void insere_pilha(Lista **h, Lista *elem) {
    elem->prox = *h;
    *h = elem;
}

Lista *remove_pilha(Lista **h) {
    Lista *atual;

    atual = *h;
    if (atual) {
        (*h) = atual->prox;
    } else {
        printf("Pilha vazia\n");
    }

    return(atual);
}

int main() {
    int i,N,aux;
    Lista *novo, *usage, *pilha=NULL;
    
    do {
        scanf("%d",&aux);
        switch (aux) {
            case 1:
                novo = criar();
                insere_pilha(&pilha,novo);
                break;
            case 2:
                usage = remove_pilha(&pilha);
                printf("%d ",usage->key);
                break;
            case 3:
                listar(pilha);
                break;
        }
    } while (aux < 4);

}