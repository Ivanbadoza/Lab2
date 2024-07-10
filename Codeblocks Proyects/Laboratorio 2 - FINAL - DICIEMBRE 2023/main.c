#include <stdio.h>
#include <stdlib.h>
#include "prot.h"
#include<string.h>
int main()
{
  nodoListaBoleteria* lista = NULL;

    // Agregar nodos a la lista
    agregarNodoLista(&lista, "Concierto");
    agregarNodoLista(&lista, "Deporte");
    agregarNodoLista(&lista, "Teatro");

    // Mostrar la lista
    printf("Lista de categorías:\n");
    mostrarLista(lista);

    // Buscar una categoría específica
    const char* categoriaBuscada = "Deporte";
    if (existeCategoria(lista, categoriaBuscada)) {
        printf("La categoría %s existe en la lista.\n", categoriaBuscada);
    } else {
        printf("La categoría %s no existe en la lista.\n", categoriaBuscada);
    }

   stEntrada nuevaEntrada;

    // Cargar una entrada y mostrar sus datos
    cargarEntrada(&nuevaEntrada, 150.50, "VIP");
    printf("Nueva entrada cargada:\n");
    printf("Precio: %.2f\n", nuevaEntrada.precio);
    printf("Sector: %s\n", nuevaEntrada.sector);

    // Cargar una entrada directamente
    stEntrada entradaDirecta = cargarEntrada2();

    // Imprimir la entrada cargada
    printf("Precio: %.2f, Sector: %s\n", entradaDirecta.precio, entradaDirecta.sector);

    // Crear varios árboles de ejemplo de entradas
    nodoArbolEntrada* arbol1 = NULL;
    arbol1 = insertarNodo(arbol1, (stEntrada){150.50, "VIP"});
    arbol1 = insertarNodo(arbol1, (stEntrada){100.00, "General"});

    nodoArbolEntrada* arbol2 = NULL;
    arbol2 = insertarNodo(arbol2, (stEntrada){200.00, "VIP Plus"});
    arbol2 = insertarNodo(arbol2, (stEntrada){120.00, "Regular"});

    // Crear una lista de boleterías
    nodoListaBoleteria* listaBoleterias = NULL;
    listaBoleterias = insertarNodoLista(listaBoleterias, "Concierto", arbol1);
    listaBoleterias = insertarNodoLista(listaBoleterias, "Teatro", arbol2);

    // Visualizar la lista de boleterías
    visualizarListaBoleterias(listaBoleterias);

        // Crear una fila vacía
    fila unaFila = {NULL, NULL};

    // Pasar todos los árboles de la lista de boleterías a la fila
    pasarListaAfila(listaBoleterias, &unaFila);

    // Imprimir la fila resultante
    imprimirFila(unaFila);

    return 0;
}
