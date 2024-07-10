#include <stdio.h>
#include <stdlib.h>
#include "Lib.h"
int main() {
    nodoConsola* listaConsolas = NULL;
    nodoCliente* listaClientes = NULL;
    int opcion;
    int totalVendidos=0;
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        getchar(); // Para consumir el salto de l�nea despu�s de la opci�n
        switch (opcion) {
            case 1: {
                stConsola consola;
                printf("Ingrese c�digo del producto: ");
                scanf("%d", &consola.codigoProducto);
                getchar(); // Para consumir el salto de l�nea
                printf("Ingrese marca: ");
                fgets(consola.marca, 50, stdin);
                consola.marca[strcspn(consola.marca, "\n")] = '\0'; // Remover el salto de l�nea
                printf("Ingrese precio en miles: ");
                scanf("%d", &consola.precioEnMiles);
                printf("Ingrese stock: ");
                scanf("%d", &consola.stock);
                getchar(); // Para consumir el salto de l�nea
                printf("Ingrese modelo: ");
                fgets(consola.modelo, 50, stdin);
                consola.modelo[strcspn(consola.modelo, "\n")] = '\0'; // Remover el salto de l�nea
                nodoConsola* nuevoNodo = crearNodoConsola(consola);
                if (nuevoNodo != NULL) {
                    listaConsolas = agregarNodoOrdenadoPorStock(listaConsolas, nuevoNodo);
                    printf("Consola agregada con �xito.\n");
                } else {
                    printf("Error al agregar la consola.\n");
                }
                break;
            }
            case 2: {
                char nombre[50];
                int medioDePago, numProductos;
                printf("Ingrese nombre del cliente: ");
                fgets(nombre, 50, stdin);
                nombre[strcspn(nombre, "\n")] = '\0'; // Remover el salto de l�nea
                printf("Ingrese medio de pago (1-efectivo, 2-patacones, 3-d�lar ahorro): ");
                scanf("%d", &medioDePago);
                printf("Ingrese n�mero de productos a comprar: ");
                scanf("%d", &numProductos);

                stConsola productos[numProductos];
                int cantidades[numProductos];

                for (int i = 0; i < numProductos; ++i) {
                    printf("Ingrese marca del producto %d: ", i + 1);
                    getchar(); // Para consumir el salto de l�nea
                    fgets(productos[i].marca, 50, stdin);
                    productos[i].marca[strcspn(productos[i].marca, "\n")] = '\0'; // Remover el salto de l�nea
                    printf("Ingrese modelo del producto %d: ", i + 1);
                    fgets(productos[i].modelo, 50, stdin);
                    productos[i].modelo[strcspn(productos[i].modelo, "\n")] = '\0'; // Remover el salto de l�nea
                    printf("Ingrese cantidad del producto %d: ", i + 1);
                    scanf("%d", &cantidades[i]);
                }

                int resultado = manejarCompra(nombre, medioDePago, productos, cantidades, numProductos, &listaClientes, &listaConsolas);
                if (resultado) {
                    printf("Compra realizada con �xito.\n");
                } else {
                    printf("Compra fallida. Verifique el stock y los datos ingresados.\n");
                }
                break;
            }
            case 3:
                printf("Lista de clientes:\n");
                mostrarClientesRecursivo(listaClientes);
                break;
            case 4: {
                int precio;
                printf("Ingrese el precio en miles de las consolas a mostrar: ");
                scanf("%d", &precio);
                printf("Consolas con precio %d :\n", precio);
                mostrarConsolasPorPrecio(listaConsolas, precio);
                break;
            }
            case 5:
                guardarConsolasEnArchivo(listaConsolas, "consolas.dat");
                printf("Consolas guardadas en archivo.\n");
                break;
            case 6:
                listaConsolas = leerConsolasDesdeArchivo("consolas.dat");
                printf("Consolas le�das desde archivo.\n");
                break;
            case 7:
                guardarClientesEnArchivo(listaClientes, "clientes.dat");
                printf("Clientes guardados en archivo.\n");
                break;
            case 8:
                listaClientes = leerClientesDesdeArchivo("clientes.dat");
                printf("Clientes le�dos desde archivo.\n");
                break;
            case 9:

                totalVendidos=totalVendido(listaClientes);
                printf("El total vendido es : %d ", totalVendidos);
                break;
            case 10:
                printf("\nProcesando atenci�n de clientes:\n");
                procesarAtencionClientes(&listaClientes);
                break;
            case 11:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opci�n no v�lida. Intente de nuevo.\n");
        }
    } while (opcion != 9);

    return 0;
}
