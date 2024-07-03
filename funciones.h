#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "funciones.c"
//#include "main.c"

//funciones generales
void limpearBuffer();
int cadenaVacia(const char *aux);
void azulSetColor();
void amarilloSetColor();
void blancoSetColor();
void saltoLinea();


//  MAnin
// void bienvenida();
// void limpiarTerminal();
// void header();
// void Home(tusuario *persona);
// int menuInicio();
// void monitorearActividades();
// void verAnalisisRendimiento();
// void menuRegistroAct(tusuario *persona);


//REGISTRO ACTIVIDAD
void liberarArbolActividad(tactividad* raiz);
int tomarDistancia();
int tomarTiempo();
tfecha ObtenerFecha();
tfecha ObtenerFecha();
tactividad *ObtenerDatosActividades(tusuario *persona);
void imprimirActividad(tactividad *actividad);
tactividad *insertarActividad(tactividad *arbol, tactividad *actividad);
tactividad *leerArbolActividad(const char *filename);
void guardarActividad(FILE *file, tactividad *arbolActividad, tactividad *actividad);
void guardarDatosEnArchivo(const char *filename, tactividad *arbol, tactividad *arbolActividad);




#endif /* LIBRERIA_H */