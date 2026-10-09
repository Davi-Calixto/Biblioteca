#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "adicionar_livro.h"

int add_livro_inicio(Biblioteca *bib){

    unsigned int cod, ano, qtd;
    char autor[100], titulo[100], sinopse[100];

    if(!ler_livro(titulo, autor, sinopse, &ano, &qtd, &cod, bib)){
        return 0;
    }

    Livro *novo = malloc(sizeof(Livro)); 
    
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        return 0;
    }

    novo->codigo = cod;
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    strcpy(novo->sinopse, sinopse);
    novo->ano = ano;
    novo->qtd = qtd;
    novo->emprestados = 0;
    novo->prox_livro = bib->inicio;
    bib->inicio = novo;
    bib->tam++;

    printf("-> Livro adicionado :)\n");

    return 1;
}

int add_livro_final(Biblioteca *bib){

    unsigned int cod, ano, qtd;
    char autor[100], titulo[100], sinopse[100];

    if(!ler_livro(titulo, autor, sinopse, &ano, &qtd, &cod, bib)){
        return 0;
    }
        
    Livro *novo = malloc(sizeof(Livro));

    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        return 0;
    }

    Livro *aux = bib->inicio;

    novo->codigo = cod;
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    strcpy(novo->sinopse, sinopse);
    novo->ano = ano;
    novo->qtd = qtd;
    novo->emprestados = 0;

    if(bib->inicio == NULL){

        bib->inicio = novo;
        novo->prox_livro = NULL;
        bib->tam++;

    } else{
        while(aux->prox_livro != NULL){
            aux = aux->prox_livro;
        }

        aux->prox_livro = novo;
        novo->prox_livro = NULL;
        bib->tam++;
    }

    printf("-> Livro adicionado :)\n");

    return 1;

}