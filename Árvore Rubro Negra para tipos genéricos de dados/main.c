#include <stdio.h>
#include <stdlib.h>

#include "Rubro.h"

/* Struct do cliente*/
typedef struct informacoes{
    int id;              //Ex: 20
    char marca[64];      //Ex: Pirelli
    int largura;         //Ex: 175
    int relacao_H_e_L;   //Ex: 60
    int diametro;        //Ex: 15
    long int codigo_de_barras;  //Ex: 6088473184014

}infor;

int comparaInformacao(void* chave, void* chave1){
    /*Função para comparar os ID's do struct infor*/

    int a = ((infor*)chave)->id; //Atribuição do void para int
    int b = ((infor*)chave1)->id; //Atribuição do void para int

    if(a > b)
        return -1;  //Retorna -1 se a maior que b
    else if(a < b)
        return 1;   //Retorna -1 se a menor que b
    else
        return 0;   //Retorna 0 de ambas as chaves/ID são iguias

}

infor * buscaInfor(){
    /*Função que cria um elemento de informação para fazer a busca ou deleção, contendo apenas o ID*/

    infor *temp = (infor *) malloc(sizeof(infor));
    printf("Insira o ID pneu: ");
    scanf("%d", &temp->id);

    return temp;
}

void uniaoConjunto(redBlack *b, redBlack **c){
    //Função que faz a união dos elementos da arvore A com o os elementos da arvore B

    if(!b  || b == vazio) //se a arvore B estiver vazia, não ocorre a união
        return;

    infor  *temp = (infor*) malloc(sizeof (infor));   //alocação da variavel temp do tipo infor
    infor  *novaInfor = (infor*) malloc(sizeof (infor)); //alocação da variavel novaInfor do tipo infor

    temp = getInformacao(b);
    novaInfor -> id = temp -> id;

    uniaoConjunto( b->direita,c); //recursividade para pecorrer toda a arvore B
    uniaoConjunto(b->esquerda,c); //recursividade para pecorrer toda a arvore b

    insereRedBlack(c, novaInfor, &comparaInformacao);  // inserção na arvore C os elementos da arvore B, lembrando
                                                       //que na insereRedBlack há uma verificação se o elemento já
                                                       //percente a arvore
}

infor * inserirInformacao(){
    //Junta as informações no struct infor para ser lançado na arvore

    infor *temp = (infor *) malloc(sizeof(infor));
    printf("Insira o ID da informação: ");
    scanf("%d", &temp->id);
    printf("Insira a marca do pneu: ");
    scanf("%s", temp->marca);
    printf("Insira a largura do pneu: ");
    scanf("%d", &temp->largura);
    printf("Insira a relação da altura e largura: ");
    scanf("%d", &temp->relacao_H_e_L);
    printf("Insira o diâmetro do pneu: ");
    scanf("%d", &temp->diametro);
    printf("Insira o código de barras do pneu: ");
    scanf("%ld", &temp->codigo_de_barras);

    return temp;
}

void imprimeArvore(redBlack * arvore){
    //Função para a impressão dos conjuntos, recebendo como parametro a raiz da arvore a ser impressa
    if(!arvore || arvore == vazio)
        return;
    int i, nivel = alturaRedblack(arvore);

    if(arvore){
        imprimeArvore(arvore->esquerda);

        for(i=0; i<nivel; i++) printf("\t");
            infor *temp = (infor *) getInformacao(arvore);

        if(getCor(arvore) == VERMELHO)
            printf("[%d : R]\n\n", temp->id);
        else
            printf("[%d : B]\n\n", temp->id);

        imprimeArvore(arvore->direita);
    }
}
void imprimeInfor(void *chave){
    /*Função para a impressão dos dados contidos na struct infor do cliente*/

    infor *temp = (infor *) chave; //casting da variavel para o tipo infor

    printf("\nID: %d\n", temp->id);
    printf("Marca: %s\n", temp->marca);
    printf("Largura: %d\n",temp->largura);
    printf("Relação da altura e largura: %d\n",temp->relacao_H_e_L);
    printf("Diâmetro: %d\n", temp->diametro);
    printf("Código de barras: %ld \n\n", temp->codigo_de_barras);

}

