#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORES 100


// Función para inicializar el arreglo de árboles
void inicializarArregloArboles(ArregloArboles* arreglo) {
    arreglo->cantidad = 0;
    for (int i = 0; i < MAX_DIRECTORES; i++) {
        arreglo->directores[i].arbolPeliculas = NULL;
        strcpy(arreglo->directores[i].direccion, "");
    }
}

// Función para crear un nodo de árbol de película
nodoArbolPeli* crearNodoArbolPeli(pelicula peli) {
    nodoArbolPeli* nuevoNodo = (nodoArbolPeli*)malloc(sizeof(nodoArbolPeli));
    nuevoNodo->dato = peli;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

// Función para insertar una película en el árbol
nodoArbolPeli* insertarPelicula(nodoArbolPeli* raiz, pelicula peli) {
    if (raiz == NULL) {
        return crearNodoArbolPeli(peli);
    }

    if (peli.id < raiz->dato.id) {
        raiz->izq = insertarPelicula(raiz->izq, peli);
    } else if (peli.id > raiz->dato.id) {
        raiz->der = insertarPelicula(raiz->der, peli);
    }
    // Si la película ya existe (mismo id), no se inserta
    return raiz;
}
// Función para agregar un nuevo director
int agregarDirector(ArregloArboles* arreglo, const char* nombreDirector) {
    int resultado = 1; // Valor por defecto para éxito
    int directorEncontrado = 0;

    for (int i = 0; i < arreglo->cantidad; i++) {
        if (strcmp(arreglo->directores[i].direccion, nombreDirector) == 0) {
            directorEncontrado = 1; // El director ya existe
            resultado = 0;
        }
    }

    if (!directorEncontrado) { // Solo intenta agregar si no se encontró el director
        if (arreglo->cantidad >= MAX_DIRECTORES) {
            resultado = -1; // No hay espacio para más directores
        } else {
            strcpy(arreglo->directores[arreglo->cantidad].direccion, nombreDirector);
            arreglo->directores[arreglo->cantidad].arbolPeliculas = NULL;
            arreglo->cantidad++;
        }
    }

    return resultado;
}

int agregarPeliculaADirector(ArregloArboles* arreglo, const char* nombreDirector, pelicula peli) {
    int resultado = 0; // Valor por defecto para director no encontrado

    for (int i = 0; i < arreglo->cantidad; i++) {
        if (strcmp(arreglo->directores[i].direccion, nombreDirector) == 0) {
            arreglo->directores[i].arbolPeliculas = insertarPelicula(arreglo->directores[i].arbolPeliculas, peli);
            resultado = 1; // Película agregada exitosamente
        }
    }

    return resultado;
}
// Función para buscar la posición de un director de forma recursiva
int buscarDirectorRecursivo(ArbolDirector directores[], const char* nombreDirector, int inicio, int fin) {
    int resultado = -1; // Valor por defecto para director no encontrado

    if (inicio <= fin) {
        if (strcmp(directores[inicio].direccion, nombreDirector) == 0) {
            resultado = inicio; // Director encontrado en la posición 'inicio'
        } else {
            resultado = buscarDirectorRecursivo(directores, nombreDirector, inicio + 1, fin);
        }
    }

    return resultado;
}
// Función para buscar la posición de un director
int buscarDirector(ArregloArboles* arreglo, const char* nombreDirector) {
    return buscarDirectorRecursivo(arreglo->directores, nombreDirector, 0, arreglo->cantidad - 1);
}

// Función para insertar una película y asegurarse de que el director existe
int insertarPeliculaADirector(ArregloArboles* arreglo, pelicula peli) {
    int resultado = 1; // Valor por defecto para éxito
    int posicion = -1;
    int directorExistente = 0;

    // Buscar la posición del director o agregarlo si no existe
    int i = 0;
    while (i < arreglo->cantidad && !directorExistente) {
        if (strcmp(arreglo->directores[i].direccion, peli.direccion) == 0) {
            posicion = i;
            directorExistente = 1;
        }
        i++;
    }

    // Si el director no existe, agregarlo
    if (!directorExistente) {
        if (arreglo->cantidad >= MAX_DIRECTORES) {
            resultado = -1; // No hay espacio para más directores
        } else {
            strcpy(arreglo->directores[arreglo->cantidad].direccion, peli.direccion);
            arreglo->directores[arreglo->cantidad].arbolPeliculas = NULL;
            posicion = arreglo->cantidad; // La posición del nuevo director agregado
            arreglo->cantidad++;
        }
    }

    // Insertar la película en el árbol del director si todo fue exitoso
    if (resultado == 1) {
        arreglo->directores[posicion].arbolPeliculas = insertarPelicula(arreglo->directores[posicion].arbolPeliculas, peli);
    }

    return resultado;
}

// Función para cargar películas desde un archivo binario al arreglo de árboles
int cargarDesdeArchivoBinario(ArregloArboles *arreglo, const char *nombreArchivo) {
    FILE *archivo;
    pelicula peli;
    int resultado = 1; // Valor por defecto para éxito

    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return -1;
    }

    while (fread(&peli, sizeof(pelicula), 1, archivo) == 1) {
        // Insertar la película en el arreglo de árboles
        resultado = insertarPeliculaADirector(arreglo, peli);
        if (resultado != 1) {
            printf("Error al insertar la película %s para el director %s\n", peli.nombre, peli.direccion);
            break;
        }
    }

    fclose(archivo);
    return resultado;
}

