#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "gerenciamento_livros.h"

void listarbib(Biblioteca *bib){

    Livro *aux = bib->inicio;
    int i = 1;

    if(bib->inicio != NULL){

        while(aux != NULL){

            printf("%d. Codigo: %u | Titulo: %s | Autor: %s | Quantidade: %u\n", 
                i, aux->codigo, aux->titulo, aux->autor, aux->qtd);
            i++;
            aux = aux->prox_livro;
        }
    } else{
        printf("Biblioteca vazia!\n");
    }
}

void consulta_livro(Biblioteca *bib, unsigned int codigo){

    Livro *aux = bib->inicio;

    while(aux != NULL && aux->codigo != codigo){
        aux = aux->prox_livro;
    }

    if(aux == NULL){
        printf("Livro nao encontrado :(\n");

    } else{
            printf("--%s==\n", aux->titulo);
            printf("Autor: %s\nAno: %u\n", aux->autor, aux->ano);
            printf("Sinopse:\n%s\n", aux->sinopse);

            if(aux->qtd > 0){
                printf("\nBoa noticia! Temos %u exemplares disponiveis!\n", aux->qtd);
            } else{
                printf("\nNao temos copias disponiveis, volte outro dia :(\n");
            }           
    }

}

void emprestimo_devolucao(Biblioteca *bib, unsigned int codigo, unsigned int opcao){

    Livro *aux = bib->inicio;

    while(aux != NULL && aux->codigo != codigo){
        aux = aux->prox_livro;
    }

    if(aux == NULL){
        printf("Livro nao encontrado :(\n");
        return;
    }

    if(opcao == 1){
        // emprestimo

        if(aux->qtd > 0){
        aux->qtd--;
        aux->emprestados++;
            printf("Emprestimo realizado com sucesso!!\n");
        } else{
            printf("Nao temos exemplares disponiveis :(\n");
        }

    } else{
        // devolucao

        if(aux->emprestados > 0){
            aux->emprestados--;
            aux->qtd++;
            printf("Devolucao realizada com sucesso!\n");
        } else{
            printf("Erro! O livro ja foi devolvido ou nunca foi emprestado!\n");   
        }

    } 
}

void removerlivro(Biblioteca *bib, unsigned int codigo){

    if(bib->inicio == NULL){ 
        printf("Livro nao encontrado! Biblioteca vazia!\n");
        return;
    }

    Livro *aux = bib->inicio, *aux2;

    if(aux->codigo == codigo){

        bib->inicio = aux->prox_livro;
        free(aux);
        bib->tam--;
        printf("Livro removido :)\n");

    } else{

        while(aux != NULL && aux->codigo != codigo){
            aux2 = aux;
            aux = aux->prox_livro;
        }

        if(aux == NULL){
            printf("Livro nao encontrado :(\n");
        } else{
            aux2->prox_livro = aux->prox_livro;
            free(aux);
            bib->tam--;
            printf("Livro removido :)\n");
        }
    }
}

void liberarbiblioteca(Biblioteca *bib){
    Livro *aux = bib->inicio; Livro *aux2;

    while(aux != NULL){
        aux2 = aux->prox_livro;
        free(aux);
        aux = aux2;
    }

    bib->inicio = NULL;
    bib->tam = 0;
}