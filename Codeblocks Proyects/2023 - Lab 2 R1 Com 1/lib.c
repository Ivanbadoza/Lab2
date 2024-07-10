#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARTAS 10  // Dimensión máxima del arreglo de cartas

/// Función para crear un nodo con una stCarta
nodoCarta *crearNodoCarta(stCarta carta) {
    nodoCarta *nuevoNodo = (nodoCarta *)malloc(sizeof(nodoCarta));
    nuevoNodo->dato = carta;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    return nuevoNodo;
}

/// Función para contar la cantidad de stCarta con un destino específico
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


/// Función para agregar un elemento al final de la fila
void AgregarALaFila(nodoCarta **inicio, nodoCarta **fin, stCarta carta) {
    // Crear un nuevo nodo para la carta
    nodoCarta *nuevoNodo = crearNodoCarta(carta);
    // Si la fila está vacía, el nuevo nodo es el inicio y el fin
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

/// Función para extraer la primera carta de la fila (lista doblemente enlazada)
stCarta extraerDeLaFila(nodoCarta **inicio, nodoCarta **fin) {
    stCarta cartaExtraida;
    nodoCarta *seg;

    // Inicializar cartaExtraida con un valor de error por defecto
    cartaExtraida.tipoCarta = -1;

    // Verificar si la fila está vacía
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
        printf("La fila está vacía. No se puede extraer ninguna carta.\n");
    }

    return cartaExtraida;
}

/// Función para pasar cartas de un tipo específico a un arreglo
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
                    *fin = NULL; // Lista vacía
                }
            } else {
                // Si actual no es el primer nodo, ajustar el nodo anterior
                anterior->siguiente = siguiente;
                if (siguiente != NULL) {
                    siguiente->anterior = anterior;
                } else {
                    *fin = anterior; // Actual es el último nodo
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



/// Función para mostrar el arreglo de cartas
void mostrarArreglo(stCarta arreglo[MAX_CARTAS], int cantidad) {
    printf("Cartas en el arreglo:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Destino: %s, Tipo de carta: %d\n", arreglo[i].destino, arreglo[i].tipoCarta);
    }
}


/// Función para mostrar todos los elementos de la fila
void MostrarFila(nodoCarta *inicio) {
    if (inicio == NULL) {
        printf("La fila está vacía.\n");

    }

    printf("Elementos de la fila:\n");
    nodoCarta *seg = inicio;
    while (seg != NULL) {
        printf("Destino: %s, Tipo de carta: %d\n", seg->dato.destino, seg->dato.tipoCarta);
        seg = seg->siguiente;
    }
}

// Función para liberar todos los nodos de la fila al final del programa
void LiberarFila(nodoCarta **inicio) {
    nodoCarta *seg = *inicio;
    while (seg != NULL) {
        nodoCarta *temp = seg;
        seg = seg->siguiente;
        free(temp);
    }
    *inicio = NULL;
}
// Función para vaciar una lista doblemente enlazada
void vaciarLista(nodoCarta **inicio, nodoCarta **fin) {
    nodoCarta *seg = *inicio;
    nodoCarta *siguiente = NULL;

    // Recorrer la lista y liberar memoria de cada nodo
    while (seg != NULL) {
        siguiente = seg->siguiente;
        free(seg); // Liberar nodo actual
        seg = siguiente; // Avanzar al siguiente nodo
    }

    // Establecer inicio y fin a NULL (lista vacía)
    *inicio = NULL;
    *fin = NULL;
}
