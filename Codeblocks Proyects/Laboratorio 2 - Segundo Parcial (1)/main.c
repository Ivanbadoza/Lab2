#include <stdio.h>
#include <stdlib.h>
#include "prot.h"

int main()
{
      ArregloArboles arreglo = {0};

    // Ejemplo de inserción de películas (simulado)
    pelicula pelicula1 = {1, "Peli1", 120, "Director1", "Accion", 2022};
    pelicula pelicula2 = {2, "Peli2", 110, "Director2", "Comedia", 2021};
    pelicula pelicula3 = {3, "Peli3", 100, "Director1", "Drama", 2023};

    printf("Inserción de películas:\n");
    if (insertarPeliculaADirector(&arreglo, pelicula1) == 1) {
        printf("Película 'Peli1' insertada correctamente.\n");
    }
    if (insertarPeliculaADirector(&arreglo, pelicula2) == 1) {
        printf("Película 'Peli2' insertada correctamente.\n");
    }
    if (insertarPeliculaADirector(&arreglo, pelicula3) == 1) {
        printf("Película 'Peli3' insertada correctamente.\n");
    }

    printf("\n");

    // Mostrar todos los elementos del arreglo de árboles
    printf("Listado de películas por director:\n");
    mostrarArregloArboles(&arreglo);

    printf("\n");

     // Ejemplo de búsqueda por director y año en todo el arreglo
    buscarPeliculaEnArreglo(&arreglo, "Director1", 2023);

    return 0;
}
