#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
//#include "funciones.h"

const int NUM_MAX_USUARIO = 97;
//#define NUM_MAX_USUARIO 97


const char *archivoUsuarios = "usuarios.txt";
const char *archivoActividadesName = "actividades.txt";

//GENERALES
void limpearBuffer(){
    char buffer[100]; 
    fgets(buffer, sizeof(buffer), stdin);	    // Limpiar buffer de entrada
}

typedef struct {                    // Estructura de elemento de  tabla hash
    int clave;
    char *valor;
} Elemento;

typedef struct {                    // Estructura tabla hash
    int NUM_MAX_USUARIO;
    Elemento *tabla;
} TablaHash;

typedef struct fecha{
    int dd;
    int mm;
    int aaaa;
}tfecha;

typedef struct {
    int duracion;
    int distancia;
}DatosActividad;

// Enumeración para tipos de actividad
typedef enum {
    CORRER,
    CAMINAR,
    CICLISMO,
    YOGA,
    CROSSFIT,
    PILATES,
    TENIS,
    FUTBOL,
    ARTESMARCIALES,
    NADAR
} TipoActividad;

// ACTIVIDAD 
typedef struct nodo{
    int id;
    int ciUser;
    tfecha fecha;
    TipoActividad tipo;
    DatosActividad datos;    
    float caloriaQuemadas;
    struct nodo *der, *izq;
}tactividad;

typedef struct {
    int ciUser;
    tactividad *arbolActividades;
} tnodoTHActividades;

typedef struct {
    int NUM_MAX_USUARIOS;
    tnodoTHActividades *tabla;
} ttablaHash;

//USUARIO
typedef enum {
    FEMENINO,
    MASCULINO
} tgenero;

typedef struct usuario{
    int ci;
    char nombre[30];
    int clave;
    tgenero genero;
    int altura;   //cm
    int peso;     //kg
    int edad;
    tactividad *actividades;
}tusuario;

/////////////////////////////funciones generales
int cadenaVacia(const char *aux){
        if (strlen(aux)== 0)
            return 1;
        return 0;
}

const char* tipoGeneroStr(tgenero tipo) {
    switch (tipo) {
        case MASCULINO:
            return "Masculino";
        case FEMENINO:
            return "Femenino";
        default:
            return "Desconocido";
    }
}

const char* tipoActividadStr(TipoActividad tipo) {
    switch (tipo) {
        case CORRER:
            return "Correr";
        case CAMINAR:
            return "Caminar";
        case CICLISMO:
            return "Ciclismo";
        case YOGA:
            return "Yoga";
        case CROSSFIT:
            return "CrossFit";
        case PILATES:
            return "Pilates";
        case TENIS:
            return "Tenis";
        case FUTBOL:
            return "Futbol";
        case ARTESMARCIALES:
            return "Artes Marciales";
        case NADAR:
            return "Nadar";
        default:
            return "Desconocido";
    }
}

void liberarArbolActividad(tactividad* raiz) {
    if (raiz == NULL)  return;
    liberarArbolActividad(raiz->izq);
    liberarArbolActividad(raiz->der);
    free(raiz);
}

void azulSetColor(){ printf("\033[34m");  }

void amarilloSetColor(){ printf("\033[1;33m");  }

void blancoSetColor(){  printf("\033[0m"); }

void saltoLinea(){ printf("\n\n"); }


///////////ACTIVIDADES
tfecha ObtenerFecha() {
    time_t tiempoActual;
    struct tm *infoTiempo;
    tfecha fecha;

    time(&tiempoActual);						// Obtener el tiempo actual en segundos
    infoTiempo = localtime(&tiempoActual);		// Convertir el tiempo en una estructura de tiempo local
    fecha.dd = infoTiempo->tm_mday;
    fecha.mm = infoTiempo->tm_mon + 1; 		// tm_mon es de 0 a 11
    fecha.aaaa = infoTiempo->tm_year + 1900; // tm_year es desde 1900
    return fecha;
}

int generarID(){
    time_t tiempoActual;
    struct tm *infoTiempo;
    tfecha fecha;

    time(&tiempoActual);						// Obtener el tiempo actual en segundos
    infoTiempo = localtime(&tiempoActual);		// Convertir el tiempo en una estructura de tiempo local
    char aux[256];
    sprintf(aux, "%02d%02d%02d%02d%02d", 
            infoTiempo->tm_mon + 1, 
            infoTiempo->tm_mday, infoTiempo->tm_hour, 
            infoTiempo->tm_min, infoTiempo->tm_sec);
    int id = strtoll(aux, NULL, 10);
    return id;
}

int tomarDistancia(){
    int distancia;
    printf("\nIngrese la distancia a recorrer (km): ");
    scanf("%d", &distancia);
    limpearBuffer();
    return distancia;
}

int tomarTiempo(){
    int tiempo;
    printf("Ingrese el tiempo estimado de la actidad (min): ");
    scanf("%d", &tiempo);
    limpearBuffer();
    return tiempo;
}