void copiaArvore(redBlack *arvore, redBlack ** arvore_C){
    //Função que recebe a arvore a ser copiada e o endereço de memoria da que vai receber essa cópia
    if(arvore == vazio || arvore == NULL) //se a arvore estiver vazia, não ocorre a cópia
        return ;

    else {
        infor  *temp = (infor*) malloc(sizeof (infor));      //alocação da variavel temp do tipo infor
        infor  *novaInfor = (infor*) malloc(sizeof (infor));   //alocação da variavel novaInfor do tipo infor

        temp = getInformacao(arvore); //Armazenando a infor da arvore na variavel temp
        novaInfor->id = temp->id;     //setando o ID de temp na variavel novaInfor
        insereRedBlack(arvore_C, novaInfor, &comparaInformacao); //inserção dá cópia da arvore "arvore" na arvore_C

        copiaArvore(arvore->direita, arvore_C);  //recursividade para pecorrer toda a arvore
        copiaArvore(arvore->esquerda, arvore_C); //recursividade para pecorrer toda a arvore
    }

}

redBlack *intersecao(redBlack *arvore_A, redBlack *arvore_B, redBlack **arvore_C){
    //Função para realizar a interseção entre os conjuntos desejados pelo usuario
    //Recebe duas arvores e cria a arvore_C como a interseção das arvores

    if(arvore_A == vazio || arvore_A == NULL || arvore_B == NULL || arvore_B == vazio || arvore_C == NULL ){
        return NULL;}

    else{
        redBlack *aux;
        infor  *temp = (infor*) malloc(sizeof (infor));
        infor  *novoInfor = (infor*) malloc(sizeof (infor));
        temp = getInformacao(arvore_A);

        novoInfor -> id = temp -> id;
        aux = procuraRedBlack(arvore_B, novoInfor, &comparaInformacao);

        if(aux)
            insereRedBlack(arvore_C, novoInfor, &comparaInformacao);

        intersecao(arvore_A->direita,arvore_B,arvore_C);
        intersecao(arvore_A->esquerda,arvore_B,arvore_C);

    }

    return *arvore_C;
}

void diferenca(redBlack *arvore_A, redBlack *arvore_B, redBlack **arvore_C){
    //Função para realizar a diferença entre os conjuntos desejados pelo usuario
    //Recebe duas arvores e cria a arvore_C como a diferença das arvores

    if(arvore_A == vazio || arvore_A == NULL  || arvore_A == NULL || arvore_A == vazio || arvore_C == NULL ){
        return ;}

    else{

        redBlack *auxiliar;
        infor  *temp = (infor*) malloc(sizeof (infor));
        infor  *novaInfo = (infor*) malloc(sizeof (infor));

        temp = getInformacao(arvore_A);
        novaInfo -> id = temp -> id;
        auxiliar = procuraRedBlack(arvore_B, novaInfo, &comparaInformacao);

        if(!auxiliar)
            insereRedBlack(arvore_C, novaInfo, &comparaInformacao);

        diferenca(arvore_A->direita,arvore_B,arvore_C);
        diferenca(arvore_A->esquerda,arvore_B,arvore_C);
    }

}
void esvaziaArvore(redBlack * arvore_C){
    //Função que recebe a arvore a ser esvaziada
    if( arvore_C == NULL || arvore_C == vazio )
        return ;

    else {

        redBlack *aux;
        infor  *temp = (infor*) malloc(sizeof (infor));      //alocação da variavel temp do tipo infor
        temp = getInformacao(arvore_C); //Armazenando a infor da arvore na variavel temp
        aux = procuraRedBlack(arvore_C, temp, &comparaInformacao);

        if(aux)
            removeRedBlack(&arvore_C, aux);

        esvaziaArvore(arvore_C->direita);  //recursividade para pecorrer toda a arvore
        esvaziaArvore(arvore_C->esquerda); //recursividade para pecorrer toda a arvore
    }

}

