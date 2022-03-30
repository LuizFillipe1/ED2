#ifndef BMAIS_H
#define BMAIS_H


#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define GRAU 2

/* Struct do artigo*/
typedef struct{
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[20];
    char palavraChave[200];
}artigo;

/* Struct do artigo da arvore*/
typedef struct node{
	int chave[2 * GRAU - 1];        //índice
	struct node* filho[2 * GRAU];   //Vetor de paginas filhas
	int folha;                      //Se a página é folha ou não (1 = TRUE (é folha))
	int n;                          //Numero de chaves contidas na pagina
	artigo infor [2 * GRAU - 1];    //Vetor que armazena as informações do struct artigo
	struct node* next;              //Lista encadeada

}
node;
/*Struct que criar uma raiz*/
typedef struct Bmais{
	node* root;
}Bmais;

/*Função que solicita ao usuario as informações a serem inseridas
    a partir do ponteiro para o artigo passado como parametro*/
void pedeArtigo(artigo *art);
/*Função que insere na arvore B+ o índice k e o artigo art, passados como paremetrôs*/
void bMaisInsere(Bmais* T, int k,artigo* art);
/* Função que é chamada na função bMaisInsere que insere o artigo e o índice em uma página que está com espaço vago */
void bMaisInsereNaoCheio(node* x, int k, artigo *art);
/* Cria uma árvore B+ inicialmente vazia */
void criarArvore(Bmais* T);
/* Funcão que realiza a cisão na página cheia a fim de inserir um artigo */
void bMaisCisao(node* x, int i,artigo *art);
/* Função principal de remoção, a qual irá realizar a remoção e a verificar a situação
    da página após a remoção a fim de normalizada de acordo com as espeficicações da árvore b+*/
void bMaisRemove_main(node* x, int k);
/*Função que irá chamar a imprime bMaisImprimeFolhas passando como parametro a raiz da árvore que irá ser impressa */
void passaRaizImpressao(Bmais* T);
/*Função que imprime a arvore recebendo como parametro a raiz dela*/
void imprimeArvore(node* x, int h);
/*Função que faz a cisão da arvore*/
void bCisao(node* x, int i);
/*Função inicial que irá chamar a função principal bMaisRemove_main a fim de realizar a remoção da chave*/
void bMaisRemove(Bmais* T, int k);
/*Função que recebe como paramêtro a raiz da árvore e imprime todas as suas folhas que contem a informação*/
void bMaisImprimeFolhas(Bmais* x);
/*Função que recebe como paramêtro a raiz da árvore e uma inteiro y que é a chave a ser buscada. Nela se for encontrada
    a chave na ávore, irá imprimir a sua respectiva informação*/
void mostraArtigo(Bmais* T ,int y);
/*Função que faz um busca simples para ver se há a chave na árvore, retornando se encontrou ou não como inteiro*/
int bMaisBuscaSimples(Bmais* T, int x,int encontrou);
/*Função que imprime a lista encadeada das folhas a partir da chave informada pelo usuario passada como paramêtro */
void bMaisImprimeFolhasApartirDaChave(Bmais* T, int chave);

#endif
