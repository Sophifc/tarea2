#include <stdio.h>
#include "menu.h"
#include "hashmap.h"
#include "funciones.h"
#include "list.h"


void initMenu(){

    HashMap *mapaMarcas=createMap(100);
    HashMap *mapaTipos=createMap(100);
    HashMap *mapaProductos=createMap(100); 
    //HashMap *mapaCarritos=createMap(100);
    List* listaCarritos=createList();

   int eleccion;

   while(eleccion !=0){

       //Despliega las opciones que puede escoger el usuario
       printf("Opciones del Menu\n");
       printf("0-. Salir del menu\n");
       printf("1-. Importar Productos\n");
       printf("2-. Exportar Productos\n");
       printf("3-. Agregar Producto\n");
       printf("4-. Buscar Producto Por Tipo\n");
       printf("5-. Buscar Producto Por Marca\n");
       printf("6-. Buscar Producto Por Nombre\n");
       printf("7-. Mostrar Todos Los Productos\n");
       printf("8-. Agregar Al Carrito\n");
       printf("9-. Eliminar Del Carrito\n");
       printf("10-. Concretar Compra\n");
       printf("11-. Mostrar Carritos De Compra\n");

       //Lee la opcion del usuario
       scanf("%d", &eleccion);
   

       switch (eleccion){

           case 1:
        
           //Función que importa los Porductos del archivo CSV
           importarProductos(mapaMarcas,mapaProductos,mapaTipos);
        
           break;

           case 2:
        
           //Función que exporta los productos en un archivo csv
        
           break;

           case 3:
       
           //Función que agrega el producto
           menuAgregarPorducto(mapaMarcas,mapaProductos,mapaTipos);
        
           break;

           case 4:
        
           //Función que busca el producto por tipo
           buscarProductoTipo(mapaTipos);    

           break;

           case 5:
        
           //Función que busca el producto por marca
           buscarProductoMarca(mapaMarcas);
        
           break;

           case 6:
        
           //Función que busca el producto por nombre
           buscarProductos(mapaProductos);
        
           break;

           case 7:
        
           //Función que muestra todos los productos
           mostrarProductos(mapaProductos);
        
           break;

           case 8:
        
           //Función que agrega al carrito
           agregarCarrito(listaCarritos,mapaProductos);
        
           break;

           case 9:
        
           //Función que elimina del carrito
        
           break;

           case 10:
        
           //Función que concreta compra
        
           break;

           case 11:

           //funcion que muestra los carritos

           break;
        }
   }
}

void menuAgregarPorducto(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos){

    char nombre[100];
    char marca[100];
    char tipo[100];
    char stock[100];
    char precio[100];

    printf("Ingrese el nombre del producto\n");
    fgets(nombre,100,stdin);

    printf("Ingrese la marca del producto\n");
    fgets(marca,100,stdin);

    printf("Ingrese el tipo de producto\n");
    fgets(tipo,100,stdin);

    printf("Ingrese el stock del producto\n");
    fgets(stock,100,stdin);

    printf("Ingrese el precio del producto\n");
    fgets(precio,100,stdin);

    agregarProducto(mapaMarcas, mapaProductos, mapaTipos, nombre, marca, tipo, stock, precio);

    printf("Producto agregado correctamente \n");


}