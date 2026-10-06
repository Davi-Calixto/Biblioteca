# Sistema de Biblioteca em C

Programa de terminal para gerenciar o acervo de uma biblioteca, escrito em C. Os livros são armazenados em uma lista simplesmente encadeada, em memória.

## Funcionalidades

- Cadastrar livros no início ou no final da lista
- Listar todos os livros
- Consultar um livro pelo código
- Emprestar e devolver exemplares
- Remover um livro pelo código

Cada livro possui: código, título, autor, sinopse, ano e quantidade de exemplares.

## Requisitos

Compilador C com suporte a C99 ou superior (por exemplo, GCC).

## Compilação e execução

```
gcc -Wall -Wextra -o biblioteca biblioteca.c
./biblioteca
```

## Uso

O programa exibe um menu e repete até que a opção 0 seja escolhida:

```
1 - Cadastrar livro
2 - Listar livros
3 - Consultar livro
4 - Emprestar livro
5 - Devolver livro
6 - Remover livro
0 - Sair
```

| Opção | Comportamento |
|-------|---------------|
| 1 | Pergunta se o livro entra no início (1) ou no final (0) da lista e solicita os dados do livro. |
| 2 | Lista código, título, autor e quantidade de cada livro. |
| 3 | Exibe título, autor, ano, sinopse e disponibilidade do livro com o código informado. |
| 4 | Reduz em um a quantidade de exemplares, se houver exemplar disponível. |
| 5 | Aumenta em um a quantidade de exemplares. |
| 6 | Remove da lista o livro com o código informado. |

Valores numéricos são lidos linha a linha e validados. Entradas inválidas (texto, valores negativos ou fora do intervalo de `unsigned int`) fazem o programa pedir uma nova digitação.

## Detalhes de implementação

- Lista simplesmente encadeada: `Livro` representa cada nó e `Biblioteca` guarda o início da lista e o tamanho.
- Alocação dinâmica com `malloc`, com verificação de falha, e liberação do nó com `free` na remoção.
- Leitura numérica com `fgets` e `strtol`, sem uso de `scanf`.
- Tratamento de fim de entrada (EOF) em todas as leituras.

## Limitações conhecidas

- O getchar devolvendo int pode travar em loop infinito em plataformas ARM 
- A 'ler_uint' apresenta comportamento indefinido caso o limite de 99 caracteres seja ultrapassado
- Remover o último livro também mostra a mensagem "biblioteca vazia"
- No cadastro qualquer posição != 1 vai para o final

## Estrutura do repositório

```
biblioteca.c   código-fonte
README.md      este arquivo
```
