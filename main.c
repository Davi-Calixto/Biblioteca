#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int limpar_buffer() {

    int buffer = 0;
    char c;
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

        if(titulo[0] = '\n'){
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
                printf("Digite um titulo menor!(0-99)\n");
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
                printf("Digite um titulo menor!(0-99)\n");
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

void listarbib(Biblioteca *bib){

    Livro *aux = bib->inicio;
    int i = 1;

    while(aux != NULL){

        printf("%d. Codigo: %u | Titulo: %s | Autor: %s | Quantidade: %u\n", 
            i, aux->codigo, aux->titulo, aux->autor, aux->qtd);
        i++;
        aux = aux->prox_livro;
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
                printf("Boa noticia!\nTemos %u exemplares disponiveis!\n", aux->qtd);
            } else{
                printf("Nao temos copias disponiveis, volte outro dia :(\n");
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

    } else if(aux->emprestados > 0){
        // devolucao

            aux->qtd++;
            aux->emprestados--;
            printf("Devolucao realizada com sucesso!!\n");
    } else{
        printf("Este livro nunca foi emprestado!\n");
    }
}

void removerlivro(Biblioteca *bib, unsigned int codigo){

    if(bib->inicio == NULL){ 
        printf("Livro nao encontrado! Biblioteca vazia!\n");
        return;
    }

    Livro *aux = bib->inicio, *aux2;

    if(aux->prox_livro == NULL && aux->codigo == codigo){
        free(aux);
        bib->tam--;
        bib->inicio = NULL;
        printf("Biblioteca vazia!\n");

    } else if(aux->codigo == codigo){

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
                    return 0;
                }
                
                if(aux == 1){

                    if(!add_livro_inicio(&bib)){
                        continue;
                    }

                } else{

                    if(!add_livro_final(&bib)){
                        continue;
                    }

                }

                break;

            case 2:

                listarbib(&bib);
                break;
        
            case 3:
            
                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    return 0;
                }

                consulta_livro(&bib, codigo);
                break;

            case 4:
            
                aux = 1;
                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    return 0;
                }

                emprestimo_devolucao(&bib, codigo, aux);
                break;

            case 5:

                aux = 0;
                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    return 0;
                }

                emprestimo_devolucao(&bib, codigo, aux);
                break;
            
            case 6:

                printf("Forneca um codigo:\n"); 

                if(!ler_uint(&codigo)){
                    return 0;
                }

                removerlivro(&bib, codigo);
                break;
                
        }
        
    }while(opcao != 0);

    return 0;
}