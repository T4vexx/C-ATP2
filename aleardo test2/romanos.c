#include <stdio.h>

int romano_para_int(char *romano) {
    int i=0,vetor[20]={0},decimal=0;
    do {
        switch (romano[i]) {
        case 'M':
            vetor[i] = 1000;
            break;
        case 'D':
            vetor[i] = 500;
            break;
        case 'C':
            vetor[i] = 100;
            break;
        case 'L':
            vetor[i] = 50;
            break;
        case 'X':
            vetor[i] = 10;
            break;
        case 'V':
            vetor[i] = 5;
            break;
        case 'I':
            vetor[i] = 1;
            break;
        }
        i++;
    } while(romano[i] != '\0');

    i=0;
    do {
        if (vetor[i] > vetor[i+1]) {
            decimal = decimal + vetor[i];
        } else if (vetor[i] < vetor[i+1]) {
            decimal = decimal + vetor[i+1] - vetor[i];
            i++;
        } else if (vetor[i] = vetor[i+1]) {
            decimal = decimal + vetor[i];
        }
        i++;
    }while(vetor[i] != 0);
    return decimal;
}

void decimal_para_romano(int decimal) {
    int aux=0,count=0;
    char romano[20]="";
    aux = decimal;

    while(aux != 0){
        if (aux >= 1000) {
            romano[count] = 'M';
            count++;
            aux -= 1000;
        } else if (aux >= 900) {
            romano[count] = 'C';
            romano[count+1] = 'M';
            count += 2;
            aux -= 900;
        } else if (aux >= 500) {           
            romano[count] = 'D';
            count++;
            aux -= 500;
        } else if (aux >= 400) {
            romano[count] = 'C';
            romano[count+1] = 'D';
            count += 2;
            aux -= 400;
        } else if (aux >= 100) {
            romano[count] = 'C';
            count++;
            aux -= 100;                       
        } else if (aux >= 90) {
            romano[count] = 'X';
            romano[count+1] = 'C';
            count += 2;
            aux -= 90;                                              
        } else if (aux >= 50) {
            romano[count] = 'L';
            count++;
            aux -= 50;                                                                     
        } else if (aux >= 40) {
            romano[count] = 'X';
            romano[count+1] = 'L';
            count += 2;         
            aux -= 40;
        } else if (aux >= 10) {
            romano[count] = 'X';
            count++;
            aux -= 10;           
        } else if (aux >= 9) {
            romano[count] = 'I';
            romano[count+1] = 'X';
            count += 2; 
            aux -= 9;                         
        } else if (aux >= 5) {
            romano[count] = 'V';
            count++;
            aux -= 5;                                     
        } else if (aux >= 4) {
            romano[count] = 'I';
            romano[count+1] = 'V';
            count += 2; 
            aux -= 4;                                                            
        } else if (aux >= 1)  {
            romano[count] = 'I';
            count++;
            aux -= 1;                                                                                   
        }
    }
    printf("%s\n",romano);

    return 1;
}



int main() {
    int N,C,i=0,soma=0,dec;
    char romano[20]="";

    scanf("%d", &N);
    for (i=0;i<N;i++) {
        scanf("%d", &C);

        switch (C) {
            case 1:
                scanf("%s", romano);
                dec = romano_para_int(romano);
                printf("%d\n",dec);
                soma = soma + dec;
                break;
            case 2: 
                scanf("%d", &dec);
                decimal_para_romano(dec);
                break;
        }
    }

    printf("%d\n",soma);

    return 0;
}