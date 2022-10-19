#include <stdio.h>

int main(){
int n1=0,n2=0,n3=0, maior;

scanf("%d %d %d", &n1, &n2, &n3);
if(n1>n2 && n1>n3)
    maior=n1;
else if(n2>n1 && n2>n3)
    maior=n2;
else
    maior=n3;
printf("o maior eh %d", maior);

    return 0;
}