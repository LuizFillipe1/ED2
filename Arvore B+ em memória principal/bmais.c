#include "bmais.h"

void pedeArtigo(artigo *art){
	printf("\nPreencha os campos do artigo: \n");
	printf("\nID: ");
	scanf("%d", &(art->id));
	printf("Ano: ");
	scanf("%d", &(art->ano));
	printf("Autor: ");
	scanf(" %[^\n]s", art->autor);
	printf("Titulo: ");
	scanf(" %[^\n]s", art->titulo);
	printf("Revista: ");
	scanf(" %[^\n]s", art->revista);
	printf("DOI: ");
	scanf(" %s", art->DOI);
	printf("Palavra Chave: ");
	scanf(" %[^\n]s", art->palavraChave);
	printf("\n");
}

void criarArvore(Bmais* T){
	node* x = malloc(sizeof(node));

	if (x == NULL) {
		printf("ERRO ao alocar na memória");
		return;
	}
	x->next = NULL;
	x->folha = TRUE;
	x->n = 0;
	T->root = x;
}
int bMaisBuscaSimples(Bmais* T, int chave, int encontrou){
	node* x = T->root;
	while (x->folha == 0) {
		x = x->filho[0];
	}
	while (x->next != NULL) {
		for (int i = 0; i < x->n; i++) {
			if(x->chave[i] == chave)
				encontrou++;
		}
		x = x->next;
	}
	for (int i = 0; i < x->n; i++) {
		if(x->chave[i] == chave)
				encontrou++;
	}
	return encontrou;
}

void bMaisInsere(Bmais* T, int k, artigo *art)
{
	node* r = T->root;
	int encontrou = 0;
	encontrou = bMaisBuscaSimples(T , k, encontrou);
	if(encontrou != 0){
		printf("\nID já existente na árvore");
		printf("\nFalha na inserção!\n");
		return;
	}
	if (r->n == 2 * GRAU - 1){
		node* s = malloc(sizeof(node));
		if (s == NULL) {
			printf("ERRO ao alocar na memória");
			return;
		}
		T->root = s;
		s->folha = FALSE;
		s->next = NULL;
		s->n = 0;
		s->filho[0] = r;
		if (r->folha == 1) {
			bMaisCisao(s, 0, art);
		}
		else{
			bCisao(s, 0);
		}
		bMaisInsereNaoCheio(s, k,art);
	}
	else{
		bMaisInsereNaoCheio(r, k,art);
	}
}
void bCisao(node* x, int i){
	node* z = malloc(sizeof(node));
	if (z == NULL){
		printf("ERRO ao alocar na memória");
		return;
	}
	node* y = x->filho[i]; // 0 <= i
	z->folha = y->folha;
	z->n = GRAU - 1;
	for (int j = 0; j < GRAU - 1; j++){
		z->chave[j] = y->chave[j + GRAU];
	}
	if (y->folha == FALSE){
		for (int j = 0; j < GRAU; j++){
			z->filho[j] = y->filho[j + GRAU];
		}
	}
	y->n = GRAU - 1;
	for (int j = x->n; j > i; j--){
		x->filho[j + 1] = x->filho[j];
	}
	x->filho[i + 1] = z;
	for (int j = x->n - 1; j > i - 1; j--){
		x->chave[j + 1] = x->chave[j];
	}
	x->chave[i] = y->chave[GRAU - 1];
	x->n = x->n + 1;
}

void bMaisRemove(Bmais* T, int k) {
	node* r = T->root;
	if ((r->n == 1 && r->folha == FALSE) && ((r->filho[0])->n == GRAU-1 && (r->filho[1])->n == GRAU-1)) {
		node* y = r->filho[0];
		node* z = r->filho[1];
		if (y->folha == TRUE) {
			for (int j = 0; j < GRAU - 1; j++) {
				y->chave[j + GRAU - 1] = z->chave[j];
			}
			y->n = 2 * GRAU - 2;
			y->next = NULL;
			T->root = y;
			free(r);
			free(z);
			bMaisRemove_main(y, k);
		}
		else {
			y->chave[GRAU - 1] = r->chave[0];
			for (int j = 0; j < GRAU - 1; j++) {
				y->chave[GRAU + j] = z->chave[j];
			}
			for (int j = 0; j < GRAU; j++) {
				y->filho[GRAU + j] = z->filho[j];
			}
			y->n = 2 * GRAU - 1;
			T->root = y;
			free(r);
			free(z);
			bMaisRemove_main(y, k);
		}
	}
	else {
		bMaisRemove_main(r, k);
	}
	return;
}

