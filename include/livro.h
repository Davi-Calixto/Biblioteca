#ifndef LIVRO_H
#define LIVRO_H

//structs do projeto e funções de existelivro e ler livro

typedef struct Livro{
    unsigned int codigo;
    char titulo[100];
    char autor[100];
    unsigned int ano;
    unsigned int qtd;
    char sinopse[100];
    unsigned int emprestados;
    struct Livro *prox_livro;
} Livro;

typedef struct{
    Livro *inicio;
    unsigned int tam;
} Biblioteca;

int existelivro(Biblioteca *bib, unsigned int codigo);
int ler_livro(char titulo[], char autor[], char sinopse[], unsigned int *ano, unsigned int *qtd, unsigned *cod, Biblioteca *bib);

#endif