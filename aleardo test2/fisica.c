#include <stdio.h>
#include <math.h>

double distancia_mru(double V, double T) 
{
    return V*T;
}

double velocidade_mru(double S, double T) 
{
    return S/T;
}

double tempo_mru(double S, double V) 
{
    return S/V;
}

double distancia_muv(double V, double A, double T) 
{
    return (V*T)+(A*T*T)/2;
}

double velocidade_muv(double V, double A, double T) 
{
    return V+(A*T);
}

double velocidade_inicial_muv(double S, double A, double T) 
{
    double vo;
    vo = (S - (A * T * T) / 2) / T;
    return vo;
    //return S/T-(A*T)/2;
}

double tempo_muv(double S, double V, double A) 
{
    double delta,raiz1;
    delta = 2*V*2*V + 4 * 2 * A * S;
    raiz1 = ((-1*2*V) + sqrt(delta))/(2*A);
    return raiz1;
}

int main() {
    int N=0,i=0,opt=0;
    double num1=0, num2=0, num3=0;

    scanf("%d", &N);
    for (i = 0; i < N; i++) 
    {
        scanf("%d", &opt);
        
        switch (opt) 
        {
            case 1:
                scanf("%lf %lf", &num1, &num2);
                printf("%.2lf\n",distancia_mru(num1,num2)); break;
            case 2:
                scanf("%lf %lf", &num1, &num2);
                printf("%.2lf\n",velocidade_mru(num1,num2)); break;
            case 3: 
                scanf("%lf %lf", &num1, &num2);
                printf("%.2lf\n",tempo_mru(num1,num2)); break;
            case 4:
                scanf("%lf %lf %lf", &num1, &num2, &num3);
                printf("%.2lf\n",distancia_muv(num1,num2,num3)); break;
            case 5: 
                scanf("%lf %lf %lf", &num1, &num2, &num3);
                printf("%.2lf\n",velocidade_muv(num1,num2,num3)); break;
            case 6:
                scanf("%lf %lf %lf", &num1, &num2, &num3);
                printf("%.2lf\n",velocidade_inicial_muv(num1,num2,num3)); break;
            case 7:
                scanf("%lf %lf %lf", &num1, &num2, &num3);
                printf("%.2lf\n",tempo_muv(num1,num2,num3)); break;
        }
    }
    return 0;
}