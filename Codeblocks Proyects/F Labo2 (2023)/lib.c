#include "prot.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


nodoListaJugador* inicializarLista() {
    return NULL;
}
nodoListaJugador* crearNodo(stJugador j) {
    nodoListaJugador* nuevo = (nodoListaJugador*) malloc(sizeof(nodoListaJugador));
    if (!nuevo) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevo->j = j;
    nuevo->sig = NULL;
    return nuevo;
}

nodoListaJugador* insertarNodoRecursivo(nodoListaJugador* lista, stJugador j) {
    if (lista == NULL) {
        return crearNodo(j);
    } else {
        lista->sig = insertarNodoRecursivo(lista->sig, j);
        return lista;
    }
}


nodoListaJugador* agregarJugador(nodoListaJugador * lista, stJugador j) {
    nodoListaJugador * nuevo = (nodoListaJugador *) malloc(sizeof(nodoListaJugador));
    if (!nuevo) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevo->j = j;
    nuevo->sig = lista;
    return nuevo;
}

int buscarEquipo(arregloEquipo* equipos, int cantidad, char* nombreEquipo) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(equipos[i].e.nombreEquipo, nombreEquipo) == 0) {
            return i;
        }
    }
    return -1;
}

int agregarEquipo(arregloEquipo* equipos, int* cantidad, char* nombreEquipo) {
    int indice = *cantidad;
    equipos[indice].e.idEquipo = indice + 1;
    strcpy(equipos[indice].e.nombreEquipo, nombreEquipo);
    equipos[indice].e.puntosGanados = 0;
    equipos[indice].listaJugadores = inicializarLista();
    (*cantidad)++;
    return indice;
}
int buscarPosicionEquipo(arregloEquipo* equipos, int cantidad, char* nombreEquipo) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(equipos[i].e.nombreEquipo, nombreEquipo) == 0) {
            return i;
        }
    }
    return -1;
}

int crearNuevoEquipo(arregloEquipo* equipos, int* cantidad, char* nombreEquipo) {
    int indice = *cantidad;
    equipos[indice].e.idEquipo = indice + 1;
    strcpy(equipos[indice].e.nombreEquipo, nombreEquipo);
    equipos[indice].e.puntosGanados = 0;
    equipos[indice].listaJugadores = inicializarLista();
    (*cantidad)++;
    return indice;
}

void darAltaNuevoJugador(arregloEquipo* equipos, int* cantidad, stJugador jugador, char* nombreEquipo) {
    int indiceEquipo = buscarPosicionEquipo(equipos, *cantidad, nombreEquipo);
    if (indiceEquipo == -1) {
        // Si el equipo no se encuentra, se crea un nuevo equipo
        indiceEquipo = crearNuevoEquipo(equipos, cantidad, nombreEquipo);
    }
    // Se agrega el nuevo jugador al equipo encontrado o creado
    equipos[indiceEquipo].listaJugadores = insertarNodoRecursivo(equipos[indiceEquipo].listaJugadores, jugador);
}

void leerArchivoYAgregarJugadores(arregloEquipo* equipos, int* cantidad, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) {
        printf("Error al abrir el archivo %s.\n", nombreArchivo);
        return;
    }

    stRegistroJugador registro;
    while (fread(&registro, sizeof(stRegistroJugador), 1, archivo) == 1) {
        printf("Leyendo registro: %s %s, Equipo: %s\n", registro.nombreJugador, registro.apellidoJugador, registro.nombreEquipo);

        stJugador jugador;
        jugador.nroJugador = registro.nroJugador;
        strcpy(jugador.nombreJugador, registro.nombreJugador);
        strcpy(jugador.apellidoJugador, registro.apellidoJugador);
        jugador.clase = registro.clase;
        strcpy(jugador.puestoJugador, registro.puestoJugador);

        darAltaNuevoJugador(equipos, cantidad, jugador, registro.nombreEquipo);
    }

    fclose(archivo);
}

