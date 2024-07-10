#include <stdio.h>
#include <stdlib.h>
#include "prot.h"
#include <string.h>

nodo* inicializarLista()
{
    return NULL;
}
// Función para inicializar la lista secundaria
nodo2* inicializarListaSecundaria()
{
    return NULL;
}
///Creo nuevo nodo
nodo* CrearNuevoNodo (stDeporte datos)
{
    nodo* nuevoNodo=(nodo*)malloc(sizeof(nodo));
    nuevoNodo->datos=datos;
    nuevoNodo->sig=NULL;
    nuevoNodo->listaDeLista=inicializarListaSecundaria;

    return nuevoNodo;
}
// Función para agregar al final de la lista principal y retornar la lista principal actualizada
nodo* agregarDeporte(nodo* cabeza, stDeporte datos)
{
    nodo* nuevoNodo = CrearNuevoNodo(datos);
    if (cabeza == NULL)
    {
        cabeza= nuevoNodo;
    }
    else
    {
        nodo* actual = cabeza;
        while (actual->sig != NULL)
        {
            actual = actual->sig;
        }
        actual->sig = nuevoNodo;
    }
    return cabeza;
}
nodo2* CrearNuevoNodoDoble (stClub datos)
{
    nodo2* nuevoNodoD=(nodo2*)malloc(sizeof(nodo2));
    nuevoNodoD->datos=datos;
    nuevoNodoD->sig=NULL;
    nuevoNodoD->ante=NULL;

    return nuevoNodoD;
}
/// Función para agregar un socio ordenado por nombre a la lista secundaria a una Lista Doble
nodo2* agregarSocioOrdenado(nodo2* cabeza, stClub datos)
{
    nodo2* nuevoNodo = CrearNuevoNodoDoble(datos);

    if (cabeza == NULL)
    {
        cabeza= nuevoNodo;
    }
    else
    {
        nodo2* actual = cabeza;
        nodo2* previo = NULL;
        while (actual != NULL && strcmp(actual->datos.nya, datos.nya) < 0)
        {
            previo = actual;
            actual = actual->sig;
        }
        nuevoNodo->sig = actual;
        nuevoNodo->ante = previo;
        if (previo == NULL)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            previo->sig = nuevoNodo;
        }
        if (actual != NULL)
        {
            actual->ante = nuevoNodo;
        }
    }
    return cabeza;
}
/// Función para imprimir la lista secundaria de socios
void imprimirSocios(nodo2* lista)
{
    nodo2* actual = lista;
    while (actual != NULL)
    {
        printf("ID Socio: %d, Nombre: %s, Edad: %d, Ultima Cuota Paga: %d, Valor Cuota: %.2f\n",
               actual->datos.idSocio, actual->datos.nya, actual->datos.edad,
               actual->datos.UltimaCuotaPaga, actual->datos.valorCuota);
        actual = actual->sig;
    }
}

/// Función para imprimir la lista principal de deportes y sus socios
void imprimirDeportesYSocios(nodo* lista)
{
    nodo* actual = lista;
    while (actual != NULL)
    {
        printf("Deporte: %s\n", actual->datos.NombreDeporte);
        imprimirSocios(actual->listaDeLista);
        actual = actual->sig;
    }
}

/// Función para buscar un deporte en la lista principal
nodo* buscarDeporte(nodo* cabeza, const char* nombreDeporte)
{
    nodo* actual = cabeza;
    while (actual != NULL && strcmp(actual->datos.NombreDeporte, nombreDeporte) != 0)
    {
        actual = actual->sig;
    }
    return actual;
}




/// Función para ingresar los datos de un nuevo socio manualmente
stClub ingresarDatosSocio()
{
    stClub nuevoSocio;
    printf("Ingrese ID de socio: ");
    scanf("%d", &nuevoSocio.idSocio);
    printf("Ingrese Nombre y Apellido: ");
    scanf(" %[^\n]", nuevoSocio.nya); // Leer cadena con espacios
    printf("Ingrese Ultima Cuota Paga (1 a 12 meses): ");
    scanf("%d", &nuevoSocio.UltimaCuotaPaga);
    printf("Ingrese Valor de la Cuota: ");
    scanf("%f", &nuevoSocio.valorCuota);
    printf("Ingrese Edad: ");
    scanf("%d", &nuevoSocio.edad);

    return nuevoSocio;
}

