#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
//#include "funciones.h"

const int NUM_MAX_USUARIO = 97;
const char *archivoUsuarios = "usuarios.txt";
const char *archivoActividadesName = "actividades.txt";


typedef enum {
    BRONCE,
    PLATA,
    ORO,
    PLATINO
}InsigniaNivel;

typedef enum {
    H1,
    H2,
    H3
}Logros;

typedef struct {
    Logros calorias;
    Logros distancia;
    Logros tiempo;
    InsigniaNivel nivel;
}tinsignias;

typedef struct fecha{
    int dd;
    int mm;
    int aaaa;
}tfecha;

typedef struct {
    int duracion;
    int distancia;
    float caloriaQuemadas;
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
    struct nodo *der, *izq;
}tactividad;


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
    int UCABCOIN;
    tinsignias insignias;
    DatosActividad rendimiento;
    tactividad *actividades;
}tusuario;

/////////////////////////////funciones generales
int cadenaVacia(const char *aux){
        if (strlen(aux)== 0)    return 1;
        return 0;
}

void limpearBuffer(){
    char buffer[100]; 
    fgets(buffer, sizeof(buffer), stdin);	    // Limpiar buffer de entrada
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

const char* insigniaSTR(tinsignias insignia, int op) {
    //1 imprime el nivel, 2, imprime logros de distanci, 3 tiempo, 4 calorias
    if (op == 1){
        switch (insignia.nivel) {
            case BRONCE:
                return "Bronce";   
            case PLATA:
                return "Plata";
            case ORO:
                return "Oro";
            case PLATINO:
                return "Platino";
            default:
                return "Desconocido";
        }
    }else if (op == 2 ){
        switch (insignia.distancia) {
            case H1:
                return "+50 KM";   
            case H2:
                return "+100 KM";
            case H3:
                return "+200 KM";
            default:
                return "Desconocido";
        }
    }else if (op == 3){
        switch (insignia.tiempo) {
            case H1:
                return "+24h";   
            case H2:
                return "+48h";
            case H3:
                return "+168h";
            default:
                return "Desconocido";
        }
    } else if (op == 4){
        switch (insignia.calorias) {
            case H1:
                return "+4500 kcal";   
            case H2:
                return "+9000 kcal";
            case H3:
                return "+18000 kcal";
            default:
                return "Desconocido";
        }
    }
}

void liberarArbolActividad(tactividad* raiz) {
    if (raiz == NULL)  return;
    liberarArbolActividad(raiz->izq);
    liberarArbolActividad(raiz->der);
    free(raiz);
}

void liberarUsuario(tusuario *usuario) {
    if (usuario == NULL) {
        return;
    }
    liberarArbolActividad(usuario->actividades);
    free(usuario);
}

void azulSetColor(){ printf("\033[34m");  }

void MagentaSetColor(){ printf("\033[35m");  }

void CianSetColor(){ printf("\033[36m");  }

void rojoSetColor() { printf("\033[31m");  }

void amarilloSetColor(){ printf("\033[1;33m");  }

void blancoSetColor(){  printf("\033[0m"); }

void saltoLinea(){ printf("\n\n"); }

/////// GAMIFICACION
void calcularUCABCOIN( tusuario *persona, tactividad *actividad ){
    int aux1, aux2, aux3;
    if (actividad->datos.caloriaQuemadas <= 450){             //asignando puntos por calorias quemadas
        aux1 = 1;
    }else if (actividad->datos.caloriaQuemadas <= 900){
        aux1 = 3;
    }else if(actividad->datos.caloriaQuemadas > 900){
        aux1 = 5;
    }

    if (actividad->datos.duracion <= 30){              //asignando puntos por tiempo de ejercicio
        aux2 = 1;
    }else if (actividad->datos.duracion <= 60){
        aux2 = 2;
    }else if(actividad->datos.duracion > 60){
        aux2 = 3;
    }

    if (actividad->datos.distancia == 0){                //asignando puntos por km recorrido
        aux3 = 0;
    }else if (actividad->datos.distancia < 3){
        aux3 = 1;
    }else if (actividad->datos.distancia <= 5){
        aux3 = 2;
    }else if(actividad->datos.distancia > 10){
        aux3 = 3;
    }
    
    amarilloSetColor();    
    printf("\nHas recibido %i UCABCOIN por tu desempeño en calorias quemadas!\n", aux1);
    printf("Has recibido %i UCABCOIN por tu tiempo invertido!\n", aux2);
    if (aux3 != 0){
       printf("Has recibido %i UCABCOIN por tu marca de kilometros recorridos!\n", aux3);
    }
    blancoSetColor();
    getchar();

    persona->UCABCOIN += aux1 + aux2 + aux3;
}

void determinarInsigniaNivel(tusuario *persona){
    int aux = persona->UCABCOIN;
    tusuario *insigniaAnter = persona;
    if (aux <= 50){
        persona->insignias.nivel = BRONCE;
    }else if (aux <= 100){
        persona->insignias.nivel = PLATA;
    }else if(aux <= 200){
        persona->insignias.nivel = ORO;
    }else if ( aux > 201 ){
        persona->insignias.nivel = PLATINO;
    }

    //impirmiendo mensaje de cambio de insignia
    if (insigniaAnter->insignias.nivel != persona->insignias.nivel){
        amarilloSetColor(); printf("Has alcanzado un nuevo nivel de insignia: %s!\n", insigniaSTR(persona->insignias, 1)); blancoSetColor();
    }
}

void calcularDistanciaUsuario(tusuario *persona, tactividad *actividad){
    if (actividad == NULL || persona == NULL){                                          //validacion
        perror("Algo salio mal con el calculo de la distancia del usuario."); exit(1);
    }

    int logroDistAnter = persona->insignias.distancia;          //tomando el logro actual del usuario
    persona->rendimiento.distancia += actividad->datos.distancia;

    //calculo de insignia
    if (persona->rendimiento.distancia >= 200) {
        persona->insignias.distancia = H3;
    } else if (persona->rendimiento.distancia >= 100) {
        persona->insignias.distancia = H2;
    } else if (persona->rendimiento.distancia >= 50) {
        persona->insignias.distancia = H1;
    }

    //determinando si cumplio nuevo un logro eimpirmiendo mensaje de cambio de insignia 
    if (logroDistAnter != persona->insignias.distancia) {
        if (persona->rendimiento.distancia >= 200) {
            persona->UCABCOIN += 40;
        } else if (persona->rendimiento.distancia >= 100) {
            persona->UCABCOIN += 20;
        } else if (persona->rendimiento.distancia >= 50) {
            persona->UCABCOIN += 10;
        }
        amarilloSetColor();  printf("Has alcanzado un nuevo Logro!\n\t%s recorridos. Felicitaciones!\n", 
            insigniaSTR(persona->insignias, 2)); blancoSetColor();
    }
}

void calcularTiempoUsuario(tusuario *persona, tactividad *actividad){
    if (actividad == NULL || persona == NULL){                                          //validacion
        perror("Algo salio mal con el calculo del tiempo del usuario."); exit(1);
    }

    int logroAnter = persona->insignias.tiempo;          //tomando el logro actual del usuario
    persona->rendimiento.duracion += actividad->datos.duracion;

    //calculo de insignia
    if (persona->rendimiento.distancia >= 8640) {
        persona->insignias.distancia = H3;
    } else if (persona->rendimiento.distancia >= 2880) {
        persona->insignias.distancia = H2;
    } else if (persona->rendimiento.distancia >= 1440) {
        persona->insignias.distancia = H1;
    }

    //impirmiendo mensaje de cambio de insignia si se da
    if (logroAnter != persona->insignias.distancia) {
        if (persona->rendimiento.distancia >= 8640) {
            persona->UCABCOIN += 40;
        } else if (persona->rendimiento.distancia >= 2880) {
            persona->UCABCOIN += 20;
        } else if (persona->rendimiento.distancia >= 1440) {
            persona->UCABCOIN += 10;
        }
        amarilloSetColor();
        printf("Has alcanzado un nuevo Logro!\n\t%s dedicadas. Felicitaciones!\n", 
                insigniaSTR(persona->insignias, 3)); blancoSetColor();
    }
}

void calcularCaloriasUsuario(tusuario *persona, tactividad *actividad){
    if (actividad == NULL || persona == NULL){                                          //validacion
        perror("Algo salio mal con el calculo del tiempo del usuario."); exit(1);
    }

    int logroAnter = persona->insignias.calorias;          //tomando el logro actual del usuario
    persona->rendimiento.caloriaQuemadas += actividad->datos.caloriaQuemadas;

    //calculo de insignia
    if (persona->rendimiento.caloriaQuemadas >= 18000){
        persona->insignias.calorias = H3;
    }else if (persona->rendimiento.caloriaQuemadas >= 9000){
        persona->insignias.calorias = H2;
    }else if(persona->rendimiento.caloriaQuemadas >= 4500){
        persona->insignias.calorias = H1;
    }

    //impirmiendo mensaje de cambio de insignia si se da
    if (logroAnter != persona->insignias.calorias){
        if (persona->rendimiento.caloriaQuemadas >= 18000){
            persona->UCABCOIN += 40;
        }else if (persona->rendimiento.caloriaQuemadas >= 9000){
            persona->UCABCOIN += 20;
        }else if(persona->rendimiento.caloriaQuemadas >= 4500){
            persona->UCABCOIN += 10;
        }
        CianSetColor(); 
        printf("Has alcanzado un nuevo Logro!\n\t%s quemadas. Felicitaciones!\n", 
                insigniaSTR(persona->insignias, 4)); blancoSetColor();
    }
}

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
    while (distancia <= 0) {
        printf("La distancia debe ser un número mayor que 0. Intente de nuevo: ");
        scanf("%d", &distancia);
        limpearBuffer();
    }
    return distancia;
}

