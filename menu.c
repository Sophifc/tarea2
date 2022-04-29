#include <stdio.h>
//#include "menu.h"
#include "Map.h"
//#include "funciones.h"


void initMenu(){

    Map *mapaMarcas=createMap;
    Map *mapaTipos=createMap;
    Map *mapaProductos=createMap; //PUEDE SER UNA LISTA DE PRODUCTOS 
    Map *mapaCarritos=createMap;

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
        
           //Función que importa las canciones del archivo CSV
        
           break;

           case 2:
        
           //Función que exporta las canciones
        
           break;

           case 3:
       
           //Función que agrega las canciones
        
           break;

           case 4:
        
           //Función que busca las canciones por nombre
        
           break;

           case 5:
        
           //Función que busca las canciones por artista
        
           break;

           case 6:
        
           //Función que busca las canciones por genero
        
           break;

           case 7:
        
           //Función que elimina una cancion
        
           break;

           case 8:
        
           //Función que muestra los nombre de todas las playlists
        
           break;

           case 9:
        
           //Función que muestra las canciones de una playlist
        
           break;

           case 10:
        
           //Función que muestra todas las canciones
        
           break;
        }
   }
}