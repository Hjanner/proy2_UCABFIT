# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <time.h>


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
    int altura;   //cm
    int peso;     //kg
    int edad;
    int UCABCOIN;
    tinsignias insignias;
    DatosActividad rendimiento;
    tactividad *actividades;
}tusuario;


typedef struct {
    int capacidad;
    tusuario *tabla;
}TablaHash;

const int NUM_MAX_USUARIOS = 100;
const char *nombreArchivo = "usuarios.txt";

void azulSetColor(){ printf("\033[34m");  }

void MagentaSetColor(){ printf("\033[35m");  }

void CianSetColor(){ printf("\033[36m");  }

void rojoSetColor() { printf("\033[31m");  }

void amarilloSetColor(){ printf("\033[1;33m");  }

void blancoSetColor(){  printf("\033[0m"); }

void saltoLinea(){ printf("\n\n"); }


TablaHash *crear_tabla(){
    TablaHash *tabla = malloc(sizeof(TablaHash));
    tabla->capacidad = NUM_MAX_USUARIOS;
    tabla->tabla = malloc(sizeof(tusuario) * NUM_MAX_USUARIOS);
    for (int i = 0; i < NUM_MAX_USUARIOS; i++){
        tabla->tabla[i].ci = -1;
        strcpy(tabla->tabla[i].nombre," ");
        tabla->tabla[i].edad = 0;
        tabla->tabla[i].altura = 0;
        tabla->tabla[i].peso = 0;
        tabla->tabla[i].UCABCOIN = 0;
    }

    return tabla;

}

TablaHash *insertar_tabla_hash(TablaHash *tabla,int ci,char *nombre, int edad, int altura, int peso){
    int indice = ci % tabla->capacidad;
    while(tabla->tabla[indice].ci != -1){
        indice = (indice + 1) % tabla->capacidad;
    }
    tabla->tabla[indice].ci = ci;
    strcpy(tabla->tabla[indice].nombre,nombre);
    tabla->tabla[indice].edad = edad;
    tabla->tabla[indice].altura = altura;
    tabla->tabla[indice].peso = peso;
    return tabla;
}

TablaHash *leer_tabla_hash(){
    FILE *file = fopen("usuarios.txt", "rt");                             //apertura del archivo
	if (file == NULL){
        file = fopen("usuarios.txt", "wt");                         //creando archivo sino existe
        if (file == NULL){
            printf("Error al crear el archivo"); exit(1);
        }
        fclose(file);

        file = fopen("usuarios.txt", "rt");                        
        if (file == NULL){
            printf("Error al abrir el archivo"); exit(1);
        }
	} 

    TablaHash *tabla = crear_tabla();
    char buffer[1024];
    char nombre[30];
    int ci;
    int altura;
    int peso;
    int edad;
    while (fgets(buffer, 1024, file) != NULL) {
        if (strncmp(buffer, "Usuarios:", 9) == 0) {
            fgets(buffer, 1024, file);
            sscanf(buffer, "CI Usuario: %d\n",&ci);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Nombre: %s\n",nombre);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Edad: %d",&edad);
            fgets(buffer, 1024, file);            
            sscanf(buffer, "Altura: %d\n", &altura);
            fgets(buffer, 1024, file);
            sscanf(buffer, "Peso: %d\n", &peso);
            tabla = insertar_tabla_hash(tabla,ci,nombre,edad,altura,peso);
        }
    }
    fclose(file);
    return tabla;
}



void limpearBuffer(){
    char buffer[100]; 
    fgets(buffer, sizeof(buffer), stdin);	    // Limpiar buffer de entrada
}

int cadenaVacia(const char *aux){
        if (strlen(aux)== 0)
            return 1;
        return 0;
}