void bMaisRemove_main(node* x, int k) {
	int i = x->n;
	while (i > 0 && x->chave[i - 1] > k) {
		i--;
	}
	int i_chave = x->n;
	while (i_chave > 0 && x->chave[i_chave - 1] >= k) {
		i_chave--;
	}
	if (x->folha == TRUE) {
		if (x->chave[i_chave] == k) {
			for (int j = i_chave; j < x->n - 1; j++) {
				x->chave[j] = x->chave[j + 1];
			}
			x->n--;
			printf("\nArtigo removido com sucesso!\n");
			return;
		}
		else {
			printf("Não foi encontrado o ID na árvore.\n\n");
			return;
		}

	}
	else if ((x->filho[i])->n == GRAU - 1) {
		node* aux = x->filho[i];
		if (aux->folha == FALSE) {
			if (i != 0 && (x->filho[i - 1])->n > GRAU - 1){
				node* esquerdo = x->filho[i - 1];
				for (int j = GRAU - 2; j >= 0; j--) {
					aux->chave[j + 1] = aux->chave[j];
				}
				if (aux->folha == FALSE){
					for (int j = GRAU - 1; j >= 0; j--) {
						aux->filho[j + 1] = aux->filho[j];
					}
				}
				aux->chave[0] = x->chave[i - 1];
				aux->filho[0] = esquerdo->filho[esquerdo->n];
				aux->n++;
				x->chave[i - 1] = esquerdo->chave[esquerdo->n - 1];
				esquerdo->n--;
			}
			else if (i != x->n && (x->filho[i + 1])->n > GRAU - 1){
				node* direito = x->filho[i + 1];
				aux->chave[GRAU - 1] = x->chave[i];
				aux->filho[GRAU] = direito->filho[0];
				aux->n++;
				x->chave[i] = direito->chave[0];
				for (int j = 0; j < direito->n - 1; j++){
					direito->chave[j] = direito->chave[j + 1];
				}
				for (int j = 0; j < direito->n; j++) {
					direito->filho[j] = direito->filho[j + 1];
				}
				direito->n--;
			}
			else {
				if (i == 0) {
					node* direito = x->filho[i + 1];
					for (int j = 0; j < GRAU - 1; j++) {
						direito->chave[j + GRAU] = direito->chave[j];
						direito->chave[j] = aux->chave[j];
					}
					if (direito->folha == 0) {
						for (int j = 0; j < GRAU; j++) {
							direito->filho[j + GRAU] = direito->filho[j];
							direito->filho[j] = aux->filho[j];
						}
					}
					direito->chave[GRAU - 1] = x->chave[i];
					direito->n = GRAU * 2 - 1;
					for (int j = 0; j < x->n - 1; j++) {
						x->chave[j] = x->chave[j + 1];
					}
					for (int j = 0; j < x->n; j++){
						x->filho[j] = x->filho[j + 1];
					}
					free(aux);
					aux = direito;
					x->n--;
				}
				else {
					node* esquerdo = x->filho[i - 1];
					esquerdo->chave[GRAU - 1] = x->chave[i - 1];
					for (int j = 0; j < GRAU - 1; j++) {
						esquerdo->chave[j + GRAU] = aux->chave[j];
					}
					if (esquerdo->folha == 0) {
						for (int j = 0; j < GRAU; j++) {
							esquerdo->filho[j + GRAU] = aux->filho[j];
						}
					}
					esquerdo->n = 2 * GRAU - 1;
					for (int j = i - 1; j < x->n - 1; j++) {
						x->chave[j] = x->chave[j + 1];
					}
					for (int j = i; j < x->n; j++) {
						x->filho[j] = x->filho[j + 1];
					}
					free(aux);
					aux = esquerdo;
					x->n--;
				}
			}
			bMaisRemove_main(aux, k);

		}
		else {
			if (i != 0 && (x->filho[i - 1])->n > GRAU - 1) {

				node* esquerdo = x->filho[i - 1];
				for (int j = GRAU - 2; j >= 0; j--) {
					aux->chave[j + 1] = aux->chave[j];
				}
				aux->chave[0] = esquerdo->chave[esquerdo->n - 1];
				aux->n++;
				x->chave[i - 1] = esquerdo->chave[esquerdo->n - 1];
				esquerdo->n--;
			}
			else if (i != x->n && (x->filho[i + 1])->n > GRAU - 1) {

				node* direito = x->filho[i + 1];
				aux->chave[GRAU - 1] = direito->chave[0];
				aux->n++;
				for (int j = 0; j < direito->n - 1; j++) {
					direito->chave[j] = direito->chave[j + 1];
				}
				x->chave[i] = direito->chave[0];
				direito->n--;
			}
			else {

				if (i == 0) {
					node* direito = x->filho[i + 1];
					for (int j = 0; j < GRAU - 1; j++) {
						aux->chave[GRAU - 1 + j] = direito->chave[j];
					}
					aux->n = 2*GRAU-2;
					aux->next = direito->next;
					for (int j = 0; j < x->n - 1; j++) {
						x->chave[j] = x->chave[j + 1];
					}
					for (int j = 1; j < x->n; j++) {
						x->filho[j] = x->filho[j + 1];
					}
					x->n--;
					free(direito);
				}
				else{
					node* esquerdo = x->filho[i - 1];
					for (int j = 0; j < GRAU - 1; j++) {
						esquerdo->chave[GRAU - 1 + j] = aux->chave[j];
					}
					esquerdo->n = 2 * GRAU - 2;
					esquerdo->next = aux->next;
					for (int j = i - 1; j < x->n - 1; j++) {
						x->chave[j] = x->chave[j + 1];
					}
					for (int j = i; j < x->n; j++) {
						x->filho[j] = x->filho[j + 1];
					}
					x->n--;
					free(aux);
					aux = esquerdo;
				}
			}
			bMaisRemove_main(aux, k);
		}
	}
	else {
		bMaisRemove_main(x->filho[i], k);
	}
	return;
}

