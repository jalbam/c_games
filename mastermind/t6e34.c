#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define N 4
#define PAUSA "pause >NUL"


int comparar_numero(int numero_generat, int numero_introduit);
int comparar_numero2(int numero_generat, int numero_introduit);
void vector_digits (int digits[], int num);


int main()
{
    int numero_generat, numero_introduit, xifres_encertades;
    int min = 0, max = pow(10, N) - 1;
    srand(time(NULL));
    numero_generat = rand() % (max - min + 1) + min;
    //numero_generat=405;

    printf("\nTrampes: %d\n\n", numero_generat);
    
    do
    {
      do
      {
        printf("\nFica el numero: ");
        scanf("%d", &numero_introduit);
        if (numero_introduit < 0) { numero_introduit *= -1; }
        if (numero_introduit < min || numero_introduit > max)
        {
           printf("El numero ha de ser de %d xifres!\n", N);
        }
      } while (numero_introduit < min || numero_introduit > max);
      xifres_encertades = comparar_numero2(numero_generat, numero_introduit);
    } while (xifres_encertades != N);

    system(PAUSA);
    
}


int comparar_numero(int numero_generat, int numero_introduit)
{
    int xifres_encertades = 0, index = N-1, numeros_existents[10] = { 0 };
    int numero_generat_backup = numero_generat;
    char matriu_encerts[N];

    while (numero_generat > 0)
    {
          numeros_existents[numero_generat%10] = 1;
          numero_generat /= 10;
    }
    
    numero_generat = numero_generat_backup;

    for (index = N-1; index >= 0; index--)
    {
          if (numero_generat%10 == numero_introduit%10) { matriu_encerts[index] = '*'; xifres_encertades++; }
          else if (numeros_existents[numero_introduit%10]) { matriu_encerts[index] = '?'; }
          else { matriu_encerts[index] = '0'; }
          numero_generat /= 10;
          numero_introduit /= 10;
    }
    
    printf("\t\t");
    for (index = 0; index < N; index++)
    {
        printf("%c", matriu_encerts[index]);
    }

    return xifres_encertades;
}

int comparar_numero2(int numero_generat, int numero_introduit)
{
    int v_numero_generat[N] = { 0 }, v_numero_introduit[N] = { 0 };
    int xifres_encertades = 0, index, numeros_existents[10] = { 0 };
    char matriu_encerts[N];
    
    vector_digits(v_numero_generat,numero_generat);
    vector_digits(v_numero_introduit,numero_introduit);

    for (index = N-1; index >= 0; index--)
          numeros_existents[v_numero_generat[index]] = 1;
    
    for (index = N-1; index >= 0; index--)
    {
          if (v_numero_generat[index] == v_numero_introduit[index]) { matriu_encerts[index] = '*'; xifres_encertades++; }
          else if (numeros_existents[v_numero_introduit[index]]) { matriu_encerts[index] = '?'; }
          else { matriu_encerts[index] = '0'; }
    }
    
    printf("\t\t");
    for (index = 0; index < N; index++)
    {
        printf("%c", matriu_encerts[index]);
    }

    return xifres_encertades;
}

void vector_digits (int digits[], int num)
{
     int x;
     for (x=N-1; x>=0; x--)
     {
         digits[x] = num%10; num/=10;
     }
}
