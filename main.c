#include "funciones.h"

void limpiarTermial(){
    getchar(); 
    //system("clear");
    //system("tput clear");
    //printf("\033[2J");
    //printf("\f");
    system("cls");
}

void bienvenida(){
    printf("\033[34m");  printf("\n\n");// setea a color azul 
    printf("*********************************************************\n");
    printf("*                                                      *\n");
    printf("  *              ¡Bienvenido a UCAB FIT!            *\n");
    printf("*                                                      *\n");
    printf("*********************************************************\n");   
    printf("\n\n"); printf("\033[0m"); //setea a blanco

    printf("En UCAB FIT, puedes:\n");
    printf("- Rastrear tus pasos diarios, distancia y calorías quemadas.\n");
    printf("- Establecer metas y desafíos de fitness personalizados.\n");
    printf("- Ganar recompensas e insignias por tus logros.\n");
    printf("- Competir con amigos y familiares en la tabla de posiciones.\n"); printf("\n");
    printf("¡Empieza a moverte y alcanza tus metas de fitness con UCAB FIT!\n"); printf("\n"); getchar();
    system("cls");
}

void header(){
    printf("\033[34m");  printf("\n\n");// setea a color azul 
    printf("****************** UCAB FIT ******************\n"); 
    printf("\n"); printf("\033[0m"); //setea a blanco
}

int menuInicio(){
    header();
    int opMenu, userValido;
    printf("Bienvenido al sistema de UCAB FIT\n");
    printf("1. Ingresar\n");
    printf("2. Registrarse\n");
    printf("3. Salir\n");
    printf("\n");
    amarilloSetColor(); printf("Seleccione una opción: "); blancoSetColor();
    scanf("%i", &opMenu); limpearBuffer();  // Para limpiar el buffer de entrada después de scanf
    
    switch (opMenu)
    {
    case 1:
        printf("es valido?"); 
        scanf("%i", &userValido); limpearBuffer();
        if (userValido){
            limpiarTermial(); 
            return 1;
        }
            limpiarTermial();
            return 0;
        break;
    case 2: 
        printf("ejecutar registro"); limpiarTermial();
        break;  
    case 3: 
        printf("Saliendo.."); limpiarTermial();
        return 0;               //retornar null
        break; 
    default:
        printf("Opción no válida. Intente de nuevo.\n"); getchar(); 
        menuInicio();
        break;
    }
}

void menuRegistroAct(tusuario *persona){
    header();
    tactividad *actividad = ObtenerDatosActividades(persona);
    tactividad *arbol = leerArbolActividad(archivoActividadesName);
    guardarDatosEnArchivo(archivoActividadesName, arbol, actividad);
}

void Home(tusuario *persona){
    int h = 0;
    do{
        header();
        printf("\033[33m");// setea a color azul 
        printf("**********************************************\n");
        printf("*                                            *\n");
        printf("*                    HOME                    *\n");
        printf("*                                            *\n");
        printf("**********************************************\n");   
        printf("\n"); printf("\033[0m"); //setea a blanco    printf("1. Ver Perfil\n");                                  //modificar
        printf("1. Ver Perfil\n");                         //registrar
        printf("2. Registrar Actividad\n");                         //registrar
        printf("3. Monitorear Actividades\n");                      //monitoreo
        printf("4. Ver Análisis de Rendimiendo\n");                 //analisis
        printf("5. Cerrar App\n");    printf("\n");
        printf("Seleccione una opción: ");
        int opHome;
        scanf("%i", &opHome); limpearBuffer();
        switch (opHome) {
            case 1:
                printf("ver peril");                    limpiarTermial();
                break;
            case 2:
                menuRegistroAct(persona);               limpiarTermial();
                break;
            case 3:
                printf("monitorearActividades();");     limpiarTermial();
                break;
            case 4:
                printf("verAnalisisRendimiento();");    limpiarTermial();
                break;
            case 5:
                h = 1;
                printf("\n¡Gracias por usar UCAB FIT! Saliendo del sistema...\n"); limpiarTermial();
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n"); limpiarTermial();
                Home(persona);
            }
    } while ( h != 1);
}

int main(){
    bienvenida();
    //int persona = menuInicio();         //aqui tiene que ir los datos de la persona
    tusuario *persona = (tusuario*)malloc(sizeof(tusuario));
    strcpy(persona->nombre, "Pedro");
    persona->ci = 23790848;
    persona->altura = 190;
    persona->peso = 80;
    persona->edad = 20;
    persona->genero = MASCULINO;



    if (persona)
        Home(persona);
    
    //limpear variables
    return 0;
}