void bMaisCisao(node* x, int i, artigo * art) {
	node* z = malloc(sizeof(node));
	if (z == NULL)
	{
		printf("ERRO ao alocar na memória");
		return;
	}
	node* y = x->filho[i];
	z->folha = y->folha;
	z->n = GRAU;
	for (int j = x->n - 1; j > i - 1; j--) {
		x->chave[j + 1] = x->chave[j];
		x->infor[j + 1] = x->infor[j];
		memcpy(&x->infor[j+1] ,art,sizeof(artigo));
	}
	for (int j = x->n; j > i; j--) {
		x->filho[j + 1] = x->filho[j];
	}
	x->chave[i] = y->chave[GRAU - 1];
	x->infor[i] = y->infor[GRAU-1];
	x->filho[i + 1] = z;
	for (int j = 0; j < GRAU; j++) {
		z->chave[j] = y->chave[GRAU - 1 + j];
		x->infor[i] = y->infor[GRAU-1 + j];
	}
	y->n = GRAU - 1;
	x->n++;
	z->next = y->next;
	y->next = z;
}

void bMaisInsereNaoCheio(node* x, int k, artigo *art){
	node *aux;
	aux = (node*)malloc(sizeof(node));

	int i = x->n;
	if (x->folha){
		i--;
		while (i >= 0 && k < x->chave[i]){
			x->chave[i + 1] = x->chave[i];
			x->infor[i + 1] = x->infor[i];
			i--;
		}
		x->chave[i + 1] = k;
		memcpy(aux,art,sizeof(artigo));
		memcpy(&x->infor[i+1],aux,sizeof(artigo));
		x->n = x->n + 1;
	}
	else {
		while (i >= 1 && k < x->chave[i - 1]){
			i--;
		}
		if ((x->filho[i])->n == 2 * GRAU - 1){
			if ((x->filho[0])->folha == 1) {
				bMaisCisao(x, i,art);
			}
			else {
				bCisao(x, i);
			}
			if (k > x->chave[i]) {
				i++;
			}
		}
		bMaisInsereNaoCheio(x->filho[i], k,art);
	}
}

