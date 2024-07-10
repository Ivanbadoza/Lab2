#ifndef PROT_H_INCLUDED
#define PROT_H_INCLUDED

typedef struct {
char destino[50];
int tipoCarta; //1-simple, 2-encomienda, 3-caja
}stCarta ;

typedef struct {
stCarta dato;
struct nodoCarta * siguiente;
struct nodoCartas * anterior;
}nodoCarta;


nodoCarta* crearNodo(stCarta carta);
void agregarALaFila(nodoCarta **inicio, nodoCarta **fin, stCarta carta);
stCarta extraerDeLaFila(nodoCarta **inicio, nodoCarta **fin);
void mostrarFila(nodoCarta *inicio);
void vaciarLista(nodoCarta **inicio, nodoCarta **fin);
#endif // PROT_H_INCLUDED
