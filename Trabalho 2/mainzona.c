#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <time.h>
#include "printPersonagem.h"
#include "criador.h"
#include <math.h>





/**********************************************************************************************************************/
/* Definicoes */

#define TAM 16
#define PRIMORDIAIS 4
#define DESCENDENTES 4
#define NOVA_G 8


typedef struct nodo{
	Tree* personagem;
	struct nodo* prox;
	struct nodo* ant; 
}Nodo;

typedef struct lista{  
	Nodo* cabeca;
}Lista;

typedef struct lista_g{  
	Genetica **vetor;
	int tamanho;
	int cabeca;
}Lista_g;






/**********************************************************************************************************************/
/* Lista de Tree */

Lista* cria_lista(){
	Lista *ptr  = (Lista *)malloc(sizeof(Lista));
	ptr->cabeca = NULL;

	return ptr;
}

Nodo* cria_nodo(Tree* personagem){
	Nodo *ptr = (Nodo *)malloc(sizeof(Nodo));
	ptr->prox = NULL;
	ptr->ant  = NULL;
	ptr->personagem = personagem;

	return ptr;
}

int vazia_lista(Lista* cabeca){
	return(cabeca->cabeca == NULL);
}

void insere_lista(Lista* cabeca, int posicao, Tree* personagem){
	Nodo *ptr = cria_nodo(personagem);
	int i = 0;

	if(vazia_lista(cabeca)){
		cabeca->cabeca = ptr;
	}
	else if (posicao <= 0){
		cabeca->cabeca->an = ptr;
		ptr->prox = cabeca->cabeca;
		cabeca->cabeca = ptr;
	}
	else if (posicao > 0){
		Nodo *aux = cabeca->cabeca;
		for(i = 0; i < posicao-1 && aux->prox != NULL; ++i){
			aux = aux->prox;
		}
		ptr->prox = aux->prox;
		ptr->ant  = aux;

		if(aux->prox != NULL){
			aux->prox->ant = ptr;
		}
		aux->prox = ptr;
	}
}

Tree* busca_personagem(Lista *lista, int id){
	int i;
	Nodo *ptr = lista->cabeca;
	for(i = 0; i < id && ptr!= NULL; ++i){
		ptr = ptr->prox;
	}
	return ptr->personagem;
}

void remove_lista(Lista* cabeca, int posicao){
	int i;
	if(!vazia_lista(cabeca)){
		Nodo *ptr = cabeca->cabeca;
		for(i = 0; i < posicao && ptr->prox != NULL; ++i){
			ptr = ptr->prox;
		}
		if(ptr == cabeca->cabeca){
			cabeca->cabeca = ptr->prox;
		}
		else{
			ptr->ant->prox = ptr->prox;
		}
		if(ptr->prox != NULL){
			ptr->prox->ant = ptr->ant;
		}
		tree_free(ptr->personagem);
		free(ptr);		
	}
}

void free_lista(Lista* cabeca){
	while(!vazia_lista(cabeca)){
		remove_lista(cabeca, 0);
	}
	free(cabeca);
}




/**********************************************************************************************************************/
/* Lista de Genetica */

Lista_g* cria_lista_g(int tamanho){
	Lista_g *lista  = (Lista_g *)malloc(sizeof(Lista_g));

	lista->vetor = (Genetica **)malloc(sizeof(Genetica *)*tamanho);
	lista->tamanho = tamanho;
	lista->cabeca = 0;

	return lista;
}

void insere_lista_g(Lista_g* lista, Genetica* carac){
	if(lista->cabeca >= lista->tamanho){
		printf("A lista está totalmente preeenchida.\n");
	}

	else{
		lista->vetor[lista->cabeca] = carac;
		++lista->cabeca;
	}
}

void free_lista_g(Lista_g* lista){
	free(lista->vetor);
	free(lista);
}





/**********************************************************************************************************************/
/* Funcoes gerais para preenchimento e leitura de caracteristicas */


