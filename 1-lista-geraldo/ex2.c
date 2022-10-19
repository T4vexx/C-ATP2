#include <stdio.h>

int main(){
int anonasc=0, anoatual=0;
int anos=0;

scanf("%d %d", &anonasc, &anoatual);
anos=anoatual-anonasc;
printf("Voce tem %d anos, %d meses, %d semanas, %d dias e %d horas", anos, anos*12, anos*52, anos*365, anos*8760);



    return 0;
}