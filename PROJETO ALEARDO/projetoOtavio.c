#include <stdio.h>
#include <stdlib.h>
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
        //Scanner dos valores de codigo.dat
        fscanf(codigos, "%d", &codigo);
        
        //Opção quando o codigo for maior que zero 
        if(codigo > 0) {
            //For para scanear as palavras e printar no arquivo linhas.dat 
            for (i = 0; i < codigo; i++) {
                fscanf(palavras, "%s", string);
                fprintf(linhas, "%s ", string);
            }
            fprintf(linhas, "\n");

            //Opção quando o codigo for menor que zero 
        } else if(codigo < 0) {
            pos = abs(codigo);

            //Laço que volta o tanto de palavras para o codigo negativo
            for (i = 0; i < pos; i++) {
                //Essa opção eu adicionei pois quando i é maior que zero ele a posição no arquivo é espaço ja, então ele tava escapando do do
                if (i > 0) {
                    fseek(palavras, -1, SEEK_CUR);
                }
                //Laço que volta ate o espaço
                do{
                    fseek(palavras, -1, SEEK_CUR);
                    fscanf(palavras, "%c", &caract);
                    //Esse if eu adicionei pois quando eu volto uma posição e leio ela, o ponteiro acaba ficando no mesmo lugar, portanto quando carat nao for espaço deve se voltar novamente
                    if (caract != ' ') {
                        fseek(palavras, -1, SEEK_CUR);
                    }
                }while(caract != ' ');
            }

            //For para scanear as palavras e printar no arquivo linhas.dat 
            for (i = 0; i < pos; i++) {
                fscanf(palavras, "%s", string);
                fprintf(linhas, "%s ", string);
            }
            fprintf(linhas, "\n");
            //Opção quando o codigo for menor que zero 
        } else if (codigo == 0) {
            fprintf(linhas,"0\n");
        }

        //Esse if roda quando acabou as palavras já e ainda tem código, portanto deve ser printados todos os codigos na linha seguinte
        if (feof(palavras)) {
            do {
                fscanf(codigos, "%d", &codigo);
                fprintf(linhas, "%d ", codigo);
            }while(!feof(codigos));  
        }

    }while(!feof(codigos));

    //Esse while roda pra quando sobrou palavras porém já acabou os codigos, assim devemos printas as palavras de 5 em 5
    while(!feof(palavras)){
        fscanf(palavras, "%s", string);
        fprintf(linhas, "%s ", string);
        counter++;
        if (counter%5 == 0){
            fprintf(linhas, "\n");
        }
    }
        
    //Fechamento dos arquivos abertos
    fclose(codigos);
    fclose(palavras);
    fclose(linhas);

    //Fim do codigo
    return 0;
} 