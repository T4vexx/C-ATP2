#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));

  int max = 0, a, b, c, i, aux;
  FILE *txt = fopen("bigint2.dat", "w");

  max = 600000; //+ rand() % 10000;
  
  for (i = 0; i < max; i++) {
    a = -500 + rand() % 1000;
    b = 1 + rand() % 32000;
    c = 1 + rand() % 999;
    fprintf(txt, "%d %d%d\n", a, b,c);

  }

  return 0;
}
