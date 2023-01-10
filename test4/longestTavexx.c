#include <stdio.h>
#include <stdlib.h>

typedef struct TempoLista {
  int ti;
  int ci;
  struct TempoLista *prox;
} Listati;

Listati *scanear() {
  Listati *aux = malloc(sizeof(Listati));

  scanf("%d", &aux->ti);
  scanf("%d", &aux->ci);

  aux->prox = NULL;
  
  return aux;
}

Listati *adicionar(Listati *h, Listati *p) {
  Listati *aux, *anterior;
  if (h == NULL)
    return p;

  aux = anterior = h;

  while (aux->prox && p->ti > aux->ti) {
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

void retiraitem(Listati **h, int ci) {
  Listati *aux = *h, *anterior;
  if (aux != NULL && aux->ci == ci) {
    *h = aux->prox;
    free(aux);
    return;
  }
  while (aux != NULL && aux->ci != ci) {
    anterior = aux;
    aux = aux->prox;
  }
  if (aux == NULL)
    return;
  anterior->prox = aux->prox;
  free(aux);
}

int busca(Listati *h, int menor) {
  Listati *aux = h;
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
  int N, j, menor = 10001, maior, *resp; //Esse maximo no menor é definido no exer
  Listati *Listati = NULL, *new; //inicia a Listati vazia
  scanf("%d", &N);

  resp = malloc(N * sizeof(int));

  for (j=0;j<N;j++) {
    new = scanear();

    if (new->ti < menor) {
      menor = new->ti;
    }
      
    Listati = adicionar(Listati, new);
  }

  j = 0;

  do  {
    if (Listati) {
      maior = busca(Listati, menor);

      if (maior == 0) {
        menor = Listati->ti;
        maior = busca(Listati, menor);
      }

      retiraitem(&Listati, maior);

      resp[j] = maior;
      j++;
      menor += maior;
    }
  } while (Listati);

  j=0;
  
  while (j<N) {
    printf("%d ", resp[j]);
    j++;
  }
  printf("\n");

  return 0;
}