///Ingresar deporte epor teclado
stDeporte ingresarDatosDeporte()
{
    stDeporte nuevoDeporte;
    printf("Ingrese ID del deporte: ");
    scanf("%d", &nuevoDeporte.idDeporte);
    printf("Ingrese Nombre del Deporte: ");
    scanf(" %[^\n]", nuevoDeporte.NombreDeporte); // Leer cadena con espacios
    return nuevoDeporte;
}

// Función para agregar un nuevo socio a un deporte específico
void altaManualSocio(nodo* listaDeportes)
{
    int idDeporte;
    printf("Ingrese ID del deporte donde desea agregar el socio: ");
    scanf("%d", &idDeporte);

    nodo* deporte = buscarDeportePorId(listaDeportes, idDeporte);
    if (deporte != NULL)
    {
        stClub nuevoSocio = ingresarDatosSocio();
        // Agregar el socio a la lista de socios del deporte encontrado
        deporte->listaDeLista = agregarSocioOrdenado(deporte->listaDeLista, nuevoSocio);

        printf("Socio agregado correctamente al deporte ID %d.\n", idDeporte);
    }
    else
    {
        printf("Deporte no encontrado para ID: %d\n", idDeporte);
    }
}

// Función para agregar una nueva disciplina deportiva
void altaManualDeporte(nodo** listaDeportes)
{
    stDeporte nuevoDeporte = ingresarDatosDeporte();

    // Crear un nuevo nodo para el deporte
    nodo* nuevoNodo =CrearNuevoNodo(nuevoDeporte);

    // Agregar el nuevo nodo al final de la lista principal de deportes
    if (*listaDeportes == NULL)
    {
        *listaDeportes = nuevoNodo;
    }
    else
    {
        nodo* actual = *listaDeportes;
        while (actual->sig != NULL)
        {
            actual = actual->sig;
        }
        actual->sig = nuevoNodo;
    }

    printf("Deporte agregado correctamente.\n");
}
/// Función para agregar un nuevo socio a ambas listas
void agregarNuevoSocio(nodo* lista, const char* nombreDeporte, stClub datos)
{
    nodo* deporte = buscarDeporte(lista, nombreDeporte);
    if (deporte != NULL)
    {
        deporte->listaDeLista = agregarSocioOrdenado(deporte->listaDeLista, datos);
    }
    else
    {
        printf("Deporte no encontrado.\n");
    }
}
/// Función para buscar un deporte por ID en la lista principal
nodo* buscarDeportePorId(nodo* cabeza, int idDeporte)
{
    nodo* actual = cabeza;
    while (actual != NULL && actual->datos.idDeporte != idDeporte)
    {
        actual = actual->sig;
    }
    return actual;
}


/// Función para listar todas las disciplinas deportivas y los socios que las practican
void listarDisciplinasYSocios(nodo* listaDeportes)
{
    nodo* actual = listaDeportes;
    while (actual != NULL)
    {
        printf("Deporte: %s\n", actual->datos.NombreDeporte);
        imprimirSocios(actual->listaDeLista);
        actual = actual->sig;
    }
}

/// Función para encontrar el deporte con más socios, recorro la lista y cuento con un acumulador cada socio y comparo
char* deporteConMasSocios(nodo* lista)
{
    nodo* actual = lista;
    int maxCount = 0;
    char* deporteMax = NULL;
    while (actual != NULL)
    {
        int count = 0;
        nodo2* socio = actual->listaDeLista;
        while (socio != NULL)
        {
            count++;
            socio = socio->sig;
        }
        if (count > maxCount)
        {
            maxCount = count;
            deporteMax = actual->datos.NombreDeporte;
        }
        actual = actual->sig;
    }
    return deporteMax;
}
// Función para listar socios del deporte con más socios
void listarSociosDeporteConMasSocios(nodo* lista)
{
    char* deporteMax = deporteConMasSocios(lista);
    if (deporteMax != NULL)
    {
        printf("Deporte con más socios: %s\n", deporteMax);
        nodo* actual = lista;
        while (actual != NULL)
        {
            if (strcmp(actual->datos.NombreDeporte, deporteMax) == 0)
            {
                imprimirSocios(actual->listaDeLista);
            }
            actual = actual->sig;
        }
    }
    else
    {
        printf("No hay deportes registrados.\n");
    }
}