tactividad *ObtenerDatosActividades(tusuario *persona){
	tactividad *actividad = (tactividad*)malloc(sizeof(tactividad));
    actividad->datos.duracion = 0;
    actividad->datos.distancia = 0;
    actividad->id = generarID();
    actividad->der = actividad->izq = NULL;
    actividad->ciUser = persona->ci;

	tfecha fecha = ObtenerFecha();      //obtener fecha de  prtf("Fecha: %02d", fecha.dd); donaciones->fecha.dd
	actividad->fecha.dd = fecha.dd;
	actividad->fecha.mm = fecha.mm;
	actividad->fecha.aaaa = fecha.aaaa;

	int op;
	do{
        printf("**Menú de Actividades Físicas**\n\n");
        printf("1. Correr\n");
        printf("2. Caminar\n");
        printf("3. Ciclismo\n");
        printf("4. Yoga\n");
        printf("5. Crossfit\n");
        printf("6. Pilates\n");
        printf("7. Fútbol\n");
        printf("8. Tenis\n");
        printf("9. Artes Marciales\n");
        printf("10. Nadar\n");
        //printf("0. Regresar al Menú\n");
        printf("Seleccione una opción: ");
	 	scanf("%i", &op);
        limpearBuffer();
	 	switch (op) {
            case 1:
                actividad->tipo = CORRER;
                actividad->datos.distancia = tomarDistancia();
                actividad->datos.duracion = tomarTiempo();
                break;
            case 2:
                actividad->tipo = CAMINAR;
                actividad->datos.distancia = tomarDistancia();
                actividad->datos.duracion = tomarTiempo();
                break;
            case 3:
                actividad->tipo = CICLISMO;
                actividad->datos.distancia = tomarDistancia();
                actividad->datos.duracion = tomarTiempo();
                break;
            case 4:
                actividad->tipo = YOGA;
                actividad->datos.duracion = tomarTiempo();
                break;
            case 5:
                actividad->tipo = CROSSFIT;
                actividad->datos.duracion = tomarTiempo();
                break;
            case 6:
                actividad->tipo = PILATES;
                actividad->datos.duracion = tomarTiempo();
                break;
            case 7:
                actividad->tipo = FUTBOL;
                actividad->datos.duracion = tomarTiempo();
                break;
            case 8:
                actividad->tipo = TENIS;
                actividad->datos.duracion = tomarTiempo();
                break;
            case 9:
                actividad->tipo = ARTESMARCIALES;
                actividad->datos.duracion = tomarTiempo();
                break;
            case 10:
                actividad->tipo = NADAR;
                actividad->datos.duracion = tomarTiempo();
                break;
            // case 0:
            //     printf("\nRegresando al Menú...\n");
            //     Home(persona);
            //     break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
	 	}

        if (actividad->datos.duracion != 0){
            int get;
            if (persona->genero == MASCULINO){
                get = ((10 * persona->peso) + (6,25 * persona->altura) - (5 * persona->edad) + 5) * 1.5;
            }else{
                get = ((10 * persona->peso) + (6,25 * persona->altura) - (5 * persona->edad) - 161) * 1.5;
            }

            actividad->caloriaQuemadas = get * actividad->datos.duracion;          
            if (actividad->datos.distancia != 0) 
                actividad->caloriaQuemadas *= actividad->datos.distancia;
        }
	} while (op == 0); 
    amarilloSetColor(); printf("\n\nActividad Registrada exitosamente.\n");
    blancoSetColor(); printf("Volviendo Al Inicio. Presione para continuar..\n"); getchar();

	return actividad;
}

void imprimirActividad(tactividad *actividad){
    printf("Fecha: %02d/%02d/%04d\n", actividad->fecha.dd, actividad->fecha.mm, actividad->fecha.aaaa);
    printf("CI del usuario: %d\n", actividad->ciUser);
    printf("Tipo de actividad: %s\n", tipoActividadStr(actividad->tipo)); 
    if (actividad->datos.distancia)
        printf("Distancia: %i km\n", actividad->datos.distancia);
    
    if (actividad->datos.duracion) 
        printf("Duración: %d minutos\n", actividad->datos.duracion); 
    
    printf("Calorías quemadas: %.2f\n", actividad->caloriaQuemadas);
}

tactividad *insertarActividad(tactividad *arbol, tactividad *actividad){
    if (arbol == NULL){
        return actividad;
    }

    if (actividad->caloriaQuemadas < (arbol)->caloriaQuemadas){
        arbol->izq = insertarActividad(arbol->izq, actividad);
    }else if (actividad->caloriaQuemadas >= (arbol)->caloriaQuemadas){
        arbol->der = insertarActividad(arbol->der, actividad);
    }
    return arbol;
}

