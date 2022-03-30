#include "trie.h"


//Essa é uma função básica da árvore trie, que tem como trabalho alocar o espaço para o nó e o cria vazio, no fim retorna ele para o programa
trie *cria_no(){
    // aloca o espaço para o nó,e o cria vazio, e retorna ele para o programa
    int i;
    trie *novo_no = malloc(sizeof *novo_no);

    for (i = 0; i < TAMANHO; i++){
        novo_no->filhos[i] = NULL;
    }
    novo_no->estado = false;
    return novo_no;
}

/*Em suma essa função recebe a palavra desejada, conta cada letra da palavra, busca na árvore se a sequência já foi empregada e após isso coloca de forma
recursiva as letras em sequência, colocando assim a letra anterior como pai dele e por fim adicionando na árvore*/
bool insere_trie(trie **T, char *palavra){
    int i;
    if(*T == NULL){
        *T = cria_no();
    }
    unsigned char *texto = (unsigned char*) palavra;
    trie *temp = *T;
    int comprimento;
    comprimento = strlen(palavra);

    for (i = 0; i < comprimento; i++) {
        if (temp->filhos[texto[i]] == NULL){
            //create a new node
            temp->filhos[texto[i]] = cria_no();
        }
        temp = temp->filhos[texto[i]];
    }
    if (temp->estado) {
        return false;
     } else {
        temp->estado = true;
        return true;
    }
}

/*Função que faz o print da árvore trie ao usuário. A função basicamente armazena cada letra existente no char prefixo até que o no filho seja dado
como ocupado (false), o que demonstra que a palavra acabou a função e a retorna ao ponto de separação das palavras, onde uma mesma letra pode dar seguimento a
mais de uma palavra, e printa-lá até o fim novamente, mostrando na tela final do usuário todas as palavras contidas em uma ordem lexicograficamente crescente*/
void print_trie_recurssiva(trie *T, unsigned char *prefixo, int comprimento) {

    unsigned char novo_prefixo[comprimento+2];
    memcpy (novo_prefixo, prefixo, comprimento);
    novo_prefixo[comprimento+1] = 0;
    if (T->estado) {
        printf("%s\n", prefixo);
    }
    for (int i=0; i< TAMANHO; i++) {
        if (T->filhos[i] != NULL) {
            novo_prefixo[comprimento] = i;
            print_trie_recurssiva(T->filhos[i], novo_prefixo, comprimento+1);
         }
    }
}

/*Função responsável por fazer a ponte entre o sistema e o usuário, a função basicamente compara a
informação no nó se for diferente de NULL e utiliza a função print_trie_recurssiva para fazer o print.*/
void print_trie(trie* T){
    // compara a informação no nó se for diferente de null, utiliza a função print_trie_recurssivaurssiva
    if(T == NULL){
        return;
    }
    print_trie_recurssiva(T, NULL,0);

}

/*A função busca na trie refere a uma função que conta cada letra da palavra com o intuito de achar o comprimento final, se ele
conseguir achar dentro da árvore trie o número de chaves correspondentes ao comprimento da palavra iremos de fato saber que a string
está dentro da árvore, por exemplo, a palavra “carro”, nesse exemplo a função irá contar quantas letras tem e irá busca-la na árvore,
se a letra c estiver presente, ele tentará achar a letra a, e assim sucessivamente até bater o limite do comprimento da palavra.*/
bool busca_trie(trie *T, char* palavra){

    unsigned char *texto = (unsigned char *) palavra;
    int comprimento;
    comprimento = strlen(texto);
    trie* temp = T;

    for(int i = 0; i < comprimento; i++){
        if(temp->filhos[texto[i]] == NULL){
            return false;
        }
        unsigned char c = texto[i];
        temp = temp->filhos[c];
       }

       return temp->estado;
}

/*Essa função faz a ponte entre a função remove_trie_recursiva e o usuário, recebendo a informação de qual palavra será retirada da árvore,
com isso filtrando se a função é nula, após isso ela repassa essa informação para a remove_trie recursiva a qual fará o trabalho de retirada da palavra.*/
bool remove_trie(trie** T, char *palavra){

    unsigned char *texto = (unsigned char*) palavra;
    bool resultado = false;

    if (*T == NULL){
        return false;
    }

    *T = remove_trie_recurssiva(*T, texto, &resultado);
    return resultado;
}

