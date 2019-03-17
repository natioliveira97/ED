/** 
	\file pilha.c
	\author Natalia Oliveira Borges - 16/0015863
	\date 04/17
	\name Resolução de Expressōes e Calculadora
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h" /* Biblioteca de funçōes para tipo pilha. */
#include "calculadora.h" /* Biblioteca de funçōes para calculadora */

// Implementação das funçōes:

t_pilha* get_pilha(){
	t_pilha *ptr = (t_pilha *)malloc(sizeof(t_pilha));
	ptr->topo    = NULL;
	return ptr;
}

t_elemento* get_elemento(double dado){
	t_elemento *ptr = (t_elemento *)malloc(sizeof(t_elemento));
	ptr->dado       = dado;
	ptr->anterior   = NULL;
	return ptr;
}

int pilha_vazia(t_pilha *pilha){
	return(pilha->topo == NULL);
}

void inserir_elemento(t_pilha *pilha, double dado){
	t_elemento *ptr = get_elemento(dado);
	ptr->anterior   = pilha->topo;
	pilha->topo     = ptr;
}

int retirar_elemento(t_pilha *pilha){
	if (pilha_vazia(pilha)){
		printf("Não foi possível retirar elemento, a pilha está vazia.\n");
		return 0;
	}
	else{
		t_elemento *ptr = pilha->topo;
		pilha->topo     = pilha->topo->anterior;
		free(ptr);
		return 1;
	}
}

void libera_pilha(t_pilha *pilha){
	while (pilha->topo != NULL){
		retirar_elemento(pilha);
	}
	free(pilha);
}

int tamanho_pilha(t_pilha *pilha){
	t_elemento *ptr = pilha->topo;
	int tamanho     = 0; //Tamanho da pilha. 
	while (ptr != NULL){
		++tamanho;
		ptr = ptr->anterior;
	}
	return tamanho;
}

void imprime_pilha(t_pilha *pilha){
	int tamanho; // Tamanho da pilha.
	int posicao; // Posição do elemento na pilha.
	int i,j=1;

	t_elemento *ptr = pilha->topo;
	tamanho         = tamanho_pilha(pilha);

	if(tamanho == 0){
		printf("Pilha Vazia.\n");
	}
	for(posicao = tamanho; posicao >= 1; --posicao){
		printf("%d. ",posicao);
		for(i=0; i<tamanho-j; ++i){
			ptr = ptr->anterior;
		}
		++j;
		imprime_numero(ptr->dado);
		ptr = pilha->topo;
	}
}