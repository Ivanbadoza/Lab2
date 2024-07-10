#include "Lib.h"
#include <stdio.h>
#include <stdlib.h>

/// 1  Hacer una función que cree un nodo con una stConsola, inicialice sus datos y retorne un puntero al mismo
nodoConsola* crearNodoConsola (stConsola datos)
{
    nodoConsola* aux= (nodoConsola*)malloc(sizeof(nodoConsola));
    aux->dato=datos;
    aux->siguiente=NULL;

    return aux;
}

/// 2 Hacer una función que agregue un nuevo nodo ordenado por stock a la lista de consolas

nodoConsola* agregarNodoOrdenadoPorStock(nodoConsola* lista,nodoConsola* nuevoNodo)
{

    if(lista==NULL||lista->dato.stock>nuevoNodo->dato.stock ){
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    else {
        nodoConsola* seg = lista;

        while (seg->siguiente != NULL && seg->siguiente->dato.stock <= nuevoNodo->dato.stock) {
            seg = seg->siguiente;
        }
        nuevoNodo->siguiente = seg->siguiente;
        seg->siguiente = nuevoNodo;
    }
    return lista;
}

/// 3 Función recursiva para mostrar consolas por precio
void mostrarConsolasPorPrecio(nodoConsola* lista, int precioEnMiles) {
    if (lista != NULL) {
        if (lista->dato.precioEnMiles == precioEnMiles) {
            printf("Codigo: %d, Marca: %s, Precio: %d, Stock: %d, Modelo: %s\n",
                   lista->dato.codigoProducto,
                   lista->dato.marca,
                   lista->dato.precioEnMiles,
                   lista->dato.stock,
                   lista->dato.modelo);
        }
        mostrarConsolasPorPrecio(lista->siguiente, precioEnMiles);
    }
}

/// 4  Función para controlar el stock de una consola

int controlarStock(nodoConsola* lista, char* marca, char* modelo, int cantidadPedida) {

    int rta=-1;

    while (lista != NULL) {
        if (strcmp(lista->dato.marca, marca) == 0 && strcmp(lista->dato.modelo, modelo) == 0) {
            if (lista->dato.stock >= cantidadPedida) {
                rta=1; // Hay suficiente stock
            } else {
                rta=0; // No hay suficiente stock
            }
        }
        lista = lista->siguiente;
    }
    return rta; // No se encontró la consola
}
///Crear nodo cliente doble
nodoCliente* crearNodoCliente(stCliente datos) {
    nodoCliente* aux = (nodoCliente*)malloc(sizeof(nodoCliente));
    if (aux != NULL) {
        aux->dato = datos;
        aux->siguiente = NULL;
        aux->anterior = NULL;
    }
    return aux;
}
///Añadir al final de la lista doble enlazada
nodoCliente* agregarNodoClienteAlFinal(nodoCliente* lista, nodoCliente* nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        nodoCliente* seg = lista;
        while (seg->siguiente != NULL) {
            seg = seg->siguiente;
        }
        seg->siguiente = nuevoNodo;
        nuevoNodo->anterior = seg; // Establecer el nodo anterior al nuevo nodo
    }
    return lista;
}
///Eliminamos primero , por que tiene comportamiento de fila
nodoCliente* eliminarPrimerCliente(nodoCliente* listaClientes) {
    if (listaClientes != NULL) {
        nodoCliente* seg = listaClientes;
        listaClientes = listaClientes->siguiente;
        free(seg);
    }

    return listaClientes;
}


///Controlamos stock de varias compras
int controlarStockDeVarios(nodoConsola* listaConsolas, stConsola productos[], int cantidades[], int numProductos) {

    int rta=0;

    for (int i = 0; i < numProductos; i++) {
        nodoConsola* seg = listaConsolas;
        int encontrado = 0;
        while (seg != NULL) {
            if (strcmp(seg->dato.marca, productos[i].marca) == 0 && strcmp(seg->dato.modelo, productos[i].modelo) == 0) {
                if (seg->dato.stock >= cantidades[i]) {
                    encontrado = 1;
                    break;
                } else {
                    rta= 0; // No hay suficiente stock
                }
            }
            seg = seg->siguiente;
        }
        if (!encontrado) {
            rta= 0; // Producto no encontrado
        }
    }
    return rta; // Hay suficiente stock para todos los productos
}


void restarStockDeVarios(nodoConsola* listaConsolas, stConsola productos[], int cantidades[], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        nodoConsola* seg = listaConsolas;
        while (seg != NULL) {
            if (strcmp(seg->dato.marca, productos[i].marca) == 0 && strcmp(seg->dato.modelo, productos[i].modelo) == 0) {
                seg->dato.stock -= cantidades[i];
                break;
            }
            seg = seg->siguiente;
        }
    }
}


