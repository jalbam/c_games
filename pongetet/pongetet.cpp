/***********   Pongetet   ************/
/* Joc del Pong, compilat en Dev-C++ */
/************* 31/1/2007 *************/
/*********** rev. 1/2/2007 ***********/
/******** Joan Alba Maldonado ********/

/*
   FALTA: * Al treure, que la pilota surti aleatoriament cap a la dreta o cap a l'esquerra.
          * Que l'ordinador no mogui la paleta a vegades, per fer-lo mes facil.
*/


/* Biblioteques necessaries: */
#include <stdio.h>
#include <stdlib.h> /* Necessaria per utilitzar system(), srand() i rand(). */
//#include <ncurses.h> /* Necessaria en Unix per a utilitzar kbhit() i getch(). */
#include <conio.h> /* Necessaria en MS-DOS i Windows per a utilitzar kbhit() i getch(). */
#include <time.h> /* Necessaria per a utilitzar time(). */


/* Constants necessaries: */
#define ESBORRAR_PANTALLA "cls" /* En sistems posix ficar "clear". */
#define SEPARACIO_PALETES 21
#define AE 0 /* Direccio de la pilota cap adalt a l'esquerra. */
#define AD 1 /* Direccio de la pilota cap adalt a la dreta. */
#define BE 2 /* Direccio de la pilota cap abaix a l'esquerra. */
#define BD 3 /* Direccio de la pilota cap abaix a la dreta. */


/* Prototip de les funciones necessaries: */
void representa_paletes(); /* Representa les paleta en unes coordenades. */
void mou_pilota(); /* Calcula colisions i mou la pilota. */
void mou_ordinador(); /* Mou la paleta del ordinador. */


/* Variables necessaries: */
int usuari_x = 0, ordinador_x = 20; /* Posicio horizontal inicial de les paletes. */
int paletes_ample = 15; /* El ample de les paletes (sense contar l'espai final). */
int gols_ordinador = 0; /* Gols que ha fet l'ordinador. */
int gols_usuari = 0; /* Gols que ha fet l'usuari. */
int pilota_treta = 0; /* Variable boolean. 0 = pilota encara no treta. */
int li_toca_a = 0; /* 0 = li toca treure al ordinador, 1 = li toca treure al usuari */
int pilota_x = 0, pilota_y = 0; /* Coordenades de la pilota. */
int pilota_direccio = (li_toca_a) ? AD : BE; /* Direccio inicial de la pilota. */
int tope_x = 78; /* Tope de columnes - 2. */
int tope_y = 25; /* Tope de files. */
int ordinador_moviment_horizontal = 3; /* Punts que es desplaça la paleta del ordinador en cada moviment. */
int usuari_moviment_horizontal = 3; /* Punts que es desplaça la paleta del usuari en cada moviment. */
int inclinacio = 1; /* Defineix la inclinacio (horizontal) inicial de la pilota. */


/* Funcio principal: */
int main()
{
    /* Variables necessaries: */
    int tecla = 0;

    /* Representa la paleta del usuari i la de l'ordinador: */
    representa_paletes();
    
    /* Mentre no es premi la tecla "escape": */
    while (tecla != 27)
    {
          /* Capturem la tecla: */
          if(kbhit()) { tecla = getch(); } /* Fletxa adalt: 72, abaix: 80, dreta: 77, esquerra: 75, espai: 32. */
          else { tecla = 0; }

          /* Si es prem la fletxa dreta, mou la paleta cap a la dreta: */
          if (tecla == 77) { usuari_x += usuari_moviment_horizontal; }
          /* Si es prem la fletxa esquerra, mou la paleta cap a l'esquerra: */
          if (tecla == 75) { usuari_x -= usuari_moviment_horizontal; }
          /* Si es prem l'espai o la fletxa cap adalt i encara no s'ha tret i li toca treure al usuari, es treu: */
          if ((tecla == 32 || tecla == 72) && !pilota_treta && li_toca_a == 1) { pilota_treta = 1; inclinacio = 1; }

          /* Si les coordenares son menors a 0, es fiquen a 0: */
          if (usuari_x < 0) { usuari_x = 0; }

          /* Si les coordenares son major que el seu tope, es fiquen al tope: */
          if (usuari_x + paletes_ample > tope_x) { usuari_x = tope_x - paletes_ample; }

          /* Fa moure al ordinador, si cal: */
          mou_ordinador();

          /* Representem la paleta del usuari i de l'ordinador: */
          representa_paletes();
    }
    
    /* Surt del programa: */
    return 0;
}


