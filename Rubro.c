/*Estrutura da dados II
Componentes do grupo:
    - Emanuel Silva Sergio             - 2019107863
    - Luiz Fillipe Oliveira Morais     - 2019107733
    - Vinicius Rodrigues de Cerqueira  - 2019109895
*/

#include <stdio.h>
#include <stdlib.h>
#include "Rubro.h"

redBlack * novoNo(){ //
    // Função que cria um novo nó de árvore rubro negra e o retorna */

    redBlack* no = (redBlack *) malloc(sizeof(redBlack));    //Alocação do nó
    if(!no)
        return NULL;

    no->direita = vazio;
    no->esquerda = vazio;
    no->pai = vazio;
    no->cor = VERMELHO;

    return no;
}
void insereRedBlack(redBlack** pt, void* conjuChave, int (*compara)(void*, void*)){
    // Função para inserir o conjunto void na arvore, recebendo o ponteiro da arvore, a informação generica e a comparação

    if(!conjuChave)
        return;

    redBlack *noInserir = novoNo();
    redBlack *x, *v;

    noInserir->chave = conjuChave;
    v = vazio;
    x = *pt;

    while(x != vazio){
        if(compara(conjuChave, x->chave) == 0)
            return;
        v = x;
        if(compara(conjuChave, x->chave) < 0)
            x = x->direita;
        else
            x = x->esquerda;
    }

    noInserir->pai = v;
    if(v == vazio)
        *pt = noInserir;
    else if(compara(conjuChave, v->chave) < 0)
        v->direita = noInserir;
    else
        v->esquerda = noInserir;

    rubroIFixUp(pt, noInserir);
}
void rubroRFixUp(redBlack **pt, redBlack* x){
    // Função para correção da arvore rubro-negra para manter suas regras.


    if(!pt || *pt == vazio) return;

    redBlack *w;

    while(x!=*pt && x->cor == PRETO){


        if(x == x->pai->esquerda){
            w = x->pai->direita;
            if(w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoEsquerda(pt, x->pai);
                w = x->pai->direita;
            }
            if(w->esquerda->cor == PRETO && w->direita->cor == PRETO){
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{

                if (w->direita->cor == PRETO){
                    w->esquerda->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoDireita(pt, w);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->direita->cor = PRETO;
                rotacaoEsquerda(pt, x->pai);
                x = *pt;
            }
        }
        else{
            w = x->pai->esquerda;
            if(w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoDireita(pt, x->pai);
                w = x->pai->esquerda;
            }
            if(w->direita->cor == PRETO && w->esquerda->cor == PRETO){
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{
                if (w->esquerda->cor == PRETO){
                    w->direita->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoEsquerda(pt, w);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esquerda->cor = PRETO;
                rotacaoDireita(pt, x->pai);
                x = *pt;
            }
        }

    }
    x->cor = PRETO;

}

void rubroIFixUp(redBlack **arvore, redBlack* no){
     // Função para correção da arvore rubro-negra para manter suas regras.

    if(!*arvore || !no || *arvore == vazio || no == vazio)
        return;

    redBlack *pai, *avo, *t;
    while(no->pai->cor == VERMELHO){

        pai = no->pai;
        avo = no->pai->pai;
        if(pai == avo->esquerda){
            t = avo->direita;
            if(t->cor == VERMELHO){
                pai->cor = t->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
            }
            else{
                if(no == pai->direita){
                    no = pai;
                    rotacaoEsquerda(arvore, no);
                }
                no->pai->cor = PRETO;
                avo->cor = VERMELHO;
                rotacaoDireita(arvore, avo);
            }
        }else{


            t = avo->esquerda;
            if(t->cor == VERMELHO){
                pai->cor = t->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
            }
            else{
                if(no == pai->esquerda){
                    no = pai;
                    rotacaoDireita(arvore, no);
                }
                no->pai->cor = PRETO;
                avo->cor = VERMELHO;
                rotacaoEsquerda(arvore, avo);
            }
        }
    }
    (*arvore)->cor = PRETO;
}


 void freeArvore(redBlack * arvore){

    if(!arvore || arvore == vazio)
        return;

    freeArvore(arvore->direita);
    freeArvore(arvore->esquerda);

    free(arvore->chave);
    free(arvore);
 }

redBlack * maiorRedBlack(redBlack* pt){
    // Função que encontra e retorna um ponteiro para o maior elemento de uma árvore

    if(pt == vazio)
        return vazio;
    if(pt->direita == vazio)
        return pt;
    return maiorRedBlack(pt->direita);
}

int alturaRedblack (redBlack * ptr){
    // Função que retorna a altura de uma árvore

    int r, l;
    if(!ptr || ptr == vazio)
        return 0;

    r = 1 + alturaRedblack(ptr->direita);
    l = 1 + alturaRedblack(ptr->esquerda);
    if(r>l)
        return r;
    return l;
}

void* getInformacao(redBlack * no){
    // Função que retorna um ponteiro para a chave contida na arvore

    if(!no || no == vazio)
        return vazio;
    return no->chave;
}

color getCor(redBlack* no){
    // Função que retorna a cor de um no da árvore
    return no->cor;
}

redBlack* procuraRedBlack(redBlack * pt, void* infor, int (*compara)(void*, void*)){
    // Função que recebe a raiz da arvore e a informação a ser procurada nela, além da função de comparação

    if (!pt || !infor || pt == vazio)
        return NULL;

    if (compara(infor, pt->chave) == 0)
        return pt;
    if(compara(infor, pt->chave)<0)
        return procuraRedBlack(pt->direita, infor, compara);
    return procuraRedBlack(pt->esquerda, infor, compara);
}

void rotacaoEsquerda(redBlack ** pt, redBlack *w){
    // Função que realiza a rotação esquerda;


    if(!*pt || !w || *pt == vazio || w == vazio)
        return;

    redBlack *temp;

    temp = w->direita;
    w->direita = temp->esquerda;

    if(temp->esquerda!=vazio)
        temp->esquerda->pai = w;
    if(temp!=vazio)
        temp->pai = w->pai;
    if(w->pai == vazio)
        *pt = temp;
    else if(w == w->pai->esquerda)
        w->pai->esquerda = temp;
    else w->pai->direita = temp;

    temp->esquerda = w;
    w->pai = temp;
}

void rotacaoDireita(redBlack ** arvore, redBlack *no){
    // Função que realiza a rotação direita;
    if(!*arvore || !no || *arvore == vazio || no == vazio)
        return;

    redBlack *temp;

    temp = no->esquerda;
    no->esquerda = temp->direita;
    if(temp->direita!=vazio)
        temp->direita->pai = no;
    if(temp!=vazio)
        temp->pai = no->pai;
    if(no->pai == vazio)
        *arvore = temp;
    else if(no == no->pai->direita)
        no->pai->direita = temp;
    else
        no->pai->esquerda = temp;

    temp->direita = no;
    no->pai = temp;
}

int quantidadeRedBlack(redBlack *arvore){
    if (arvore == NULL || arvore == vazio)
        return 0;
    else
        return 1 + quantidadeRedBlack(arvore -> direita) + quantidadeRedBlack(arvore -> esquerda);

}

void transferePaiRubro(redBlack ** pt, redBlack* u, redBlack*v){
    // Função para a troca de pais

    if(!pt || *pt == vazio )
        return;

    if(u->pai == vazio)
        *pt = v;
    else {
        if(u == u->pai->esquerda)
            u->pai->esquerda = v;
        else
            u->pai->direita = v;
    }
    v->pai = u->pai;
}


void removeRedBlack(redBlack **pt, redBlack *z){
    // Função para remoção de um nó na arvore recebendo como parametro a arvore e o nó desejado
    redBlack *x, *y;
    color enumCor;

    y = z;
    enumCor = y->cor;
    if(z->esquerda == vazio){
        x = z->direita;
        transferePaiRubro(pt, z, z->direita);
        free(z->chave);
        free(z);
    }
    else if (z->direita == vazio){

        x = z->esquerda;
        transferePaiRubro(pt, z, z->esquerda);
        free(z->chave);
        free(z);
    }
    else{

        y = maiorRedBlack(z->esquerda);
        enumCor=y->cor;
        x = y->esquerda;

        if(y->pai == z) x->pai = y;
        else{
            transferePaiRubro(pt, y, x);
            y->esquerda = z->esquerda;
            y->esquerda->pai = y;
        }
        transferePaiRubro(pt, z, y);
        y->direita = z->direita;
        y->direita->pai = y;
        y->cor = z->cor;
        free(z->chave);
        free(z);
    }

    if(enumCor == PRETO)
        rubroRFixUp(pt, x);

    (*pt)->cor = PRETO;
    vazio->pai=vazio->direita=vazio->esquerda=vazio;
}

