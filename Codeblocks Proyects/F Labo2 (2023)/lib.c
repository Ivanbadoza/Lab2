#include "prot.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

///Inic Lista
nodoListaJugador* inicializarLista()
{
    return NULL;
}

///Crearr Nodo
nodoListaJugador* crearNodo(stJugador j)
{
    nodoListaJugador* nuevo = (nodoListaJugador*) malloc(sizeof(nodoListaJugador));
    nuevo->j = j;
    nuevo->sig = NULL;
    return nuevo;
}

///Insertar Nodo de Forma Recursiva
nodoListaJugador* insertarNodoRecursivo(nodoListaJugador* lista, stJugador j)
{
    if (lista == NULL)
    {
        lista= crearNodo(j);
    }
    else
    {
        lista->sig = insertarNodoRecursivo(lista->sig, j);
        return lista;
    }
}

///Creo un equipo nuevo
int agregarEquipo(arregloEquipo* equipos, int* cantidad, char* nombreEquipo)
{
    int indice = *cantidad;
    equipos[indice].e.idEquipo = indice + 1; ///se genera el id automatico
    strcpy(equipos[indice].e.nombreEquipo, nombreEquipo);
    equipos[indice].e.puntosGanados = 0;
    equipos[indice].listaJugadores = inicializarLista();
    (*cantidad)++;
    return indice;
}

///Busco posicion del equipo , si no existe devuelvo -1
int buscarPosicionEquipo(arregloEquipo* equipos, int cantidad, char* nombreEquipo)
{

    int rta=-1;
    for (int i = 0; i < cantidad; i++)
    {
        if (strcmp(equipos[i].e.nombreEquipo, nombreEquipo) == 0)
        {
            rta=i;
        }
    }
    return rta;
}
///Creo nodo arreglo equipo
int crearNuevoEquipo(arregloEquipo* equipos, int* cantidad, char* nombreEquipo)
{
    int indice = *cantidad;
    equipos[indice].e.idEquipo = indice + 1;
    strcpy(equipos[indice].e.nombreEquipo, nombreEquipo);
    equipos[indice].e.puntosGanados = 0;
    equipos[indice].listaJugadores = inicializarLista();
    (*cantidad)++;
    return indice;
}
/// Doy alta a un nuevo jugador , si no existe equipo , lo agrego.

void darAltaNuevoJugador(arregloEquipo* equipos, int* cantidad, stJugador jugador, char* nombreEquipo)
{
    int indiceEquipo = buscarPosicionEquipo(equipos, *cantidad, nombreEquipo);
    if (indiceEquipo == -1)
    {
        // Si el equipo no se encuentra, se crea un nuevo equipo
        indiceEquipo = crearNuevoEquipo(equipos, cantidad, nombreEquipo);
    }
    // Se agrega el nuevo jugador al equipo encontrado o creado
    equipos[indiceEquipo].listaJugadores = insertarNodoRecursivo(equipos[indiceEquipo].listaJugadores, jugador);
}
/// Leo un archivo de jugadores
void leerArchivoYAgregarJugadores(arregloEquipo* equipos, int* cantidad, const char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo)
    {
        stRegistroJugador registro;
        while (fread(&registro, sizeof(stRegistroJugador), 1, archivo) == 1)
        {
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
    else
    {
        printf("No se pudo abrir el archivo . ");
    }

}
///Recorro el arreglo y muestro equipos con sus jugadores
void mostrarEquiposYJugadores(arregloEquipo* equipos, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("Equipo: %s\n", equipos[i].e.nombreEquipo);
        nodoListaJugador* lista = equipos[i].listaJugadores;
        while (lista)
        {
            printf("\tJugador: %s %s\n", lista->j.nombreJugador, lista->j.apellidoJugador);
            lista = lista->sig;
        }
    }
}
///Guardo jugadores em archivo
void generarArchivoJugadores(const char* nombreArchivo, arregloEquipo* equipos, int cantidadEquipos) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (!archivo) {
        printf("No se pudo generar el archivo %s.\n", nombreArchivo);
        return;
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

    printf("Archivo %s generado con éxito.\n", nombreArchivo);
    fclose(archivo);
}

// Función para cargar jugadores desde el archivo
void cargarJugadoresDesdeArchivo(arregloEquipo* equipos, int* cantidadEquipos, const char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo)
    {
        printf("Error al abrir el archivo %s.\n", nombreArchivo);
        return;
    }

    stRegistroJugador registro;
    while (fread(&registro, sizeof(stRegistroJugador), 1, archivo) == 1)
    {
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
int buscarNumeroJugador(arregloEquipo* equipos, int cantidadEquipos, char* nombreEquipo, char* nombreJugador, char* apellidoJugador)
{
    int rta=-1;
    int indiceEquipo = buscarPosicionEquipo(equipos, cantidadEquipos, nombreEquipo);
    if (indiceEquipo == -1)
    {
        rta= -1; // Equipo no encontrado
    }

    nodoListaJugador* lista = equipos[indiceEquipo].listaJugadores;
    while (lista)
    {
        if (strcmp(lista->j.nombreJugador, nombreJugador) == 0 && strcmp(lista->j.apellidoJugador, apellidoJugador) == 0)
        {
            return lista->j.nroJugador; // Jugador encontrado
        }
        lista = lista->sig;
    }

    return rta; // Jugador no encontrado en el equipo
}

stJugador cargarJugadorDesdeTeclado()
{
    stJugador jugador;

    printf("Ingrese el número del jugador: ");
    fflush(stdin);
    scanf("%d",&jugador.nroJugador);
    printf("Ingrese el nombre del jugador: ");
    fflush(stdin);
    gets(jugador.nombreJugador);
    printf("Ingrese el apellido del jugador: ");
    fflush(stdin);
    gets(jugador.apellidoJugador);
    printf("Ingrese el año de nacimiento del jugador: ");
    fflush(stdin);
    scanf("%d", &jugador.clase);
    printf("Ingrese el puesto del jugador: ");
    fflush(stdin);
    gets(jugador.puestoJugador);

    return jugador;
}
// Función para cargar un equipo desde el teclado
stEquipo cargarEquipoDesdeTeclado()
{
    stEquipo equipo;

    printf("Ingrese el nombre del equipo: ");
    scanf("%s", equipo.nombreEquipo);
    printf("Ingrese los puntos ganados por el equipo: ");
    scanf("%d", &equipo.puntosGanados);
    // ID del equipo será generado al agregarlo al arreglo

    return equipo;
}

// Función para mostrar el menú
void mostrarMenu()
{
    printf("\n--- Menu ---\n");
    printf("1. Cargar jugadores desde archivo\n");
    printf("2. Mostrar jugadores por equipo\n");
    printf("3. Buscar numero de jugador\n");
    printf("4. Cargar nuevo jugador\n");
    printf("5. Cargar nuevo equipo\n");
    printf("6. Guardar Archivo Equipos\n");
    printf("7. Salir .\n");
    printf("Seleccione una opcion: ");
}
