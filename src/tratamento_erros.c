#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "tratamento_erros.h"

int limpar_buffer() {

    int buffer = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF){
        buffer = 1;
    }   

    return buffer;
}

int ler_uint(unsigned int *valor){

        char entrada[100];
        char *fim;
        long numero;
        
        while(1) {

            if(fgets(entrada, sizeof(entrada), stdin) == NULL){
                return 0;
            }

            errno = 0;
            numero = strtol(entrada, &fim, 10);

            if(fim != entrada && 
                *fim == '\n' &&
                 errno == 0 &&
                  numero >= 0 && 
                  numero <= UINT_MAX) {
                    
                *valor = (unsigned int) numero;
                return 1;

            } else{
                printf("Entrada invalida. Digite um numero:\n");
            }
        }
        
}