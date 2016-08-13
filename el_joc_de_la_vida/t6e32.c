#include <stdio.h>
#include <stdlib.h>
#include "vida.h"

int main()
{
    int cicles = 0, poblacio, estable, tauler[F][C] = { 0 }, tauler_veins[F][C] = { 0 };
    int opcio, jugar;

    do
    {
      system(ESBORRAR_PANTALLA);
      printf ("\n\n\t\t= El joc de la vida =\n\n\
               \t\t1) Entrar manualment\n\
               \t\t2) Generar aleatoriament\n\
               \t\t3) Sortir\n\
               Opcio: ");
      scanf("%d", &opcio);
      switch (opcio)
      {
             case 1: jugar = 1; preguntar_tauler(tauler); break;
             case 2: jugar = 1; crear_tauler_aleatoriament(tauler); break;
             case 3: jugar = 0;
      }
    } while (opcio != 1 && opcio != 2 && opcio != 3);
    
    while (jugar)
    {
          system(ESBORRAR_PANTALLA);

          poblacio = mostrar_tauler(tauler);

          sumar_veins(tauler, tauler_veins);
          
          estable = fer_batec(tauler, tauler_veins);
          
          printf("\n[");
          if (!estable) { printf("no "); }
          printf("es estable]");
          printf("\tCicles: %d\t\t\tPoblacio: %d", cicles, poblacio);
          if (poblacio == 0) { printf(" (extingida)"); }
          
          cicles++;

          retard();
    }
}
