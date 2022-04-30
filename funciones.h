#include "hashmap.h"

typedef struct Producto Producto;

char* get_csv_field (char * tmp, int k);
void importarProductos(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos);
void agregarProducto(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos,char* nombre,char* marca,char* tipo,char* stock,char* precio);
void agregarMapaMarcas(HashMap* mapaMarcas,Producto* auxProducto);
void agregarMapaTipos(HashMap* mapaTipos,Producto* auxProducto);
void buscarProductoTipo(HashMap* mapaTipos);
void buscarProductoMarca(HashMap* mapaMarcas);
void buscarProductos(HashMap* mapaProductos);