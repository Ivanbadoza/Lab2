#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED

#define MAX_EQUIPOS 100

typedef struct {
    int idRegistro;
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase; //anio de nacimiento
    char puestoJugador[30];// Delantero-Medio-Defensor-Arquero
    char nombreEquipo[30];
    int puntosGanados;
} stRegistroJugador;

typedef struct {
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase;
    char puestoJugador[30];
} stJugador;

typedef struct nodoListaJugador {
    stJugador j;
    struct nodoListaJugador * sig;
} nodoListaJugador;

typedef struct {
    int idEquipo; // (generarlo, no est� en el archivo)
    char nombreEquipo[30];
    int puntosGanados;
} stEquipo;

typedef struct {
    stEquipo e;
    nodoListaJugador * listaJugadores;
} arregloEquipo;

nodoListaJugador* inicializarLista();
nodoListaJugador* crearNodo(stJugador j) ;
nodoListaJugador* insertarNodoRecursivo(nodoListaJugador* lista, stJugador j);
int agregarEquipo(arregloEquipo* equipos, int* cantidad, char* nombreEquipo);
int buscarPosicionEquipo(arregloEquipo* equipos, int cantidad, char* nombreEquipo);
stJugador cargarJugadorDesdeTeclado();
stEquipo cargarEquipoDesdeTeclado();
void mostrarEquiposYJugadores(arregloEquipo* equipos, int cantidad);
void generarArchivoJugadores(const char* nombreArchivo, arregloEquipo* equipos, int cantidadEquipos);
#endif // PROT_H_INCLUDED
