#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORES 100


// Funci�n para inicializar el arreglo de �rboles
void inicializarArregloArboles(ArregloArboles* arreglo) {
    arreglo->cantidad = 0;
    for (int i = 0; i < MAX_DIRECTORES; i++) {
        arreglo->directores[i].arbolPeliculas = NULL;
        strcpy(arreglo->directores[i].direccion, "");
    }
}

// Funci�n para crear un nodo de �rbol de pel�cula
nodoArbolPeli* crearNodoArbolPeli(pelicula peli) {
    nodoArbolPeli* nuevoNodo = (nodoArbolPeli*)malloc(sizeof(nodoArbolPeli));
    nuevoNodo->dato = peli;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

// Funci�n para insertar una pel�cula en el �rbol
nodoArbolPeli* insertarPelicula(nodoArbolPeli* raiz, pelicula peli) {
    if (raiz == NULL) {
        return crearNodoArbolPeli(peli);
    }

    if (peli.id < raiz->dato.id) {
        raiz->izq = insertarPelicula(raiz->izq, peli);
    } else if (peli.id > raiz->dato.id) {
        raiz->der = insertarPelicula(raiz->der, peli);
    }
    // Si la pel�cula ya existe (mismo id), no se inserta
    return raiz;
}
// Funci�n para agregar un nuevo director
int agregarDirector(ArregloArboles* arreglo, const char* nombreDirector) {
    int resultado = 1; // Valor por defecto para �xito
    int directorEncontrado = 0;

    for (int i = 0; i < arreglo->cantidad; i++) {
        if (strcmp(arreglo->directores[i].direccion, nombreDirector) == 0) {
            directorEncontrado = 1; // El director ya existe
            resultado = 0;
        }
    }

    if (!directorEncontrado) { // Solo intenta agregar si no se encontr� el director
        if (arreglo->cantidad >= MAX_DIRECTORES) {
            resultado = -1; // No hay espacio para m�s directores
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
            resultado = 1; // Pel�cula agregada exitosamente
        }
    }

    return resultado;
}
// Funci�n para buscar la posici�n de un director de forma recursiva
int buscarDirectorRecursivo(ArbolDirector directores[], const char* nombreDirector, int inicio, int fin) {
    int resultado = -1; // Valor por defecto para director no encontrado

    if (inicio <= fin) {
        if (strcmp(directores[inicio].direccion, nombreDirector) == 0) {
            resultado = inicio; // Director encontrado en la posici�n 'inicio'
        } else {
            resultado = buscarDirectorRecursivo(directores, nombreDirector, inicio + 1, fin);
        }
    }

    return resultado;
}
// Funci�n para buscar la posici�n de un director
int buscarDirector(ArregloArboles* arreglo, const char* nombreDirector) {
    return buscarDirectorRecursivo(arreglo->directores, nombreDirector, 0, arreglo->cantidad - 1);
}

// Funci�n para insertar una pel�cula y asegurarse de que el director existe
int insertarPeliculaADirector(ArregloArboles* arreglo, pelicula peli) {
    int resultado = 1; // Valor por defecto para �xito
    int posicion = -1;
    int directorExistente = 0;

    // Buscar la posici�n del director o agregarlo si no existe
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
            resultado = -1; // No hay espacio para m�s directores
        } else {
            strcpy(arreglo->directores[arreglo->cantidad].direccion, peli.direccion);
            arreglo->directores[arreglo->cantidad].arbolPeliculas = NULL;
            posicion = arreglo->cantidad; // La posici�n del nuevo director agregado
            arreglo->cantidad++;
        }
    }

    // Insertar la pel�cula en el �rbol del director si todo fue exitoso
    if (resultado == 1) {
        arreglo->directores[posicion].arbolPeliculas = insertarPelicula(arreglo->directores[posicion].arbolPeliculas, peli);
    }

    return resultado;
}

// Funci�n para cargar pel�culas desde un archivo binario al arreglo de �rboles
int cargarDesdeArchivoBinario(ArregloArboles *arreglo, const char *nombreArchivo) {
    FILE *archivo;
    pelicula peli;
    int resultado = 1; // Valor por defecto para �xito

    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return -1;
    }

    while (fread(&peli, sizeof(pelicula), 1, archivo) == 1) {
        // Insertar la pel�cula en el arreglo de �rboles
        resultado = insertarPeliculaADirector(arreglo, peli);
        if (resultado != 1) {
            printf("Error al insertar la pel�cula %s para el director %s\n", peli.nombre, peli.direccion);
            break;
        }
    }

    fclose(archivo);
    return resultado;
}

