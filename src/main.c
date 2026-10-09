#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "tratamento_erros.h"
#include "livro.h"
#include "adicionar_livro.h"
#include "gerenciamento_livros.h"

int main(){
    unsigned int opcao, aux, codigo;

    Biblioteca bib = {
        .inicio = NULL,
        .tam = 0
    };

    do{
        printf("\n===============\nSistema de Biblioteca\n===============\n\n");

        printf("1 - Cadastrar livro\n2 - Listar livros\n3 - Consultar livro\n4 - Emprestar livro\n5 - Devolver livro\n6 - Remover livro\n0 - Sair\n");
        if(!ler_uint(&opcao)){
            return 0;
        }

        switch(opcao){

            case 1:

                printf("Deseja colocar livro no inicio da biblioteca(1) ou no final(0)?\n");

                if(!ler_uint(&aux)){
                    opcao = 0;
                    break;
                }
                
                if(aux == 1){

                    if(!add_livro_inicio(&bib)){
                        continue;
                    }

                } else if (aux == 0){

                    if(!add_livro_final(&bib)){
                        continue;
                    }

                } else{
                    printf("Erro! Opcao invalida!\n");
                    continue;
                }

                break;

            case 2:

                listarbib(&bib);
                break;
        
            case 3:
            
                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    opcao = 0;
                    break;
                }

                consulta_livro(&bib, codigo);
                break;

            case 4:
            
                aux = 1;
                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    opcao = 0;
                    break;
                }

                emprestimo_devolucao(&bib, codigo, aux);
                break;

            case 5:

                aux = 0;
                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    opcao = 0;
                    break;
                }

                emprestimo_devolucao(&bib, codigo, aux);
                break;
            
            case 6:

                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    opcao = 0;
                    break;
                }

                removerlivro(&bib, codigo);
                break;
                
        }
        
    }while(opcao != 0);

    liberarbiblioteca(&bib);
    return 0;
}