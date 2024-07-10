#include <stdio.h>
#include <stdlib.h>
#include "prot.h"


int main() {
    nodoPersona* listaPersonas = NULL;
    nodoContacto* listaContactos = NULL;
    stPersona nuevaPersona;
    stContacto nuevoContacto;
    int opcion;
    const char* archivoPersonas = "personas.dat";
    const char* archivoContactos = "contactos.dat";

    do {
        printf("\n--- Menu ---\n");
        printf("1. Agregar varias personas\n");
        printf("2. Mostrar personas\n");
        printf("3. Agregar contacto\n");
        printf("4. Mostrar contactos\n");
        printf("5. Contar contactos activos\n");
        printf("6. Guardar personas en archivo\n");
        printf("7. Cargar personas desde archivo\n");
        printf("8. Guardar contactos en archivo\n");
        printf("9. Cargar contactos desde archivo\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                listaPersonas=cargarVariasPersonas(listaPersonas);
             //   listaPersonas = agregarAlFinalPersona(listaPersonas, nuevaPersona);
                break;
            case 2:
                mostrarPersonas(listaPersonas);
                break;
            case 3:
                cargarContacto(listaPersonas, &nuevoContacto);
                listaContactos = agregarOrdenadoContacto(listaContactos, nuevoContacto);
                break;
            case 4:
                printf("Mostrando lista de contactos:\n");
                mostrarListaDobleRecursiva(listaContactos);
                break;
            case 5: {
                int activos = contarContactosActivos(listaContactos);
                printf("Cantidad de contactos activos: %d\n", activos);
                break;
            }
            case 6:
                guardarPersonasEnArchivo(listaPersonas, archivoPersonas);
                break;
            case 7:
                listaPersonas = cargarPersonasDesdeArchivo(archivoPersonas);
                break;
            case 8:
                guardarContactosEnArchivo(listaContactos, archivoContactos);
                break;
            case 9:
                listaContactos = cargarContactosDesdeArchivo(archivoContactos);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 0);

    // Liberar memoria
    nodoPersona* auxPersona;
    while (listaPersonas != NULL) {
        auxPersona = listaPersonas;
        listaPersonas = listaPersonas->siguiente;
        free(auxPersona);
    }

    nodoContacto* auxContacto;
    while (listaContactos != NULL) {
        auxContacto = listaContactos;
        listaContactos = listaContactos->siguiente;
        free(auxContacto);
    }

    return 0;
}
