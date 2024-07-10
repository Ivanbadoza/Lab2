#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED

typedef struct {
    int idSocio;
    char nya[50];
    int UltimaCuotaPaga; // 1 a 12 meses
    float valorCuota;
    int edad;
} stClub;

typedef struct {
    int idDeporte;
    char NombreDeporte[50];
} stDeporte;

// Nodo para la lista secundaria (socios)
typedef struct nodo2 {
    stClub datos;
    struct nodo2* sig;
    struct nodo2* ante;
} nodo2;

// Nodo para la lista principal (deportes)
typedef struct nodo {
    stDeporte datos;
    struct nodo* sig;
    nodo2* listaDeLista; // Lista de socios
} nodo;

 nodo* buscarDeportePorId(nodo* listaDeportes,int idDeporte);



#endif // PROT_H_INCLUDED
