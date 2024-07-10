#include "prot.h"
#include <string.h>


// Implementación de funciones
nodoListaLibro* crearNodoLista(char nombreLibro[], int cantPaginas, char genero[], int Puntaje) {
    nodoListaLibro* nuevoNodo = (nodoListaLibro*)malloc(sizeof(nodoListaLibro));
    strcpy(nuevoNodo->nombreLibro, nombreLibro);
    nuevoNodo->cantPaginas = cantPaginas;
    strcpy(nuevoNodo->genero, genero);
    nuevoNodo->Puntaje = Puntaje;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}

void insertarNodoEnLista(nodoListaLibro** lista, nodoListaLibro* nuevoNodo) {
    if (*lista == NULL || (*lista)->Puntaje > nuevoNodo->Puntaje) {
        nuevoNodo->sig = *lista;
        *lista = nuevoNodo;
    } else {
        nodoListaLibro* actual = *lista;
        while (actual->sig != NULL && actual->sig->Puntaje <= nuevoNodo->Puntaje) {
            actual = actual->sig;
        }
        nuevoNodo->sig = actual->sig;
        actual->sig = nuevoNodo;
    }
}

int buscarPosEnArreglo(celda A[], int dimension, char NombrePersona[]) {
    for (int i = 0; i < dimension; i++) {
        if (strcmp(A[i].NombrePersona, NombrePersona) == 0) {
            return i;
        }
    }
    return -1;
}

void insertarEnArreglo(celda A[], int *dimension, nodoArbol* arbol) {
    int pos = buscarPosEnArreglo(A, *dimension, arbol->NombrePersona);
    if (pos == -1) {
        pos = (*dimension)++;
        strcpy(A[pos].NombrePersona, arbol->NombrePersona);
        A[pos].listaLibros = NULL;
    }
    nodoListaLibro* nuevoNodo = crearNodoLista(arbol->nombreLibro, arbol->cantPaginas, arbol->genero, arbol->Puntaje);
    insertarNodoEnLista(&(A[pos].listaLibros), nuevoNodo);
}

void recorrerArbolInOrder(nodoArbol* arbol, celda A[], int *dimension) {
    if (arbol != NULL) {
        recorrerArbolInOrder(arbol->izq, A, dimension);
        insertarEnArreglo(A, dimension, arbol);
        recorrerArbolInOrder(arbol->der, A, dimension);
    }
}

int pasarDeArbolToArregloDeListas(nodoArbol* arbol, celda A[], int dimension) {
    int dimensionFinal = 0;
    recorrerArbolInOrder(arbol, A, &dimensionFinal);
    return dimensionFinal;
}

void mostrarLista(nodoListaLibro* lista) {
    nodoListaLibro* actual = lista;
    while (actual != NULL) {
        printf("Nombre del Libro: %s\n", actual->nombreLibro);
        printf("Cantidad de Paginas: %d\n", actual->cantPaginas);
        printf("Genero: %s\n", actual->genero);
        printf("Puntaje: %d\n\n", actual->Puntaje);
        actual = actual->sig;
    }
}

void mostrarArregloDeListas(celda A[], int dimension) {
    for (int i = 0; i < dimension; i++) {
        printf("Nombre de la Persona: %s\n", A[i].NombrePersona);
        mostrarLista(A[i].listaLibros);
    }
}

nodoArbol* crearNodoArbol(char nombreLibro[], int cantPaginas, char genero[], int Puntaje, char NombrePersona[]) {
    nodoArbol* nuevoNodo = (nodoArbol*)malloc(sizeof(nodoArbol));
    strcpy(nuevoNodo->nombreLibro, nombreLibro);
    nuevoNodo->cantPaginas = cantPaginas;
    strcpy(nuevoNodo->genero, genero);
    nuevoNodo->Puntaje = Puntaje;
    strcpy(nuevoNodo->NombrePersona, NombrePersona);
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

nodoArbol* insertarEnArbol(nodoArbol* arbol, char nombreLibro[], int cantPaginas, char genero[], int Puntaje, char NombrePersona[]) {
    if (arbol == NULL) {
        return crearNodoArbol(nombreLibro, cantPaginas, genero, Puntaje, NombrePersona);
    }
    if (Puntaje < arbol->Puntaje) {
        arbol->izq = insertarEnArbol(arbol->izq, nombreLibro, cantPaginas, genero, Puntaje, NombrePersona);
    } else {
        arbol->der = insertarEnArbol(arbol->der, nombreLibro, cantPaginas, genero, Puntaje, NombrePersona);
    }
    return arbol;
}

celda* buscarPosEnArregloRec(celda *A, celda *fin, char NombrePersona[]) {
    if (A == fin) {
        return NULL;
    }
    if (strcmp(A->NombrePersona, NombrePersona) == 0) {
        return A;
    }
    return buscarPosEnArregloRec(A + 1, fin, NombrePersona);
}

int buscarEnListaRec(nodoListaLibro* lista, int Puntaje) {
    if (lista == NULL) {
        return -1;
    }
    if (lista->Puntaje == Puntaje) {
        return 1;
    }
    return buscarEnListaRec(lista->sig, Puntaje);
}

int decimeSiExiste(celda A[], int dimension, char NombrePersona[], int Puntaje) {
    celda *pos = buscarPosEnArregloRec(A, A + dimension, NombrePersona);
    if (pos == NULL) {
        return -1;
    }
    return buscarEnListaRec(pos->listaLibros, Puntaje);
}