int main(){
    //atribuição das variaveis e arvores a serem ultilizadas no programa

    int rodando = 1, auxiliarMenu, opcao;
    char auxMenu;

    //criação de uma sentinela (T.nill), que é um objeto com os mesmo atributos que um nó comum da arvore,
    //sua cor é preta e seua atributos p,esquer,direita e chave podem ser abitrários.
    //Fonte: Algoritmos teoria e prática, 3ed, Thomas H. Cormen

    vazio = (redBlack *) malloc(sizeof(redBlack));
    vazio->cor = PRETO;
    vazio->pai = vazio->direita = vazio->esquerda = vazio;
    redBlack *auxiliar = vazio, *Arvore_A = vazio , *Arvore_B = vazio , *Arvore_C = vazio ;
    infor * informacao;

    while(rodando){
        printf("*************** Casa do Silencioso *****************\n");
        printf("* 1 - Inserir dados no conjunto A                  *\n");
        printf("* 2 - Inserir dados no conjunto B                  *\n");
        printf("* 3 - Pesquisar dados                              *\n");
        printf("* 4 - Remover dados                                *\n");
        printf("* 5 - Esvaziar conjunto                            *\n");
        printf("* 6 - Imprimir quantidade de elementos no conjunto *\n");
        printf("* 7 - Imprimir dados do conjunto A                 *\n");
        printf("* 8 - Imprimir dados do conjunto B                 *\n");
        printf("* 9 - Imprimir a união de cojuntos                 *\n");
        printf("* 10 - Imprimir a interseção de cojuntos           *\n");
        printf("* 11 - Imprimir a diferença de conjuntos           *\n");
        printf("* 0 - Fechar o programa                            *\n");
        printf("****************************************************\n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                //1 - Inserir dados no conjunto A

                informacao = inserirInformacao();
                insereRedBlack(&Arvore_A, informacao, &comparaInformacao);
                printf("\n\nInformação salva com sucesso!\n");

                break;

            case 2:
                //2 - Inserir dados no conjunto B

                informacao = inserirInformacao();
                insereRedBlack(&Arvore_B, informacao, &comparaInformacao);
                printf("\n\nInformação salva com sucesso!\n");

                break;

            case 3:
                //3 - Pesquisar dados

                printf("Em qual conjunto você deseja realizar a busca?\n");
                printf("1 - A\n");
                printf("2 - B\n");
                scanf("%d",&auxiliarMenu);
                switch(auxiliarMenu){
                    case 1:
                        informacao = buscaInfor();
                        auxiliar = procuraRedBlack(Arvore_A, informacao, &comparaInformacao);
                        if(!auxiliar)
                            printf("\nID de informação inválido!\n");
                        else
                            imprimeInfor(getInformacao(auxiliar));
                        free(informacao);

                        break;

                    case 2:
                        informacao = buscaInfor();
                        auxiliar = procuraRedBlack(Arvore_B, informacao, &comparaInformacao);
                        if(!auxiliar)
                            printf("\nID de informação inválido!\n");
                        else
                            imprimeInfor(getInformacao(auxiliar));
                        free(informacao);

                        break;
                }
                break;

            case 4:
                //4 - Remover dados
                printf("Em qual conjunto você deseja realizar a remoção?\n");
                printf("1 - A\n");
                printf("2 - B\n");
                scanf("%d",&auxiliarMenu);

                switch(auxiliarMenu){
                    case 1:

                        informacao = buscaInfor();
                        auxiliar = procuraRedBlack(Arvore_A, informacao, &comparaInformacao);
                        if(!auxiliar)
                            printf("\n\nID de informação inválido!\n");
                        else {

                            imprimeInfor(getInformacao(auxiliar));
                            printf("\n\nDeseja removê-lo? (s/n):  ");
                            getchar();
                            scanf("%c", &auxMenu);
                        if (auxMenu =='s' || auxMenu =='S'){
                            removeRedBlack(&Arvore_A, auxiliar);
                            printf("\nInformação removida com sucesso!\n\n");
                        }
                    }
                    free(informacao);
                    break;
                case 2:
                    informacao = buscaInfor();
                    auxiliar = procuraRedBlack(Arvore_B, informacao, &comparaInformacao);
                    if(!auxiliar)
                    printf("\n\nID de informação inválido!\n");
                    else{
                        imprimeInfor(getInformacao(auxiliar));
                        printf("\n\nDeseja removê-lo? (s/n):  ");
                        getchar();
                        scanf("%c", &auxMenu);
                    if(auxMenu =='s' || auxMenu =='S'){
                        removeRedBlack(&Arvore_A, auxiliar);
                        printf("\nInformação removida com sucesso\n\n");
                    }
                }
                free(informacao);
                break;

                }
                break;
            case 5:
                printf("Deseja esvaziar qual conjunto?\n");
                printf("1 - A\n");
                printf("2 - B\n");
                scanf("%d",&auxiliarMenu);

                switch(auxiliarMenu){

                    case 1:

                        printf("\nConjunto esvaziado!\n\n");
                        esvaziaArvore(Arvore_A);
                        Arvore_A = vazio;

                        break;


                    case 2:

                        printf("\nConjunto esvaziado!\n\n");
                        esvaziaArvore(Arvore_B);
                        Arvore_B = vazio;

                        break;
                }

                break;

            case 6:
                //6 - Imprimir quantidade de elementos no conjunto

                printf("\n\n Conjunto A : %d elementos\n", quantidadeRedBlack(Arvore_A));
                printf("\n Conjunto B : %d elementos\n\n", quantidadeRedBlack(Arvore_B));

                break;

            case 7:
               //7 - Imprimir dados do conjunto A

                printf("Imprimindo árvore: \n\n");
                imprimeArvore(Arvore_A);

                break;

             case 8:
                //8 - Imprimir dados do conjunto B

                printf("Imprimindo árvore: \n\n");
                imprimeArvore(Arvore_B);

                break;
            case 9:
                //9 - Imprimir a união de cojuntos

                copiaArvore(Arvore_A, &Arvore_C);
                uniaoConjunto(Arvore_B,&Arvore_C);
                imprimeArvore(Arvore_C);
                freeArvore(Arvore_C);

                break;
            case 10:
                //10 - Imprimir a interseção de cojuntos

                printf("\n\nImprimindo a intersecao: \n\n");
                auxiliar = intersecao(Arvore_A,Arvore_B,&Arvore_C);
                imprimeArvore(auxiliar);
                freeArvore(auxiliar);
                auxiliar = vazio;

                break;

            case 11:
                //11 - Imprimir a diferença de conjuntos

                printf("Deseja fazer qual diferença de conjutos? \n");
                printf("1 --> A - B\n");
                printf("2 --> B - A\n");
                scanf("%d", &auxiliarMenu);
                switch(auxiliarMenu){
                    case 1:
                        printf("\n A - B\n\n");
                        diferenca(Arvore_A,Arvore_B,&Arvore_C);
                        imprimeArvore(Arvore_C);
                        freeArvore(Arvore_C);

                        break;
                    case 2:
                        printf("\n B - A\n\n");
                        diferenca(Arvore_B,Arvore_A,&Arvore_C);
                        imprimeArvore(Arvore_C);
                        freeArvore(Arvore_C);
                        break;

                }
                break;
            case 0:
                //0 - Fechar o programa

                freeArvore(Arvore_A); //Liberação da árvore na memória
                freeArvore(Arvore_B); //Liberação da árvore na memória
                free(vazio);  //Liberação do nó vazio
                rodando = 0;

                break;
        }
    }
}
