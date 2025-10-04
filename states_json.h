#ifndef STATES_JSON
#define STATES_JSON

#include <stddef.h>

typedef enum {
    INICIO,
    ABRE_LLAVE,
    CLAVE_OBJETO,
    DOS_PUNTOS_OBJETO,
    ABRE_ARRAY,
    ABRE_LLAVE_INSTANCIA,
    ABRE_COMILLAS_NK,
    NOMBRE_KEY,
    CIERRA_COMILLAS_NK,
    DOS_PUNTOS_NOMBRE,
    ABRE_COMILLAS_NV,
    NOMBRE_VALUE,
    CIERRA_COMILLAS_NV,
    COMA_NOMBRE,
    ABRE_COMILLAS_AK,
    APELLIDO_KEY,
    CIERRA_COMILLAS_AK,
    DOS_PUNTOS_APELLIDO,
    ABRE_COMILLAS_AV,
    APELLIDO_VALUE,
    CIERRA_COMILLAS_AV,
    CIERRA_INSTANCIA,
    COMA_O_CIERRE,
    CIERRA_ARRAY,
    ACEPTADO,
    ERROR
} State;

//Validación de cadenas alfabeticas
int alfabetica(const char *str);

//Validación de cadenas alfanuméricas
int alfanumerico(const char *str);

//Validación de JSON
int validarJ(const char *input);


#endif