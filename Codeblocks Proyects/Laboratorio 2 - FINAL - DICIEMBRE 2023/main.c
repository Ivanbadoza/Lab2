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
    printf("Lista de categor�as:\n");
    mostrarLista(lista);

    // Buscar una categor�a espec�fica
    const char* categoriaBuscada = "Deporte";
    if (existeCategoria(lista, categoriaBuscada)) {
        printf("La categor�a %s existe en la lista.\n", categoriaBuscada);
    } else {
        printf("La categor�a %s no existe en la lista.\n", categoriaBuscada);
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

    // Crear varios �rboles de ejemplo de entradas
    nodoArbolEntrada* arbol1 = NULL;
    arbol1 = insertarNodo(arbol1, (stEntrada){150.50, "VIP"});
    arbol1 = insertarNodo(arbol1, (stEntrada){100.00, "General"});

    nodoArbolEntrada* arbol2 = NULL;
    arbol2 = insertarNodo(arbol2, (stEntrada){200.00, "VIP Plus"});
    arbol2 = insertarNodo(arbol2, (stEntrada){120.00, "Regular"});

    // Crear una lista de boleter�as
    nodoListaBoleteria* listaBoleterias = NULL;
    listaBoleterias = insertarNodoLista(listaBoleterias, "Concierto", arbol1);
    listaBoleterias = insertarNodoLista(listaBoleterias, "Teatro", arbol2);

    // Visualizar la lista de boleter�as
    visualizarListaBoleterias(listaBoleterias);

        // Crear una fila vac�a
    fila unaFila = {NULL, NULL};

    // Pasar todos los �rboles de la lista de boleter�as a la fila
    pasarListaAfila(listaBoleterias, &unaFila);

    // Imprimir la fila resultante
    imprimirFila(unaFila);

    return 0;
}
