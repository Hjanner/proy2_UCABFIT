# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct usuarios {
    char clave[50];
    char nombre[50];
    int edad;
    char genero;
    float altura;
    float peso;
    float masa_muscular;
    float grasa;
    char antiguedad[30];
}Usuarios;

typedef struct {
    int capacidad;
    int contador;
    Usuarios *tabla;
}TablaHash;


TablaHash *crear_tabla(int capacidad){
    TablaHash *tabla = (TablaHash*)malloc(sizeof(TablaHash));
    tabla->capacidad = capacidad;
    tabla->contador = 1;
    tabla->tabla = (Usuarios*)malloc(sizeof(Usuarios) * capacidad);
    for (int i = 0; i < capacidad; i++){
        strcpy(tabla->tabla[i].clave, "ass");
        tabla->tabla[i].nombre = " ";
        tabla->tabla[i].edad = 0;
        tabla->tabla[i].genero = ' ';
        tabla->tabla[i].altura = 0;
        tabla->tabla[i].peso = 0;
        tabla->tabla[i].masa_muscular = 0;
        tabla->tabla[i].grasa = 0;
        tabla->tabla[i].antiguedad = " ";
    }

    return tabla;

}


void insertar_tabla_hash(TablaHash *tabla, char *clave,char *nombre, int edad, char genero, float altura, float peso, float masa_muscular,float grasa, char *antiguedad){
    int tam = strlen(clave);
    int indice = tam % tabla->capacidad;
    while(tabla->tabla[indice].clave != -1){
        indice = (indice + 1) % tabla->capacidad;
    }
    tabla->tabla[indice].clave = clave;
    strcpy(tabla->tabla[indice].nombre,nombre);
    tabla->tabla[indice].edad = edad;
    tabla->tabla[indice].genero = genero;
    tabla->tabla[indice].altura = altura;
    tabla->tabla[indice].peso = peso;
    tabla->tabla[indice].masa_muscular = masa_muscular;
    tabla->tabla[indice].grasa = grasa;
    strcpy(tabla->tabla[indice].antiguedad,antiguedad);
}

void listar_elementos(TablaHash *tabla){
    for (int i = 0; i < tabla->capacidad; i++){
        if (tabla->tabla[i].clave != -1){
            printf("\nNombre: %s, edad: %d, Genero: %c\nAltura: %f, peso: %f, Masa muscular: %f, Grasa: %f, Antiguedad: %s",tabla->tabla[i].nombre,tabla->tabla[i].edad,tabla->tabla[i].genero,tabla->tabla[i].altura,tabla->tabla[i].peso,tabla->tabla[i].masa_muscular,tabla->tabla[i].grasa,tabla->tabla[i].antiguedad);
        }
    }
}

int main(){
    TablaHash *tabla = crear_tabla(40);
    insertar_tabla_hash(tabla,"31701591","Alejandro",18,'M',1.73,58,34,45,"Hace 2 dias");
    listar_elementos(tabla);
    return 0;
}