tactividad *leerArbolActividad(const char *filename){
    FILE *file = fopen(filename, "rt");
    if (file == NULL) {
        perror("Error al abrir el archivo"); exit(1);
    }
    tactividad *arbol = NULL;
    char buffer[1024];

    while (fgets(buffer, 1024, file) != NULL) {
            printf("hoa1"); getchar();

        if (strncmp(buffer, "Actividad:", 10) == 0) {
            tactividad* actividad = (tactividad*) malloc(sizeof(tactividad));

            fgets(buffer, 1024, file);
            sscanf(buffer, "ID: %d\n", &actividad->id);
            fgets(buffer, 1024, file);
            sscanf(buffer, "CI Usuario: %d\n", &actividad->ciUser);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Fecha: %02d/%02d/%04d\n", &actividad->fecha.dd, &actividad->fecha.mm, &actividad->fecha.aaaa);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Tipo de actividad: %d\n", (int*)&actividad->tipo);
            fgets(buffer, 1024, file);            
            sscanf(buffer, "Calorías quemadas: %f\n", &actividad->caloriaQuemadas);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Duración: %d\n", &actividad->datos.duracion);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Distancia: %d\n", &actividad->datos.distancia);
            actividad->izq = actividad->der = NULL;
            arbol = insertarActividad(arbol, actividad);
            free(actividad);
        }
    }
    fclose(file);
    return arbol;
}

void guardarActividad(FILE *file, tactividad *arbolActividad, tactividad *actividad){
    if (arbolActividad == NULL){
        fprintf(file, "Actividad:\n");
        fprintf(file, "ID: %d\n", actividad->id);
        fprintf(file, "CI Usuario: %d\n", actividad->ciUser);
        fprintf(file, "Fecha: %02d/%02d/%04d\n", actividad->fecha.dd, actividad->fecha.mm, actividad->fecha.aaaa);
        fprintf(file, "Tipo de actividad: %d\n", actividad->tipo);
        fprintf(file, "Calorías quemadas: %f\n", actividad->caloriaQuemadas);
        fprintf(file, "Duración: %d\n", actividad->datos.duracion);
        fprintf(file, "Distancia: %d\n", actividad->datos.distancia);
        return;
    }

    if (actividad->caloriaQuemadas < arbolActividad->caloriaQuemadas ) {
        fprintf(file, "Subárbol izquierdo:\n");
        guardarActividad(file, actividad->izq, actividad);
    }
    if (actividad->caloriaQuemadas >= arbolActividad->caloriaQuemadas) {
        fprintf(file, "Subárbol derecho:\n");
        guardarActividad(file, actividad->der, actividad);
    }
    fprintf(file, "\n");
}

void guardarDatosEnArchivo(const char *filename, tactividad *arbol, tactividad *actividad) {
    FILE *file = fopen(filename, "at");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    guardarActividad(file, arbol, actividad);
    fclose(file);
}


//TABLA HASH DE ACTIVIDADES
ttablaHash *inicializarTH(int maxUsuarios){
    ttablaHash *tabla = (ttablaHash*)malloc(sizeof(ttablaHash));
    if (tabla == NULL) {
        perror("Error al asignar memoria para la tabla hash"); return NULL;
    }

    tabla->NUM_MAX_USUARIOS = maxUsuarios;
    tabla->tabla = (tnodoTHActividades*)malloc(sizeof(tnodoTHActividades) * maxUsuarios);
    if (tabla->tabla == NULL) {
        perror("Error al asignar memoria para la tabla hash"); return NULL;
    }
    //inicializando cada elemente
    for (size_t i = 0; i < maxUsuarios; i++){
        tabla->tabla[i].ciUser = -1;
        tabla->tabla[i].arbolActividades = NULL;
    }
    return tabla;
}

int funcionHashArbold(int ciUsaer, int maxUsuarios) {
    return ciUsaer % maxUsuarios;
}

void insertarTHARbolActividades( ttablaHash *tabla, int ciUser, tactividad *actividad ){
    int indice = funcionHashArbol(ciUser, NUM_MAX_USUARIO);
    while ( tabla->tabla[indice].ciUser != -1 ){
        indice = (indice + 1) % tabla->NUM_MAX_USUARIOS;
    }
    tabla->tabla[indice].ciUser = ciUser;
    tabla->tabla[indice].arbolActividades = actividad;
}

ttablaHash buscarTHArbolActividades( ttablaHash *tabla, int ciUser ){
    int indice = funcionHashArbold(ciUser, NUM_MAX_USUARIO);

    while (tabla->tabla[indice].clave != ciUser && tabla->tabla[indice].clave != -1) {
        indice = (indice + 1) % tabla->NUM_MAX_USUARIOS;
    }

    if (tabla->tabla[indice].clave == ciUser) {
        return tabla->tabla[indice].arbolActividades;
    }else{
        return NULL;
    }   
}

void liberarTablaHash(ttablaHash *tabla) {
    if (tabla != NULL) {
        if (tabla->tabla != NULL) {
            free(tabla->tabla);
        }
        free(tabla);
    }
}

