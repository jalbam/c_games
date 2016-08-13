#include <stdio.h>
#include <stdlib.h>
#include "ruleta_antigua.h"

/* Nota: se podria hacer teniendo la bola siempre en un cuadrado fijo y solo
   volver a crear la ruleta (para distribuir los numeros aleatoriamente) */

int main()
{
    int opcion, ruleta_numeros[CUADRADOS];
    float apostado, premio, saldo = SALDO_INICIAL;
    bool ruleta_colores[CUADRADOS];

    /* Crea la ruleta: */
    crear_ruleta(ruleta_numeros, ruleta_colores);
    
    /* Bucle principal del juego: */
    do
    {
         system(BORRAR_PANTALLA);
         printf("\t\t= Menu Ruleta =\t\t[ Saldo: %.2f ]\n\n\
                  Escoge el tipo de apuesta:\n\n\
                  1) Numero (35 a 1: apuesta + 35)\n\
                  2) Color (paridad 1 a 1: el doble de apuesta)\n\
                  3) Par o impar (paridad 1 a 1: el doble de apuesta)\n\
                  4) Bajos o altos (paridad 1 a 1: el doble de apuesta)\n\
                  5) Salir\n\n\
                     Opcion: ", saldo);
         scanf("%d", &opcion);
         /* Si se ha elegido jugar en alguna apuesta: */
         if (opcion >= 1 && opcion < 5)
         {
            /* Pregunta cuanto deseamos apostar: */
            do { printf("\nIntroduce tu apuesta (el saldo minimo es %d): ", SALDO_MINIMO); scanf("%f", &apostado); } while (apostado <= 0 || saldo-apostado < SALDO_MINIMO);

            /* Descuenta lo apostado del saldo: */
            saldo -= apostado;
            
            /* Hace la apuesta (comienza el juego): */
            premio = hacer_apuesta(ruleta_numeros, ruleta_colores, opcion, apostado);
            
            /* Informa de si hemos ganado y cuanto o si no: */
            if (premio == 0) { printf("\nLastima... otra vez sera."); }
            else { printf("\nEnhorabuena, has ganado %.2f", premio); saldo += premio; }
            
            /* Informa del saldo que queda: */
            printf("\nTu saldo es ahora de %.2f", saldo);
            
            /* Si ha llegado al saldo minimo, informa del hecho y sale del juego: */
            if (saldo <= SALDO_MINIMO) { printf("\nTu saldo no llega al minimo (%d). Se te retira del juego.", SALDO_MINIMO); opcion = 5; }
            else
            {
                /* ...pero si no, pregunta si queremos volver a jugar: */
                printf("\n\nEscribe 1 si quieres volver a jugar, otro numero para acabar: ");
                scanf("%d", &opcion);
                if (opcion != 1) { opcion = 5; }
            }
         }
    } while (opcion != 5);

    
    printf("\n\nGracias por su visita.");
    system(PAUSA);
    return 0;    
}
