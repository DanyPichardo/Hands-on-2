#ifndef STATES_JSON
#define STATES_JSON

#include <stddef.h>

typedef enum {
    INICIO,
    ABRE_LLAVE_CLASE,
    CLASE_KEY,
    DOS_PUNTOS_CLASE,
    ABRE_ARRAY,
    ABRE_LLAVE_OBJETO,
    NOMBRE_KEY,
    DOS_PUNTOS_NOMBRE,
    NOMBRE_VALUE,
    COMA_NOMBRE,
    APELLIDO_KEY,
    DOS_PUNTOS_APELLIDO,
    APELLIDO_VALUE,
    CIERRA_OBJETO,
    COMA_O_CIERRE,
    CIERRA_ARRAY,
    ACEPTADO
} State;

//Validación de cadenas alfabeticas
int alfabetico(const char *str);

//Validación de cadenas alfanuméricas
int alfanumerico(const char *str);

//Validación de los valores y keys
const char* cadenas(const char *ptr, char *buffer);

//Validación de JSON
int validarJ(const char *input);


#endif