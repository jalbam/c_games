#include <stdio.h>
#include <stdlib.h>

#include "bjack.h" /* Biblioteca con funciones necesarias para el juego. */

/*
  FALTA:
         * Que pregunte el numero de jugadores (creo que necesita tener un maximo).
         * LA FUNCION DE SUMAR PODRIA DEVOLVER LO QUE VALE UNA CARTA Y YA ESTA
           (DEVOLVERIA LO QUE VALE UN AS DEPENDIENDO DE LA PUNTUACION DEL JUGADOR).
           LA PUNTUACION DEL JUGADOR PODRIA SER UNA VARIABLE.
*/

int main()
{
    bool baraja[4][13], mano[JUGADORES][4][13], perdedores[JUGADORES], ganadores[JUGADORES];
    bool sortir = false, juego_activo = true;
    int x, opcion, jugador_actual = 0, cartas_existentes = PALOS * CARTAS - JUGADORES * 2;

    /* Se inicia el juego: */
    iniciar_juego(baraja, mano, perdedores, ganadores);

    /* Comienza el bucle inicial del juego: */
    do
    {
      /* Borra la pantalla: */
      system(BORRAR_PANTALLA);
      
      /* Muestra cartas y puntuaciones de cada jugador (siempre que no haya perdido): */
      for (x = 0; x < JUGADORES; x++) { if (!perdedores[x] && !ganadores[x]) { mostrar_cartas(x, mano); } }

      /* Muestra el numero de cartas existentes: */
      printf("\n\nCartas en baza: %d\n\n", cartas_existentes);

      /* Calcula si hay ganador o todavia no (por si al repartir hay ganador): */
      juego_activo = continua_juego(mano, perdedores, ganadores);

      /* Si el jugador actual ha ganado o perdido, pasa al siguiente (si lo hay): */
      while (perdedores[jugador_actual] || ganadores[jugador_actual])
      {
            jugador_actual++;
      }

      
      /* Si el juego acaba, hace una pausa para leer los mensajes y pregunta si se quiere continuar: */
      if (!juego_activo || jugador_actual >= JUGADORES || cartas_existentes == 0)
      {
         /* Si se ha llegado al ultimo jugador, lo notifica: */
         if (jugador_actual >= JUGADORES) { printf("\nSe ha acabado la ronda."); }
         system(PAUSA);
         /* Si se ha acabado el juego, pregunta si se quiere volver a jugar: */
         printf("\n\nEscribe 1 si quieres volver a jugar, otra cosa para finalizar: ");
         scanf("%d", &opcion);
         /* Si ha apretado una opcion que no es 1, sale del juego: */
         if (opcion != 1) { opcion = 3; }
         /* ...pero si ha apretado 1, vuelve a iniciar el juego: */
         else { juego_activo = true; jugador_actual = 0; cartas_existentes = PALOS * CARTAS - JUGADORES * 2; iniciar_juego(baraja, mano, perdedores, ganadores); }
      }
      /* ...pero si el juego continua, imprime el menu del juego: */
      else
      {
         printf("\n\n\t\tMenu BlackJack:\n\
                 1) Recibir carta\n\
                 2) Pasar\n\
                 3) Acabar\n\n\
                 Opcion (jugador %d): ", jugador_actual + 1);
         scanf("%d", &opcion);
         switch (opcion)
         {
                /* Si se ha elegido recibir carta, la da al jugador actual: */
                case 1:
                     cartas_existentes = dar_carta(jugador_actual, baraja, mano);
                     if (cartas_existentes <= 0) { printf("Ya no quedan cartas! Elige pasar o acabar.\n."); }
                     break;
                /* ...pero si se ha elegido pasar, pasa al siguiente jugador que aun no ha ganado ni perdido (si lo hay): */
                case 2:
                     do
                     {
                       jugador_actual++;
                     } while (jugador_actual < JUGADORES && (perdedores[jugador_actual] || ganadores[jugador_actual]));
                     break;
                /* ...pero si se ha elegido salir, se despide: */
                case 3: sortir = true; printf("Adios");
         }
      }

      /* Calcula si hay ganador o todavia no: */
      /*juego_activo = continua_juego(mano, perdedores);*/
    } while (!sortir); /* Mientras no se salga y continue el juego y queden cartas. */
    
    printf("\n\n\nFin del juego\n\n");
    
    /* Fin del programa: */
    system(PAUSA);
    return;
}
