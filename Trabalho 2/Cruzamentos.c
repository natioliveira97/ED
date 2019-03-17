/** 
	@file Cruzamentos.c
	@author Lívia Gomes Costa Fonseca - 16/0034078
	@author Natalia Oliveira Borges - 16/0015863
	@date 06/2017
	@name SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z
*/
#include <stdio.h>
#include <stdlib.h>
#include "Cruzamentos.h"

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

int sorteia_numero(int min, int max){
	int num;
	num = rand()%(max - min + 1) + min;
	return num;
}

void personagem_aleatorio(Tree* personagem){
	int gene;
	Lista_g* lista = cria_lista_g(TAM);
	preenche_lista_carac(personagem, lista);

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

int** cria_matriz_cruzamentos(int tam){
	int i, j;
	int ** matriz = (int **) malloc(tam*sizeof(int*));

	for(i = 0; i < tam; i++){
		matriz[i] = (int *) malloc(tam*sizeof(int));
	}

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			if(i == j){
				matriz[i][j] = 1;
			}
			else matriz[i][j] = 0;
		}
	}

	return matriz;
}

void libera_matriz(int** matriz, int tam){
	int i;

	for(i = 0; i < tam; i++){
		free(matriz[i]);
	}
	free(matriz);
}

void atualiza_cruzamento(int ** matriz, int pai, int mae){
	matriz[pai-1][mae-1] = 1;
	matriz[mae-1][pai-1] = 1;
}

int cruzamento_possivel(int ** matriz, int pai, int mae){
	return (matriz[pai-1][mae-1] == 0);
}

Tree* gera_filho(Lista* lista, int id_pai, int id_mae, int id_filho){
	int mutante, dominante, gene, i;

	/* Primeiramente, procura-se a árvore dos personagens pai e mãe na lista. */
	Tree *pai   = busca_personagem(lista, id_pai);
	Tree *mae   = busca_personagem(lista, id_mae);

	/* Cria-se um personagem vazio que será o filho. */	
	Tree *filho = cria_arvore_personagem(id_filho);

	/* Os campos de pai e mae da raiz da árvore de personagem são preenchidos. */
	filho->info->pai = id_pai;
	filho->info->mae = id_mae;
	
	/* Cria-se uma lista com ponteiros para a estrutura Genética dos nós folhas do pai, da mãe e do filho. */
	Lista_g *carac_pai = cria_lista_g(TAM);
	preenche_lista_carac(pai, carac_pai);
	Lista_g *carac_mae = cria_lista_g(TAM);
	preenche_lista_carac(mae, carac_mae);
	Lista_g *carac_filho = cria_lista_g(TAM);
	preenche_lista_carac(filho, carac_filho);

	/* Para cada característica escolhemos o gene dominane do pai e o gene dominante da mãe para preencher os genes do filho. */
	for(i = 0; i < TAM; ++i){
		dominante = (carac_pai->vetor[i]->dom > carac_pai->vetor[i+1]->dom) ? carac_pai->vetor[i+1]->dom : carac_pai->vetor[i]->dom;
		preenche_genetica(carac_filho->vetor[i], id_pai, id_mae, id_filho, 0, dominante);

		++i;

		dominante = (carac_mae->vetor[i-1]->dom > carac_mae->vetor[i]->dom) ? carac_mae->vetor[i]->dom : carac_mae->vetor[i-1]->dom;
		preenche_genetica(carac_filho->vetor[i], id_pai, id_mae, id_filho, 0, dominante);
	}

	/* Para cada característica, sortemos um número entre 1 e 5 para indicar mutação, se der 1 (há 20% de chance disso ocorrer),
	   sorteamos dois genes aleátórios para essa caracteristica e setamos a variável mutante de Genetica como 1.*/

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

	/* Liberamos as listas de ponteiros para Genética, afinal elas são apenas auxiliares no processo de leitura e preenchimento da árvore. */
	free_lista_g(carac_pai);
	free_lista_g(carac_mae);
	free_lista_g(carac_filho);

	return filho;
}

void descendentes(Lista *lista, int **matriz_cruzamentos){
	Tree *personagem;
	int i, pai, mae;

	for(i = PRIMORDIAIS+1; i <= DESCENDENTES+PRIMORDIAIS; ++i){
		do{
			pai = sorteia_numero(1, PRIMORDIAIS);
			mae = sorteia_numero(1, PRIMORDIAIS);
		}while(!cruzamento_possivel(matriz_cruzamentos, pai, mae));
		atualiza_cruzamento(matriz_cruzamentos, pai, mae);
		personagem = gera_filho(lista, pai, mae, i);
		insere_lista(lista, i, personagem);
	}

}

void nova_geracao(Lista *lista, int **matriz_cruzamentos){
	Tree *personagem;
	int i, pai, mae;

	for(i = DESCENDENTES+PRIMORDIAIS+1; i <= DESCENDENTES+PRIMORDIAIS+NOVA_G; ++i){
		do{
			pai = sorteia_numero(1, PRIMORDIAIS+DESCENDENTES);
			mae = sorteia_numero(1, PRIMORDIAIS+DESCENDENTES);
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

	for(i = 1; i <= PRIMORDIAIS; ++i){
		personagem = cria_arvore_personagem(i);
		personagem_aleatorio(personagem);
		insere_lista(lista, i, personagem);
	}
	descendentes(lista, matriz_cruzamentos);
	nova_geracao(lista, matriz_cruzamentos);
	
	libera_matriz(matriz_cruzamentos, NOVA_G);
}