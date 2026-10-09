#ifndef GERENCIAMENTO_LIVROS_H
#define GERENCIAMENTO_LIVROS_H
#include "livro.h"

//funções de listar, consulta, emprestimo, remoção e liberar

void listarbib(Biblioteca *bib);
void consulta_livro(Biblioteca *bib, unsigned int codigo);
void emprestimo_devolucao(Biblioteca *bib, unsigned int codigo, unsigned int opcao);
void removerlivro(Biblioteca *bib, unsigned int codigo);
void liberarbiblioteca(Biblioteca *bib);

#endif