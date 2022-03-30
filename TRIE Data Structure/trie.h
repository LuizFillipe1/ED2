#ifndef TRIE_H
#define TRIE_H
#define TAMANHO 256 //Definição da quantidade de caracteres possíveis na árvore (tabela ASCII)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Estrutura responsavel por armazenar a estrutura trie
typedef struct trie{
    struct trie * filhos[TAMANHO];
    bool estado;
}trie;


/*Função que cria um nó, alocando cada nó correspondente ao tamanho da ASCII, setando inicialmente todos os estados para false (livre)*/
trie *cria_no();
/*Função booleana que irá fazer uma busca na estrutura trie a partir de uma chave informada pelo usuário, retornando true se encontrou e
false caso contrário*/
bool busca_trie(trie *T, char* palavra);
/*Função booleana que irá realizar a inserção na estrutura/árvore a partir de uma chave informada pelo usuario. Caso a chave já esteja contida na estrutura,
a função irá retorna false, no qual indicará erro na inserção*/
bool insere_trie(trie **T, char *palavra);
/*Função ultilizada apenas na trie.c a com irá ser chamada pela função "mãe" print_trie no qual, recurssivamente, irá percorrer toda estrutra buscando
elementos as quais são terminador pelo estado (true) e armazenando os caracteres em um char a fim de ser impresso ao usuário */
void print_trie_recurssiva(trie *node, unsigned char *prefixo, int comprimento) ;
/*Função mãe que irá ser utilizada pelo usuário, recebendo como paremetro a raiz da estrutura, a fim de chamar a função filha (print_trie_recurssiva) */
void print_trie(trie* T);
/*Função do tipo struct trie que irá ser chamada pela função remove_trie no qual é responsável por remover uma chave da estrutura trie utilizando a recurssividade*/
trie* remove_trie_recurssiva(trie *T, unsigned char* texto, bool* deletado);
/*Função mãe booleana que irá chamar a remove_trie_recurssiva, recebendo como paremetro um ponteiro para ponteiro da raiz da estrutura e um ponteiro char que é a chave a ser removida*/
bool remove_trie(trie** T, char *palavra);
/*Função booleana que recebe como parametro um ponteiro de algum nó da estrutura e reporta se é filho ou não de alguem */
bool no_eh_filho(trie* T);
/*Função booleana que retorna se a estrutura trie está vazia ou não*/
bool verifica_vazio_trie(trie* T);
/*Função mãe booleana que irá receber como paramêtro a raiz da árvore que irá chamar a filha tamanho_trie_recurssiva e retornar se a estrutura está vazia ou não*/
void tamanho_trie(trie* T);
/*Função do tipo void que era ser responsavél por percorrer toda a estrutura e ir armazenando na variavel contagem, a ocorrencia de chaves/elementos contidos na árvore*/
void tamanho_trie_recurssiva(trie *T, unsigned char *prefixo, int comprimento, int *contagem);
/*Função que irá receber como paramêtro um prefixo palavra e a raiz da estrutura. Nela irá percorrer toda estrutura e ir imprimindo as palavras com o prefixo passado como parâmetro */
bool busca_prefixo(trie *T, char* palavra);

#endif
