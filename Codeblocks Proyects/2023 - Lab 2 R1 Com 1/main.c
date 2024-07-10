#include <stdio.h>
#include <stdlib.h>
#include "prot.h"
#define MAX_CARTAS 10  // Dimensión máxima del arreglo de cartas

int main()
{
    nodoCarta *inicio = NULL;
    nodoCarta *fin = NULL;
    stCarta arreglo[MAX_CARTAS];
    stCarta carta;
    int i, cantidad;

    // Automatizar la carga de información
    stCarta cartas[] =
    {
        {"Destino1", 1},
        {"Destino2", 2},
        {"Destino3", 1},
        {"Destino4", 3},
        {"Destino5", 2},
        {"Destino6", 1},
        {"Destino7", 1},
        {"Destino8", 2},
        {"Destino9", 3},
        {"Destino10", 1}
    };

    // Agregar las cartas a la fila
    for (i = 0; i < 10; i++)
    {
        AgregarALaFila(&inicio, &fin, cartas[i]);
    }

    ///Cartas por destino


    int cantdestino=contarCartasPorDestino(inicio,"Destino1");
    printf("Contar cartas por destino : %d \n ",cantdestino);
    // Mostrar fila antes de extraer
    printf("Fila antes de extraer:\n");
    nodoCarta *temp = inicio;
    while (temp != NULL)
    {
        printf("Destino: %s, Tipo: %d\n", temp->dato.destino, temp->dato.tipoCarta);
        temp = temp->siguiente;
    }

    // Extraer una carta de la fila
    stCarta cartaExtraida ;
    cartaExtraida= extraerDeLaFila(&inicio, &fin);
    if (cartaExtraida.tipoCarta != -1)
    {
        printf("\nSe extrajo la carta: Destino: %s, Tipo: %d\n", cartaExtraida.destino, cartaExtraida.tipoCarta);
    }


    // Mostrar fila después de extraer
    printf("\nFila después de extraer:\n");
    temp = inicio;
    while (temp != NULL)
    {
        printf("Destino: %s, Tipo: %d\n", temp->dato.destino, temp->dato.tipoCarta);
        temp = temp->siguiente;
    }

    // Pasar cartas de tipo 1 a un arreglo
    cantidad = pasarCartasAArreglo(&inicio, &fin, 1, arreglo);
    printf("\nSe pasaron %d cartas de tipo 1 al arreglo:\n", cantidad);
    for (i = 0; i < cantidad; i++)
    {
        printf("Destino: %s, Tipo: %d\n", arreglo[i].destino, arreglo[i].tipoCarta);
    }

    // Mostrar fila después de pasar cartas al arreglo
    printf("\nFila después de pasar cartas al arreglo:\n");
    temp = inicio;
    while (temp != NULL)
    {
        printf("Destino: %s, Tipo: %d\n", temp->dato.destino, temp->dato.tipoCarta);
        temp = temp->siguiente;
    }

    // Vaciar la lista
    vaciarLista(&inicio, &fin);
    printf("\nLista vaciada. Inicio y fin ahora son NULL.\n");

    return 0;
}
