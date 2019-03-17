/** 
	@file Lista.c
	@author Lívia Gomes Costa Fonseca - 16/0034078
	@author Natalia Oliveira Borges - 16/0015863
	@date 06/2017
	@name SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z
*/

#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"

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
	int i;

	/* Se não houver elementos na lista, apenas aponta a cabeça da lista para o elemento criado. */
	if(vazia_lista(cabeca)){
		cabeca->cabeca = ptr;
	}
	/* Se a posição de inserção for 0 ou menor que 0 o elemento é colocado no inicio da lista. */
	else if (posicao <= 0){
		cabeca->cabeca->ant = ptr;
		ptr->prox = cabeca->cabeca;
		cabeca->cabeca = ptr;
	}
	/* Se a posição for maior que 0. */
	else if (posicao > 0){
		Nodo *aux = cabeca->cabeca;

		/* Anda com o ponteiro aux até a posição anterior a que se deseja inserir o novo elemento.
		   Se a posição desejada for maior que a quantidade de elementos na lista, o elemento é inserido no final. */
		for(i = 0; i < posicao-1 && aux->prox != NULL; ++i){
			aux = aux->prox;
		}

		/* Seta as variáveis de anterior e próximo do elemento criado. */
		ptr->prox = aux->prox;
		ptr->ant  = aux;

		/* Seta as variáveis de anterior e próximo dos elementos ligados ao elemento criado. */
		if(aux->prox != NULL){
			aux->prox->ant = ptr;
		}
		aux->prox = ptr;
	}
}

Tree* busca_personagem(Lista *lista, int id){
	int i;
	Nodo *ptr = lista->cabeca;
	
	for(i = 1; i < id && ptr!= NULL; ++i){
		ptr = ptr->prox;
	}
	return ptr->personagem;
}

void remove_lista(Lista* cabeca, int posicao){
	int i;
	if(!vazia_lista(cabeca)){
		Nodo *ptr = cabeca->cabeca;

		/* Anda com o ponteiro ptr até a posição que se deseja retirar o elemento.
		   Se a posição desejada for maior que a quantidade de elementos na lista, retira-se o elemento do final.
		   Se a posição desejada for menor que 0, retira-se o elemento do começo. */
		for(i = 0; i < posicao && ptr->prox != NULL; ++i){
			ptr = ptr->prox;
		}

		/* Se o elemento que se deseja retirar é a cabeça da lista, atualiza a cabeça. */
		if(ptr == cabeca->cabeca){
			cabeca->cabeca = ptr->prox;
		}
		/* Se o elemento que se deseja retirar está ligado a um anterior, atualiza a variável 'prox' do anterior. */
		else{
			ptr->ant->prox = ptr->prox;
		}
		/* Se o elemento que se deseja retirar está ligado a um próximo, atualiza a variável 'ant' do próximo. */
		if(ptr->prox != NULL){
			ptr->prox->ant = ptr->ant;
		}
		tree_free(ptr->personagem);
		free(ptr);		
	}
}

void free_lista(Lista* cabeca){
	while(!vazia_lista(cabeca)){
		remove_lista(cabeca,0);
	}
	free(cabeca);
}


/**********************************************************************************************************************/
/* Lista de Genetica */

Lista_g* cria_lista_g(int tamanho){

	Lista_g *lista  = (Lista_g *)malloc(sizeof(Lista_g));

	lista->vetor = (Genetica **)malloc(sizeof(Genetica *)*tamanho);
	lista->tamanho = tamanho;
	lista->fim = 0;

	return lista;
}

void insere_lista_g(Lista_g* lista, Genetica* carac){
	if(lista->fim >= lista->tamanho){
		printf("A lista está totalmente preeenchida.\n");
	}

	else{
		lista->vetor[lista->fim] = carac;
		++lista->fim;
	}
}

void free_lista_g(Lista_g* lista){
	free(lista->vetor);
	free(lista);
}