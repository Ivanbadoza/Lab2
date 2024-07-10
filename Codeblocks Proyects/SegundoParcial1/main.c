#include <stdio.h>
#include <stdlib.h>
#include "SegundoParcial.h"

int main()
{
  nodoArbol* arbol = NULL; // Árbol vacío inicialmente.

    // Insertar algunos nodos en el árbol para pruebas.
    arbol = insertarEnArbol(arbol, "Libro1", 200, "Genero1", 90, "Persona1");
    arbol = insertarEnArbol(arbol, "Libro2", 150, "Genero2", 85, "Persona2");
    arbol = insertarEnArbol(arbol, "Libro3", 300, "Genero1", 95, "Persona1");
    arbol = insertarEnArbol(arbol, "Libro4", 220, "Genero3", 70, "Persona3");

    int dimension = 100; // Tamaño máximo del arreglo.
    celda A[dimension];

    int cantCeldas = pasarDeArbolToArregloDeListas(arbol, A, dimension);
    printf("ESTO ES EL ARREGLO DE LISTAS : \n");
    mostrarArregloDeListas(A, cantCeldas);

    // Buscar un autor y un puntaje específico
    char NombrePersona[] = "Persona1";
    int Puntaje = 90;
    int existe = decimeSiExiste(A, cantCeldas, NombrePersona, Puntaje);

    if (existe == 1) {
        printf("El autor %s con puntaje %d existe.\n", NombrePersona, Puntaje);
    } else {
        printf("El autor %s con puntaje %d no existe.\n", NombrePersona, Puntaje);
    }


    return 0;
}
