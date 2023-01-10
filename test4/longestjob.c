#include <stdio.h>
#include <stdlib.h>

typedef struct Lista {
    int ti;
    int ci;
    struct Lista *prox;
} TLista;

TLista *scanear() {
  TLista *aux = malloc(sizeof(TLista));

  scanf("%d", &aux->ti);
  scanf("%d", &aux->ci);

  aux->prox = NULL;
  return aux;
}

TLista *insere(TLista *h, TLista *p) {
    TLista *aux, *anterior;
    if (h == NULL)
        return p;

    aux = anterior = h;

    while (aux->prox && p->ci > aux->ti) {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == h) {
        if (p->ti > aux->ti) {
            p->prox = h->prox;
            h->prox = p;
            return h;
        } else {
            p->prox = h;
            return p;
        }
    }

    if (p->ti > aux->ti) {
        p->prox = aux->prox;
        aux->prox = p;
    } else {
        p->prox = aux;
        anterior->prox = p;
    }
    return h;
}

void remover(TLista **h, int ci) {
    TLista *aux = *h, *anterior;
    if (aux != NULL && aux->ci == ci) {
        *h = aux->prox;
        free(aux);
        return;
    }

    while (aux != NULL && aux->ci != ci) {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        return;
    }
  
    anterior->prox = aux->prox;
    free(aux);
}

int buscar(TLista *h, int menor) {
    TLista *aux = h;
    int maior = 0;

    while (aux && aux->ti <= menor) {
        if (aux->ci > maior) {
        maior = aux->ci;
        }

        aux = aux->prox;
        
    }
    return maior;
}

int main() {
    int N,i,menor,biggest=10001,*resp;
    TLista *listaTempo = NULL, *novo;

    scanf("%d",&N);

    resp = malloc(N * sizeof(int));

    for(i=0;i<N;i++) {
        novo = scanear();
        if (novo->ti < menor) {
            menor = novo->ti;
        }
        listaTempo = insere(listaTempo,novo);
    }

    i = 0;

    while (listaTempo) {
        biggest = buscar(listaTempo, menor);

        if (biggest == 0) {
            menor = listaTempo->ti;
            biggest = buscar(listaTempo, menor);
        }

        remover(&listaTempo, biggest);

        resp[i] = biggest;
        i++;
        menor += biggest;
    }

    for (i=0;i<N;i++) {
        printf("%d ", resp[i]);
    }
    printf("\n");

    return 0;
}
