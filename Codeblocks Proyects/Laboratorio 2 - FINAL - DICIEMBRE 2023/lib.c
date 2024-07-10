#include <stdio.h>
#include <stdlib.h>
#include "prot.h"
#include<string.h>
// Función para crear e inicializar un nuevo nodo de la lista
nodoListaBoleteria* inicializarNodoLista(const char* categoria) {
    nodoListaBoleteria* nuevoNodo = (nodoListaBoleteria*)malloc(sizeof(nodoListaBoleteria));
    if (nuevoNodo) {
        strcpy(nuevoNodo->categoria, categoria);
        nuevoNodo->sig = NULL;
        nuevoNodo->entradas = NULL; // Inicialmente no tiene entradas asignadas
    }
    return nuevoNodo;
}

// Función para agregar un nodo al final de la lista
void agregarNodoLista(nodoListaBoleteria** lista, const char* categoria) {
    nodoListaBoleteria* nuevoNodo = inicializarNodoLista(categoria);
    if (*lista == NULL) {
        *lista = nuevoNodo;
    } else {
        nodoListaBoleteria* actual = *lista;
        while (actual->sig != NULL) {
            actual = actual->sig;
        }
        actual->sig = nuevoNodo;
    }
}

// Función para mostrar el contenido de la lista
void mostrarLista(nodoListaBoleteria* lista) {
    nodoListaBoleteria* actual = lista;
    while (actual != NULL) {
        printf("Categoría: %s\n", actual->categoria);
        actual = actual->sig;
    }
}

// Función para verificar la existencia de una categoría
int existeCategoria(nodoListaBoleteria* lista, const char* categoriaBuscada) {
    nodoListaBoleteria* actual = lista;
    while (actual != NULL) {
        if (strcmp(actual->categoria, categoriaBuscada) == 0) {
            return 1; // Se encontró la categoría
        }
        actual = actual->sig;
    }
    return 0; // No se encontró la categoría
}
// Función para cargar una stEntrada
void cargarEntrada(stEntrada* entrada, float precio, const char* sector) {
    entrada->precio = precio;
    strcpy(entrada->sector, sector);
}

// Función para crear un nuevo nodo del árbol
nodoArbolEntrada* nuevoNodoArbol(stEntrada unaEntrada) {
    nodoArbolEntrada* nuevoNodo = (nodoArbolEntrada*)malloc(sizeof(nodoArbolEntrada));
    if (nuevoNodo != NULL) {
        nuevoNodo->unaEntrada = unaEntrada;
        nuevoNodo->izq = NULL;
        nuevoNodo->der = NULL;
    }
    return nuevoNodo;
}

// Función para insertar un nodo en el árbol
nodoArbolEntrada* insertarNodo(nodoArbolEntrada* raiz, stEntrada unaEntrada) {
    // Si el árbol está vacío, se crea un nuevo nodo
    if (raiz == NULL) {
        return nuevoNodoArbol(unaEntrada);
    }

    // Insertar en el subárbol izquierdo si el precio es menor
    if (unaEntrada.precio < raiz->unaEntrada.precio) {
        raiz->izq = insertarNodo(raiz->izq, unaEntrada);
    }
    // Insertar en el subárbol derecho si el precio es mayor o igual
    else {
        raiz->der = insertarNodo(raiz->der, unaEntrada);
    }

    // Devolver el puntero a la raíz actualizada
    return raiz;
}

// Función para imprimir el árbol en orden
void imprimirArbolOrdenado(nodoArbolEntrada* raiz) {
    if (raiz != NULL) {
        imprimirArbolOrdenado(raiz->izq);
        printf("Precio: %.2f, Sector: %s\n", raiz->unaEntrada.precio, raiz->unaEntrada.sector);
        imprimirArbolOrdenado(raiz->der);
    }
}

// Función para crear un nuevo nodo de la lista de boleterías
nodoListaBoleteria* nuevoNodoLista(char categoria[], nodoArbolEntrada* arbol) {
    nodoListaBoleteria* nuevoNodo = (nodoListaBoleteria*)malloc(sizeof(nodoListaBoleteria));
    if (nuevoNodo != NULL) {
        strcpy(nuevoNodo->categoria, categoria);
        nuevoNodo->entradas = arbol;
        nuevoNodo->sig = NULL;
    }
    return nuevoNodo;
}