int tomarTiempo(){
    int tiempo;
    printf("Ingrese el tiempo estimado de la actidad (min): ");
    scanf("%d", &tiempo);
    limpearBuffer();
    while (tiempo <= 0) {
        printf("El tiempo debe ser un número mayor que 0. Intente de nuevo: ");
        scanf("%d", &tiempo);
        limpearBuffer();
    }
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

	int op = 0;                                     //tomar datos de la actividad
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
            default:
                op = 0;
                rojoSetColor(); printf("\nOpción no válida. Intente de nuevo.\n"); blancoSetColor(); getchar();
	 	}
	} while (op == 0); 

    //calcular calorias de la actividad
    if (actividad->datos.duracion != 0){                
        int get;
        if (persona->genero == MASCULINO){
            get = ((5 * persona->peso) + (0,55 * persona->altura) - (5 * persona->edad)) + 5 ;
        }else{
            get = ((5 * persona->peso) + (0,55 * persona->altura) - (5 * persona->edad)) - 161;
        }

        actividad->datos.caloriaQuemadas = get * actividad->datos.duracion  * 0.05;         //calculos por tiempo y distancia de la actividad       
        if (actividad->datos.distancia != 0) 
            actividad->datos.caloriaQuemadas *= actividad->datos.distancia * 0.16;
    }

    //calculos de sistemas de gamificacion
    calcularUCABCOIN(persona, actividad);
    determinarInsigniaNivel(persona);
    calcularDistanciaUsuario(persona, actividad);
    calcularTiempoUsuario(persona, actividad);
    calcularCaloriasUsuario(persona, actividad);
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
    
    printf("Calorías quemadas: %.2f\n", actividad->datos.caloriaQuemadas);
}

