#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dictionary {
    char palavra[20];
    struct dictionary *prox;
} Tdic;

void insere(Tdic **h,char *word) {
    Tdic *aux,*antes,*adicionar;
    if (!(*h)) {
        adicionar = (Tdic *)malloc(sizeof(Tdic));
        strcpy(adicionar->palavra,word);
        adicionar->prox = NULL;
        *h = adicionar;
    } else {
        aux=antes=*h;
        while (aux->prox && strcmp(word,aux->palavra)>0) {
            antes=aux;
            aux=aux->prox;
        }

        if (aux==*h) {
            adicionar = (Tdic *)malloc(sizeof(Tdic));
            if(strcmp(word,aux->palavra)>0) {
                aux->prox = adicionar;
                adicionar->prox = NULL;
                strcpy(adicionar->palavra,word);
            } else if(strcmp(word,aux->palavra)<0) {
                adicionar->prox = aux;
                strcpy(adicionar->palavra,word);
                *h=adicionar;
            } else {
                return;
            }
        }else {
            if (strcmp(word,aux->palavra)>0) {
                adicionar = (Tdic *)malloc(sizeof(Tdic));
                adicionar->prox = aux->prox;
                aux->prox = adicionar;
                strcpy(adicionar->palavra,word);
            }else if (strcmp(word,aux->palavra)<0) {
                adicionar = (Tdic *)malloc(sizeof(Tdic));
                antes->prox = adicionar;
                adicionar->prox = aux;
                strcpy(adicionar->palavra,word);
            } else {
                return;
            }   
        }
    } 
}

void remover(Tdic **h, char *word) {
    Tdic *aux,*antes;
    if (!(*h)) {
       return;
    } else {
        aux=antes=*h;
        while(strcmp(word,aux->palavra)!=0 && aux->prox) {
            antes=aux;
            aux=aux->prox;
        }
        if(aux == (*h)) {
            if(!strcmp(word,aux->palavra)) {
                *h = aux->prox; 
                free(aux);
            }    
        } else {
            if(!strcmp(word,aux->palavra)) {
                antes->prox = aux->prox;
                free(aux);
            }
        }
        
    } 
}

void listar(Tdic *h) {
    while(h != NULL)    
    {
        printf("%s ",h->palavra);
        h = h->prox;   
    }
    printf("\n");
}

int main() {
    int N,M,i,aux;
    char auxP[20];
    Tdic *dicionario = NULL;

    scanf("%d %d",&N,&M);

    for(i=0;i<N;i++){
        scanf("%s", auxP);
        insere(&dicionario,auxP);
    }

    for(i=0;i<M;i++) {
        scanf("%d %s",&aux,auxP);
        if(aux==1) {
            insere(&dicionario,auxP);
        }else if(aux==0) {
            remover(&dicionario,auxP);
            if (dicionario == NULL) {
                printf("NULL\n");
            } else {
                listar(dicionario);
            }
        }               
    }

}


// void insere(TLista **h, int ti, int ci) {
//     TLista *aux,*antes,*adicionar;
//     if (!(*h)) {
//         adicionar = (TLista *)malloc(sizeof(TLista));
//         adicionar->ti = ti;
//         adicionar->ci = ci;
//         adicionar->prox = NULL;
//         *h = adicionar;
//         return;
//     } else {
//         aux=antes=*h;
//         while (aux->prox && aux->ti < ti) {
//             antes=aux;
//             aux=aux->prox;
//         }

//         if (aux == *h) {
//             adicionar = (TLista *)malloc(sizeof(TLista));
//             if(aux->ti < ti) {
//                 aux->prox = adicionar;
//                 adicionar->prox = NULL;
//                 adicionar->ti = ti;
//                 adicionar->ci = ci;
//             } else if(aux->ti > ti) {
//                 adicionar->prox = aux;
//                 adicionar->ti = ti;
//                 adicionar->ci = ci;
//                 (*h) = adicionar;
//             } 
//         }else {
//             if (aux->ti != ti) {
//                 adicionar = (TLista *)malloc(sizeof(TLista));
//                 adicionar->prox = aux;
//                 antes->prox = adicionar;
//                 adicionar->ti = ti;
//                 adicionar->ci = ci;
//             }  
//         }
//     } 
// }
