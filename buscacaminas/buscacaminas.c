#include <stdio.h>
#include <stdlib.h>
#include "buscacaminas.h"

int main()
{
    int tablero[F][C], tablero_adyacentes[F][C];
    int f = 10, c = 10, minas = 10;
    int f_origen = 0, c_origen = 0, f_destino = f - 1, c_destino = c - 1;
    int se_ha_encontrado_camino = 0;
    
    vaciar_tablero(tablero, f, c);
    se_ha_encontrado_camino = generar_camino(tablero, f, c, f_origen, c_origen, f_destino, c_destino);
    if (se_ha_encontrado_camino) { printf("\nSe ha encontrado camino!!!\n"); }
    else { printf("\nNOOOO\n"); }
    crear_tablero(tablero, f, c, minas);
    
    mostrar_tablero(tablero, f, c);

    printf("\n\n");
    
    crear_tablero_adyacentes(tablero, tablero_adyacentes, f, c);    

    mostrar_tablero(tablero_adyacentes, f, c);
    
    printf("\nAdios.");
    system(PAUSA);
    return 0;
}
