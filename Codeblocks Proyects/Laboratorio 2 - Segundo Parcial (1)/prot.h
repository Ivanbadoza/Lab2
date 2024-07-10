#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED


typedef struct
{
    int id;
    char nombre[20];
    int duracion;
    char direccion[30];
    char genero[20];
    int anio;
} pelicula;

typedef struct nodoArbolPeli
{
    pelicula dato;
    struct nodoArbolPeli * izq;
    struct nodoArbolPeli * der;
} nodoArbolPeli;



typedef struct {
    char direccion[30];
    nodoArbolPeli* arbolPeliculas;
} ArbolDirector;

typedef struct {
    ArbolDirector directores[10];
    int cantidad;
} ArregloArboles;

#endif // PROT_H_INCLUDED