/*Ela remove toda a sequência de caracteres que não serão usados pelas palavras já presentes na árvore trie. A função basicamente remove a palavra com uma
condição recursiva, ou seja, se tivermos uma palavra como “rato” anteriormente inserida e quisermos apagar a palavra “ratoeira”, a condição de existência de
uma palavra anterior será verificada e a árvore irá apagar somente até o ponto de semelhança entre as palavras, ou seja, o trecho “rato” em ratoeira, impedindo
assim a exclusão da palavra “rato” devido à semelhança.*/
trie* remove_trie_recurssiva(trie *T, unsigned char* texto, bool* deletado){

    if (T == NULL){
        return false;
    }
    if(*texto == '\0'){
        if (T->estado){
            T->estado = false;
            *deletado = true;

            if ( no_eh_filho(T) == false){
                free(T);
                T = NULL;
            }

        }
        return T;
    }
    T->filhos[texto[0]] = remove_trie_recurssiva(T->filhos[texto[0]], texto+1, deletado);

    if (*deletado && T->estado == false && no_eh_filho(T) == false){
        free(T);
        T = NULL;
    }
    return T;
}
/*A função possui uma complexidade baixa, o funcionamento consiste basicamente em uma simples
verificação de nós, onde retorna uma condição verdadeira caso o nó seja filho de outro, e falso caso contrário.*/
bool no_eh_filho(trie* T){
    //é resdponsavel por dizer se um nó e filho de outro

    if (T == NULL){
        return false;
    }
    for (int i = 0; i < TAMANHO; i++){
        if(T->filhos[i] != NULL){
            return true;
        }
    }
    return false;
}
/*Essa função tem como base somente verificar se a estrutura TRIE está vazia, retornando uma condição falso caso esteja vazia e verdeiro caso contrário.*/

bool verifica_vazio_trie(trie* T){
    //verifica se a trie esta vazia

    if (T != NULL){
        return false;
    }
    else
        return true;
}

/*A função basicamente conta cada palavra na árvore trie, indo do ponto de separação onde o nó tem mais de um filho até o ponto que o próximo nó seja dado
como vazio (null), cada vez que um novo elemento é inserido na árvore a função soma novamente a distância para sempre termos o valor atualizado de seu tamanho final.*/

void tamanho_trie_recurssiva(trie *T, unsigned char *prefixo, int comprimento, int *contagem) {

    unsigned char novo_prefixo[comprimento+2];
    memcpy (novo_prefixo, prefixo, comprimento);
    novo_prefixo[comprimento+1] = 0;
    if (T->estado) {
        *contagem = *contagem + 1;
    }
    for (int i=0; i< TAMANHO; i++) {
        if (T->filhos[i] != NULL) {
            novo_prefixo[comprimento] = i;
            tamanho_trie_recurssiva(T->filhos[i], novo_prefixo, comprimento+1, contagem);
         }
    }
}


/*Essa função é responsável pela impressão final do tamanho da árvore, seu principal trabalho é dizer ao usuário se a estrutura está vazia e dizer seu tamanho
por meio da função anteriormente citada “tamanho_trie_recursiva”.*/
void tamanho_trie(trie* T){
    //função que é responsavel pelo print final do tamanho da arvore, seu princiapal trabalho e dizer se a e vazia
    // e chamar a função tamanho_trie_recurssiva, para a contagem dos elementos da arvore

    if(T == NULL){
        printf("\nNúmero de elementos na árvore: 0\n\n");
        return;
    }
    int contagem = 0;
    tamanho_trie_recurssiva(T, NULL,0, &contagem);
    printf("\nNúmero de elementos na árvore: %d\n\n", contagem);

}
/*A função busca_prefixo tem como objetivo imprimir todas as palavras que contém um prefixo semelhante ao prefixo inserido, basicamente se
inserirmos um prefixo como “pa” ele irá imprimir (caso esteja contido dentro da árvore) as palavras “pão” “padaria” “pamonha” e
assim sucessivamente até todos as palavras que tiverem como nó pai as letras “p” e “a” sejam impressas.*/

bool busca_prefixo(trie *T, char* palavra){

    unsigned char *texto = (unsigned char *) palavra;
    int comprimento;

    comprimento = strlen(texto);
    trie* temp = T;

    for(int i = 0; i < comprimento; i++){

        if(temp->filhos[texto[i]] == NULL){
            return false;
        }
        else{
            if(comprimento - 1 == i )
                print_trie_recurssiva(temp->filhos[texto[i]], palavra, i + 1);
        }
        unsigned char c = texto[i];
        temp = temp->filhos[c];
       }
       return temp->estado;
}
