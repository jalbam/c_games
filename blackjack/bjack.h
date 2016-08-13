#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool int
#define true 1
#define false 0

#define PAUSA "pause >NUL" /* Hace una pausa (se ha de cambiar en otros sistemas operativos). */
#define BORRAR_PANTALLA "cls" /* Borra la pantalla (se ha de cambiar en otros sistemas operativos). */
#define TRUCADO 0 /* Define si se escogen las cartas a recibir o no. */


#define PUNTUACION_NECESARIA 21 /* Puntuacion necesaria para ganar. */
#define PALOS 4 /* Palos existentes. */
 #define CORAZONES 0
 #define PICAS 1
 #define ROMBOS 2
 #define TREBOLES 3
#define CARTAS 13 /* Cartes existentes en cada palo. */
#define JUGADORES 5 /* Numero de jugadores. */


void iniciar_juego(bool baraja[][CARTAS], bool mano[][PALOS][CARTAS], bool perdedores[], bool ganadores[]); /* Inicializa el juego. */
void mostrar_cartas(int jugador, bool mano[][PALOS][CARTAS]); /* Muestra las cartas del jugador enviado y su puntuacion. */
int dar_carta(int jugador, bool baraja[][CARTAS], bool mano[][PALOS][CARTAS]); /* Da una carta aleatoria al jugador (que siga en la baza). */
int continua_juego(bool mano[][PALOS][CARTAS], bool perdedores[], bool ganadores[]); /* Calcula si el juego continua (si no hay ganador y aun quedan jugadores). */
int sumar_cartas(int jugador, bool mano[][PALOS][CARTAS]); /* Suma las cartas que el jugador tiene en su mano. */


/* Funcion que inicializa el juego: */
void iniciar_juego(bool baraja[][CARTAS], bool mano[][PALOS][CARTAS], bool perdedores[], bool ganadores[])
{
     int palo, numero, x, jugador;
     
     /* Completa la baraja y vacia la mano de cada jugador: */
     for (palo = 0; palo < PALOS; palo++)
     {
         for (numero = 0; numero < CARTAS; numero++)
         {
             baraja[palo][numero] = true;
             for (jugador = 0; jugador < JUGADORES; jugador++)
             {
                mano[jugador][palo][numero] = false;
             }
         }
     }
     
     /* Reparte una carta a uno, luego al otro (dos veces): */
     jugador = 0;
     for (x = 0; x < 2 * JUGADORES; x++)
     {
         dar_carta(jugador++, baraja, mano);
         jugador %= JUGADORES;
         /* Aprobecha para definir que el jugador aun no ha perdido ni ha ganado (lo hace dos veces pero bueno...): */
         perdedores[jugador] = false;
         ganadores[jugador] = false;
     }
}


/* Funcion que muestra las cartas del jugador enviado y su puntuacion: */
void mostrar_cartas(int jugador,  bool mano[][PALOS][CARTAS])
{
     int palo, numero, puntos;
     bool tiene_cartas = false;
     
     puntos = sumar_cartas(jugador, mano);

     printf("\nCartas del jugador %d: ", jugador+1);
          
     /* Muestra las cartas del jugador escogido: */
     for (palo = 0; palo < PALOS; palo++)
     {
         for (numero = 0; numero < CARTAS; numero++)
         {
             if (mano[jugador][palo][numero])
             {
                tiene_cartas = true;
                if (numero < 10) { printf("%d de ", numero+1); }
                else if (numero == 10) { printf("J de "); }
                else if (numero == 11) { printf("Q de "); }
                else if (numero == 12) { printf("K de "); }
                switch (palo)
                {
                       case CORAZONES: printf("Corazones"); break;
                       case PICAS:     printf("Picas"); break;
                       case ROMBOS:    printf("Rombos"); break;
                       case TREBOLES:  printf("Treboles"); break;
                }
                printf(", ");
             }
         }
     }
     
     if (tiene_cartas) { printf("\b\b "); }
     
     /* Muestra su puntuacion: */
     printf("(%d puntos)", puntos);

     printf("\n");     
}


