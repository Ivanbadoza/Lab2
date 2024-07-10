#include "prot.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    arregloEquipo equipos[MAX_EQUIPOS];
    int cantidadEquipos = 0;
    int opcion;
    char nombreArchivo[50];
    char nombreEquipo[30];
    char nombreJugador[30];
    char apellidoJugador[30];
    int numeroJugador;

    do
    {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            cargarJugadoresDesdeArchivo(equipos, &cantidadEquipos, "jugadores.dat");
            printf("Jugadores cargados exitosamente.\n");
            break;
        case 2:
            mostrarEquiposYJugadores(equipos, cantidadEquipos);
            break;
        case 3:
            printf("Ingrese el nombre del equipo: ");
            scanf("%s", nombreEquipo);
            printf("Ingrese el nombre del jugador: ");
            scanf("%s", nombreJugador);
            printf("Ingrese el apellido del jugador: ");
            scanf("%s", apellidoJugador);
            numeroJugador = buscarNumeroJugador(equipos, cantidadEquipos, nombreEquipo, nombreJugador, apellidoJugador);
            if (numeroJugador != -1)
            {
                printf("El numero del jugador %s %s en el equipo %s es: %d\n", nombreJugador, apellidoJugador, nombreEquipo, numeroJugador);
            }
            else
            {
                printf("Jugador no encontrado en el equipo %s.\n", nombreEquipo);
            }
            break;
        case 4:
        {
            stJugador nuevoJugador = cargarJugadorDesdeTeclado();
            printf("Ingrese el nombre del equipo al que pertenece el jugador: ");
            fflush(stdin);
            gets(nombreEquipo);
            darAltaNuevoJugador(equipos, &cantidadEquipos, nuevoJugador, nombreEquipo);
            printf("Jugador agregado exitosamente.\n");
        }
        break;
        case 5:
        {
            stEquipo nuevoEquipo = cargarEquipoDesdeTeclado();
            crearNuevoEquipo(equipos, &cantidadEquipos, nuevoEquipo.nombreEquipo);
            printf("Equipo agregado exitosamente.\n");
        }
        break;
        case 6:
        {
            generarArchivoJugadores("jugadores.dat", equipos, cantidadEquipos);
        }

        break;
        case 7:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opcion no valida. Intente nuevamente.\n");
            break;
        }
    }
    while (opcion != 6);

    return 0;
}