/* Funcio que representa la paleta en unes coordenades: */
void representa_paletes()
{
     /* Variable contador: */
     int x;
     
     /* Esborra la pantalla: */
     system(ESBORRAR_PANTALLA);

     /* Dibuixa el marcador: */
     printf("Marcador: %d - %d ", gols_ordinador, gols_usuari);
     if (gols_ordinador > gols_usuari) { printf("(guanya ordinador)"); }
     else if (gols_ordinador < gols_usuari) { printf("(guanya usuari)"); }
     else { printf("(taules)"); }
     //printf(" [fletxes mou, ESC surt]");
     if (pilota_treta) { printf(" - Pilota treta"); }
     else { printf(" - Pilota no treta"); }
     printf(" (%d, %d) - Inclinacio: %d\n\n", pilota_x, pilota_y, inclinacio);

     /* Si no s'ha tret, actualitza les coordenades de la pilota: */
     if (!pilota_treta && li_toca_a == 0) { pilota_x = ordinador_x + (paletes_ample / 2); pilota_y = 4; }
     else if (!pilota_treta && li_toca_a == 1) { pilota_x = usuari_x + (paletes_ample / 2); pilota_y = 23; }
     
     /* Posiciona el cursor per dibuixar la paleta del ordinador: */
     for (x = 0; x < ordinador_x; x++) { printf(" "); }
     /* Dibuixa la paleta del ordinador: */
     printf("[=============] "); /* Fa un espai a la dreta per esborrar cap a dreta si existeis algun caracter. */     

     /* Si la pilota no sha tret i li toca treure al ordinador, la dibuixa a la seva paleta: */
     if (!pilota_treta && li_toca_a == 0) /* Podriem ficar !li_toca_a. */
     {
        printf("\n");
        for (x = 0; x < ordinador_x + (paletes_ample / 2); x++) { printf(" "); }
        printf("*");
        /* Calcula aleatoriament la direccio que prendra la pilota, BE (2) o BD (3): */
        srand(time(NULL)); /* Es fa per utilitzar despres rand(). */
        pilota_direccio = rand() % 2 + 2; /* Calcula un numero entre 0 i 1 i despres li suma 2, i el guarda com a enter. */
     }
     else { printf("\n"); }

     /* Si ja s'ha tret: */
     if (pilota_treta)
     {
        /* Dibuia la pilota: */
        mou_pilota();
     }
     /* ...pero si no: */
     else
     {
         /* Fa les lines que separen un jugador de l'altre: */
         for (x = 0; x < SEPARACIO_PALETES - 2; x++) { printf("\n"); }
     }
     
     /* Si la pilota no sha tret i li toca treure al usuari, la dibuixa a la seva paleta: */
     if (!pilota_treta && li_toca_a == 1) /* Podriem ficar li_toca_a. */
     {
        for (x = 0; x < usuari_x + (paletes_ample / 2); x++) { printf(" "); }
        printf("*");
        /* Calcula aleatoriament la direccio que prendra la pilota, AE (0) o AD (1): */
        srand(time(NULL)); /* Es fa per utilitzar despres rand(). */
        pilota_direccio = rand() % 2; /* Calcula un numero entre 0 i 1 i el guarda com a enter. */
     }
     printf("\n");

     /* Posiciona el cursor per dibuixar la paleta del usuari: */
     for (x = 0; x < usuari_x; x++) { printf(" "); }
     /* Dibuixa la paleta del usuari: */
     printf("[=============] "); /* Fa un espai a la dreta per esborrar cap a dreta si existeis algun caracter. */     
}