/* Funcion que da una carta aleatoria al jugador (que siga en la baza): */
int dar_carta(int jugador, bool baraja[][CARTAS], bool mano[][PALOS][CARTAS])
{
     int numero, palo, cartas_existentes[PALOS * CARTAS], numero_cartas_existentes = 0;
     /* int numeros_existentes[PALOS][CARTAS] = { 0 }, palos_existentes[PALOS] = { 0 }; 
     int corazones_x = 0, picas_x = 0, rombos_x = 0, treboles_x = 0, palos_x = 0; */
     
     /* Pone todas las cartas existentes en cuatro matrices (una por palo): */
     for (palo = 0; palo < PALOS; palo++)
     {
         for (numero = 0; numero < CARTAS; numero++)
         {
             if (baraja[palo][numero])
             {
                cartas_existentes[numero_cartas_existentes++] = 100 * palo + numero;
                /*
                palos_existentes[palos_x++] = palo;
                if (palo == 0) { numeros_existentes[palo][corazones_x++] = numero; }
                else if (palo == 1) { numeros_existentes[palo][picas_x++] = numero; }
                else if (palo == 2) { numeros_existentes[palo][rombos_x++] = numero; }
                else { numeros_existentes[palo][treboles_x++] = numero; }
                */
             }
         }
     }
     
     /* Calcula un palo aleatorio de los existentes: */
     /*
     srand(time(NULL));
     palo = rand() % palos_x;
     palo = palos_existentes[palo];
     */
     
     /* Calcula un numero existente del palo escogido: */
     /*
     if (palo == 0) { numero = rand() % corazones_x; }
     else if (palo == 1) { numero = rand() % picas_x; }
     else if (palo == 2) { numero = rand() % rombos_x; }
     else { numero = rand() % treboles_x; }
     numero = numeros_existentes[palo][numero];
     */
     
     /* Siempre que queden cartas, reparte: */
     if (numero_cartas_existentes - 1 >= 1)
     {
        /* Si esta trucado, pregunta la carta que se desea recibir: */
        if (TRUCADO)
        {
           do
           {
             printf("\n[TRUCAT] Numero de carta a recibir para jugador %d (-1 para salir): ", jugador+1);
             scanf("%d", &numero);
             if (!baraja[numero/100][numero%100]) { printf("\tEsta carta ya no esta en la baza, vuelve a intentarlo.\n"); }
           } while(!baraja[numero/100][numero%100] && numero != -1); /* Pregunta mientras la carta no este en la baza. */
        }
        else
        {
            /* Calcula una carta aleatoriamente de las existentes: */
            srand(time(NULL));
            numero = rand() % numero_cartas_existentes;
            numero = cartas_existentes[numero];
        }
     
        /* Decodificamos la carta (por ejemplo, 108 seria el 8 de picas): */
        palo = numero / 100;
        numero = numero % 100;

        /* Quita la carta de la baraja: */
        baraja[palo][numero] = false;

        /* Le da la carta al jugador: */
        mano[jugador][palo][numero] = true;
     }
     
     /* Retorna el numero de cartas que aun quedan en la baraja: */
     return numero_cartas_existentes - 1;
}


/* Funcion que calcula si el juego continua (si no hay ganador y aun quedan jugadores). */
int continua_juego(bool mano[][PALOS][CARTAS], bool perdedores[], bool ganadores[])
{
    int x, puntos[JUGADORES], quedan_jugadores = 0, unico_ganador = -1;
    bool juego_activo = false;
    
    /* Recoge la puntuacion de los jugadores: */
    for (x = 0; x < JUGADORES; x++)
    {
        puntos[x] = sumar_cartas(x, mano);
        /* Calcula si ha pasado de la puntuacion maxima y entonces pierde (siempre que no haya perdido ya): */
        if (puntos[x] > PUNTUACION_NECESARIA && !perdedores[x]) { perdedores[x] = true; printf("\nEl jugador %d ha perdido (puntos: %d).", x+1, puntos[x]); }
        /* si no, calcula si ha alcanzado la puntuacion necesaria para ganar (siempre que no haya ganado ya): */
        else if (puntos[x] == PUNTUACION_NECESARIA && !ganadores[x]) { ganadores[x] = true; printf("\nEl jugador %d ha alcanzado %d, enhorabuena.", x+1, PUNTUACION_NECESARIA); }
    }

    /* Calcular si aun queda mas de uno sin perder ni ganar (si no, se acabara el juego): */
    for (x = 0; x < JUGADORES; x++)
    {
        if (!perdedores[x] && !ganadores[x]) { quedan_jugadores++; unico_ganador = x; }
    }

    /* Si aun quedan 2 jugadores o mas, el juego continua: */
    juego_activo = (quedan_jugadores >= 2);
    
    /* Si solo queda un jugador, se imprime que es el ganador: */
    if (quedan_jugadores == 1) { ganadores[unico_ganador] = true; printf("\nGana el jugador %d (puntos: %d), enhorabuena.", unico_ganador+1, puntos[unico_ganador]); }
    
    /* Retorna si aun continua el juego o no: */
    return juego_activo;
}


/* Suma las cartas que el jugador tiene en su mano: */
int sumar_cartas(int jugador, bool mano[][PALOS][CARTAS])
{
    int puntos = 0, palo, numero, ases = 0;
    
    
    /* Calcula la puntuacion haciendo que los ases valgan 11: */
     for (palo = 0; palo < PALOS; palo++)
     {
         for (numero = 0; numero < CARTAS; numero++)
         {
             if (mano[jugador][palo][numero])
             {
                /* Si es un as (0), cuenta 11: */
                if (numero == 0) { puntos += 11; ases++; }
                /* ...pero si no, y es menor que 10 (10 = J), cuenta lo mismo que el numero: */
                else if (numero < 10) { puntos += numero + 1; }
                /* ...pero si es una figura, cuenta 10: */
                else { puntos += 10; }
             }
         }
     }
                
    /* Si su puntuacion es mayor a la puntuacion necesaria y tiene algun AS,
       hace que los ases valgan 1 (solo los necesarios): */
    while (ases > 0 && puntos > PUNTUACION_NECESARIA)
    {
          /* printf("\nUn AS del jugador %d vale 1 y no 11.\n", jugador+1); */
          puntos -= 10; /* Si antes valia 11, ahora valdra 1 (resta 10). */
          ases--; /* Como se ha "gastado" un as, se resta. */
    }
    
    /* Retorna la puntuacion: */
    return puntos;
}
