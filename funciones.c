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


struct  Carrito{
    char nombre[100];
    int cantidad;
    List* productos;
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
void importarProductos(HashMap* mapaMarcas,HashMap* mapaProductos,HashMap* mapaTipos, char* archivo){

   /* char archivo[100];
    printf("Ingrese el nombre del Archivo a importar\n");
    scanf("%s", archivo);*/

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


    Pair* aux=searchMap(mapaMarcas,auxProducto->marca);

    if(aux!=NULL){
        //la lista para ese tipo ya existe
        List* auxLista=aux->value;
        //agregar producto a la lista
        pushBack(auxLista,auxProducto);
        //insertar lista al mapa de tipos
        insertMap(mapaMarcas,auxProducto->marca,auxLista);

    }
    else{
        //se crea la lista de la marca
        List* listaMarca=createList();
       //agregar producto a la lista
       pushBack(listaMarca,auxProducto);
       //insertar lista al mapa de marcas
       insertMap(mapaMarcas,auxProducto->marca,listaMarca);
    }

}


//FUNCION QUE AGREGA UN PRODUCTO AL MAPA DE TIPOS
void agregarMapaTipos(HashMap* mapaTipos,Producto* auxProducto){

    Pair* aux=searchMap(mapaTipos,auxProducto->tipo);

    if(aux!=NULL){
        //la lista para ese tipo ya existe
        List* auxLista=aux->value;
        //agregar producto a la lista
        pushBack(auxLista,auxProducto);
        //insertar lista al mapa de tipos
        insertMap(mapaTipos,auxProducto->tipo,auxLista);

    }
    else{
        //se crea la lista del tipo
        List* listaTipo=createList();
        //agregar producto a la lista
        pushBack(listaTipo,auxProducto);
       //insertar lista al mapa de tipos
       insertMap(mapaTipos,auxProducto->tipo,listaTipo);
    }
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

        printf("AUMENTANDO STOCK\n");
        auxProducto=aux->value;
        auxProducto->stock++;

        //incrementa stock en mapa de marcas
        aux=searchMap(mapaMarcas,marca);
        List* auxList=aux->value;
        Producto* auxProducto=firstList(auxList);

        //buscar el producto en la lista de la marca
        while (auxProducto!=NULL){
            if(strcmp(auxProducto->nombre,nombre)==0){

                printf("AUMENTANDO STOCK MARCAS\n");
                //aumenta el stock del producto
                auxProducto->stock=atoi(stock);
                
            }
            else{
                auxProducto=nextList(auxList);
            }

        }
        

        //incrementa el sotkc en mapa de tipos
        aux=searchMap(mapaTipos,tipo);
        auxList=aux->value;
        auxProducto=firstList(auxList);
        //buscar el producto en la lista del tipo
        while (auxProducto!=NULL){
            if(strcmp(auxProducto->nombre,nombre)==0){

                printf("AUMENTANDO STOCK TIPOS\n");

                //aumenta el stock del producto
                auxProducto->stock=atoi(stock);
                
            }
            else{
                auxProducto=nextList(auxList);
            }

        }
    }
    
    

}

//FUNCION QUE BUSCA UN PRODUCTO POR TIPO
void buscarProductoTipo(HashMap* mapaTipos){

    char auxTipo[100];
    printf("Ingrese el tipo de producto que desea buscar\n");
    fgets(auxTipo,100, stdin);
    fgets(auxTipo,100, stdin);
    strtok(auxTipo, "\n");

    Pair* aux=searchMap(mapaTipos,auxTipo);

    if(aux==NULL){
        printf("No se encontro ningún producto de dicho tipo\n");

    }
    else{

        List* auxList=aux->value;
        Producto* auxProducto=firstList(auxList);
        while(auxProducto!=NULL){
            printf("Nombre: %s -",auxProducto->nombre);
            printf("Marca: %s -",auxProducto->marca);
            printf("Tipo: %s -",auxProducto->tipo);
            printf("Stock: %d -",auxProducto->stock);
            printf("Precio: %d\n\n",auxProducto->precio);

            auxProducto=nextList(auxList);
        }
    }

}

//FUNCION QUE BUSCA LOS PRODUCTOS SEGUN LA MARCA
void buscarProductoMarca(HashMap* mapaMarcas){

    char auxMarca[100];
    printf("Ingrese la marca del producto que desea buscar\n");
    fgets(auxMarca,100, stdin);
    fgets(auxMarca,100, stdin);
    strtok(auxMarca, "\n");

    Pair* aux=searchMap(mapaMarcas,auxMarca);

    if(aux==NULL){
        printf("No se encontro ningún producto de dicha marca\n");
        

    }
    else{

        List* auxList=aux->value;
        Producto* auxProducto=firstList(auxList);
        while(auxProducto!=NULL){


            printf("Nombre: %s -",auxProducto->nombre);
            printf("Marca: %s -",auxProducto->marca);
            printf("Tipo: %s -",auxProducto->tipo);
            printf("Stock: %d -",auxProducto->stock);
            printf("Precio: %d\n\n",auxProducto->precio);

            auxProducto=nextList(auxList);
        }

    }

}


