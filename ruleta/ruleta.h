#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool int
#define true 1
#define false 0

#define PAUSA "pause >NUL" /* Hace una pausa (se ha de cambiar en otros sistemas operativos). */
#define BORRAR_PANTALLA "cls" /* Borra la pantalla (se ha de cambiar en otros sistemas operativos). */

#define SALIR 5 /* Valor que debe tomar la opcion para salir del juego. */
#define ROJO 0 
#define NEGRO 1
#define PAR 0
#define IMPAR 1
#define BAJOS 0
#define ALTOS 1
#define APOSTAR_NUMERO 1
#define APOSTAR_COLOR 2
#define APOSTAR_PARIDAD 3
#define APOSTAR_ALTITUD 4

#define CUADRADOS 38 /* Numero de casillas que tiene la ruleta. */
#define SALDO_INICIAL 10000.00 /* Saldo con el que comienza el juego. */
#define SALDO_MINIMO -10000.00 /* Saldo minimo al que se puede llegar. */



void crear_ruleta(int ruleta_numeros[], bool ruleta_colores[]); /* Crea la ruleta con los numeros distribuidos aleatoriamente. */
int opciones(float saldo); /* Pregunta el tipo de apuesta. */
int hacer_apuesta(int tipo_apuesta, float *saldo, float *apostado); /* Pregunta las opciones del tipo de apuesta. */
int girar_ruleta(int ruleta_numeros[], bool ruleta_colores[]); /* Gira la ruleta y devuelve la posicion donde ha caido la bola. */
float jugar(int ruleta_numeros[], bool ruleta_colores[], int tipo_apuesta, float apostado, int apuesta); /* Comienza el juego y dice el tipo de premio segun la apuesta realizada. */



/* Funcion que crea la ruleta con los numeros distribuidos aleatoriamente: */
void crear_ruleta(int ruleta_numeros[], bool ruleta_colores[])
{
     int numero = -1, posicion;
     bool color;
     
     /* Pone todos los numeros del vector a -2: */
     for (posicion = 0; posicion < CUADRADOS; posicion++)
     {
         ruleta_numeros[posicion] = -2;
     }
     
     /* Distribuye los numeros aleatoriamente (de -1 a CUADRADOS): */
     srand(time(NULL));
     while (numero <= CUADRADOS - 2)
     {
           posicion = rand() % CUADRADOS;
           if (ruleta_numeros[posicion] == -2)
           {
              ruleta_numeros[posicion] = numero;
              numero++;
           }
     }
     
     /* Distribuye los colores alternandolos: */
     color = rand() % 2;
     for (posicion = 0; posicion < CUADRADOS; posicion++)
     {
         ruleta_colores[posicion] = color;
         color = !color;
     }

     return;
}


/* Funcion que gira la ruleta y devuelve la posicion donde ha caido la bola: */
int girar_ruleta(int ruleta_numeros[], bool ruleta_colores[])
{
    int posicion;
    
    /* Calcula una posicion aleatoria (un cuadrado) de la ruleta: */
    srand(time(NULL));
    posicion = rand() % CUADRADOS;
    
    /* Devuelva la posicion: */
    return posicion;
    
}


