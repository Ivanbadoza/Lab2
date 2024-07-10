#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED


typedef struct {
float precio;
char sector[50];
}stEntrada;

typedef struct {
stEntrada unaEntrada;
struct nodoArbolEntrada* izq;
struct nodoArbolEntrada* der;
}nodoArbolEntrada;

typedef struct {
char categoria[20];
struct nodoListaBoleteria*sig;
nodoArbolEntrada * entradas;
}nodoListaBoleteria;

typedef struct {
stEntrada entradaAsignada;
struct nodoFila *sig;
}nodoFila;

typedef struct
{
nodoFila * ultimo;
nodoFila * primero;
}fila;




#endif // PROT_H_INCLUDED
