#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED


typedef struct {
    char nombre[50];
    char telefono[50];
    int DNI; // valores del 1 al 100
} stPersona;

typedef struct nodoPersona {
    stPersona dato;
    struct nodoPersona* siguiente;
} nodoPersona;

typedef struct {
    int DNI;
    int tipoContacto; // 1-familia 2-trabajo 3-amigos
    int activo; // 1-true 0-false
} stContacto;

typedef struct nodoContacto {
    stContacto dato;
    struct nodoContacto* siguiente;
    struct nodoContacto* anterior;
} nodoContacto;

nodoPersona* crearNodoPersona(stPersona persona);
nodoPersona* agregarAlFinalPersona(nodoPersona* lista, stPersona persona);
void mostrarPersonas(nodoPersona* lista);
int buscarDNIPersonaRecursivo(nodoPersona* lista, int DNI);
void cargarPersona(stPersona* persona);
nodoPersona* cargarVariasPersonas(nodoPersona* lista);
nodoContacto* crearNodoContacto(stContacto contacto);
nodoContacto* agregarOrdenadoContacto(nodoContacto* lista, stContacto contacto);
void cargarContacto(nodoPersona* listaPersonas, stContacto* contacto);
void mostrarListaDobleRecursiva(nodoContacto* lista);
int contarContactosActivos(nodoContacto* lista);
void guardarPersonasEnArchivo(nodoPersona* lista, const char* filename);
nodoPersona* cargarPersonasDesdeArchivo(const char* filename);
void guardarContactosEnArchivo(nodoContacto* lista, const char* filename);
nodoContacto* cargarContactosDesdeArchivo(const char* filename);

#endif // PROT_H_INCLUDED
