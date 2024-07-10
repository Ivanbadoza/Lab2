#include "prot.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
  //     generarArchivoJugadores("jugadores.dat");

   arregloEquipo equipos[MAX_EQUIPOS];
    int cantidadEquipos = 0;

    for (int i = 0; i < MAX_EQUIPOS; i++) {
        equipos[i].listaJugadores = NULL;
    }

   // leerArchivoYAgregarJugadores(equipos, &cantidadEquipos, "jugadores.dat");

    cargarJugadoresDesdeArchivo(equipos, &cantidadEquipos, "jugadores.dat");
    mostrarEquiposYJugadores(equipos, cantidadEquipos);


    // Ejemplo de búsqueda de número de jugador
    char equipoBusqueda[] = "Barcelona";
    char nombreBusqueda[] = "Lionel";
    char apellidoBusqueda[] = "Messi";

    int numeroJugador = buscarNumeroJugador(equipos, cantidadEquipos, equipoBusqueda, nombreBusqueda, apellidoBusqueda);
    if (numeroJugador != -1) {
        printf("El número del jugador %s %s en el equipo %s es: %d\n", nombreBusqueda, apellidoBusqueda, equipoBusqueda, numeroJugador);
    } else {
        printf("Jugador no encontrado en el equipo %s.\n", equipoBusqueda);
    }
    return 0;
}
