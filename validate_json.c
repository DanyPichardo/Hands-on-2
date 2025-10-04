#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "states_json.h"

int alfabetico(const char *str){
    for (int i = 0; str[i] != '\0'; i++){
        if (!isalpha(str[i])){
            return 0;
        }
    }
    return 1;
}

int alfanumerico (const char *str){
    if (!isalpha(str[0])){
        return 0;
    }
    for (int i = 1; str[i] != '\0'; i++){
        if (!isalnum(str[i])){
            return 0;
        }
    }
    return 1;
}

const char* cadenas(const char *ptr, char *buffer){
    if (*ptr != '\"'){
        return NULL;
    }
    ptr++;
    int i = 0;
    while (*ptr != '\"' && *ptr != '\0'){
        buffer[i++] = *ptr;
        ptr++;
    }
    if (*ptr != '\"'){
        return NULL;
    }
    buffer[i] = '\0';
    return ptr+1;
}

int validarJ(const char *input){
    State st = INICIO;
    const char *ptr = input;
    char buffer[128];

    while (*ptr != '\0'){
        switch (st){
        case INICIO:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == '{'){
                st = ABRE_LLAVE_CLASE;
                ptr++;
            } else {
                return 0;
            }
            break;
        
        case ABRE_LLAVE_CLASE:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (strncmp(ptr, "\"employees\"", 11) == 0){
                ptr += 11;
                st = CLASE_KEY;
            } else {
                return 0;
            }
            break;
        
        case CLASE_KEY:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == ':'){
                st = DOS_PUNTOS_CLASE;
                ptr++;
            } else {
                return 0;
            }
            break;

        case DOS_PUNTOS_CLASE:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == '['){
                st = ABRE_ARRAY;
                ptr++;
            } else {
                return 0;
            }
            break;

        case ABRE_ARRAY:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == '{'){
                st = ABRE_LLAVE_OBJETO;
                ptr++;
            } else {
                return 0;
            }
            break;

        case ABRE_LLAVE_OBJETO:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (strncmp(ptr, "\"firstName\"", 11) == 0){
                ptr += 11;
                st = NOMBRE_KEY;
            } else {
                return 0;
            }
            break;

        case NOMBRE_KEY:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == ':'){
                st = DOS_PUNTOS_NOMBRE;
                ptr++;
            } else {
                return 0;
            }
            break;

        case DOS_PUNTOS_NOMBRE:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == '\"'){
                ptr = cadenas(ptr, buffer);
                if (!ptr || !alfabetico(buffer)){
                    return 0;
                }
                st = NOMBRE_VALUE;
            } else {
                return 0;
            }
            break;

        case NOMBRE_VALUE:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == ','){
                ptr++;
                st = COMA_NOMBRE;
            } else if(*ptr == '}'){
                st = CIERRA_OBJETO;
                ptr++;
            } else {
                return 0;
            }
            break;
        
        case COMA_NOMBRE:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (strncmp(ptr, "\"lastName\"", 10) == 0){
                ptr += 10;
                st = APELLIDO_KEY;
            } else {
                return 0;
            }
            break;

        case APELLIDO_KEY:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == ':'){
                st = DOS_PUNTOS_APELLIDO;
                ptr++;
            } else {
                return 0;
            }
            break;

        case DOS_PUNTOS_APELLIDO:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == '\"'){
                ptr = cadenas(ptr, buffer);
                if (!ptr || !alfabetico(buffer)){
                    return 0;
                }
                st = APELLIDO_VALUE;
            } else {
                return 0;
            }
            break;

        case APELLIDO_VALUE:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == '}'){
                st = CIERRA_OBJETO;
                ptr++;
            } else {
                return 0;
            }
            break;

        case CIERRA_OBJETO:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == ','){
                ptr++;
                st = ABRE_ARRAY;
            } else if (*ptr == ']'){
                st = CIERRA_ARRAY;
                ptr++;
            } else {
                return 0;
            }
            break;

        case CIERRA_ARRAY:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            if (*ptr == '}'){
                st = ACEPTADO;
                ptr++;
            } else {
                return 0;
            }
            break;

        case ACEPTADO:
            if (isspace(*ptr)){
                ptr++;
                break;
            }
            return 0;   

        default:
            return 0;
        }
    }

    return st == ACEPTADO;

}