/* Funcion que comienza el juego y dice el tipo de premio segun la apuesta realizada: */
float jugar(int ruleta_numeros[], bool ruleta_colores[], int tipo_apuesta, float apostado, int apuesta)
{
     int posicion, numero;
     float premio = 0;

     /* Hace girar la ruleta y recoge la posicion final de la bola: */
     posicion = girar_ruleta(ruleta_numeros, ruleta_colores);
     
     /* Si la bola ha caido en 0 o 00 (-1), pierde automaticamente: */
     if (ruleta_numeros[posicion] <= 0) { printf("La bola ha caido en verde. Has perdido de inmediato.\n"); }
     /* ...pero si no, se calcula si se ha ganado y cuanto (depdende de la apuesta): */
     else
     {
         /* Si se ha hecho la apuesta tipo 1: */
         switch (tipo_apuesta)
         {
                case APOSTAR_NUMERO:
                     /* Si ha acertado, gana apuesta + 35: */
                     if (numero == ruleta_numeros[posicion]) { premio = apostado * (CUADRADOS - 2); }
                break;
                case APOSTAR_COLOR:
                     /* Si ha acertado, gana el doble de la apuesta: */
                     if (numero == ruleta_colores[posicion]) { premio = apostado * 2; }
                break;       
                case APOSTAR_PARIDAD:
                     /* Si ha acertado, gana el doble de la apuesta: */
                     if (ruleta_numeros[posicion] % 2 == numero) { premio = apostado * 2; }
                break;       
                case APOSTAR_ALTITUD:
                     /* Si ha acertado, gana el doble de apuesta: */
                     if (numero == BAJOS && ruleta_numeros[posicion] <= (CUADRADOS - 2) / 2 ||
                         numero == ALTOS && ruleta_numeros[posicion] >  (CUADRADOS - 2) / 2)
                         { premio = apostado * 2; }
                break;       
         }
     }

     /* Informa de lo que ha salido: */
     printf("\tHa salido: %d ", ruleta_numeros[posicion]);
     if (ruleta_numeros > 0)
     {
        if (ruleta_colores[posicion]) { printf("(negro)"); }
        else { printf("(rojo)"); }
     } else { printf("(verde)"); }

     /* Retorna el premio obtenido: */
     return premio;
}


/* Funcion que pregunta el tipo de apuesta: */
int opciones(float saldo)
{
    int opcion;
    do
    {
         printf("\t\t= Menu Ruleta =\t\t[ Saldo: %.2f ]\n\n\
                  Escoge el tipo de apuesta:\n\n\
                  1) Numero (35 a 1: apuesta + 35)\n\
                  2) Color (paridad 1 a 1: el doble de apuesta)\n\
                  3) Par o impar (paridad 1 a 1: el doble de apuesta)\n\
                  4) Bajos o altos (paridad 1 a 1: el doble de apuesta)\n\
                  5) Salir\n\n\
                     Opcion: ", saldo);
         scanf("%d", &opcion);
    } while (opcion <= 0 || opcion > 5);
    return opcion;    
}

/* Pregunta las opciones del tipo de apuesta. */
int hacer_apuesta(int tipo_apuesta, float *saldo, float *apostado)
{
    int numero;
    
    /* Pregunta cuanto deseamos apostar: */
    do
    {
      printf("\nIntroduce tu apuesta (el saldo minimo es %.2f): ", SALDO_MINIMO);
      scanf("%f", apostado);
    } while (*apostado <= 0 || *saldo-*apostado < SALDO_MINIMO);

    /* Pregunta las opciones del tipo de apuesta: */
    switch (tipo_apuesta)
    {
           case APOSTAR_NUMERO:
                /* Pregunta el numero (de 0 a CUADRADOS - 2): */
                do
                {
                 printf("Escribe el numero por el que apuestas (de 1 a %d): ", CUADRADOS-2);
                 scanf("%d", &numero);
                } while(numero <= 0 || numero > CUADRADOS - 2);
           break;
           case APOSTAR_COLOR:
                /* Pregunta color (rojo o negro): */
                do
                {
                  printf("Escribe 0 para rojo y 1 para negro: ");
                  scanf("%d", &numero);
                } while(numero != ROJO && numero != NEGRO);
           break;
           case APOSTAR_PARIDAD:
                /* Pregunta si quiere par o impar: */
                do
                {
                  printf("Escribe 0 para par y 1 para impar: ");
                  scanf("%d", &numero);
                } while(numero != PAR && numero != IMPAR);
           break;
           case APOSTAR_ALTITUD:
                /* Pregunta si quiere altos o bajos: */
                do
                {
                  printf("Escribe 0 para bajos y 1 para altos: ");
                  scanf("%d", &numero);
                } while(numero != 0 && numero != 1);
    }

    /* Descuenta lo apostado del saldo: */
    /* *saldo -= *apostado; */
    
    /* Devuelve la casilla escogida (0 o 1 si es una apuesta "booleana"): */
    return numero;
}
