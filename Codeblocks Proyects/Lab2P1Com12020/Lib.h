#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED



typedef struct {
int codigoProducto;
char marca[50]; // Nintendo Switch, Xbox,Playstation
int precioEnMiles;
int stock;
char modelo[50];// Común, Pro, Slim
}stConsola ;

typedef struct nodoConsola{
stConsola dato ;
struct nodoConsola * siguiente;
}nodoConsola;

typedef struct {
char Nombre[50];
int mediodepago; //1 efectivo, 2 patacones, 3 dolarahorro
int totalCompra;
}stCliente ;

typedef struct nodoCliente{
stCliente dato;
struct nodoCliente* siguiente;
struct nodoCliente* anterior;
}nodoCliente;


nodoConsola* crearNodoConsola (stConsola datos);
nodoConsola* agregarNodoOrdenadoPorStock(nodoConsola* lista,nodoConsola* nuevoNodo);
void mostrarConsolasPorPrecio(nodoConsola* lista, int precioEnMiles);
int controlarStock(nodoConsola* lista, char* marca, char* modelo, int cantidadPedida);
nodoCliente* crearNodoCliente(stCliente datos);
nodoCliente* agregarNodoClienteAlFinal(nodoCliente* lista, nodoCliente* nuevoNodo);
nodoCliente* eliminarPrimerCliente(nodoCliente* listaClientes);
int controlarStockDeVarios(nodoConsola* listaConsolas, stConsola productos[], int cantidades[], int numProductos);
void restarStockDeVarios(nodoConsola* listaConsolas, stConsola productos[], int cantidades[], int numProductos);
int manejarCompra(char nombre[], int medioDePago, stConsola productos[], int cantidades[], int numProductos, nodoCliente** listaClientes, nodoConsola** listaConsolas) ;
int totalVendido(nodoCliente* listaClientes);
void mostrarClientesRecursivo(nodoCliente* lista);
void guardarConsolasEnArchivo(nodoConsola* listaConsolas, const char* nombreArchivo) ;



#endif // LIB_H_INCLUDED
