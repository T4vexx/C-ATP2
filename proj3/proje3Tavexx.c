#include <stdio.h>
#include <stdlib.h>

//Atribuição da lista circular
typedef struct lista {
    int ind;
    int K;
    int O;
    struct lista *prox;
} Circ;

//Função de criar os novos structs a serem adicionados na lista
Circ *criar(int index, int N) {
    int K,O,auxK;
    Circ *aux;
    aux = (Circ *)malloc(sizeof(Circ));

    scanf("%d %d",&K,&O);

    aux->prox = aux;
    aux->ind = index;
    aux->K = K;
    aux->O = O;

    return aux;
}

//Função de inserção dos objetos um por um
void insere_circ(Circ **h, Circ *elem) {
    Circ *atual,*antes;

    //caso em que a lista esta vazia
    if((*h) == NULL) {
        *h = elem;
        return;
    }
    //caso que so possui 1 item na lista
    if((*h)->prox == (*h)) {
        (*h)->prox = elem;
        elem->prox = (*h);
        return;
    }

    atual=antes=(*h);
    while(antes->prox != (*h)) {
        antes = atual;
        atual = atual->prox;
    }
    //como a inserção sempre e em ordem so possui um caso normal aqui
    antes->prox = elem;
    elem->prox = atual;
    return;
}

//Função de reinserção dos itens que foram excluidos na lista
void reinsere_circ(Circ **h, Circ *elem) {
    Circ *atual,*antes;

    //reincere quando so tem um elemento
    if((*h)->prox == (*h)) {
        (*h)->prox = elem;
        elem->prox = (*h);
        return;
    }

    atual=antes=(*h);
    while(antes->prox != (*h) && elem->ind>atual->ind) {
        antes = atual;
        atual = atual->prox;
    }

    //quando o elemento e menor
    if ((atual == (*h)) && (elem->ind<atual->ind)) {
        while(antes->prox != atual) {
            antes = antes->prox;
        }
        antes->prox = elem;
        elem->prox = atual;
        return;
    }

    //Reincersao normal
    elem->prox = atual;
    antes->prox = elem;
    return;
}

//Função que facilita a reinserção dos itens, pois ela busca qual é a cabeça menor ou seja ela acha qual e o menor index e seta como a cabeça para a reinserção
Circ *acharHead(Circ **h) {
    Circ *antes,*atual;
    int menor;
    antes=atual=(*h);
    menor=antes->ind;

    //while que procura qual é o menor index e salva em uma variavel
    while(antes->prox != (*h)) {
        antes=atual;
        atual=atual->prox;
        if(antes->ind < menor) {
            menor = antes->ind;
        }
    }
    
    //while que procura qual é o item da lista que tem o index menor para ser retornado como cabeça 
    while(antes->ind != menor) {
        antes=atual;
        atual=atual->prox;
    }

    return antes;
}

int main() {
    int N,i,j=0,Kteste;
    Circ *novo,*listaCirc=NULL,*atual,*anterior,*fixo;
    Circ *lastRemoved,*achar;

    scanf("%d",&N);
    //inserção dos item ordenados 1 por 1
    for(i=1;i<=N;i++) {
        novo = criar(i,N);
        insere_circ(&listaCirc,novo);
    }

    atual=anterior=fixo=lastRemoved=listaCirc;
    Kteste=fixo->K; //variavel k que e quantas casas vao andar para retirar sendo a primeira atribuida pelo primeiro valor de K

    //while que roda ate a lista so ter 1 valor que é o resultado 
    while(atual->prox != atual) {
        i=1;

        //segundo while que anda o numero k de casa para retira-lo da lista
        while(i<Kteste) {
            anterior=atual;
            atual = atual->prox;
            i++;
        }
        
        //if para saber se é so tirar o item da lista ou se é para tirar e re inserior o anterior
        if (atual->O == 0) {
            //aqui eu faço a logica de retirada e seto o ultimo que foi retirado para um possivel uso mais para frente
            fixo=atual->prox;
            anterior->prox=atual->prox;
            Kteste=atual->K;
            lastRemoved=NULL;
            lastRemoved=atual;
            lastRemoved->O=0;
            atual=anterior=fixo;
        } else {
            //chamada da função que facilita a reinserção
            achar = acharHead(&atual);
            //reinserção do ultimo item que nao foi inserido
            reinsere_circ(&achar,lastRemoved);
            //aqui eu faço a logica de retirada e seto o ultimo que foi retirado para um possivel uso mais para frente (mesmo do de cima)
            fixo=atual->prox;
            anterior->prox=atual->prox;
            Kteste=atual->K;
            lastRemoved=NULL;
            lastRemoved=atual;
            lastRemoved->O=0;
            atual=anterior=fixo;
        }
    }
    //print da resposta
    printf("%d",atual->ind);
}