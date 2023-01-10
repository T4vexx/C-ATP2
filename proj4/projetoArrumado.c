#include <stdio.h>
#include <stdlib.h>

// struct que armazena a fila ordenada por ordem de chegada com sua restrições
typedef struct fila {
    int Ii;
    int Oi;
    int Ci;
    struct fila *prox;
} Tfila;

// struct que armazena os caixar, contendo o tempo(tempo para cada operação que vai sendo decrecido) e total(total de tempo gasto)
typedef struct caixa {
    int tempo;
    int totalC;
    int total;
} Tcaixa;

// função que cria os itens da fila e retorna para a main para serem alocados na fila
Tfila *criar() {
    int Ii,Oi,Ci;
    Tfila *aux;
    aux = (Tfila *)malloc(sizeof(Tfila));
    scanf("%d %d %d",&Ii,&Oi,&Ci);

    aux->Ii = Ii;
    aux->Oi = Oi;
    aux->Ci = Ci;
    aux->prox = NULL;

    return aux;
}

// função que pegas os elementos e organizam eles na fila de acordo com a ordem de chegada e suas outras restrições 
void insere_ordfila(Tfila **h, Tfila *elem) {
    Tfila *antes,*atual;

    if(!(*h)) {
        *h = elem;
        return;
    }

    antes=atual=*h;
    while(atual->prox && elem->Oi > atual->Oi) {
        antes=atual;
        atual=atual->prox;
    }

    // caso em que o atual continua sendo a cabeça
    if(atual == (*h)) {
        if(elem->Oi>atual->Oi) {
            atual->prox = elem;
        } else if (elem->Oi<atual->Oi) {
            elem->prox = atual;
            *h=elem;
        } else if (elem->Oi==atual->Oi) {
            if(elem->Ii<atual->Ii) {
                elem->prox = atual;
                *h=elem;
            } else {
                if(atual->prox != NULL && (atual->prox)->Ii < elem->Ii) {
                    atual = atual->prox;
                    atual->prox = elem;
                    return;
                }

                
                elem->prox = atual->prox;
                atual->prox = elem;
            }
        }
        return;
    }

    //caso em que nao tem prox e o elemento tem que ser adicionado por ultimo
    if((!(atual->prox)) && elem->Oi > atual->Oi) {
        atual->prox = elem;
        return;
    }

    //caso em que o os tempos sao iguais 
    if(elem->Oi == atual->Oi) {
        if(elem->Ii<atual->Ii) {
           antes->prox = elem;
           elem->prox = atual;
        } else {
            elem->prox = atual->prox;
            atual->prox = elem;
        }
        return;
    }

    //caso padrao
    antes->prox = elem;
    elem->prox = atual;
    return;
}

// função que remove o item da fila e retorna ele para ser usado nos caixas 
Tfila *remover_fila(Tfila **h) {
    Tfila *aux;

    // remoção para lista vazia
    if(!(*h)) {
        return NULL;
    }

    // remoção para unica
    if ((*h)->prox == NULL) {
        aux = *h;
        *h = NULL;
        return aux;
    }

    // remoção padrão
    aux = *h;
    *h = (*h)->prox;
    return aux;
}

// função auxiliar de listagem -- teste -- 
// void listar(Tfila *h) {
//     Tfila *aux=h;
//     while (aux!= NULL) {
//         printf("%d ", aux->Ii);
//         aux = aux->prox;
//     } 

//     return;
// }

//listar(lista_h);

int main() {
    int i,N,M,*count,flag=0;
    Tfila *lista_h=NULL,*aux;
    Tcaixa *caixa;
    
    scanf("%d %d",&N,&M);

    // for que cria o item e ja adiciona o mesmo na fila ordenado
    for(i=0;i<N;i++) {
        aux = criar();
        insere_ordfila(&lista_h,aux);
    }   

    count = (int *)malloc(M * sizeof(int));
    caixa = (Tcaixa *)malloc(M * sizeof(Tcaixa));

    //inicialização dos contadores como zero
    for (i = 0; i < M; i++) {
        caixa[i].tempo = 0; 
        caixa[i].total = 0;
        caixa[i].totalC = 0;
        count[i] = 0;
    }

    // while que faz toda a logica dos caixas com tempo decrecido
    while(aux != NULL) {
        for (i = 0; i < M; i++) {
            if(caixa[i].tempo == 0) {
                aux = remover_fila(&lista_h);
                if (aux != NULL && caixa[i].totalC >= aux->Oi) {
                    caixa[i].tempo = aux->Ci;
                    caixa[i].totalC = caixa[i].totalC + aux->Ci;
                    caixa[i].total = caixa[i].total + aux->Ci + count[i];
                    count[i] = 0;
                } else if (aux != NULL) {
                    caixa[i].totalC++;
                    //caixa[i].total++;
                    count[i]++;
                    insere_ordfila(&lista_h,aux);
                }
            } else {
                caixa[i].tempo--;
            }   
        }

    } 

    // printa os tempos dos caixas 
    for (i = 0; i < M; i++) {
        printf("%d ",caixa[i].total);
    }
}