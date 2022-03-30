#include "bmais.h"
/* Está é a função principal do programa, a qual irá fazer todas as chamadas de funções decorrido das solicitações do usuário*/
int main(){
	artigo *art;
	art = (artigo*)malloc(sizeof(artigo));
	Bmais* T = malloc(sizeof(Bmais));
	if (T == NULL) {
		printf("ERRO ao alocar na memória");
		return 0;
	}
	criarArvore(T);
	int opcao, x, y;
	printf("##########################\n\n       ÁRVORE B MAIS  \n\n##########################\n\n");
	while (1) {
		printf("--------------------------");
		printf("\n1- Inserir artigo da árvore\n2- Buscar artigo na árvore\n3- Deletar artigo\n4- Mostrar lista encadeada de ID's\n5- Imprimir árvore\n6- Imprimir artigos crescentes a partir de um ID (incluso o ID)\n\nDigite o item desejado: ");
		scanf("%d", &opcao);
		if (opcao == 1) {
			pedeArtigo(art);
			bMaisInsere(T, art->id, art);
		}
		else if (opcao == 2){
			printf("\nInsira o ID do artigo que deseja buscar: ");
			getchar();
			scanf("%d", &x);
			mostraArtigo(T,x);
		}
		else if (opcao == 3){
			printf("\nInsira o ID do artigo que deseja remover: ");
			getchar();
			scanf("%d", &x);
			bMaisRemove(T, x);

		}
		else if (opcao == 4){
			bMaisImprimeFolhas(T);
		}
		else if (opcao == 5){
			passaRaizImpressao(T);
		}
		else if (opcao == 6){
			printf("\nInsira o ID do artigo que deseja imprimir a lista de todos os artigos crescentes a apartir dele: ");
			getchar();
			scanf("%d", &x);
			bMaisImprimeFolhasApartirDaChave(T, x);
		}
		else if (opcao == 0) {
			break;
		}
		getchar();
	}
	free(T);
	free(art);
}
