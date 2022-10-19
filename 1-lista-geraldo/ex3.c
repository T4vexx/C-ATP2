#include <stdio.h>

typedef struct
{
int idade;
int peso;
float altura;
}pessoas;

int main(){
int i, media=0, botijao=0,altos=0, jovens=0;
float dado;

pessoas pessoa[10];

for(i=0;i<10;i++)
{   scanf("%d", &pessoa[i].idade);
    scanf("%d", &pessoa[i].peso);
    scanf("%f", &pessoa[i].altura);

   media+=pessoa[i].idade;
    if(pessoa[i].altura<1.5 && pessoa[i].peso>90)
        botijao++;
    if(pessoa[i].altura>1.9)
    {   altos++;
        if(pessoa[i].idade>10 && pessoa[i].idade<30)
            jovens++;;
    }

}
printf(" jovens %d, altos %d ", jovens, altos);

dado=100*jovens;
dado=dado/altos;
printf("A media das idades eh %d \n",media/10);
printf("A quantidade de pessoas com peso superior a 90kg e altura inferior a 1,5m eh %d \n",botijao);
printf("A porcentagem de pessoas de idades entre 10 e 30, entre as pessoas que medem mais de 1,9 eh %.2f \n", dado);


    return 0;
}