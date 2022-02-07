#include <stdio.h>
#include <stdlib.h>

//enum para as cores dos nós da arvore rubro-negra
typedef enum COR {
    VERMELHO, PRETO
} color;

typedef enum boolean{
    /* Boolean usado para tratamentos */
    false,
    true
}bool;

typedef struct redBlack{
    //arvore rubro negra
    void * chave; //dado VOID para a chave
    color  cor;    // cor rubro/negro
    struct redBlack * esquerda; //lado esquerdo da arvore
    struct redBlack *direita; //lado direito da arvore
    struct redBlack *pai; //pai do no
}redBlack;

redBlack * vazio; //declaração da variavel globlal sentinela T.nill

redBlack * novoNo();
void insereRedBlack(redBlack** pt, void* conjuChave, int (*compara)(void*, void*));
void rubroRFixUp(redBlack **pt, redBlack* x);
void rubroIFixUp(redBlack **arvore, redBlack* no);
void freeArvore(redBlack * arvore);
redBlack * maiorRedBlack(redBlack* pt);
int alturaRedblack (redBlack * ptr);
void* getInformacao(redBlack * no);
color getCor(redBlack* no);
redBlack* procuraRedBlack(redBlack * pt, void* infor, int (*compara)(void*, void*));
void rotacaoEsquerda(redBlack ** pt, redBlack *w);
void rotacaoDireita(redBlack ** arvore, redBlack *no);
int quantidadeRedBlack(redBlack *arvore);
void transferePaiRubro(redBlack ** pt, redBlack* u, redBlack*v);
void removeRedBlack(redBlack **pt, redBlack *z);