void guardarTablaHash(TablaHash *tabla){
    FILE *file = fopen("usuarios.txt","at");
    for (int i = 0; i < tabla->capacidad; i++){
        if (tabla->tabla[i].ci != -1){
            fprintf(file, "Usuarios:\n");
            fprintf(file, "CI Usuario: %d\n", tabla->tabla[i].ci);
            fprintf(file, "Nombre: %s\n", tabla->tabla[i].nombre);
            fprintf(file, "Edad: %d\n", tabla->tabla[i].edad);
            fprintf(file, "Altura: %d\n", tabla->tabla[i].altura);
            fprintf(file, "Peso: %d\n", tabla->tabla[i].peso);
        }
    }
    fclose(file);
    return;
}

int verificar_cedula(TablaHash *tabla, int ci){
    int indice = ci % tabla->capacidad;
    while(tabla->tabla[indice].ci != ci && tabla->tabla[indice].ci != -1){
        indice = (indice + 1) % tabla->capacidad;
    }
    if (tabla->tabla[indice].ci == ci){
        return 1;
    }
    else{
        return 0;
    }
}


int validarCI(char ci[15], int caso ){		//var caso 1 si es procedimiento registro, 2 para donaciones
	FILE *archivo = fopen("usuarios.txt", "rt");										//abriendo archivo
	if (archivo == NULL){			//si el archivo no existe
		fclose(archivo);
		if (caso == 1) return 1;	//para el proceso de registro, indica que es el primer usuario por lo tanto, la ci es valida
		if (caso == 2) {			//para el proceso de donaciones, indica no hay datos registradps
			printf("No hay datos regisitrado.\n");
			//retornar al menu principal
			return 0;
		}	 
	}
    fclose(archivo);
	int clave;
    sscanf(ci, "%d", &clave);
    TablaHash *tabla = leer_tabla_hash();
	//leer cedula
    int verificacion;
    verificacion = verificar_cedula(tabla, clave);

    if (caso == 1)	{
        if (verificacion == 0){
            return 1; //la cedula es valida para el registro porque no se encuantra en la data
        }
        else{
            printf("\nEl usuario ya se encuentra registrado\n");
            return 0;
        }	
    }
    if ( caso == 2){
        if (verificacion == 1){
            printf("\nBienvenido al programa");
            return 1;
        }
        else{
            printf("La cedula no se encuentra registrada. Intende de nuevo. \n"); 
            return 0; //indica que no es valida para la donacion ya que no se encuentra registrada
        }			
    }
}



void EscribirEnArchivoTXT(const char *nombreArchivo, TablaHash *tabla){
    FILE *file = fopen("usuarios.txt", "at");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    fclose(file);
    guardarTablaHash(tabla);
    CianSetColor(); printf("\nUsuario Registrado exitosamente.\n\n");
    blancoSetColor(); printf("Volviendo Al Inicio. Presione para continuar..\n"); getchar();
}