void mostrarEquiposYJugadores(arregloEquipo* equipos, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("Equipo: %s\n", equipos[i].e.nombreEquipo);
        nodoListaJugador* lista = equipos[i].listaJugadores;
        while (lista) {
            printf("\tJugador: %s %s\n", lista->j.nombreJugador, lista->j.apellidoJugador);
            lista = lista->sig;
        }
    }
}
void generarArchivoJugadores(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (!archivo) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    stRegistroJugador registros[] = {
        {1, 10, "Lionel", "Messi", 1987, "Delantero", "Barcelona", 100},
        {2, 7, "Cristiano", "Ronaldo", 1985, "Delantero", "Real Madrid", 90},
        {3, 8, "Andres", "Iniesta", 1984, "Medio", "Barcelona", 80},
        {4, 1, "Iker", "Casillas", 1981, "Arquero", "Real Madrid", 85},
        {5, 3, "Gerard", "Pique", 1987, "Defensor", "Barcelona", 75},
        {6, 4, "Sergio", "Ramos", 1986, "Defensor", "Real Madrid", 70}
    };

    size_t cantidadRegistros = sizeof(registros) / sizeof(stRegistroJugador);

    arregloEquipo equipos[MAX_EQUIPOS];
    int cantidadEquipos = 0;

    for (size_t i = 0; i < cantidadRegistros; i++) {
        stJugador jugador;
        jugador.nroJugador = registros[i].nroJugador;
        strcpy(jugador.nombreJugador, registros[i].nombreJugador);
        strcpy(jugador.apellidoJugador, registros[i].apellidoJugador);
        jugador.clase = registros[i].clase;
        strcpy(jugador.puestoJugador, registros[i].puestoJugador);

        darAltaNuevoJugador(equipos, &cantidadEquipos, jugador, registros[i].nombreEquipo);
    }

    for (int i = 0; i < cantidadEquipos; i++) {
        nodoListaJugador* lista = equipos[i].listaJugadores;
        while (lista) {
            stRegistroJugador registro;
            registro.idRegistro = equipos[i].e.idEquipo;
            registro.nroJugador = lista->j.nroJugador;
            strcpy(registro.nombreJugador, lista->j.nombreJugador);
            strcpy(registro.apellidoJugador, lista->j.apellidoJugador);
            registro.clase = lista->j.clase;
            strcpy(registro.puestoJugador, lista->j.puestoJugador);
            strcpy(registro.nombreEquipo, equipos[i].e.nombreEquipo);
            registro.puntosGanados = equipos[i].e.puntosGanados;
            fwrite(&registro, sizeof(stRegistroJugador), 1, archivo);
            lista = lista->sig;
        }
    }

    fclose(archivo);
    printf("Archivo %s generado con éxito.\n", nombreArchivo);
}


// Función para cargar jugadores desde el archivo
void cargarJugadoresDesdeArchivo(arregloEquipo* equipos, int* cantidadEquipos, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) {
        printf("Error al abrir el archivo %s.\n", nombreArchivo);
        return;
    }

    stRegistroJugador registro;
    while (fread(&registro, sizeof(stRegistroJugador), 1, archivo) == 1) {
        stJugador jugador;
        jugador.nroJugador = registro.nroJugador;
        strcpy(jugador.nombreJugador, registro.nombreJugador);
        strcpy(jugador.apellidoJugador, registro.apellidoJugador);
        jugador.clase = registro.clase;
        strcpy(jugador.puestoJugador, registro.puestoJugador);

        darAltaNuevoJugador(equipos, cantidadEquipos, jugador, registro.nombreEquipo);
    }

    fclose(archivo);
}

// Función para buscar el número de jugador por equipo, nombre y apellido
int buscarNumeroJugador(arregloEquipo* equipos, int cantidadEquipos, char* nombreEquipo, char* nombreJugador, char* apellidoJugador) {
    int indiceEquipo = buscarPosicionEquipo(equipos, cantidadEquipos, nombreEquipo);
    if (indiceEquipo == -1) {
        return -1; // Equipo no encontrado
    }

    nodoListaJugador* lista = equipos[indiceEquipo].listaJugadores;
    while (lista) {
        if (strcmp(lista->j.nombreJugador, nombreJugador) == 0 && strcmp(lista->j.apellidoJugador, apellidoJugador) == 0) {
            return lista->j.nroJugador; // Jugador encontrado
        }
        lista = lista->sig;
    }

    return -1; // Jugador no encontrado en el equipo
}