// Función para insertar un nodo en la lista de boleterías
nodoListaBoleteria* insertarNodoLista(nodoListaBoleteria* lista, char categoria[], nodoArbolEntrada* arbol) {
    nodoListaBoleteria* nuevoNodo = nuevoNodoLista(categoria, arbol);
    if (nuevoNodo != NULL) {
        // Si la lista está vacía, el nuevo nodo es el primer nodo
        if (lista == NULL) {
            return nuevoNodo;
        }

        // Buscar el final de la lista
        nodoListaBoleteria* actual = lista;
        while (actual->sig != NULL) {
            actual = actual->sig;
        }

        // Enlazar el nuevo nodo al final de la lista
        actual->sig = nuevoNodo;
    }
    return lista;
}

// Función para visualizar la lista de boleterías
void visualizarListaBoleterias(nodoListaBoleteria* lista) {
    printf("Visualización de la lista de boleterías:\n");
    int numBoleteria = 1;
    nodoListaBoleteria* actual = lista;
    while (actual != NULL) {
        printf("Categoría: %s\n", actual->categoria);
        printf("Árbol de entradas:\n");
        imprimirArbolOrdenado(actual->entradas);
        printf("\n");
        actual = actual->sig;
        numBoleteria++;
    }
}

// Función para insertar una entrada en la fila
void insertarEnFila(fila* unaFila, stEntrada entrada) {
    nodoFila* nuevoNodo = (nodoFila*)malloc(sizeof(nodoFila));
    if (nuevoNodo != NULL) {
        nuevoNodo->entradaAsignada = entrada;
        nuevoNodo->sig = NULL;

        // Si la fila está vacía, el nuevo nodo es tanto el primero como el último
        if (unaFila->primero == NULL) {
            unaFila->primero = nuevoNodo;
            unaFila->ultimo = nuevoNodo;
        } else {
            // Enlazar el nuevo nodo al final de la fila
            unaFila->ultimo->sig = nuevoNodo;
            unaFila->ultimo = nuevoNodo;
        }
    }
}

// Función para pasar todos los árboles de la lista de boleterías a la fila
void pasarListaAfila(nodoListaBoleteria* lista, fila* unaFila) {
    nodoListaBoleteria* actual = lista;
    while (actual != NULL) {
        nodoArbolEntrada* arbolActual = actual->entradas;
        pasarArbolAfila(arbolActual, unaFila);
        actual = actual->sig;
    }
}

// Función auxiliar para pasar un árbol a la fila
void pasarArbolAfila(nodoArbolEntrada* raiz, fila* unaFila) {
    if (raiz != NULL) {
        pasarArbolAfila(raiz->izq, unaFila);
        insertarEnFila(unaFila, raiz->unaEntrada);
        pasarArbolAfila(raiz->der, unaFila);
    }
}

// Función para imprimir la fila
void imprimirFila(fila unaFila) {
    printf("Contenido de la fila:\n");
    nodoFila* actual = unaFila.primero;
    while (actual != NULL) {
        printf("Precio: %.2f, Sector: %s\n", actual->entradaAsignada.precio, actual->entradaAsignada.sector);
        actual = actual->sig;
    }
}

// Función para cargar una entrada
// Función para cargar una entrada utilizando scanf
stEntrada cargarEntrada2() {
    stEntrada nuevaEntrada;

    // Solicitar y leer el precio
    printf("Ingrese el precio de la entrada: ");
    scanf("%f", &nuevaEntrada.precio);

    // Limpiar el buffer de entrada
    while (getchar() != '\n');

    // Solicitar y leer el sector
    printf("Ingrese el sector de la entrada: ");
    fgets(nuevaEntrada.sector, sizeof(nuevaEntrada.sector), stdin);
    nuevaEntrada.sector[strcspn(nuevaEntrada.sector, "\n")] = '\0';  // Eliminar el salto de línea al final

    return nuevaEntrada;
}
