#include "hashmap.h"
#include "list.h"

typedef struct Producto Producto;
typedef struct  Carrito Carrito;

char* get_csv_field (char * tmp, int k);
void importarProductos(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos);
void agregarProducto(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos,char* nombre,char* marca,char* tipo,char* stock,char* precio);
void agregarMapaMarcas(HashMap* mapaMarcas,Producto* auxProducto);
void agregarMapaTipos(HashMap* mapaTipos,Producto* auxProducto);
void buscarProductoTipo(HashMap* mapaTipos);
void buscarProductoMarca(HashMap* mapaMarcas);
void buscarProductos(HashMap* mapaProductos);
void mostrarProductos(HashMap* mapaProductos);
void crearCarrito(char* auxCarrito,List* listaCarritos);
void agregarCarrito(List* listaCarritos, HashMap* mapaProductos);
void mostrarCarritos(List* listaCarritos);
void exportarProductos(HashMap* mapaProductos);