void preenche_lista_carac(Tree* personagem, Lista_g* lista){
	if(personagem->right == NULL && personagem->left == NULL){

		insere_lista_g(lista, personagem->info);
		return;
	}
	preenche_lista_carac(personagem->left, lista);
	preenche_lista_carac(personagem->right, lista);
}
 
void preenche_carac(Genetica *caracteristica){

	switch (caracteristica->dom){

		/* Cor do olho. */
		case 1:
			sprintf(caracteristica->carac, "azul");
		break;

		case 2:
			sprintf(caracteristica->carac, "castanho");
		break;

		case 3:
			sprintf(caracteristica->carac, "preto");
		break;

		case 4:
			sprintf(caracteristica->carac, "verde");
		break;

		/* Formato do olho. */
		case 5:
			sprintf(caracteristica->carac, "circular");
		break;

		case 6:
			sprintf(caracteristica->carac, "triangular");
		break;

		/* Cor do cabelo. */
		case 7:
			sprintf(caracteristica->carac, "amarelo");
		break;

		case 8:
			sprintf(caracteristica->carac, "azul");
		break;

		case 9:
			sprintf(caracteristica->carac, "preto");
		break;

		case 10:
			sprintf(caracteristica->carac, "vermelho");
		break;

		/* Formato do cabelo. */
		case 11:
			sprintf(caracteristica->carac, "careca");
		break;

		case 12:
			sprintf(caracteristica->carac, "goku");
		break;

		case 13:
			sprintf(caracteristica->carac, "trunks");
		break;

		case 14:
			sprintf(caracteristica->carac, "vegeta");
		break;

		/* Calças. */
		case 15:
			sprintf(caracteristica->carac, "azul");
		break;

		case 16:
			sprintf(caracteristica->carac, "laranja");
		break;

		case 17:
			sprintf(caracteristica->carac, "preta");
		break;

		/* Cor da bota. */
		case 18:
			sprintf(caracteristica->carac, "azul");
		break;

		case 19:
			sprintf(caracteristica->carac, "marrom");
		break;

		case 20:
			sprintf(caracteristica->carac, "preta");
		break;

		/* Raça. */
		case 21:
			sprintf(caracteristica->carac, "humano");
		break;

		case 22:
			sprintf(caracteristica->carac, "namekusei");
		break;

		case 23:
			sprintf(caracteristica->carac, "saiyajin");
		break;

		/* Camisa. */
		case 24:
			sprintf(caracteristica->carac, "armadura");
		break;

		case 25:
			sprintf(caracteristica->carac, "treino");
		break;

		case 26:
			sprintf(caracteristica->carac, "sem camisa");
		break;
		
	}
}

void preenche_genetica(Genetica* carac, int pai, int mae, int id, int mut, int dom){
	carac->pai = pai;
	carac->mae = mae;
	carac->id  = id;
	carac->mutante = mut;
	carac->dom = dom;
	preenche_carac(carac);
}

/**********************************************************************************************************************/
/* Imprimindo personagem */

void print_persongem(Tree *personagem){
	char caracteristica[20];
	int dominante;
	Genetica *aux;
	Lista_g *lista = cria_lista_g(TAM);
	preenche_lista_carac(personagem, lista); 

	
	printf("Identificacao: %d--Pai: %d--Mae: %d-----\n", personagem->info->id, personagem->info->pai, personagem->info->mae);

	/* Cor do olho*/
	(lista->vetor[0]->dom > lista->vetor[1]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[1]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[0]->carac));
	printf("olhos cor: ");
	if(lista->vetor[0]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Formato do olho */
	(lista->vetor[2]->dom > lista->vetor[3]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[3]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[2]->carac));
	printf("formato: ");
	if(lista->vetor[2]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Cor do cabelo */
	(lista->vetor[4]->dom > lista->vetor[5]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[5]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[4]->carac));
	printf("cabelos cor: ");
	if(lista->vetor[4]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Tipo do cabelo */
	(lista->vetor[6]->dom > lista->vetor[7]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[7]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[6]->carac));
	printf("tipo: ");
	if(lista->vetor[6]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Calças */
	(lista->vetor[8]->dom > lista->vetor[9]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[9]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[8]->carac));
	printf("membros calca: ");
	if(lista->vetor[8]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Botas */
	(lista->vetor[10]->dom > lista->vetor[11]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[11]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[10]->carac));
	printf("botas cor: ");
	if(lista->vetor[10]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Raça */
	(lista->vetor[12]->dom > lista->vetor[13]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[13]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[12]->carac));
	printf("tronco raca: ");
	if(lista->vetor[12]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Camisa */
	(lista->vetor[14]->dom > lista->vetor[15]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[15]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[14]->carac));
	printf("camisa: ");
	if(lista->vetor[14]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	free_lista_g(lista);
}




