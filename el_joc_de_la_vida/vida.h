#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAUSA "pause >NUL"
#define ESBORRAR_PANTALLA "cls"

#define F 22
#define C 77


void crear_tauler_aleatoriament(int matriu[][C]); /* Crea el tauler. */
void preguntar_tauler(int matriu[][C]); /* Pregunta el tauler per a crearlo. */
int mostrar_tauler(int matriu[][C]); /* Mostra el tauler. */
void sumar_veins(int matriu[][C], int matriu_final[][C]); /* Crea una matriu a partir d'un altre amb la suma dels veins d'aquesta: */
int fer_batec(int matriu[][C], int matriu_veins[][C]); /* Funcio que fa evolucionar el joc. */
void retard(); /* Funcio que fa un retard. */


/* Funcio que crea el tauler: */
void crear_tauler_aleatoriament(int matriu[][C])
{
     int digit, f, c;
     
     srand(time(NULL));
     
     for (f = 0; f < F; f++)
     {
         for (c = 0; c < C; c++) { matriu[f][c] = rand() % 2; }
     }
     
     return;
}


/* Funcio que pregunta el tauler per a crearlo: */
void preguntar_tauler(int matriu[][C])
{
     int organismes, f, c, x;

     printf("\n\t\tFica el numero d'organismes: ");
     scanf("%d", &organismes);
     
     for (x = 0; x < organismes; x++)
     {
         do
         {
           do
           {
             printf("\t\tFica la fila de l'organisme #%d: ", x); scanf("%d", &f);
             if (f < 0 || f > F-1) { printf("\t\tHas de ficar un numero entre 0 i %d\n", F-1); }
           } while (f < 0 || f > F-1);
           do
           {
             printf("\t\tFica la columna de l'organisme #%d: ", x); scanf("%d", &c);
             if (c < 0 || c > C-1) { printf("\t\tHas de ficar un numero entre 0 i %d\n", C-1); }
           } while (c < 0 || c > C-1);
           if (matriu[f][c] == 1) { printf("\t\tAquesta posicio ja esta ocupada!\n"); }
         } while (matriu[f][c] == 1);
         matriu[f][c] = 1;
     }
     
     return;
}


/* Funcio que mostra el tauler: */
int mostrar_tauler(int matriu[][C])
{
     int f, c, poblacio = 0;
     
     for (f = 0; f < F; f++)
     {
         if (f == 0) { printf("*"); for (c = 0; c < C; c++) { printf("-"); } printf("*\n"); }
         printf("|");
         for (c = 0; c < C; c++)
         {
             if (matriu[f][c] != 0) { printf("%d", matriu[f][c]); poblacio++; }
             else { printf(" "); }
         }
         printf("|\n");
         if (f == F-1) { printf("*"); for (c = 0; c < C; c++) { printf("-"); } printf("*"); }
     }
     
     return poblacio;
}


/* Funcio que crea una matriu a partir d'un altre amb la suma dels veins d'aquesta: */
void sumar_veins(int matriu[][C], int matriu_final[][C])
{
    int files, columnes, suma;
    int files2, columnes2, files2_inici, columnes2_inici, files2_tope, columnes2_tope;
    for (files = 0; files < F; files++)
    {
            for (columnes = 0; columnes < C; columnes++)
            {
                matriu_final[files][columnes] =  - matriu[files][columnes];

                for (files2 = files - 1; files2 <= files + 1; files2++)
                {
                    for (columnes2 = columnes - 1; columnes2 <= columnes + 1; columnes2++)
                    {
                        if (columnes2 >= 0 && files2 >= 0 && columnes2 < C && files2 < F)
                        {
                           matriu_final[files][columnes] += matriu[files2][columnes2];
                        }
                    }
                }
                
            }
    }
    return;
}


/* Funcio que fa evolucionar el joc: */
int fer_batec(int matriu[][C], int matriu_veins[][C])
{
     int f, c, estable = 1;
     
     for (f = 0; f < F; f++)
     {
         for (c = 0; c < C; c++)
         {
             /* Si no te 2 o 3 veins, es mor: */
/*             if (matriu_veins[f][c] != 2 && matriu_veins[f][c] != 3) { matriu[f][c] = 0; }*/
             /* Si te 4 o mes veins, es mor per superpoblacio: */
             if (matriu_veins[f][c] >= 4 && matriu[f][c] == 1) { matriu[f][c] = 0; estable = 0; }
             /* Si te 1 o cap vei, es mor per aillament: */
             if (matriu_veins[f][c] <= 1 && matriu[f][c] == 1) { matriu[f][c] = 0; estable = 0; }
             /* Si te exactament 3 veins, neix: */
             if (matriu_veins[f][c] == 3 && matriu[f][c] == 0) { matriu[f][c] = 1; estable = 0; }
         }
     }
     
     return estable;
}


/* Funcio que fa un retard: */
void retard()
{
     int x, y;
     for (x = 0; x < 999; x++) { for (y = 0; y < 999; y++) {  } }
}
