#include <stdio.h>
#include <stdlib.h>
#include "prot.h"
#include <string.h>
int main()
{
   nodo* listaDeportes = NULL; // Inicialización de la lista principal de deportes

    int opcion;
    do {
        printf("\nMenu de opciones:\n");
        printf("1. Listar todas las disciplinas deportivas y los socios que la practican\n");
        printf("2. Listar socios del deporte con mayor cantidad de socios\n");
        printf("3. Escribir datos de socios en archivo binario\n");
        printf("4. Escribir datos de deportes en archivo binario\n");
        printf("5. Buscar socios con deuda de cuotas\n");
        printf("6. Alta Manual de Socio\n");
        printf("7. Alta Manual de Deporte\n");
        printf("8. Leer archivo socios\n");
        printf("9. Leer archivo deportes\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                listarDisciplinasYSocios(listaDeportes);
                break;
            case 2:
                listarSociosDeporteConMasSocios(listaDeportes);
                break;
            case 3:
                escribirDatosSocios("socios.dat", listaDeportes);
                break;
            case 4:
                escribirDatosDeportes("deportes.dat", listaDeportes);
                break;
            case 5: {
                char nombreDeporte[50];
                int mes;
                printf("Ingrese el nombre del deporte: ");
                scanf(" %[^\n]", nombreDeporte);
                printf("Ingrese el mes para filtrar (1 a 12): ");
                scanf("%d", &mes);
                int numSocios;
                stClub* sociosDeudores = buscarSociosConDeuda(listaDeportes, nombreDeporte, mes, &numSocios);
                if (sociosDeudores != NULL) {
                    printf("Socios que adeudan cuotas para %s:\n", nombreDeporte);
                    for (int i = 0; i < numSocios; i++) {
                        printf("ID Socio: %d, Nombre: %s, Ultima Cuota Paga: %d\n",
                               sociosDeudores[i].idSocio, sociosDeudores[i].nya, sociosDeudores[i].UltimaCuotaPaga);
                    }
                    free(sociosDeudores);
                }
                break;
            }
            case 6:
                altaManualSocio(listaDeportes);
                break;
            case 7:
                altaManualDeporte(&listaDeportes);
                break;
                  case 8:
                listaDeportes=leerDatosSocios("socios.dat",listaDeportes);
                break;
                  case 9:
                listaDeportes=leerDatosDeportes("deportes.dat");
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);

    // Liberar memoria de la lista de deportes al salir del programa
    liberarListaPrincipal(listaDeportes);

    return 0;
}