/**********************************************************************************************************************/
/* Criando personagens aleatorios*/

int sorteia_numero(int min, int max){
	int num;
	num = rand()%(max - min + 1) + min;
	return num;
}

void personagem_aleatorio(Tree* personagem){
	Lista_g* lista = cria_lista_g(TAM);
	preenche_lista_carac(personagem, lista);

	int seed;
	int gene;

	/* Cor do olho. */
	gene = sorteia_numero(1, 4);
	preenche_genetica(lista->vetor[0], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(1, 4);
	preenche_genetica(lista->vetor[1], 0, 0, personagem->info->id, 0, gene);

	/* Formato do olho. */
	gene = sorteia_numero(5, 6);
	preenche_genetica(lista->vetor[2], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(5, 6);
	preenche_genetica(lista->vetor[3], 0, 0, personagem->info->id, 0, gene);

	/* Cor do cabelo. */
	gene = sorteia_numero(7, 10);
	preenche_genetica(lista->vetor[4], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(7, 10);
	preenche_genetica(lista->vetor[5], 0, 0, personagem->info->id, 0, gene);

	/* Formato do cabelo. */
	gene = sorteia_numero(11, 14);
	preenche_genetica(lista->vetor[6], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(11, 14);
	preenche_genetica(lista->vetor[7], 0, 0, personagem->info->id, 0, gene);

	/* Calças. */
	gene = sorteia_numero(15, 17);
	preenche_genetica(lista->vetor[8], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(15, 17);
	preenche_genetica(lista->vetor[9], 0, 0, personagem->info->id, 0, gene);

	/* Cor da bota. */
	gene = sorteia_numero(18, 20);
	preenche_genetica(lista->vetor[10], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(18, 20);
	preenche_genetica(lista->vetor[11], 0, 0, personagem->info->id, 0, gene);

	/* Raça. */
	gene = sorteia_numero(21, 23);
	preenche_genetica(lista->vetor[12], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(21, 23);
	preenche_genetica(lista->vetor[13], 0, 0, personagem->info->id, 0, gene);

	/* Camisa. */
	gene = sorteia_numero(24, 26);
	preenche_genetica(lista->vetor[14], 0, 0, personagem->info->id, 0, gene);
	gene = sorteia_numero(24, 26);
	preenche_genetica(lista->vetor[15], 0, 0, personagem->info->id, 0, gene);

	free_lista_g(lista);
}



/**********************************************************************************************************************/
/* Cruzamento de personagens */

int** cria_matriz_cruzamentos(int tam){
	int i, j;

	int ** matriz = (int **) malloc(tam*sizeof(int*));

	for(i=0; i<tam; i++){
		matriz[i] = (int *) malloc(tam*sizeof(int));
	}

	for(i=0; i<tam; i++){
		for(j=0; j<tam; j++){
			if(i == j)
				matriz[i][j] = 1;
			else matriz[i][j] = 0;
		}
	}
	return matriz;
}

void libera_matriz(int** matriz, int tam){
	int i;

	for(i=0; i<tam; i++){
		free(matriz[i]);
	}
	free(matriz);
}

void atualiza_cruzamento(int ** matriz, int pai, int mae){
	matriz[pai][mae] = 1;
	matriz[mae][pai] = 1;
}

int cruzamento_possivel(int ** matriz, int pai, int mae){
	return (matriz[pai][mae] == 0);
}

Tree* gera_filho(Lista* lista, int id_pai, int id_mae, int id_filho){
	int mutante, dominante, gene,i;
	Tree *pai = busca_personagem(lista, id_pai);
	Tree *mae = busca_personagem(lista, id_mae);
	Tree *filho = cria_arvore_personagem(id_filho);

	filho->info->pai = id_pai;
	filho->info->mae = id_mae;
	
	Lista_g *carac_pai = cria_lista_g(TAM);
	preenche_lista_carac(pai, carac_pai);
	Lista_g *carac_mae = cria_lista_g(TAM);
	preenche_lista_carac(mae, carac_mae);
	Lista_g *carac_filho = cria_lista_g(TAM);
	preenche_lista_carac(filho, carac_filho);

	for(i = 0; i < TAM; ++i){
		dominante = (carac_pai->vetor[i]->dom > carac_pai->vetor[i+1]->dom) ? carac_pai->vetor[i+1]->dom : carac_pai->vetor[i]->dom;
		preenche_genetica(carac_filho->vetor[i], id_pai, id_mae, id_filho, 0, dominante);

		++i;

		dominante = (carac_mae->vetor[i-1]->dom > carac_mae->vetor[i]->dom) ? carac_mae->vetor[i]->dom : carac_mae->vetor[i-1]->dom;
		preenche_genetica(carac_filho->vetor[i], id_pai, id_mae, id_filho, 0, dominante);
	}

	/* Cor do olho. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(1, 4);
		preenche_genetica(carac_filho->vetor[0], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(1, 4);
		preenche_genetica(carac_filho->vetor[1], id_pai, id_mae, filho->info->id, mutante, gene);
	}
	

	/* Formato do olho. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(5, 6);
		preenche_genetica(carac_filho->vetor[2], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(5, 6);
		preenche_genetica(carac_filho->vetor[3], id_pai, id_mae, filho->info->id, mutante, gene);
	}

	/* Cor do cabelo. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(7, 10);
		preenche_genetica(carac_filho->vetor[4], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(7, 10);
		preenche_genetica(carac_filho->vetor[5], id_pai, id_mae, filho->info->id, mutante, gene);
	}

	/* Formato do cabelo. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(11, 14);
		preenche_genetica(carac_filho->vetor[6], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(11, 14);
		preenche_genetica(carac_filho->vetor[7], id_pai, id_mae, filho->info->id, mutante, gene);
	}
	/* Calças. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(15, 17);
		preenche_genetica(carac_filho->vetor[8], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(15, 17);
		preenche_genetica(carac_filho->vetor[9], id_pai, id_mae, filho->info->id, mutante, gene);
	}

	/* Cor da bota. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(18, 20);
		preenche_genetica(carac_filho->vetor[10], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(18, 20);
		preenche_genetica(carac_filho->vetor[11], id_pai, id_mae, filho->info->id, mutante, gene);
	}

	/* Raça. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(21, 23);
		preenche_genetica(carac_filho->vetor[12], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(21, 23);
		preenche_genetica(carac_filho->vetor[13], id_pai, id_mae, filho->info->id, mutante, gene);
	}
	/* Camisa. */
	mutante = sorteia_numero(1,5);
	if(mutante == 1){
		gene = sorteia_numero(24, 26);
		preenche_genetica(carac_filho->vetor[14], id_pai, id_mae, filho->info->id, mutante, gene);
		gene = sorteia_numero(24, 26);
		preenche_genetica(carac_filho->vetor[15], id_pai, id_mae, filho->info->id, mutante, gene);
	}

	free_lista_g(carac_pai);
	free_lista_g(carac_mae);
	free_lista_g(carac_filho);
	return filho;
}

void descendentes(Lista *lista, int **matriz_cruzamentos){
	Tree *personagem;
	int i, pai, mae;

	for(i = PRIMORDIAIS; i < DESCENDENTES+PRIMORDIAIS; ++i){
		do{
			pai = sorteia_numero(0, PRIMORDIAIS-1);
			mae = sorteia_numero(0, PRIMORDIAIS-1);
		}while(!cruzamento_possivel(matriz_cruzamentos, pai, mae));
		atualiza_cruzamento(matriz_cruzamentos, pai, mae);
		personagem = gera_filho(lista, pai, mae, i);
		insere_lista(lista, i, personagem);
	}
}

void nova_geracao(Lista *lista, int **matriz_cruzamentos){
	Tree *personagem;
	int i, pai, mae;

	for(i = DESCENDENTES+PRIMORDIAIS; i < DESCENDENTES+PRIMORDIAIS+NOVA_G; ++i){
		do{
			pai = sorteia_numero(0, PRIMORDIAIS+DESCENDENTES-1);
			mae = sorteia_numero(0, PRIMORDIAIS+DESCENDENTES-1);
		}while(!cruzamento_possivel(matriz_cruzamentos, pai, mae));
		atualiza_cruzamento(matriz_cruzamentos, pai, mae);
		personagem = gera_filho(lista, pai, mae, i);
		insere_lista(lista, i, personagem);
	}
}

void geracoes(Lista *lista){
	Tree *personagem;
	int **matriz_cruzamentos = cria_matriz_cruzamentos(NOVA_G);
	int i;
	for(i = 0; i < PRIMORDIAIS; ++i){
		personagem = cria_arvore_personagem(i);
		personagem_aleatorio(personagem);
		insere_lista(lista, i, personagem);
	}
	descendentes(lista, matriz_cruzamentos);
	nova_geracao(lista, matriz_cruzamentos);
	libera_matriz(matriz_cruzamentos, NOVA_G);
}

/**********************************************************************************************************************/
/* Verifica entrada */

int verifica_entrada(int tam){
	char entrada[tam];
	scanf("%20s", entrada);
	while(getchar()!='\n');
	int i, valor = 0;

	for(i = 0; entrada[i] != '\0'; i++){
		if(entrada[i] <= '9' && entrada[i] >= '0'){
			valor = valor*10 + (entrada[i]-'0');
		}
		else {
			return -1;
		}
	}
	return valor;
}


/**********************************************************************************************************************/
/* Imprime os personagens */


void mensagens(int m){
	if(m == 1){
		system("clear");
		printf("********************************************************************\n");
		printf("*                        DESENHA PERSONAGEM                        *\n");
		printf("********************************************************************\n\n\n");
	}
	if(m == 2){
		system("clear");
		printf("Fio! Imprimir o que? Você precisa criar uma população primeiro.\n");
		mensagens(4);
	}
	if(m == 3){
		printf("Id inválido!\n");
	}
	if(m == 4){
		printf("\nAperte 'enter' para voltar ao menu.\n");
		while(getchar()!='\n');
	}
	if(m == 5){
		printf("Entrada inválida!\n");
	}
}

void imprime_populacao(Lista *lista){
	int i;
	Nodo *ptr = lista->cabeca;

	while(ptr != NULL){
		print_persongem(ptr->personagem);
		printf("\n\n");
		ptr = ptr->prox;
	}
	mensagens(4);
}

void desenha_personagem(Lista *lista){
	int opcao;
	int invalida = 0;

	do{
		mensagens(1);
		printf("1- Vizualizar personagem único\n");
		printf("2- Vizualizar conjunto de personagens\n");
		printf("3- Vizualizar todos os personagens\n");
		printf("4- Voltar para o menu\n\n");

		if(invalida){
			mensagens(5);
			invalida = 0;
		}
		printf("\nDigite sua opçao: ");
		opcao = verifica_entrada(3);

		if(opcao == 1){
			int id;
			Tree* personagem;

			mensagens(1);
			do{
				printf("Digite o id do personagem: ");
				id = verifica_entrada(3);
				if(id >= 0 && id <= TAM-1){
					personagem = busca_personagem(lista, id);
					printf("\nDesenhando personagem %d...\n", id);
					imprime_personagem(personagem);
					mensagens(4);
				}
				else{
					mensagens(3);
				}
			}while(id < 0 || id > TAM-1);
		}

		else if(opcao == 2){
			int i, n;
			Tree* personagem;

			do{
				printf("Digite quantos personagens deseja vizualizar: ");
				n = verifica_entrada(3);

				if(n >= 1 && n <= TAM){
					int id[TAM];
					mensagens(1);
					printf("Digite os ids:\n");
					for(i = 0; i < n; i++){
						do{
							printf("%d. ", i+1);
							id[i] = verifica_entrada(5);
							if(id[i] < 0 || id[i] > TAM-1){
								mensagens(3);
							}
						}while(id[i] < 0 || id[i] > TAM-1);
					}

					for(i = 0; i < n; i++){
						mensagens(1);
						personagem = busca_personagem(lista, id[i]);
						printf("\nDesenhado personagem %d...\n", id[i]);
						imprime_personagem(personagem);
					}
					mensagens(4);
				}
				else{
					mensagens(5);
				}
			}while(n < 0 || n > TAM);
		}

		else if(opcao == 3){
			Nodo* ptr = lista->cabeca;

			while(ptr != NULL){
				mensagens(1);
				printf("Desenhando personagem %d...\n", ptr->personagem->info->id);
				imprime_personagem(ptr->personagem);
				ptr = ptr->prox;
			}
		}

		else{
			invalida = 1;
		}

	}while(opcao != 4);
}

/**********************************************************************************************************************/
/* Mainzona */

int main(){

	srand(clock());
	Lista *lista = cria_lista();
	int opcao, invalida = 0;
	char certeza[3];


	do{
		system("clear");
		printf("********************************************************************\n");
		printf("*        SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z         *\n");
		printf("********************************************************************\n\n");

		printf("1- Criar população");
		if(vazia_lista(lista)){
			printf(" <-");
		}
		printf("\n");	
		printf("2- Imprimir população\n");
		printf("3- Desenhar personagem\n");
		printf("4- Sair\n\n");

		if(invalida){
			mensagens(5);
			invalida = 0;
		}

		printf("\nDigite sua opção: ");

		opcao = verifica_entrada(3);

		if(opcao == 1){
			if(vazia_lista(lista)){
				geracoes(lista);
			}
			else{
				system("clear");
				printf("Voce já tem uma população. Tem certeza que deseja criar uma nova, a antiga será perdida. (S/N)\n");

				do{
					printf("Digite a sua opção: ");
					scanf("%[^\n]", certeza);
					while(getchar()!='\n');

					if((certeza[0] == 'S' || certeza[0] == 's')  && certeza[1] == '\0'){
						free_lista(lista);
						lista = cria_lista();
						geracoes(lista);
					}
					else if((certeza[0] != 'N' && certeza[0] != 'n') || certeza[1] != '\0'){
						mensagens(5);
					}
				}while((certeza[0] != 'N' && certeza[0] != 'n' && certeza[0] != 'S' && certeza[0] != 's') || certeza[1] != '\0');
			}
		}
		else if(opcao == 2){
			if(vazia_lista(lista)){
				mensagens(2);
			}
			else{
				imprime_populacao(lista);
			}
		}
		else if(opcao == 3){
			if(vazia_lista(lista)){
				mensagens(2);
			}
			else{
				desenha_personagem(lista);
			}
		}
		else{
			invalida = 1;
		}
		
	}while (opcao != 4);

	free_lista(lista);
	return 0;
}