void passaRaizImpressao(Bmais* T){
	node* r = T->root;
	imprimeArvore(r, 1);
	bMaisImprimeFolhas(T);
}

void imprimeArvore(node* x, int h){
	printf("\n");
	printf("%d : ", h);
	for (int i = 0; i < x->n; i++){
		printf("%d ", x->chave[i]);
	}
	printf("\n");
	if (x->folha == 0){
		for (int i = 0; i < x->n + 1; i++){
			imprimeArvore(x->filho[i], h + 1);
		}
	}
}

void bMaisImprimeFolhas(Bmais* T) {
	printf("\n[Lista encadeada]\n");
	node* x = T->root;
	while (x->folha == 0) {
		x = x->filho[0];
	}
	while (x->next != NULL) {
		printf("[ ");
		for (int i = 0; i < x->n; i++) {
			printf("%d ",x->chave[i]);
		}
		printf("]");
		x = x->next;
	}
	printf("[ ");
	for (int i = 0; i < x->n; i++) {
		printf("%d ", x->chave[i]);
	}
	printf("]\n");

}

void bMaisImprimeFolhasApartirDaChave(Bmais* T, int chave) {
	printf("\n[Impressão da lista encadeada a partir da chave solicitada]\n\n");
	node* x = T->root;
	int encontrou = 0;
	encontrou = bMaisBuscaSimples(T , chave, encontrou);
	if(encontrou == 0){
		printf("\nID não existente na árvore");
		printf("\nimpressão cancelada!\n");
		return;
	}
	while (x->folha == 0) {
		x = x->filho[0];
	}
	while (x->next != NULL) {

		for (int i = 0; i < x->n; i++) {
			if((x->chave[i]) >= chave)
				printf("%d ",x->chave[i]);
		}
		x = x->next;
	}
	for (int i = 0; i < x->n; i++) {
		if((x->chave[i]) >= chave)
			printf("%d ",x->chave[i]);
	}
	printf("\n");
}


void mostraArtigo(Bmais* T, int y) {

	artigo *aux = (artigo*)malloc(sizeof(artigo));
	int pause = 0 , encontrou = 0;
	node* x = T->root;
	while (x->folha == 0) {
		x = x->filho[0];
	}
	while (x->next != NULL && pause == 0) {
		for (int i = 0; i < x->n; i++) {
			if(x->chave[i] == y){
				printf("\nID: %d \n",x->infor[i].id);
			    printf("Ano: %d \n",x->infor[i].ano);
			    printf("Autor: %s \n",x->infor[i].autor);
			    printf("Titulo: %s \n",x->infor[i].titulo);
			    printf("Revista: %s \n",x->infor[i].revista);
			    printf("DOI: %s \n",x->infor[i].DOI);
			    printf("Palavra Chave: %s \n",x->infor[i].palavraChave);

				pause = 1;
				encontrou ++;
			}
		}
		if (pause == 0)
			x = x->next;
	}
	for (int i = 0; i < x->n; i++) {
		if(x->chave[i] == y){

				encontrou ++;
				printf("\nID: %d \n",x->infor[i].id);
			    printf("Ano: %d \n",x->infor[i].ano);
			    printf("Autor: %s \n",x->infor[i].autor);
			    printf("Titulo: %s \n",x->infor[i].titulo);
			    printf("Revista: %s \n",x->infor[i].revista);
			    printf("DOI: %s \n",x->infor[i].DOI);
			    printf("Palavra Chave: %s \n",x->infor[i].palavraChave);
		}
	}
	if (encontrou == 0)
		printf("\nArtigo não encontrado na árvore.\n");
	printf(" ");

}
