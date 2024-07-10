#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED


typedef struct nodoArbol
{
    char nombreLibro[30];
    int cantPaginas;
    char genero[20];
    int Puntaje;
    char NombrePersona[20];
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct celda
{
    char NombrePersona[20];
    struct nodoListaLibro * listaLibros;
} celda;

typedef struct nodoListaLibro
{
    char nombreLibro[30];
    int cantPaginas;
    char genero[20];
    int Puntaje;
    struct nodoListaLibro* sig;
} nodoListaLibro;

// Prototipos de funciones
nodoListaLibro* crearNodoLista(char nombreLibro[], int cantPaginas, char genero[], int Puntaje);
void insertarNodoEnLista(nodoListaLibro** lista, nodoListaLibro* nuevoNodo);
int buscarPosEnArreglo(celda A[], int dimension, char NombrePersona[]);
int pasarDeArbolToArregloDeListas(nodoArbol* arbol, celda A[], int dimension);
void mostrarLista(nodoListaLibro* lista);
void mostrarArregloDeListas(celda A[], int dimension);
nodoArbol* insertarEnArbol(nodoArbol* arbol, char nombreLibro[], int cantPaginas, char genero[], int Puntaje, char NombrePersona[]);
celda* buscarPosEnArregloRec(celda *A, celda *fin, char NombrePersona[]);
int buscarEnListaRec(nodoListaLibro* lista, int Puntaje);
int decimeSiExiste(celda A[], int dimension, char NombrePersona[], int Puntaje);

#endif // PROT_H_INCLUDED
