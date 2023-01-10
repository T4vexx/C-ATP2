#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
    char key[100];
    struct lista *prox;
} Tlista;

void insere(Tlista **h, Tlista *elem, char *key) {
    Tlista *antes,*atual;
    Tlista *tmp = *h, *prev = NULL;
	int res = 0;
	if (!*h) {
		elem->prox = NULL, *h = elem;
		return;
	}

	while (tmp != NULL) {
		res = strcmp(tmp->key, key);
		if (res > 0)
			break;
		if (res == 0) {
			free(elem);
			return;
		}
		prev = tmp, tmp = tmp->prox;
	}

	if (res > 0) {
		if (*h == tmp)
			elem->prox = *h, *h = elem;
		else
			elem->prox = prev->prox, prev->prox = elem;
	} else
		prev->prox = elem, elem->prox = NULL;
	return;
    // if(!(*h)) {
    //     *h = elem;
    //     return;
    // }
    // antes=atual=*h;
    // while(atual->prox && strcmp(elem->key,atual->key) > 0) {
    //     antes = atual;
    //     atual = atual->prox;
    // }
    // if(atual == *h) {
    //     if(strcmp(elem->key,atual->key)<0) {
    //         elem->prox = atual;
    //         *h=elem;
    //         return;
    //     } else if (strcmp(elem->key,atual->key)>0) {
    //         elem->prox = atual->prox;
    //         atual->prox = elem;
    //         return;
    //     }
    //     return;
    // }
    // if(!(atual->prox)) {
    //     if(strcmp(elem->key,atual->key)<0) {
    //         antes->prox = elem;
    //         elem->prox = atual;
    //         return;
    //     } else if (strcmp(elem->key,atual->key)>0) {
    //         atual->prox = elem;
    //         return;
    //     }
    //     return;
    // }
    // antes->prox = elem;
    // elem->prox = atual;
    // return;
}

void remover(Tlista **h, char *key) {
    Tlista *atual=*h,*prev=NULL;
    int response = 1;
	if (!*h)
		return;
	while (atual != NULL && (response = strcmp(atual->key, key)))
		prev = atual, atual = atual->prox;
	if (response)
		return;

	if (!prev) {
		atual = *h;
		*h = (*h)->prox;
		free(atual);

	} else if (atual != NULL) {
		prev->prox = atual->prox;
		free(atual);
	} else {
		prev->prox = NULL;
		free(atual);
	}
	return;
}

void listar(Tlista **h, char *key) {
    Tlista *atual;
    atual=*h;
    while(atual != NULL && strcmp(atual->key, key) < 0) {
        atual = atual->prox;
    }
    if(atual == NULL) {
        printf("NULL\n");
        return;
    }
    while(atual != NULL) {
        printf("%s ",atual->key);
        atual = atual->prox;
    }
    printf("\n");
    return;
}

int main() {
    int i,N,M,opt;
    char chave[100];
    Tlista *lista_h=NULL,*novo;
    scanf("%d",&N);
    scanf("%d",&M);
    for(i=0;i<N;i++) {
        scanf(" %s", chave);
        novo = (Tlista *)malloc(sizeof(Tlista));
        strcpy(novo->key,chave);
        novo->prox = NULL;
        insere(&lista_h,novo,chave);
    }
    for(i=0;i<M;i++) {
        scanf("%d",&opt);
        switch(opt) {
            case 0: {
                scanf(" %s", chave);
                remover(&lista_h,chave);
                break;
            }     
            case 1: {
                scanf(" %s", chave);
                novo = (Tlista *)malloc(sizeof(Tlista));
                strcpy(novo->key,chave);
                novo->prox = NULL;
                insere(&lista_h,novo,chave);
                break;
            } 
            case 2: {
                scanf(" %s", chave);
                listar(&lista_h, chave);
                break;
            }      
        }
    }
    return 0;
}