/* Funcio que calcula colisions i mou la pilota: */
void mou_pilota()
{
     /* Variable contadora: */
     int x;
     
     /* Calcula si s'ha arribat a un limit vertical: */
     if ((pilota_direccio == AE || pilota_direccio == AD) && pilota_y == 4 && pilota_x >= ordinador_x && pilota_x <= ordinador_x + paletes_ample || (pilota_direccio == BE || pilota_direccio == BD) && pilota_y == 23 && pilota_x >= usuari_x && pilota_x <= usuari_x + paletes_ample)
     {
        /* Si la pilota ha colisionat amb la paleta de l'ordinador, canvia la inclinacio: */
        if ((pilota_direccio == AE || pilota_direccio == AD) && pilota_y == 4 && pilota_x >= ordinador_x && pilota_x <= ordinador_x + paletes_ample)
        {
           /* Si ha colisionat molt a la punta: */
           if (pilota_x <= ordinador_x + (paletes_ample/12) || pilota_x >= ordinador_x + paletes_ample - (paletes_ample/12))
           {
              inclinacio = 4;
           }
           /* ...o si ha colisionat bastant a la punta pero mes centrat: */
           else if (pilota_x <= ordinador_x + (paletes_ample/4) || pilota_x >= ordinador_x + paletes_ample - (paletes_ample/4))
           {
              inclinacio = 3;
           }
           /* ...o si ha colisionat una mica descentrat: */
           else if (pilota_x <= ordinador_x + (paletes_ample/2) || pilota_x >= ordinador_x + paletes_ample - (paletes_ample/2))
           {
              inclinacio = 2;
           }
           /* ...pero si ha colisionat bastant centrat: */
           else { inclinacio = 1; }
        }
        /* ...o si ho ha fet amb la paleta del usuari, tambe canvia la inclinacio: */
        else if ((pilota_direccio == BE || pilota_direccio == BD) && pilota_y == 23 && pilota_x >= usuari_x && pilota_x <= usuari_x + paletes_ample)
        {
           /* Si ha colisionat molt a la punta: */
           if (pilota_x <= usuari_x + (paletes_ample/12) || pilota_x >= usuari_x + paletes_ample - (paletes_ample/12))
           {
              inclinacio = 4;
           }
           /* ...o si ha colisionat bastant a la punta pero mes centrat: */
           else if (pilota_x <= usuari_x + (paletes_ample/4) || pilota_x >= usuari_x + paletes_ample - (paletes_ample/4))
           {
              inclinacio = 3;
           }
           /* ...o si ha colisionat una mica descentrat: */
           else if (pilota_x <= usuari_x + (paletes_ample/2) || pilota_x >= usuari_x + paletes_ample - (paletes_ample/2))
           {
              inclinacio = 2;
           }
           /* ...pero si ha colisionat bastant centrat: */
           else { inclinacio = 1; }
        }

        /* ...si n'hi ha paleta, fa rebotar la pilota canviant la seva direccio: */
        if (pilota_direccio == AD) { pilota_direccio = BD; }
        else if (pilota_direccio == BD) { pilota_direccio = AD; }
        else if (pilota_direccio == AE) { pilota_direccio = BE; }
        else if (pilota_direccio == BE) { pilota_direccio = AE; }
     }
     /* ...pero si no, es fica un gol a qui correspongui i s'ha de treure un altre cop (si el gol ha sigut del ordinador treura el usuari o viceversa): */
     else if (pilota_y < 4) { gols_usuari++; li_toca_a = 0; pilota_treta = 0; inclinacio = 1; pilota_y = 4; }
     else if (pilota_y > 23) { gols_ordinador++; li_toca_a = 1; pilota_treta = 0; inclinacio = 1; pilota_y = 23; }

     /* Calcula si s'ha arribat a un limit horizontal i llavors fa rebotar la pilota: */
     if (pilota_x >= tope_x)
     {
        if (pilota_direccio == AD) { pilota_direccio = AE; }
        else if (pilota_direccio == BD) { pilota_direccio = BE; }
     }
     else if (pilota_x <= 0)
     {
        if (pilota_direccio == AE) { pilota_direccio = AD; }
        else if (pilota_direccio == BE) { pilota_direccio = BD; }
     }

     /* Calcula la X i la Y de la pilota segons la direccio que porta (sempre que no hagi agut un gol): */
     if (pilota_treta) /* Si ha agut un gol, pilota treta sera 0 i no entrara al if. */
     {
        if (pilota_direccio == AE) { pilota_x -= inclinacio; pilota_y--; }
        else if (pilota_direccio == AD) { pilota_x += inclinacio; pilota_y--; }
        else if (pilota_direccio == BE) { pilota_x -= inclinacio; pilota_y++; }
        else if (pilota_direccio == BD) { pilota_x += inclinacio; pilota_y++; }
     }

     /* Fa que la pilota no es passi dels limits: */
     if (pilota_x > tope_x) { pilota_x = tope_x; }
     else if (pilota_x < 0) { pilota_x = 0; }

     /* Baixa linies segons pilota_y (entre la paleta de l'ordinador i la pilota): */
     for (x = 3; x < pilota_y - 1; x++) { printf("\n"); }
     
     /* Fa espais segons pilota_x: */
     for (x = 0; x < pilota_x; x++) { printf(" "); }

     /* Dibuixa la pilota: */
     printf("*");
     
     /* Baixa linies segons pelota_y (entre la pilota i la paleta de l'usuari): */
     for (x = pilota_y + 1; x < tope_y - 1; x++) { printf("\n"); }
}