//FUNCION QUE BUSCA UN PRODUCTO ESPECIFICO
void buscarProductos(HashMap* mapaProductos){

    char auxNombre[100];
    printf("Ingrese el nombre del producto que desea buscar\n");
    fgets(auxNombre,100, stdin);
    fgets(auxNombre,100, stdin);
    strtok(auxNombre, "\n");

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



void mostrarProductos(HashMap* mapaProductos){

    Pair* aux=firstMap(mapaProductos);
    Producto* auxProducto;
    int cont=1;

    while (aux!=NULL){

        auxProducto=aux->value;
        printf("%d ", cont);
        printf("Nombre: %s -",auxProducto->nombre);
        printf("Marca: %s -",auxProducto->marca);
        printf("Tipo: %s -",auxProducto->tipo);
        printf("Stock: %d -",auxProducto->stock);
        printf("Precio: %d\n\n",auxProducto->precio);
        aux=nextMap(mapaProductos);

        cont++;

    }
    
}



void crearCarrito(char* auxCarrito,List* listaCarritos){

    Carrito* carrito=(Carrito*)malloc(sizeof(Carrito));
    strcpy(carrito->nombre,auxCarrito);
    carrito->cantidad=0;
    carrito->productos=createList();
    pushBack(listaCarritos,carrito);

}
//FUNCION QUE AGREGA UN PRODUCTO A UN CARRITO
void agregarCarrito(List* listaCarritos, HashMap* mapaProductos){

    char auxCarrito[100];
    printf("Ingrese el nombre del carrito al cual agregara el producto\n");
    fgets(auxCarrito,100, stdin);
    fgets(auxCarrito,100, stdin);
    strtok(auxCarrito, "\n");

    Carrito* aux=firstList(listaCarritos);

    if(aux==NULL){

        printf("El carrito no eixtse, se creara uno nuevo\n");

        //crear el carrito e ingresarlo a la lista
        crearCarrito(auxCarrito,listaCarritos);

        //agregar el producto al carrito
        //buscar el producto
        char producto[100];
        //int cantidad;
        printf("INGRESE EL NOMBRE DEL PRODUCTO A AGREGAR\n");
        fgets(producto,100, stdin);
        strtok(producto, "\n");
        //printf("Ingrese la cantidad que desea agregar\n");
        //scanf("%d", &cantidad);

        Pair* auxPair=searchMap(mapaProductos, producto);
    

        if(auxPair==NULL){
            printf("Producto no encontrado\n");
        }
        else{
            //agregar el producto al carrito
            printf("Producto encontrado\n");
            //Producto* auxProducto=auxPair->value;

            //descontar stock en el mapa de productos
            //auxProducto->stock=auxProducto->stock-cantidad;
            pushBack(listaCarritos,auxPair->value);
            aux->cantidad++;
            printf("Producto agregado al carrito\n");
            
        
        }

    }
    else{
        while(aux!=NULL){
            if(strcmp(aux->nombre,auxCarrito)==0){

                printf("Carrito encontrado\n");

                //buscar el producto
                char producto[100];
               // int cantidad;
                printf("INGRESE EL NOMBRE DEL PRODUCTO A AGREGAR\n");
                fgets(producto,100, stdin);
                strtok(producto, "\n");

                //printf("Ingrese la cantidad que desea agregar\n");
                //scanf("%d", &cantidad);

                Pair* auxPair=searchMap(mapaProductos, producto);

                if(auxPair==NULL){
                    printf("Producto no encontrado\n");
                }
                else{
                    //agregar el producto al carrito
                    printf("Producto  encontrado\n");
                    //Producto* auxProducto=auxPair->value;

                    //descontar stock en el mapa de productos
                    //auxProducto->stock=auxProducto->stock-cantidad;
                    pushBack(listaCarritos,auxPair->value);
                    aux->cantidad++;
                    printf("Producto agregado al carrito\n");
                    break;
                }
            
            }
            else{
                aux=nextList(listaCarritos);
            }
        }
    }

}


//FUNCION QUE MUESTRA LOS CARRITOS DE COMPRA EXISTENTES
void mostrarCarritos(List* listaCarritos){

    Carrito* auxCarrito=firstList(listaCarritos);
    int cont=1;

    if(auxCarrito==NULL){
        printf("No hay carritos de compra\n");
    }
    while(auxCarrito!=NULL){
        
        printf("%d) Nombre: %c , cantidad de productos: %d\n", cont,auxCarrito->nombre , auxCarrito->cantidad);
        auxCarrito=nextList(listaCarritos);
    }

}

//FUNCION QUE EXPORTA LOS PRODUCTOS EN UN ARCHIVO CSV
void exportarProductos(HashMap* mapaProductos){

    char archivo[100];
    printf("Ingrese el nombre con el cual exportar el archivo, agrege .csv al final de este\n");
    fgets(archivo,100, stdin);

    FILE *datos;
    char aux[1024];
    datos = fopen(archivo, "w");
    Pair* productoPair = firstMap(mapaProductos);

    while (productoPair != NULL) {
        
        Producto* auxProducto = productoPair->value;
        snprintf(aux, sizeof(aux), "%s, %s, %s, %d, %d\n", auxProducto->nombre, auxProducto->marca, auxProducto->tipo, auxProducto->stock, auxProducto->precio);
        fputs(aux, datos);
        productoPair = nextMap(mapaProductos);
    }
    printf("EXPORTACION EXITOSA!\n");
    fclose(datos);


}