// Función para escribir los datos de los socios a un archivo binario
void escribirDatosSocios(const char* nombreArchivo, nodo* lista)
{
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo != NULL)
    {
        nodo* actual = lista;
        while (actual != NULL)
        {
            nodo2* actualSocio = actual->listaDeLista;
            while (actualSocio != NULL)
            {
                fwrite(&(actualSocio->datos), sizeof(stClub), 1, archivo);
                actualSocio = actualSocio->sig;
            }
            actual = actual->sig;
        }
        fclose(archivo);
    }
    else
    {
        perror("No se pudo abrir el archivo para escribir");
    }
}

// Función para escribir los datos de los deportes a un archivo binario
void escribirDatosDeportes(const char* nombreArchivo, nodo* lista)
{
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL)
    {
        perror("No se pudo abrir el archivo para escribir");
        return;
    }
    nodo* actual = lista;
    while (actual != NULL)
    {
        fwrite(&(actual->datos), sizeof(stDeporte), 1, archivo);
        actual = actual->sig;
    }
    fclose(archivo);
}


// Función para leer los datos de los socios desde un archivo binario
nodo* leerDatosSocios(const char* nombreArchivo, nodo* listaDeportes)
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    nodo* listaActualizada = listaDeportes;

    if (archivo != NULL)
    {
        stClub datos;
        while (fread(&datos, sizeof(stClub), 1, archivo))
        {
            nodo* deporte = buscarDeportePorId(listaDeportes, datos.idDeporte);
            if (deporte != NULL)
            {
                deporte->listaDeLista = agregarSocioOrdenado(deporte->listaDeLista, datos);
            }
            else
            {
                printf("Deporte no encontrado para ID: %d\n", datos.idDeporte);
            }
        }

        fclose(archivo);
    }
    else
    {
        perror("No se pudo abrir el archivo para leer");
    }

    return listaActualizada;
}





// Función para leer los datos de los deportes desde un archivo binario
nodo* leerDatosDeportes(const char* nombreArchivo)
{
    nodo* listaDeportes = NULL;
    FILE* archivo = fopen(nombreArchivo, "rb");

    if (archivo != NULL)
    {
        listaDeportes = inicializarLista();
        stDeporte datos;

        while (fread(&datos, sizeof(stDeporte), 1, archivo))
        {
            listaDeportes = agregarDeporte(listaDeportes, datos);
        }

        fclose(archivo);
    }
    else
    {
        perror("No se pudo abrir el archivo para leer");
    }

    return listaDeportes;
}



// Función para buscar socios que adeuden cuotas
stClub* buscarSociosConDeuda(nodo* listaDeportes, const char* nombreDeporte, int mes, int* numSocios)
{
    *numSocios = 0;
    stClub* arregloSocios = NULL;
    nodo* actualDeporte = listaDeportes;

    // Buscar el deporte en la lista principal
    while (actualDeporte != NULL && strcmp(actualDeporte->datos.NombreDeporte, nombreDeporte) != 0)
    {
        actualDeporte = actualDeporte->sig;
    }

    if (actualDeporte == NULL)
    {
        // No se encontró el deporte
        printf("Deporte no encontrado.\n");
    }
    else
    {
        // Contar los socios que adeudan cuotas
        nodo2* actualSocio = actualDeporte->listaDeLista;
        while (actualSocio != NULL)
        {
            if (actualSocio->datos.UltimaCuotaPaga < mes)
            {
                (*numSocios)++;
            }
            actualSocio = actualSocio->sig;
        }

        if (*numSocios == 0)
        {
            // No hay socios que adeudan cuotas
            printf("No hay socios que adeuden cuotas para el deporte %s.\n", nombreDeporte);
        }
        else
        {
            // Crear el arreglo de socios que adeudan cuotas
            arregloSocios = (stClub*)malloc((*numSocios) * sizeof(stClub));

                // Copiar los socios que adeudan cuotas al arreglo
                int indice = 0;
                actualSocio = actualDeporte->listaDeLista;
                while (actualSocio != NULL)
                {
                    if (actualSocio->datos.UltimaCuotaPaga < mes)
                    {
                        arregloSocios[indice] = actualSocio->datos;
                        indice++;
                    }
                    actualSocio = actualSocio->sig;
                }

        }
    }

    return arregloSocios;
}

// Función para liberar la memoria ocupada por la lista principal
void liberarListaPrincipal(nodo* cabeza)
{
    nodo* actual = cabeza;
    while (actual != NULL)
    {
        nodo* siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }
}

// Función para liberar la memoria ocupada por la lista secundaria
void liberarListaSecundaria(nodo2* cabeza)
{
    nodo2* actual = cabeza;
    while (actual != NULL)
    {
        nodo2* siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }
}