// Función para mostrar todos los elementos del arreglo de árboles
void mostrarArregloArboles(ArregloArboles *arreglo) {
    for (int i = 0; i < arreglo->cantidad; i++) {
        printf("Director: %s\n", arreglo->directores[i].direccion);

        // Recorrer el árbol de películas del director
        mostrarArbolPeliculas(arreglo->directores[i].arbolPeliculas);

        printf("\n");
    }
}

// Función auxiliar para mostrar un árbol de películas
void mostrarArbolPeliculas(nodoArbolPeli *raiz) {
    if (raiz != NULL) {
        // Mostrar la película
        printf("- Película: %s\n", raiz->dato.nombre);

        // Recorrer el subárbol izquierdo y derecho
        mostrarArbolPeliculas(raiz->izq);
        mostrarArbolPeliculas(raiz->der);
    }
}

// Función para buscar una película por dirección y nombre
void buscarPelicula(ArregloArboles *arreglo, const char *direccion, const char *nombrePelicula) {
    for (int i = 0; i < arreglo->cantidad; i++) {
        // Buscar en el director con la dirección especificada
        if (strcmp(arreglo->directores[i].direccion, direccion) == 0) {
            // Llamar a función auxiliar para buscar en el árbol de películas
            buscarEnArbolPeliculas(arreglo->directores[i].arbolPeliculas, nombrePelicula);
             // Terminar la búsqueda después de encontrar el director
        }
    }

    printf("Director con dirección '%s' no encontrado.\n", direccion);
}

// Función auxiliar para buscar en el árbol de películas
void buscarEnArbolPeliculas(nodoArbolPeli *raiz, const char *nombrePelicula) {
    if (raiz != NULL) {
        // Comparar el nombre de la película en el nodo actual
        if (strcmp(raiz->dato.nombre, nombrePelicula) == 0) {
            printf("Película encontrada:\n");
            printf("Nombre: %s\n", raiz->dato.nombre);
            printf("Director: %s\n", raiz->dato.direccion);
            printf("Género: %s\n", raiz->dato.genero);
            printf("Año: %d\n", raiz->dato.anio);
             // Terminar la búsqueda cuando se encuentra la película
        }

        // Recorrer recursivamente el subárbol izquierdo y derecho
        buscarEnArbolPeliculas(raiz->izq, nombrePelicula);
        buscarEnArbolPeliculas(raiz->der, nombrePelicula);
    }
}


void buscarPorDirectorYAnio(nodoArbolPeli *raiz, const char *direccion, int anio) {
    if (raiz != NULL) {
        // Si el director y el año coinciden, imprimir la película encontrada
        if (strcmp(raiz->dato.direccion, direccion) == 0 && raiz->dato.anio == anio) {
            printf("Película encontrada:\n");
            printf("Nombre: %s\n", raiz->dato.nombre);
            printf("Director: %s\n", raiz->dato.direccion);
            printf("Género: %s\n", raiz->dato.genero);
            printf("Año: %d\n", raiz->dato.anio);
        }

        // Recorrer recursivamente el subárbol izquierdo y derecho
        buscarPorDirectorYAnio(raiz->izq, direccion, anio);
        buscarPorDirectorYAnio(raiz->der, direccion, anio);
    }
}

// Función para buscar una película por director y año en todo el arreglo de directores
void buscarPeliculaEnArreglo(ArregloArboles *arreglo, const char *direccion, int anio) {
    // Recorrer todo el arreglo de directores
    for (int i = 0; i < arreglo->cantidad; i++) {
      //  printf("Buscando películas para el director '%s' y año %d:\n", arreglo->directores[i].direccion, anio);
        buscarPorDirectorYAnio(arreglo->directores[i].arbolPeliculas, direccion, anio);
    }
}

// Función para mostrar todas las películas del arreglo de árboles
void mostrarTodasLasPeliculas(ArregloArboles *arreglo) {
    printf("Listado de todas las películas:\n");

    for (int i = 0; i < arreglo->cantidad; i++) {
        printf("Director: %s\n", arreglo->directores[i].direccion);
        printf("Películas:\n");
        mostrarPeliculasDeArbol(arreglo->directores[i].arbolPeliculas);
        printf("\n");
    }
}

// Función auxiliar para mostrar todas las películas de un árbol
void mostrarPeliculasDeArbol(nodoArbolPeli *raiz) {
    if (raiz != NULL) {
        mostrarPeliculasDeArbol(raiz->izq);
        printf("- %s\n", raiz->dato.nombre);
        mostrarPeliculasDeArbol(raiz->der);
    }
}

