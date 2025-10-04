#include <stdio.h>
#include <string.h>
#include "states_json.h"

#define MAX_LEN 1024

int main(){
    char input[MAX_LEN];

    while (1){
        printf("\nPara salir escribe 'exit'.\n");
        printf("Ingresa JSON: ");
        if (!fgets(input, MAX_LEN, stdin)){
            break;
        }
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "exit") == 0){
            break;
        }

        if (validarJ(input)){
            printf("El JSON es valido\n");
        } else {
            printf("El JSON es invalido\n");
        }
    }    
}