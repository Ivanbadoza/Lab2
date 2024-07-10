#include <stdio.h>
#include <stdlib.h>
#include "prot.h"

int main()
{
      ArregloArboles arreglo = {0};

    // Ejemplo de inserci�n de pel�culas (simulado)
    pelicula pelicula1 = {1, "Peli1", 120, "Director1", "Accion", 2022};
    pelicula pelicula2 = {2, "Peli2", 110, "Director2", "Comedia", 2021};
    pelicula pelicula3 = {3, "Peli3", 100, "Director1", "Drama", 2023};

    printf("Inserci�n de pel�culas:\n");
    if (insertarPeliculaADirector(&arreglo, pelicula1) == 1) {
        printf("Pel�cula 'Peli1' insertada correctamente.\n");
    }
    if (insertarPeliculaADirector(&arreglo, pelicula2) == 1) {
        printf("Pel�cula 'Peli2' insertada correctamente.\n");
    }
    if (insertarPeliculaADirector(&arreglo, pelicula3) == 1) {
        printf("Pel�cula 'Peli3' insertada correctamente.\n");
    }

    printf("\n");

    // Mostrar todos los elementos del arreglo de �rboles
    printf("Listado de pel�culas por director:\n");
    mostrarArregloArboles(&arreglo);

    printf("\n");

     // Ejemplo de b�squeda por director y a�o en todo el arreglo
    buscarPeliculaEnArreglo(&arreglo, "Director1", 2023);

    return 0;
}
