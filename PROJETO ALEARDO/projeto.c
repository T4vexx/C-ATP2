#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main() {
    //Declarações das variaveis
    char string[20],palavra[6],caract;
    int codigo,pos,i,counter=0;
    FILE *codigos, *palavras, *linhas;

    //Abertura dos arquivos para serem lidos ou escritos
    codigos = fopen("./codigos.dat", "r");
    palavras = fopen("./palavras.dat", "r");
    linhas = fopen("./linhas.dat", "w");

    //implementação para ler o arquivo codigos pegar um codigo por linhas enquanto nao for o fim do arquivo, e escrever as palavras no arquivo linhas.dat
    do{
        fscanf(codigos, "%d", &codigo);
        
        if(codigo > 0) {
            for (i = 0; i < codigo; i++) {
                fscanf(palavras, "%s", string);
                fprintf(linhas, "%s ", string);
            }
            fprintf(linhas, "\n");
        } else if(codigo < 0) {
            pos = sqrt(pow(codigo,2));
            for (i = 0; i < pos; i++) {
                if (i > 0) {
                    fseek(palavras, -1, SEEK_CUR);
                }
                do{
                    fseek(palavras, -1, SEEK_CUR);
                    fscanf(palavras, "%c", &caract);
                    if (caract != ' ') {
                        fseek(palavras, -1, SEEK_CUR);
                    }
                }while(caract != ' ');
            }

            for (i = 0; i < pos; i++) {
                fscanf(palavras, "%s", string);
                fprintf(linhas, "%s ", string);
            }
            fprintf(linhas, "\n");
        } else if (codigo == 0) {
            fprintf(linhas,"0\n");
        }

        if (feof(palavras)) {
            do {
                fscanf(codigos, "%d", &codigo);
                fprintf(linhas, "%d ", codigo);
            }while(!feof(codigos));  
        }

    }while(!feof(codigos));

   
    while(!feof(palavras)){
        fscanf(palavras, "%s", string);
        fprintf(linhas, "%s ", string);
        counter++;
        if (counter%5 == 0){
            fprintf(linhas, "\n");
        }
    }
        

    fclose(codigos);
    fclose(palavras);
    fclose(linhas);

    return 0;
} 