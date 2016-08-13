#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAUSA "pause >NUL"
#define BORRAR_PANTALLA "cls"

#define F 15
#define C 10


int sumar_adyacentes(int tablero[F][C], int f, int c, int fila_celda, int columna_celda);
void vaciar_tablero(int tablero[F][C], int f, int c);
void crear_tablero(int tablero[F][C], int f, int c, int minas);
void crear_tablero_adyacentes(int tablero[F][C], int tablero_adyacentes[F][C], int f, int c);
void mostrar_tablero(int tablero[F][C], int f, int c);
int generar_camino(int tablero[F][C], int f, int c, int f_origen, int c_origen, int f_destino, int c_destino); /* Funcion recursiva que va de origen a destino. */
int celda_adyacente_aleatoria(int tablero[F][C], int f, int c, int fila_celda, int columna_celda); /* Devuelve una celda adyacente aleatoriamente, codificada. */


int sumar_adyacentes(int tablero[F][C], int f, int c, int fila_celda, int columna_celda)
{
    int suma = 0, fila, columna, f_inicial = fila_celda - 1, c_inicial = columna_celda - 1;
    
    for (fila = f_inicial; fila <= fila_celda + 1; fila++)
    {
        for (columna = c_inicial; columna <= columna_celda + 1; columna++)
        {
            if (columna >= 0 && columna < c && fila >= 0 && fila < f)
            {
               suma += tablero[fila][columna];
            }
        }
    }

    return suma - tablero[fila_celda][columna_celda];
}


void mostrar_tablero(int tablero[F][C], int f, int c)
{
    int fila, columna;

    for (fila = 0; fila < f; fila++)
    {
        for (columna = 0; columna < c; columna++)
        {
            printf("%d", tablero[fila][columna]);
        }
        printf("\n");
    }

    return;
}


void vaciar_tablero(int tablero[F][C], int f, int c)
{
     int fila, columna;

     for (fila = 0; fila < f; fila++)
     {
         for (columna = 0; columna < c; columna++)
         {
             tablero[fila][columna] = -1;
         }
     }
     
     return;
}


void crear_tablero(int tablero[F][C], int f, int c, int minas)
{
    int fila, columna, minas_puestas = 0;
    srand(time(NULL));

    while (minas_puestas < minas)
    {
          fila = rand() % f;
          columna = rand() % c;
          if (tablero[fila][columna] == -1) { tablero[fila][columna] = 1; minas_puestas++; }
    }

    for (fila = 0; fila < f; fila++)
    {
        for (columna = 0; columna < c; columna++)
        {
            if (tablero[fila][columna] == -1) { tablero[fila][columna] = 0; }
        }
    }

    return;
}


void crear_tablero_adyacentes(int tablero[F][C], int tablero_adyacentes[F][C], int f, int c)
{
    int fila, columna;

    for (fila = 0; fila < f; fila++)
    {
        for (columna = 0; columna < c; columna++)
        {
            tablero_adyacentes[fila][columna] = sumar_adyacentes(tablero, f, c, fila, columna);
        }
    }
    
    return;
}


int celda_adyacente_aleatoria(int tablero[F][C], int f, int c, int fila_celda, int columna_celda)
{
    int celda_aleatoria_codificada, fila, columna;
    /* int f_inicial = fila_celda - 1, c_inicial = columna_celda - 1; */
    int se_escoge = 0;
    srand(time(NULL));
    
/*    for (fila = f_inicial; fila <= fila_celda + 1 && !se_escoge; fila++)
    {
        for (columna = c_inicial; columna <= columna_celda + 1 && !se_escoge; columna++)
        {
            if (columna >= 0 && columna < c && fila >= 0 && fila < f)
            {
               if (fila != fila_celda && columna != columna_celda)
               {
                  se_escoge = rand() % 2;
               }
            }
        }
    }
*/

    if (!se_escoge)
    {
       do
       {
         do { fila = (rand() % 3) + fila_celda - 1; } while (fila < 0 || fila >= f);
    srand(time(NULL));         
         do { columna = (rand() % 3) + columna_celda - 1; } while (columna < 0 || columna >= f);
       } while (fila == fila_celda && columna == columna_celda);
    }

    celda_aleatoria_codificada = (fila * c) + columna;
    printf("\nAleatoria a (%d, %d) es: %d (%d, %d)\n", fila_celda, columna_celda, celda_aleatoria_codificada, fila, columna);

    return celda_aleatoria_codificada;
}



int generar_camino(int tablero[F][C], int f, int c, int f_origen, int c_origen, int f_destino, int c_destino)
{
    /* int celda_codificada = (f_origen * c) + c_origen; */
    int celda_aleatoria_codificada = celda_adyacente_aleatoria(tablero, f, c, f_origen, c_origen);
    int f_adyacente = celda_aleatoria_codificada / c;
    int c_adyacente = celda_aleatoria_codificada % c;
    /* int tablero_generado[F][C] = { 0 }; */
    int fila, columna;
    int se_ha_encontrado_camino = 0;
    tablero[f_origen][c_origen] = 5; /* HAY QUE CAMBIAR A CERO!!! */
    /* Condicion de parada: si la celda codificada es la misma que la de destino. */
    if (f_origen == f_destino && c_origen == c_destino)
    {
/*
       for (fila = 0; fila < f; fila++)
       {
           for (columna = 0; columna < c; columna++)
           {
               tablero[fila][columna] = tablero_generado[fila][columna];
           }
       }
*/
       se_ha_encontrado_camino = 1;
       printf("\nfila: %d, columna:%d\n", f_destino, c_destino);
       mostrar_tablero(tablero, f, c);
    }
    else { se_ha_encontrado_camino = generar_camino(tablero, f, c, f_adyacente, c_adyacente, f_destino, c_destino); }
    
    return se_ha_encontrado_camino;
}