/* Funcio que mou la paleta del ordinador: */
void mou_ordinador()
{
     /* Variable que determina si la paleta de l'ordinador ja apunta a la pilota: */
     int ben_apuntada = 0;
     
     /* Probabilitat que necessita treure l'ordinador per a moure (0 = sempre, 100 = mai): */
     int probabilitat_necessaria = 25;
     /* Probabilitat aleatoria per veure si l'ordinar moura o no: */
     srand(time(NULL));
     int probabilitat_treta = rand() % 100;

     /* Si li toca treure al ordinador, ho fa: */
     if (!pilota_treta && li_toca_a == 0)
     {
        pilota_x = ordinador_x + (paletes_ample / 2);
        pilota_y = 4;
        pilota_treta = 1;
        inclinacio = 1;
     }
     /* Pero si no, seguira a la pilota per poder donar-li: */
     else if (probabilitat_treta >= probabilitat_necessaria)
     {
         /* Si la paleta ja apunta va a la pilota, ho defineix: */
         if (pilota_x >= ordinador_x && pilota_x <= ordinador_x + paletes_ample) { ben_apuntada = 1; }

         /* Si la pilota esta mes a la dreta que la paleta de l'ordinador, es mou a la dreta: */
         if (pilota_x > ordinador_x + (paletes_ample / 2))
         {
            /* Si la paleta ja apunta be, solament es mou una mica la paleta: */
            if (ben_apuntada == 1) { ordinador_x++; }
            /* ...pero si no, es mou amb el moviment horizontal definit: */
            else { ordinador_x += ordinador_moviment_horizontal; }
         }
         /* ...pero si esta mes a l'esquerra, es mou cap a l'esquerra: */
         else if (pilota_x < ordinador_x + (paletes_ample / 2))
         {
              /* Si la paleta ja apunta be, solament es mou una mica la paleta: */
              if (ben_apuntada) { ordinador_x--; }
              /* ...pero si no, es mou amb el moviment horizontal definit: */
              else { ordinador_x -= ordinador_moviment_horizontal; }
         }
         /* Si la paleta de l'ordinador esta fora dels topes, es fixa: */
         if (ordinador_x < 0) { ordinador_x = 0; }
         else if (ordinador_x > tope_x - paletes_ample) { ordinador_x = tope_x - paletes_ample; }
     }
}
