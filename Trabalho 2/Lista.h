/** 
	@file Lista.h
	@author Lívia Gomes Costa Fonseca - 16/0034078
	@author Natalia Oliveira Borges - 16/0015863
	@date 06/2017
	@name SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z
*/

#ifndef __LISTA_H__
#define __LISTA_H__ 

#include "arvore.h"

/**********************************************************************************************************************/
/* Lista de Tree */

/** O tipo Nodo é formado por uma variável 'personagem' do tipo Tree* e um ponteiro para o nodo anterior e próximo. */
typedef struct nodo{
	Tree* personagem;
	struct nodo* prox;
	struct nodo* ant; 
}Nodo;

/** O tipo Lista é formado por uma variável 'cabeca' do tipo Nodo* que aponta para o primeiro elemento da lista. */
typedef struct lista{  
	Nodo* cabeca;
}Lista;

/** @brief Cria uma lista de ponteiros para o tipo Tree.
	@details Aloca memória heap para uma estrutura do tipo Lista* e inicializa a cabeça da lista com NULL.
	@return A função retorna um ponteiro para o tipo Lista.
*/
Lista* cria_lista();

/** @brief Cria um nodo da árvore.
	@details Aloca memória heap para uma estrutura do tipo Nodo* e inicializa a variável de personagem do nodo com o parâmetro
	passado e os ponteiro para o nodo anterior e próximo com NULL.
	@param personagem Variável do tipo Tree* que será atribuída a variável 'personagem' do Nodo.
	@return A função retorna um ponteiro para o tipo Nodo.
*/
Nodo* cria_nodo(Tree* personagem);

/** @brief Verifica se a lista está vazia.
	@details Verifica se o ponteiro para a cabeça possui um endereço ou está NULL.
	@param cabeca Variável do tipo Lista*.
	@return 1 (Verdadeiro) se a lista estiver vazia.
	@return 0 (Falso) se a lista não estiver vazia.
*/
int vazia_lista(Lista* cabeca);

/** @brief Insere um nodo na lista.
	@details Coloca um nodo na lista na posição desejada.
	@param cabeca Variável do tipo Lista*.
	@param personagem Variável do tipo Tree* que será atribuída a variável 'personagem' do Nodo.
	@param posição Inteiro que define a posição desejada.
	@return A função não possui retorno.
*/
void insere_lista(Lista* cabeca, int posicao, Tree* personagem);

/** @brief Busca um nodo da lista.
	@details Encontra um nodo da lista que possui o id procurado e retorna o ponteiro para esse nodo. Será utilizada apenas para ids válidos.
	@param lista Variável do tipo Lista*.
	@param id Inteiro que indica o id do personagem procurado.
	@return A Função retorna um ponteiro para um tipo Tree.
*/
Tree* busca_personagem(Lista *lista, int id);

/** @brief Retira um nodo da lista.
	@details Retira um nodo da lista na posição desejada.
	@param cabeca Variável do tipo Lista*.
	@param posição Inteiro que define a posição desejada.
	@return A função não possui retorno.
*/
void remove_lista(Lista* cabeca, int posicao);

/** @brief Libera a memória alocada pela lista.
	@details Enquanto a lista não estiver vazia, retira o primeiro elemento.
	@param cabeca Variável do tipo Lista*.
	@return A função não possui retorno.
*/
void free_lista(Lista* cabeca);


/**********************************************************************************************************************/
/* Lista de Genetica */

/** O Tipo Lista_g é formado por um vetor de ponteiros para o tipo Genetica, e possui um inteiro indicando o fim e o tamanho desse vetor. */
typedef struct lista_g{  
	Genetica **vetor;
	int tamanho;
	int fim;
}Lista_g;

/** @brief Cria uma lista de ponteiros para o tipo Genetica.
	@details Aloca memória heap para uma estrutura do tipo Lista_g* e para o vetor de ponteiros para Genetica com o tamanho dado,
	inicializa o fim da lista como 0.
	@param tamanho Recebe o tamanho do vetor que se deseja alocar.
	@return A função retorna um ponteiro para o tipo Lista_g.
*/
Lista_g* cria_lista_g(int tamanho);

/** @brief Insere um emento na lista. 
	@details Insere um elemento no fim da lista.
	@param lista Variável do tipo Lista_g*.
	@param carac Variável do tipo Genetica* que será inserida no fim da lista.
	@return A função não possui retorno.
*/
void insere_lista_g(Lista_g* lista, Genetica* carac);

/** @brief Libera a memória alocada pela lista. 
	@details Libera a memória alocada pelo vetor de ponteiros para Genetica e pela estrutura Lista_g*.
	@param lista Variável do tipo Lista_g*.
	@return A função não possui retorno.
*/
void free_lista_g(Lista_g* lista);

#endif