TablaHash *obtener_datos_perfil(){
    FILE *file = fopen("usuarios.txt","at");
    fclose(file);
    TablaHash *tabla = crear_tabla();
    char ci[15];
    int cedula;
    char nombre[30];
    int edad;
    char edades[8];
    int peso;
    char pesos[10];
    int altura;
    char alturas[10];
    int valido;  
	do{                                                                   //validando ci
        do{                                                               //validando que solo contenga numeros
            valido = 1;
            printf("Ingrese su cedula: "); 
            fgets(ci, 15, stdin);
            ci[strcspn(ci, "\n")] = '\0';
            valido = !cadenaVacia(ci);
            for (int i = 0; ci[i] != '\0'; i++){
                if (!isdigit(ci[i])){
                    printf("La cédula solo debe contener números. Intente de nuevo.\n");
                    valido = 0;
                    break;
                }
            }
        } while (valido == 0);
	}while(validarCI(ci, 1) == 0);

    do{                                                                       //validando nombre
        valido = 1;
        printf("Ingrese su nombre: "); 
        fgets(nombre, 25, stdin);
        nombre[strcspn(nombre, "\n")] = '\0';
        valido = !cadenaVacia(nombre);
        for (int i = 0; nombre[i] != '\0'; i++){
            if (!isalpha(nombre[i]) && nombre[i] != ' ' ){
                printf("El nombre solo debe contener letras. Intente de nuevo.\n");
                valido = 0;
                break;
            }
        }
    }while(valido == 0);

    do{                                                         //validar telefono
        valido = 1;
        printf("Ingrese su edad: "); 
        fgets(edades, 7, stdin);
        edades[strcspn(edades, "\n")] = '\0';
        valido = !cadenaVacia(edades);
        for (int i = 0; edades[i] != '\0'; i++){
            if (!isdigit(edades[i])){
                printf("La edad solo debe contener numeros enteros. Intente de nuevo\n");
                valido = 0;
                break;
            }
        }
    } while (valido == 0);

    do{                                                         //validar telefono
        valido = 1;
        printf("Ingrese su peso (Kg): "); 
        fgets(pesos, 7, stdin);
        pesos[strcspn(pesos, "\n")] = '\0';
        valido = !cadenaVacia(pesos);
        for (int i = 0; pesos[i] != '\0'; i++){
            if (!isdigit(pesos[i])){
                printf("El peso debe ser entero (Redondeelo en caso de necesitarlo).\n");
                valido = 0;
                break;
            }
        }
    } while (valido == 0);

    do{                                                         //validar telefono
        valido = 1;
        printf("Ingrese su altura (cm): "); 
        fgets(alturas, 7, stdin);
        alturas[strcspn(alturas, "\n")] = '\0';
        valido = !cadenaVacia(alturas);
        for (int i = 0; alturas[i] != '\0'; i++){
            if (!isdigit(alturas[i])){
                printf("La altura debe ser entera y en cm.\n");
                valido = 0;
                break;
            }
        }
    } while (valido == 0);

    sscanf(edades,"%d",&edad);
    sscanf(alturas,"%d",&altura);
    sscanf(pesos, "%d",&peso);
    sscanf(ci, "%d",&cedula);
    tabla = insertar_tabla_hash(tabla,cedula,nombre,edad,altura,peso);
    limpearBuffer();
	return tabla;
}


void menu_login(){
    FILE *f;
    f = fopen("usuarios.txt","at");
    fclose(f);
    printf("\033[34m");  printf("\n\n");// setea a color azul 
    printf("*********************************************************\n");
    printf("*                                                      *\n");
    printf("  *              ¡Bienvenido!            *\n");
    printf("*                                                      *\n");
    printf("*********************************************************\n");   
    printf("\n\n"); printf("\033[0m"); //setea a blanco

    int opcion1;
    do {
        limpearBuffer();
    //MENU
        printf("\n--- Menu ---\n");
        printf("1. Registrarse\n");
        printf("2. Iniciar sesion\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion1);
        limpearBuffer();  // Para limpiar el buffer de entrada después de scanf
        switch (opcion1){
            case 1:
                TablaHash *tabla = obtener_datos_perfil();
                EscribirEnArchivoTXT("usuarios.txt",tabla);
                break;
            case 2:
                char ci[15];
                int valido;
                do{                                                                   //validando ci
                    do{                                                               //validando que solo contenga numeros
                        valido = 1;
                        printf("Ingrese su cedula: "); 
                        fgets(ci, 15, stdin);
                        ci[strcspn(ci, "\n")] = '\0';
                        valido = !cadenaVacia(ci);
                        for (int i = 0; ci[i] != '\0'; i++){
                            if (!isdigit(ci[i])){
                                printf("La cédula solo debe contener números. Intente de nuevo.\n");
                                valido = 0;
                                break;
                            }
                        }
                    } while (valido == 0);
	            }while(validarCI(ci, 2) == 0);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    }while(opcion1 != 0);

}
int main(){
    menu_login();
    return 0;
}

