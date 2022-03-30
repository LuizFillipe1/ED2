#include "trie.h"

int main(){

    trie* T = NULL; //Criação da estrutura da arvore TRIE
	int opcao, x, rodando = 1;
	int bool_aux;
	char chave;
	printf("##########################\n\n          TRIE        \n\n##########################\n\n");
	do{
		printf("--------------------------");
		printf("\n1- Inserir chave na árvore\n2- Buscar chave na árvore\n3- Deletar chave da árvore\n4- Imprimir chaves da árvore em ordem lexicograficamente\n5- Imprimir número de elementos contidos na árvore\n6- Verificar se o conjunto está vazio\n7- Imprimir strings que contém s como prefixo\n8- Sair do programa\n\nDigite o item desejado: ");
		scanf("%d", &opcao);
		if (opcao == 1) {
		    printf("\nInsira a chave que deseja inserir: ");
			getchar();
			scanf("%s", &chave);
			bool_aux = insere_trie(&T, &chave);
			if (bool_aux == true){
				printf("\n Chave inserida com sucesso!\n\n");
			}
			else{
				printf("\nInserção inválida!\n\n");
			}
		}
		else if (opcao == 2){
			printf("\nInsira a chave que deseja buscar: ");
			getchar();
			scanf("%s", &chave);
			bool_aux = busca_trie(T, &chave);
			if (bool_aux == true){
			    printf("\nChave encontrada\n");
			}
			else{
			    printf("\nChave NÃO encontrada\n");
			}
		}
		else if (opcao == 3){
			printf("\nInsira a chave que deseja remover: ");
			getchar();
			scanf("%s", &chave);
			bool_aux = remove_trie(&T, &chave);
			if (bool_aux == true){
			    printf("\nRemoção realizada com sucesso!\n");
			}
			else{
			    printf("\nChave NÃO encontrada ou remoção inválida!\n\n");
			}
		}
		else if (opcao == 4){
		    printf("Imprimindo a arvore: \n");
			print_trie(T);
			printf("\n");
		}
		else if (opcao == 5){
			tamanho_trie(T);
		}
		else if (opcao == 6){
			bool_aux = verifica_vazio_trie(T);
			if (bool_aux){
				printf("\nÁrvore vazia!\n\n");
			}
			else{
				printf("\nA árvore NÃO está vazia!\n\n");
			}
		}
		else if (opcao == 7) {
			printf("\nInsira o prefixo desejado: ");
			getchar();
			scanf("%s", &chave);
			busca_prefixo(T, &chave);
		}
		else if (opcao == 8){
			rodando = 0;
			break;
		}
	}while(rodando == 1);
	free(T);
}
