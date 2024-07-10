#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARTAS 10  // Dimensi�n m�xima del arreglo de cartas

/// Funci�n para crear un nodo con una stCarta
nodoCarta *crearNodoCarta(stCarta carta) {
    nodoCarta *nuevoNodo = (nodoCarta *)malloc(sizeof(nodoCarta));
    nuevoNodo->dato = carta;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    return nuevoNodo;
}

/// Funci�n para contar la cantidad de stCarta con un destino espec�fico
int contarCartasPorDestino(nodoCarta *lista, char *destinoBuscado) {
    int contador = 0;
    nodoCarta *seg = lista;

    // Recorrer la lista de nodos
    while (seg != NULL) {
        // Comparar el destino de la carta seg con el destino buscado
        if (strcmp(seg->dato.destino, destinoBuscado) == 0) {
            contador++;
        }
        // Avanzar al siguiente nodo
        seg = seg->siguiente;
    }

    return contador;
}


/// Funci�n para agregar un elemento al final de la fila
void AgregarALaFila(nodoCarta **inicio, nodoCarta **fin, stCarta carta) {
    // Crear un nuevo nodo para la carta
    nodoCarta *nuevoNodo = crearNodoCarta(carta);
    // Si la fila est� vac�a, el nuevo nodo es el inicio y el fin
    if (*inicio == NULL) {
        nuevoNodo->anterior = NULL;
        *inicio = nuevoNodo;
        *fin = nuevoNodo;
    } else {
        // Conectar el nuevo nodo al final de la fila
        nuevoNodo->anterior = *fin;
        (*fin)->siguiente = nuevoNodo;
        *fin = nuevoNodo;
    }
}

/// Funci�n para extraer la primera carta de la fila (lista doblemente enlazada)
stCarta extraerDeLaFila(nodoCarta **inicio, nodoCarta **fin) {
    stCarta cartaExtraida;
    nodoCarta *seg;

    // Inicializar cartaExtraida con un valor de error por defecto
    cartaExtraida.tipoCarta = -1;

    // Verificar si la fila est� vac�a
    if (*inicio != NULL) {
        seg = *inicio;
        cartaExtraida = seg->dato;

        *inicio = seg->siguiente;
        if (*inicio == NULL) {
            *fin = NULL;
        } else {
            (*inicio)->anterior = NULL;
        }

        free(seg);
    } else {
        printf("La fila est� vac�a. No se puede extraer ninguna carta.\n");
    }

    return cartaExtraida;
}

/// Funci�n para pasar cartas de un tipo espec�fico a un arreglo
int pasarCartasAArreglo(nodoCarta **inicio, nodoCarta **fin, int tipo, stCarta arreglo[MAX_CARTAS]) {
    int contador = 0;
    nodoCarta *seg = *inicio;
    nodoCarta *siguiente = NULL;
    nodoCarta *anterior = NULL;

    // Recorrer la lista y pasar las cartas al arreglo
    while (seg != NULL && contador < MAX_CARTAS) {
        siguiente = seg->siguiente;
        anterior = seg->anterior; // Guardar el nodo anterior antes de liberar memoria

        // Verificar si la carta es del tipo buscado
        if (seg->dato.tipoCarta == tipo) {
            arreglo[contador] = seg->dato;
            contador++;

            // Si actual es el primer nodo, ajustar *inicio
            if (anterior == NULL) {
                *inicio = siguiente;
                if (siguiente != NULL) {
                    siguiente->anterior = NULL;
                } else {
                    *fin = NULL; // Lista vac�a
                }
            } else {
                // Si actual no es el primer nodo, ajustar el nodo anterior
                anterior->siguiente = siguiente;
                if (siguiente != NULL) {
                    siguiente->anterior = anterior;
                } else {
                    *fin = anterior; // Actual es el �ltimo nodo
                }
            }

            // Liberar memoria del nodo actual
            free(seg);
        }

        // Avanzar al siguiente nodo
        seg = siguiente;
    }

    return contador;
}



/// Funci�n para mostrar el arreglo de cartas
void mostrarArreglo(stCarta arreglo[MAX_CARTAS], int cantidad) {
    printf("Cartas en el arreglo:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Destino: %s, Tipo de carta: %d\n", arreglo[i].destino, arreglo[i].tipoCarta);
    }
}


/// Funci�n para mostrar todos los elementos de la fila
void MostrarFila(nodoCarta *inicio) {
    if (inicio == NULL) {
        printf("La fila est� vac�a.\n");

    }

    printf("Elementos de la fila:\n");
    nodoCarta *seg = inicio;
    while (seg != NULL) {
        printf("Destino: %s, Tipo de carta: %d\n", seg->dato.destino, seg->dato.tipoCarta);
        seg = seg->siguiente;
    }
}

// Funci�n para liberar todos los nodos de la fila al final del programa
void LiberarFila(nodoCarta **inicio) {
    nodoCarta *seg = *inicio;
    while (seg != NULL) {
        nodoCarta *temp = seg;
        seg = seg->siguiente;
        free(temp);
    }
    *inicio = NULL;
}
// Funci�n para vaciar una lista doblemente enlazada
void vaciarLista(nodoCarta **inicio, nodoCarta **fin) {
    nodoCarta *seg = *inicio;
    nodoCarta *siguiente = NULL;

    // Recorrer la lista y liberar memoria de cada nodo
    while (seg != NULL) {
        siguiente = seg->siguiente;
        free(seg); // Liberar nodo actual
        seg = siguiente; // Avanzar al siguiente nodo
    }

    // Establecer inicio y fin a NULL (lista vac�a)
    *inicio = NULL;
    *fin = NULL;
}
