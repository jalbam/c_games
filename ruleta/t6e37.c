#include <stdio.h>
#include <stdlib.h>
#include "ruleta.h"

/* Nota: se podria hacer teniendo la bola siempre en un cuadrado fijo y solo
   volver a crear la ruleta (para distribuir los numeros aleatoriamente) */

int main()
{
    int opcion,
        apuesta,
        ruleta_numeros[CUADRADOS];
    char continuar;
    float apostado, premio, saldo = SALDO_INICIAL;
    bool ruleta_colores[CUADRADOS];

    /* Crea la ruleta: */
    crear_ruleta(ruleta_numeros, ruleta_colores);
    
    
    /* Bucle principal del juego: */
    do
    {
         system(BORRAR_PANTALLA);

         /* Muestra el menu de opciones: */
         opcion = opciones(saldo);
         
         /* Si se ha elegido jugar en alguna apuesta: */
         if (opcion != SALIR)
         {
            /* Pregunta los detalles de la apuesta: */
            apuesta = hacer_apuesta(opcion, &saldo, &apostado);
            saldo -= apostado;

            /* Comienza el juego: */            
            premio = jugar(ruleta_numeros, ruleta_colores, opcion, apostado, apuesta);
            
            /* Informa de si hemos ganado y cuanto o si no: */
            if (premio == 0) { printf("\nLastima... otra vez sera."); }
            else { printf("\nEnhorabuena, has ganado %.2f", premio);  saldo += premio; }
            
            /* Informa del saldo que queda: */
            printf("\nTu saldo es ahora de %.2f", saldo);
            
            /* Si ha llegado al saldo minimo, informa del hecho y sale del juego: */
            if (saldo <= SALDO_MINIMO) { printf("\nTu saldo no llega al minimo (%d). Se te retira del juego.", SALDO_MINIMO); opcion = 5; }
            else
            {
                /* ...pero si no, pregunta si queremos volver a jugar: */
                printf("\n\nQuieres volver a jugar? (s/n) ");
                fflush(stdin);
                scanf("%c", &continuar);
                if (continuar == 'n') { opcion = SALIR; }
            }
         }
    } while (opcion != SALIR);

    
    printf("\n\nGracias por su visita.");
    system(PAUSA);
    return 0;    
}
