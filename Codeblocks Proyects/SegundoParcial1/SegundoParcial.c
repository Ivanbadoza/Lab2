#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SegundoParcial.h"

// Implementación de funciones

nodoListaLibro* InicLista (){
return NULL;
}
//Crear Nodo Lista
nodoListaLibro* crearNodoLista(char nombreLibro[], int cantPaginas, char genero[], int Puntaje) {
    nodoListaLibro* nuevoNodo = (nodoListaLibro*)malloc(sizeof(nodoListaLibro));
    strcpy(nuevoNodo->nombreLibro, nombreLibro);
    nuevoNodo->cantPaginas = cantPaginas;
    strcpy(nuevoNodo->genero, genero);
    nuevoNodo->Puntaje = Puntaje;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}
//Insertar Nodo por puntaje
nodoListaLibro* insertarNodoEnLista(nodoListaLibro* lista, nodoListaLibro* nuevoNodo) {
    if (lista == NULL || (lista)->Puntaje > nuevoNodo->Puntaje) {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    } else {
        nodoListaLibro* seg = lista;
        while (seg->sig != NULL && seg->sig->Puntaje <= nuevoNodo->Puntaje) {
            seg = seg->sig;
        }
        nuevoNodo->sig = seg->sig;
        seg->sig = nuevoNodo;
    }
    return lista;
}
//retorna número de celda o -1 si no se encuentra
int buscarPosEnArreglo(celda A[], int dimension, char NombrePersona[]) {
    int rta=-1;

    for (int i = 0; i < dimension; i++) {
        if (strcmp(A[i].NombrePersona, NombrePersona) == 0) {
            rta=i;
        }
    }
    return rta;
}
///Inserto  en el arreglo de listas , los datos del arbol
void insertarEnArreglo(celda A[], int *dimension, nodoArbol* arbol) {
    int pos = buscarPosEnArreglo(A, *dimension, arbol->NombrePersona);
    if (pos == -1) {
        pos = (*dimension)++;
        strcpy(A[pos].NombrePersona, arbol->NombrePersona);
        A[pos].listaLibros = InicLista();
    }
    nodoListaLibro* nuevoNodo = crearNodoLista(arbol->nombreLibro, arbol->cantPaginas, arbol->genero, arbol->Puntaje);
    A[pos].listaLibros=insertarNodoEnLista((A[pos].listaLibros), nuevoNodo);
}
///Recorro el arbol inorder e inserto en el arreglo
void recorrerArbolInOrder(nodoArbol* arbol, celda A[], int *dimension) {
    if (arbol != NULL) {
        recorrerArbolInOrder(arbol->izq, A, dimension);
        insertarEnArreglo(A, dimension, arbol);
        recorrerArbolInOrder(arbol->der, A, dimension);
    }
}
///retorna la cantidad de celdas del arreglo. (validos)
int pasarDeArbolToArregloDeListas(nodoArbol* arbol, celda A[], int dimension) {
    int dimensionFinal = 0;
    recorrerArbolInOrder(arbol, A, &dimensionFinal);
    return dimensionFinal;
}
///Muestro la lista
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
///Muestro el arreglo de listas , usando la funcion de mostrar lista
void mostrarArregloDeListas(celda A[], int dimension) {
    for (int i = 0; i < dimension; i++) {
        printf("Nombre de la Persona: %s\n", A[i].NombrePersona);
        mostrarLista(A[i].listaLibros);
    }
}
///Creo el nodo arbol
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
        arbol = crearNodoArbol(nombreLibro, cantPaginas, genero, Puntaje, NombrePersona);
    } else if (Puntaje < arbol->Puntaje) {
        arbol->izq = insertarEnArbol(arbol->izq, nombreLibro, cantPaginas, genero, Puntaje, NombrePersona);
    } else {
        arbol->der = insertarEnArbol(arbol->der, nombreLibro, cantPaginas, genero, Puntaje, NombrePersona);
    }
    return arbol;
}
 // recorre el arreglo de forma recursiva
int buscarPosEnArregloRec(celda A[], int dimension, char NombrePersona[], int index) {
    int resultado = -1;
    if (index < dimension) {
        if (strcmp(A[index].NombrePersona, NombrePersona) == 0) {
            resultado = index;
        } else {
            resultado = buscarPosEnArregloRec(A, dimension, NombrePersona, index + 1);
        }
    }
    return resultado;
}
///Busco un puntaje en una lista de forma recursiva
int buscarEnListaRec(nodoListaLibro* lista, int Puntaje) {
    int resultado = -1;
    if (lista != NULL) {
        if (lista->Puntaje == Puntaje) {
            resultado = 1;
        } else {
            resultado = buscarEnListaRec(lista->sig, Puntaje);
        }
    }
    return resultado;
}
///Recorre y busca si existe
int decimeSiExiste(celda A[], int dimension, char NombrePersona[], int Puntaje) {
    int resultado = -1;
    int pos = buscarPosEnArregloRec(A, dimension, NombrePersona, 0);
    if (pos != -1) {
        resultado = buscarEnListaRec(A[pos].listaLibros, Puntaje);
    }
    return resultado;
}



