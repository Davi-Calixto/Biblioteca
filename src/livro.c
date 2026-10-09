#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "livro.h"
#include "tratamento_erros.h"

int existelivro(Biblioteca *bib, unsigned int codigo){

    if(bib->inicio == NULL){
        return 0;
    }

    Livro *aux = bib->inicio;

    while(aux->codigo != codigo && aux->prox_livro != NULL){
        aux = aux->prox_livro;
    }

    if(aux->codigo == codigo){
        return 1;
    } 

    return 0;
}

int ler_livro(char titulo[], char autor[], char sinopse[], unsigned int *ano, unsigned int *qtd, unsigned *cod, Biblioteca *bib){

    printf("-> Informe o código do livro:\n");

        if(!ler_uint(cod)){
            return 0;
        }

        if(existelivro(bib, *cod)){
            printf("Codigo já existente!\n");
            return 0;
        }

    printf("-> Informe o titulo do livro:\n");

        if(fgets(titulo, 100, stdin) == NULL){
            return 0;
        }

        if(titulo[0] == '\n'){
            printf("Erro! Titulo vazio!\n");
            return 0;
        }

        if(strchr(titulo, '\n') == NULL){
            if(limpar_buffer() != 0){
                printf("Digite um titulo menor!(0-99)\n");
                return 0;
            }
        }

            titulo[strcspn(titulo, "\n")] = '\0';

    printf("-> Informe o autor do livro:\n");

        if(fgets(autor, 100, stdin) == NULL){
            return 0;
        }

        if(strchr(autor, '\n') == NULL){
            if(limpar_buffer() != 0){
                printf("Digite um autor menor!(0-99)\n");
                return 0;
            }
        }

            autor[strcspn(autor, "\n")] = '\0';

    printf("-> Escreva uma breve sinopse do livro:\n");

        if(fgets(sinopse, 100, stdin) == NULL){
            return 0;
        }

        if(strchr(sinopse, '\n') == NULL){
            if(limpar_buffer() != 0){
                printf("Digite uma sinopse menor!(0-99)\n");
                return 0;
            }
        }

            sinopse[strcspn(sinopse, "\n")] = '\0';

    printf("-> Informe o ano do livro:\n");

        if(!ler_uint(ano)){
            return 0;
        }

    printf("-> Informe a quantidade de exemplares do livro:\n");

        if(!ler_uint(qtd)){
            return 0;
        }

    return 1;
}