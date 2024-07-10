#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED

typedef struct {
    int idSocio;
    char nya[50];
    int UltimaCuotaPaga; // 1 a 12 meses
    float valorCuota;
    int edad;
    int idDeporte;
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




nodo* inicializarLista();
nodo2* inicializarListaSecundaria();
nodo* CrearNuevoNodo (stDeporte datos);
nodo* agregarDeporte(nodo* cabeza, stDeporte datos) ;
nodo2* CrearNuevoNodoDoble (stClub datos);
nodo2* agregarSocioOrdenado(nodo2* cabeza, stClub datos);
void imprimirSocios(nodo2* lista);
void imprimirDeportesYSocios(nodo* lista);
nodo* buscarDeporte(nodo* cabeza, const char* nombreDeporte);
stClub ingresarDatosSocio();
stDeporte ingresarDatosDeporte() ;
void altaManualSocio(nodo* listaDeportes) ;
void altaManualDeporte(nodo** listaDeportes);
void agregarNuevoSocio(nodo* lista, const char* nombreDeporte, stClub datos);
void listarDisciplinasYSocios(nodo* listaDeportes);
char* deporteConMasSocios(nodo* lista);
void listarSociosDeporteConMasSocios(nodo* lista);
void escribirDatosSocios(const char* nombreArchivo, nodo* lista);
void escribirDatosDeportes(const char* nombreArchivo, nodo* lista);
nodo* leerDatosSocios(const char* nombreArchivo, nodo* listaDeportes);
nodo* leerDatosDeportes(const char* nombreArchivo);
stClub* buscarSociosConDeuda(nodo* listaDeportes, const char* nombreDeporte, int mes, int* numSocios);

 nodo* buscarDeportePorId(nodo* listaDeportes,int idDeporte);



#endif // PROT_H_INCLUDED