int manejarCompra(char nombre[], int medioDePago, stConsola productos[], int cantidades[], int numProductos, nodoCliente** listaClientes, nodoConsola** listaConsolas) {

    int compraExitosa=0;
    // Verificar si hay suficiente stock para los productos solicitados
    for (int i = 0; i < numProductos; ++i) {
        nodoConsola* temp = *listaConsolas;
        while (temp != NULL && (strcmp(temp->dato.marca, productos[i].marca) != 0 || strcmp(temp->dato.modelo, productos[i].modelo) != 0)) {
            temp = temp->siguiente;
        }
        if (temp == NULL || temp->dato.stock < cantidades[i]) {
            // No hay suficiente stock o el producto no existe en la lista
            compraExitosa= 0; // Indica compra fallida
        }
    }

    // Restar la cantidad comprada del stock y calcular el total de la compra
    int totalCompra = 0;
    for (int i = 0; i < numProductos; ++i) {
        nodoConsola* temp = *listaConsolas;
        while (temp != NULL && (strcmp(temp->dato.marca, productos[i].marca) != 0 || strcmp(temp->dato.modelo, productos[i].modelo) != 0)) {
            temp = temp->siguiente;
        }
        if (temp != NULL && temp->dato.stock >= cantidades[i]) {
            temp->dato.stock -= cantidades[i];
            totalCompra += productos[i].precioEnMiles * cantidades[i];
        }
    }

    // Crear cliente con los datos proporcionados y agregarlo a la lista de clientes
    stCliente nuevoCliente;
    strcpy(nuevoCliente.Nombre, nombre);
    nuevoCliente.mediodepago = medioDePago;
    nuevoCliente.totalCompra = totalCompra;

    nodoCliente* nodoNuevoCliente = crearNodoCliente(nuevoCliente);
    if (nodoNuevoCliente != NULL) {
        *listaClientes = agregarNodoClienteAlFinal(*listaClientes, nodoNuevoCliente);
        compraExitosa= 1; // Indica compra exitosa
    }

    return compraExitosa; // Indica error al crear el nodo de cliente
}
///Devuelve el total de compra de todos los clientes con un acumulador
int totalVendido(nodoCliente* listaClientes) {
    int total = 0;
    nodoCliente* temp = listaClientes;
    while (temp != NULL) {
        total += temp->dato.totalCompra;
        temp = temp->siguiente;
    }
    return total;
}
///Muestra clientes recursivo de atras hacia adelante
void mostrarClientesRecursivo(nodoCliente* lista) {
    if (lista != NULL) {
        mostrarClientesRecursivo(lista->siguiente);
        printf("Nombre: %s, Medio de pago: %d, Total compra: %d\n",
               lista->dato.Nombre,
               lista->dato.mediodepago,
               lista->dato.totalCompra);
    }
}
///Grabar archivo consolas
void guardarConsolasEnArchivo(nodoConsola* listaConsolas, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo) {
        nodoConsola* temp = listaConsolas;
        while (temp != NULL) {
            fwrite(&(temp->dato), sizeof(stConsola), 1, archivo);
            temp = temp->siguiente;
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para guardar consolas.\n");
    }
}
///Leer archivo consolas
nodoConsola* leerConsolasDesdeArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    nodoConsola* listaConsolas = NULL;
    if (archivo) {
        stConsola consola;
        while (fread(&consola, sizeof(stConsola), 1, archivo)) {
            nodoConsola* nuevoNodo = crearNodoConsola(consola);
            listaConsolas = agregarNodoOrdenadoPorStock(listaConsolas, nuevoNodo);
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para leer consolas.\n");
    }
    return listaConsolas;
}
///grabar archivo clientes
void guardarClientesEnArchivo(nodoCliente* listaClientes, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo) {
        nodoCliente* temp = listaClientes;
        while (temp != NULL) {
            fwrite(&(temp->dato), sizeof(stCliente), 1, archivo);
            temp = temp->siguiente;
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para guardar clientes.\n");
    }
}
///Leer archivo clientes
nodoCliente* leerClientesDesdeArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    nodoCliente* listaClientes = NULL;
    if (archivo) {
        stCliente cliente;
        while (fread(&cliente, sizeof(stCliente), 1, archivo)) {
            nodoCliente* nuevoNodo = crearNodoCliente(cliente);
            listaClientes = agregarNodoClienteAlFinal(listaClientes, nuevoNodo);
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para leer clientes.\n");
    }
    return listaClientes;
}
nodoCliente* atenderCliente(nodoCliente** listaClientes) {
    if (*listaClientes == NULL) {
        // Lista vacía
        return NULL;
    }

    nodoCliente* clienteAtendido = *listaClientes;
    *listaClientes = (*listaClientes)->siguiente;

    if (*listaClientes != NULL) {
        (*listaClientes)->anterior = NULL;
    }

    // Desvincular el nodo atendido
    clienteAtendido->siguiente = NULL;
    clienteAtendido->anterior = NULL;

    return clienteAtendido;
}
void mostrarCliente(stCliente cliente) {
    printf("Nombre: %s\n", cliente.Nombre);
    printf("Medio de pago: %d\n", cliente.mediodepago);
    printf("Total de compra: %.2f\n", cliente.totalCompra);
}

void mostrarClientesDesdeAtras(nodoCliente* listaClientes) {
    if (listaClientes == NULL) {
        return NULL;
    }

    // Ir al final de la lista
    nodoCliente* temp = listaClientes;
    while (temp->siguiente != NULL) {
        temp = temp->siguiente;
    }

    // Mostrar desde el último cliente hacia el primero
    while (temp != NULL) {
        mostrarCliente(temp->dato);
        temp = temp->anterior;
    }
}
///Atender clientes
void procesarAtencionClientes(nodoCliente** listaClientes) {
    while (*listaClientes != NULL) {
        nodoCliente* clienteAtendido = atenderCliente(listaClientes);
        if (clienteAtendido != NULL) {
            printf("Atendiendo al cliente:\n");
            mostrarCliente(clienteAtendido->dato);
            printf("\n");
            free(clienteAtendido);  // Liberar memoria del cliente atendido
        }
    }
}


void mostrarMenu() {
    printf("Seleccione una opción:\n");
    printf("1. Agregar consola\n");
    printf("2. Realizar compra\n");
    printf("3. Mostrando clientes desde atrás hacia adelante: \n");
    printf("4. Mostrar consolas por precio\n");
    printf("5. Guardar consolas en archivo\n");
    printf("6. Leer consolas desde archivo\n");
    printf("7. Guardar clientes en archivo\n");
    printf("8. Leer clientes desde archivo\n");
    printf("9. Total Monto Compras. \n ");
    printf("10. Atender Cliente \n ");
    printf("11. Salir\n");
}
