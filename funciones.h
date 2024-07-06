#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "funciones.c"
//#include "main.c"

//funciones generales
void limpearBuffer();
int cadenaVacia(const char *aux);
const char* insigniaSTR(tinsignias insignia, int op);
const char* tipoActividadStr(TipoActividad tipo);
const char* tipoGeneroStr(tgenero tipo);
void calcularDistanciaUsuario(tusuario *persona, tactividad *actividad);
void calcularTiempoUsuario(tusuario *persona, tactividad *actividad);
void calcularCaloriasUsuario(tusuario *persona, tactividad *actividad);
void azulSetColor();
void amarilloSetColor();
void blancoSetColor();
void MagentaSetColor();
void CianSetColor();
void rojoSetColor();
void saltoLinea();
void freeTusuario(tusuario *usuario);

//REGISTRO ACTIVIDAD
void liberarArbolActividad(tactividad* raiz);
int tomarDistancia();
int tomarTiempo();
tfecha ObtenerFecha();
void calcularUCABCOIN( tusuario *persona, tactividad *actividad );
void determinarInsigniaNivel(tusuario *persona);
tactividad *ObtenerDatosActividades(tusuario *persona);
void imprimirActividad(tactividad *actividad);
void imprimirArbolActividad(tactividad *actividad);
tactividad *insertarActividad(tactividad *arbol, tactividad *actividad);
tactividad *leerArbolActividad(const char *filename);
void guardarActividad(FILE *file, tactividad *arbolActividad, tactividad *actividad);
void guardarDatosEnArchivo(const char *filename, tactividad *arbol, tactividad *arbolActividad);




#endif /* LIBRERIA_H */