// Funci�n para mostrar todos los elementos del arreglo de �rboles
void mostrarArregloArboles(ArregloArboles *arreglo) {
    for (int i = 0; i < arreglo->cantidad; i++) {
        printf("Director: %s\n", arreglo->directores[i].direccion);

        // Recorrer el �rbol de pel�culas del director
        mostrarArbolPeliculas(arreglo->directores[i].arbolPeliculas);

        printf("\n");
    }
}

// Funci�n auxiliar para mostrar un �rbol de pel�culas
void mostrarArbolPeliculas(nodoArbolPeli *raiz) {
    if (raiz != NULL) {
        // Mostrar la pel�cula
        printf("- Pel�cula: %s\n", raiz->dato.nombre);

        // Recorrer el sub�rbol izquierdo y derecho
        mostrarArbolPeliculas(raiz->izq);
        mostrarArbolPeliculas(raiz->der);
    }
}

// Funci�n para buscar una pel�cula por direcci�n y nombre
void buscarPelicula(ArregloArboles *arreglo, const char *direccion, const char *nombrePelicula) {
    for (int i = 0; i < arreglo->cantidad; i++) {
        // Buscar en el director con la direcci�n especificada
        if (strcmp(arreglo->directores[i].direccion, direccion) == 0) {
            // Llamar a funci�n auxiliar para buscar en el �rbol de pel�culas
            buscarEnArbolPeliculas(arreglo->directores[i].arbolPeliculas, nombrePelicula);
             // Terminar la b�squeda despu�s de encontrar el director
        }
    }

    printf("Director con direcci�n '%s' no encontrado.\n", direccion);
}

// Funci�n auxiliar para buscar en el �rbol de pel�culas
void buscarEnArbolPeliculas(nodoArbolPeli *raiz, const char *nombrePelicula) {
    if (raiz != NULL) {
        // Comparar el nombre de la pel�cula en el nodo actual
        if (strcmp(raiz->dato.nombre, nombrePelicula) == 0) {
            printf("Pel�cula encontrada:\n");
            printf("Nombre: %s\n", raiz->dato.nombre);
            printf("Director: %s\n", raiz->dato.direccion);
            printf("G�nero: %s\n", raiz->dato.genero);
            printf("A�o: %d\n", raiz->dato.anio);
             // Terminar la b�squeda cuando se encuentra la pel�cula
        }

        // Recorrer recursivamente el sub�rbol izquierdo y derecho
        buscarEnArbolPeliculas(raiz->izq, nombrePelicula);
        buscarEnArbolPeliculas(raiz->der, nombrePelicula);
    }
}


void buscarPorDirectorYAnio(nodoArbolPeli *raiz, const char *direccion, int anio) {
    if (raiz != NULL) {
        // Si el director y el a�o coinciden, imprimir la pel�cula encontrada
        if (strcmp(raiz->dato.direccion, direccion) == 0 && raiz->dato.anio == anio) {
            printf("Pel�cula encontrada:\n");
            printf("Nombre: %s\n", raiz->dato.nombre);
            printf("Director: %s\n", raiz->dato.direccion);
            printf("G�nero: %s\n", raiz->dato.genero);
            printf("A�o: %d\n", raiz->dato.anio);
        }

        // Recorrer recursivamente el sub�rbol izquierdo y derecho
        buscarPorDirectorYAnio(raiz->izq, direccion, anio);
        buscarPorDirectorYAnio(raiz->der, direccion, anio);
    }
}

// Funci�n para buscar una pel�cula por director y a�o en todo el arreglo de directores
void buscarPeliculaEnArreglo(ArregloArboles *arreglo, const char *direccion, int anio) {
    // Recorrer todo el arreglo de directores
    for (int i = 0; i < arreglo->cantidad; i++) {
      //  printf("Buscando pel�culas para el director '%s' y a�o %d:\n", arreglo->directores[i].direccion, anio);
        buscarPorDirectorYAnio(arreglo->directores[i].arbolPeliculas, direccion, anio);
    }
}

// Funci�n para mostrar todas las pel�culas del arreglo de �rboles
void mostrarTodasLasPeliculas(ArregloArboles *arreglo) {
    printf("Listado de todas las pel�culas:\n");

    for (int i = 0; i < arreglo->cantidad; i++) {
        printf("Director: %s\n", arreglo->directores[i].direccion);
        printf("Pel�culas:\n");
        mostrarPeliculasDeArbol(arreglo->directores[i].arbolPeliculas);
        printf("\n");
    }
}

// Funci�n auxiliar para mostrar todas las pel�culas de un �rbol
void mostrarPeliculasDeArbol(nodoArbolPeli *raiz) {
    if (raiz != NULL) {
        mostrarPeliculasDeArbol(raiz->izq);
        printf("- %s\n", raiz->dato.nombre);
        mostrarPeliculasDeArbol(raiz->der);
    }
}