void imprimirArbolActividad(tactividad *actividad){
    if (actividad == NULL)
        return;

    imprimirActividad(actividad);
    imprimirArbolActividad(actividad->izq);
    imprimirArbolActividad(actividad->der);
}

tactividad *insertarActividad(tactividad *arbol, tactividad *actividad){
    if (arbol == NULL){
        return actividad;
    }

    if (actividad->datos.caloriaQuemadas < (arbol)->datos.caloriaQuemadas){
        arbol->izq = insertarActividad(arbol->izq, actividad);
    }else if (actividad->datos.caloriaQuemadas >= (arbol)->datos.caloriaQuemadas){
        arbol->der = insertarActividad(arbol->der, actividad);
    }
    return arbol;
}

tactividad *leerArbolActividad(const char *filename){
	FILE *file = fopen(filename, "rt");                             //apertura del archivo
	if (file == NULL){
        file = fopen(filename, "wt");                         //creando archivo sino existe
        if (file == NULL){
            printf("Error al crear el archivo"); exit(1);
        }
        fclose(file);

        file = fopen(filename, "rt");                        
        if (file == NULL){
            printf("Error al abrir el archivo"); exit(1);
        }
	} 

    tactividad *arbol = NULL;
    char buffer[1024];

    while (fgets(buffer, 1024, file) != NULL) {
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
            sscanf(buffer, "Calorías quemadas: %f\n", &actividad->datos.caloriaQuemadas);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Duración: %d\n", &actividad->datos.duracion);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Distancia: %d\n", &actividad->datos.distancia);
            actividad->izq = actividad->der = NULL;
            arbol = insertarActividad(arbol, actividad);
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
        fprintf(file, "Calorías quemadas: %f\n", actividad->datos.caloriaQuemadas);
        fprintf(file, "Duración: %d\n", actividad->datos.duracion);
        fprintf(file, "Distancia: %d\n", actividad->datos.distancia);
        return;
    }

    if (actividad->datos.caloriaQuemadas < arbolActividad->datos.caloriaQuemadas ) {
        fprintf(file, "Subárbol izquierdo:\n");
        guardarActividad(file, actividad->izq, actividad);
    }
    if (actividad->datos.caloriaQuemadas >= arbolActividad->datos.caloriaQuemadas) {
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
    CianSetColor(); printf("\nActividad Registrada exitosamente.\n\n");
    blancoSetColor(); printf("Volviendo Al Inicio. Presione para continuar..\n"); getchar();
}

