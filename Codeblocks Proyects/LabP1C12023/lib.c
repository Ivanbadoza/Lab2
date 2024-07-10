#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///Crear Nodo
nodoPersona* crearNodoPersona(stPersona persona) {
    nodoPersona* nuevo = (nodoPersona*) malloc(sizeof(nodoPersona));
    if (nuevo != NULL) {
        nuevo->dato = persona;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}
///Agregar nodo al final
nodoPersona* agregarAlFinalPersona(nodoPersona* lista, stPersona persona) {
    nodoPersona* nuevo = crearNodoPersona(persona);
    if (lista == NULL) {
        lista = nuevo;
    } else {
        nodoPersona* aux = lista;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
    return lista;
}
///Mostrar personas recursivo
void mostrarPersonas(nodoPersona* lista) {
    nodoPersona* aux = lista;
    if (aux != NULL) {
        printf("Nombre: %s\n", aux->dato.nombre);
        printf("Telefono: %s\n", aux->dato.telefono);
        printf("DNI: %d\n\n", aux->dato.DNI);
        mostrarPersonas(aux->siguiente);
    }
}

/// Función recursiva para buscar un DNI en la lista de personas con solo un return
int buscarDNIPersonaRecursivo(nodoPersona* lista, int DNI) {
    int encontrado = 0;
    if (lista != NULL) {
        if (lista->dato.DNI == DNI) {
            encontrado = 1;
        } else {
            encontrado = buscarDNIPersonaRecursivo(lista->siguiente, DNI);
        }
    }
    return encontrado;
}
///Cargar Persona Manual
void cargarPersona(stPersona* persona) {
    printf("Ingrese nombre: ");
    fflush(stdin);
    gets(persona->nombre);

    printf("Ingrese teléfono: ");
    fflush(stdin);
    gets(persona->telefono);

    do {
        printf("Ingrese DNI (1-100): ");
        scanf("%d", &persona->DNI);
        if (persona->DNI < 1 || persona->DNI > 100) {
            printf("DNI fuera de rango. Intente nuevamente.\n");
        }
    } while (persona->DNI < 1 || persona->DNI > 100);
}
///Cargar Varias Personas
nodoPersona* cargarVariasPersonas(nodoPersona* lista) {
    char opcion;
    stPersona nuevaPersona;

    do {
        cargarPersona(&nuevaPersona);
        if (buscarDNIPersonaRecursivo(lista, nuevaPersona.DNI)) {
            printf("La persona con DNI %d ya existe en la lista.\n", nuevaPersona.DNI);
        } else {
            lista = agregarAlFinalPersona(lista, nuevaPersona);
            printf("Persona agregada a la lista.\n");
        }

        printf("¿Desea agregar otra persona? (s/n): ");
        scanf(" %c", &opcion);
        getchar(); // Limpiar el buffer de entrada
    } while (opcion == 's' || opcion == 'S');

    return lista;
}
///Crear Nodo Doble
nodoContacto* crearNodoContacto(stContacto contacto) {
    nodoContacto* nuevo = (nodoContacto*) malloc(sizeof(nodoContacto));
    if (nuevo != NULL) {
        nuevo->dato = contacto;
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
    }
    return nuevo;
}
///Agrega por Orden de contacto
nodoContacto* agregarOrdenadoContacto(nodoContacto* lista, stContacto contacto) {
    nodoContacto* nuevo = crearNodoContacto(contacto);
    if (nuevo != NULL) {
        if (lista == NULL) {
            lista = nuevo;
        } else {
            nodoContacto* actual = lista;
            nodoContacto* anterior = NULL;

            while (actual != NULL && actual->dato.DNI < contacto.DNI) {
                anterior = actual;
                actual = actual->siguiente;
            }

            if (anterior == NULL) { // Insertar al principio
                nuevo->siguiente = lista;
                lista->anterior = nuevo;
                lista = nuevo;
            } else if (actual == NULL) { // Insertar al final
                anterior->siguiente = nuevo;
                nuevo->anterior = anterior;
            } else { // Insertar en medio
                nuevo->siguiente = actual;
                nuevo->anterior = anterior;
                anterior->siguiente = nuevo;
                actual->anterior = nuevo;
            }
        }
    }
    return lista;
}
///Cargar contacto manual y no lo ingresa si esta repetido el DNI
void cargarContacto(nodoPersona* listaPersonas, stContacto* contacto) {
    do {
        printf("Ingrese DNI: ");
        scanf("%d", &contacto->DNI);
        if (!buscarDNIPersonaRecursivo(listaPersonas, contacto->DNI)) {
            printf("El DNI ingresado no existe en la lista de personas. Intente nuevamente.\n");
        }
    } while (!buscarDNIPersonaRecursivo(listaPersonas, contacto->DNI));

    do {
        printf("Ingrese tipo de contacto (1-familia, 2-trabajo, 3-amigos): ");
        scanf("%d", &contacto->tipoContacto);
        if (contacto->tipoContacto < 1 || contacto->tipoContacto > 3) {
            printf("Tipo de contacto fuera de rango. Intente nuevamente.\n");
        }
    } while (contacto->tipoContacto < 1 || contacto->tipoContacto > 3);

    printf("Ingrese estado del contacto (1-activo, 0-inactivo): ");
    scanf("%d", &contacto->activo);
    getchar(); // Limpiar el buffer de entrada
}
///Muestro contactos recursivo (desde el final, atras para adelante)
void mostrarListaDobleRecursiva(nodoContacto* lista) {
    if (lista != NULL) {
        mostrarListaDobleRecursiva(lista->siguiente);
        printf("DNI: %d\n", lista->dato.DNI);
        printf("Tipo de Contacto: %d\n", lista->dato.tipoContacto);
        printf("Activo: %d\n\n", lista->dato.activo);
    }
}

int contarContactosActivos(nodoContacto* lista) {
    int contador = 0;
    while (lista != NULL) {
        if (lista->dato.activo == 1) {
            contador++;
        }
        lista = lista->siguiente;
    }
    return contador;
}

// Funciones para guardar y cargar datos desde un archivo
void guardarPersonasEnArchivo(nodoPersona* lista, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        while (lista != NULL) {
            fwrite(&lista->dato, sizeof(stPersona), 1, file);
            lista = lista->siguiente;
        }
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo para escritura.\n");
    }
}

nodoPersona* cargarPersonasDesdeArchivo(const char* filename) {
    FILE* file = fopen(filename, "rb");
    nodoPersona* lista = NULL;
    nodoPersona* aux = NULL;
    stPersona persona;

    if (file != NULL) {
        while (fread(&persona, sizeof(stPersona), 1, file) > 0) {
            nodoPersona* nuevo = crearNodoPersona(persona);
            if (lista == NULL) {
                lista = nuevo;
            } else {
                aux->siguiente = nuevo;
            }
            aux = nuevo;
        }
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo para lectura.\n");
    }

    return lista;
}

void guardarContactosEnArchivo(nodoContacto* lista, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        while (lista != NULL) {
            fwrite(&lista->dato, sizeof(stContacto), 1, file);
            lista = lista->siguiente;
        }
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo para escritura.\n");
    }
}

nodoContacto* cargarContactosDesdeArchivo(const char* filename) {
    FILE* file = fopen(filename, "rb");
    nodoContacto* lista = NULL;
    nodoContacto* aux = NULL;
    stContacto contacto;

    if (file != NULL) {
        while (fread(&contacto, sizeof(stContacto), 1, file) > 0) {
            nodoContacto* nuevo = crearNodoContacto(contacto);
            if (lista == NULL) {
                lista = nuevo;
            } else {
                aux->siguiente = nuevo;
                nuevo->anterior = aux;
            }
            aux = nuevo;
        }
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo para lectura.\n");
    }

    return lista;
}

