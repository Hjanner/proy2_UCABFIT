#include "funciones.h"

// Estructura para almacenar información del usuario
typedef struct {
    char nombre[50];
    unsigned edad;
    float altura;
    float peso;
} Usuario;

// Estructura para almacenar información de la actividad física
typedef struct {
    char fecha[11]; // Formato: "YYYY-MM-DD"
    char tipo[50];
    int duracion; // en minutos
    float distancia; // en km
} Actividad;

// Función para importar datos de usuarios desde un archivo TXT
Usuario* importarUsuarios(const char* archivo, int* numUsuarios) {
    FILE* fp = fopen(archivo, "r");
    if (!fp) {
        perror("Error al abrir el archivo de usuarios");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", numUsuarios);
    Usuario* usuarios = (Usuario*) malloc((*numUsuarios) * sizeof(Usuario));

    for (int i = 0; i < *numUsuarios; i++) {
        fscanf(fp, "%s %d %f %f", usuarios[i].nombre, &usuarios[i].edad, &usuarios[i].altura, &usuarios[i].peso);
    }

    fclose(fp);
    return usuarios;
}

// Función para exportar datos de usuarios a un archivo TXT
void exportarUsuarios(const char* archivo, Usuario* usuarios, int numUsuarios) {
    FILE* fp = fopen(archivo, "w");
    if (!fp) {
        perror("Error al abrir el archivo para escritura de usuarios");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d\n", numUsuarios);
    for (int i = 0; i < numUsuarios; i++) {
        fprintf(fp, "%s %d %f %f\n", usuarios[i].nombre, usuarios[i].edad, usuarios[i].altura, usuarios[i].peso);
    }

    fclose(fp);
}

// Función para importar datos de actividades desde un archivo TXT
Actividad* importarActividades(const char* archivo, int* numActividades) {
    FILE* fp = fopen(archivo, "r");
    if (!fp) {
        perror("Error al abrir el archivo de actividades");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", numActividades);
    Actividad* actividades = (Actividad*) malloc((*numActividades) * sizeof(Actividad));

    for (int i = 0; i < *numActividades; i++) {
        fscanf(fp, "%s %s %d %f", actividades[i].fecha, actividades[i].tipo, &actividades[i].duracion, &actividades[i].distancia);
    }

    fclose(fp);
    return actividades;
}

// Función para exportar datos de actividades a un archivo TXT
void exportarActividades(const char* archivo, Actividad* actividades, int numActividades) {
    FILE* fp = fopen(archivo, "w");
    if (!fp) {
        perror("Error al abrir el archivo para escritura de actividades");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d\n", numActividades);
    for (int i = 0; i < numActividades; i++) {
        fprintf(fp, "%s %s %d %f\n", actividades[i].fecha, actividades[i].tipo, actividades[i].duracion, actividades[i].distancia);
    }

    fclose(fp);
}

// Función principal para demostrar la importación y exportación de datos
int main() {
    int numUsuarios, numActividades;
    Usuario* usuarios = importarUsuarios("usuarios.txt", &numUsuarios);
    Actividad* actividades = importarActividades("actividades.txt", &numActividades);


    // Exportar los datos (se puede hacer después de procesarlos)
    exportarUsuarios("usuarios_exportados.txt", usuarios, numUsuarios);
    exportarActividades("actividades_exportadas.txt", actividades, numActividades);

    // Liberar memoria
    free(usuarios);
    free(actividades);

    return 0;
}