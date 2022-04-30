#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "hashmap.h"
#include "list.h"


struct Producto{
    char nombre[100];
    char marca[100];
    char tipo[100];
    int stock;
    int precio;
};



//Funcion para leer el k-esimo elemento de un string (separado por comas)
char* get_csv_field (char * tmp, int k){
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

//FUNCION QUE IMPORTA LOS PRODUCTOS DE UN ARCHIVO CSV
void importarProductos(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos){

    char archivo[100];
    printf("Ingrese el nombre del Archivo a importar\n");
    scanf("%s", archivo);

    FILE *file = fopen (archivo, "r");
    if (archivo) {
        char linea[1024];
        char* nombre;
        char* marca;
        char* tipo;
        char* stock;
        char* precio;

        while (fgets (linea, 1023, file) != NULL) { 
            nombre = get_csv_field(linea, 0); 
            marca = get_csv_field(linea, 1);
            tipo = get_csv_field(linea, 2);
            stock = get_csv_field(linea, 3);
            precio = get_csv_field(linea, 4);


            agregarProducto(mapaMarcas, mapaProductos, mapaTipos, nombre, marca, tipo, stock, precio);
        }
        printf("IMPORTACION EXITOSA!\n");
    } 
    else{
        printf("No se encontro el Archivo \n");
    }

}


//FUNCION QUE AGREGA UN PRODUCTO AL MAPA DE MARCAS
void agregarMapaMarcas(HashMap* mapaMarcas,Producto* auxProducto){

    //se crea la lista de la marca
    List* listaMarca=createList();
    //agregar producto a la lista
    pushBack(listaMarca,auxProducto);
    //insertar lista al mapa de marcas
    insertMap(mapaMarcas,auxProducto->marca,listaMarca);

}


//FUNCION QUE AGREGA UN PRODUCTO AL MAPA DE TIPOS
void agregarMapaTipos(HashMap* mapaTipos,Producto* auxProducto){

    //se crea la lista del tipo
    List* listaTipo=createList();
    //agregar producto a la lista
    pushBack(listaTipo,auxProducto);
    //insertar lista al mapa de tipos
    insertMap(mapaTipos,auxProducto->tipo,listaTipo);

}

//FUNCION QUE AGREGA UN PRODUCTO
void agregarProducto(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos,char* nombre,char* marca,char* tipo,char* stock,char* precio){

    Pair* aux=searchMap(mapaProductos,nombre);
    Producto* auxProducto=(Producto*)malloc(sizeof(Producto));

    if(aux==NULL){//el producto no existe
        
        //se crea el producto
        strcpy(auxProducto->nombre,nombre);
        strcpy(auxProducto->marca,marca);
        strcpy(auxProducto->tipo,tipo);
        auxProducto->stock=atoi(stock); //atoi=combierte un caracter en un entero
        auxProducto->precio=atoi(precio);

        //insertar el producto en el mapa de productos
        insertMap(mapaProductos,nombre,auxProducto);
        
        //agregar el producto al mapa de marcas y mapa de tipos
        agregarMapaMarcas(mapaMarcas,auxProducto);
        agregarMapaTipos(mapaTipos,auxProducto);
    }
    else{//el producto existe

        //incrementa el stock en el mapa de productos
        auxProducto=aux->value;
        auxProducto->stock++;

        //incrementa stock en mapa de marcas
        aux=searchMap(mapaMarcas,marca);
        auxProducto=firstList(aux->value);

        //buscar el producto en la lista de la marca
        while (auxProducto!=NULL){
            if(strcmp(auxProducto->nombre,nombre)==0){

                //aumenta el stock del producto
                auxProducto->stock=atoi(stock);
                
            }
            else{
                auxProducto=nextList(aux->value);
            }

        }
        

        //incrementa el sotkc en mapa de tipos
        aux=searchMap(mapaTipos,tipo);
        auxProducto=firstList(aux->value);
        //buscar el producto en la lista del tipo
        while (auxProducto!=NULL){
            if(strcmp(auxProducto->nombre,nombre)==0){

                //aumenta el stock del producto
                auxProducto->stock=atoi(stock);
                
            }
            else{
                auxProducto=nextList(aux->value);
            }

        }
    }
    
    

}

//FUNCION QUE BUSCA UN PRODUCTO POR TIPO
void buscarProductoTipo(HashMap* mapaTipos){

    char auxTipo[100];
    printf("Ingrese el tipo de producto que desea buscar\n");
    fgets(auxTipo,100,stdin);

    Pair* aux=searchMap(mapaTipos,auxTipo);

    if(aux==NULL){
        printf("No se encontro ningún producto de dicho tipo\n");

    }
    else{
        Producto* auxProducto=firstList(aux->value);
        while(auxProducto!=NULL){
            printf("Nombre: %s -",auxProducto->nombre);
            printf("Marca: %s -",auxProducto->marca);
            printf("Tipo: %s -",auxProducto->tipo);
            printf("Stock: %d -",auxProducto->stock);
            printf("Precio: %d\n\n",auxProducto->precio);


            auxProducto=nextList(aux->value);
        }

    }

}

//FUNCION QUE BUSCA LOS PRODUCTOS SEGUN LA MARCA
void buscarProductoMarca(HashMap* mapaMarcas){

    char auxMarca[100];
    printf("Ingrese la marca del producto que desea buscar\n");
    fgets(auxMarca,100,stdin);

    Pair* aux=searchMap(mapaMarcas,auxMarca);

    if(aux==NULL){
        printf("No se encontro ningún producto de dicha marca\n");

    }
    else{
        Producto* auxProducto=firstList(aux->value);
        while(auxProducto!=NULL){
            printf("Nombre: %s -",auxProducto->nombre);
            printf("Marca: %s -",auxProducto->marca);
            printf("Tipo: %s -",auxProducto->tipo);
            printf("Stock: %d -",auxProducto->stock);
            printf("Precio: %d\n\n",auxProducto->precio);


            auxProducto=nextList(aux->value);
        }

    }

}


//FUNCION QUE BUSCA UN PRODUCTO ESPECIFICO
void buscarProductos(HashMap* mapaProductos){

    char auxNombre[100];
    printf("Ingrese el nombre del producto que desea buscar\n");
    fgets(auxNombre,100,stdin);

    Pair* aux=searchMap(mapaProductos,auxNombre);
    if(aux==NULL){
        printf("El producto buscado no existe\n");
    }
    else{
        Producto* auxProducto=aux->value;
        printf("Nombre: %s -",auxProducto->nombre);
        printf("Marca: %s -",auxProducto->marca);
        printf("Tipo: %s -",auxProducto->tipo);
        printf("Stock: %d -",auxProducto->stock);
        printf("Precio: %d\n\n",auxProducto->precio);
    }


}
