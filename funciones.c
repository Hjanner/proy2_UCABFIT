#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct actividades
{

}tactividad;


//GENERALES
void limpearBuffer(){
    char buffer[100]; 
    fgets(buffer, sizeof(buffer), stdin);	    // Limpiar buffer de entrada
}
