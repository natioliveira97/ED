/** 
	@file Cruzamentos.h
	@author Lívia Gomes Costa Fonseca - 16/0034078
	@author Natalia Oliveira Borges - 16/0015863
	@date 06/2017
	@name SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z
*/

#ifndef __CRUZAMENTOS_H__
#define __CRUZAMENTOS_H__ 


#include "arvore.h"
#include "criador.h"
#include "Lista.h"

/** Define o tamanho da lista de ponteiros para Genetica. */
#define TAM 16 

/** Define a quantidade de personagens aleatórios que serão criados. */
#define PRIMORDIAIS 4

/** Define a quantidade de personagens gerados na primeira geração. */
#define DESCENDENTES 4

/** Define a quantidade de personagens gerados na segunda geração. */
#define NOVA_G 8

/** @brief Preenche uma lista de ponteiros para Genetica.
	@details Recebe um personagem do tipo Tree* em que cada nodo possui uma estrutura do tipo Genetica*. Percorre recursivamente
	a árvore e se o nodo for folha, insere o endereço de sua 'info' na lista de ponteiros para Genetica.
	@param personagem Variável do tipo Tree* que será percorrida.
	@param lista Variável do tipo Lista_g* que será preenchida com o endereço dos nós folhas da árvore.
	@return A função não possui retorno.
*/
void preenche_lista_carac(Tree* personagem, Lista_g* lista);

/** @brief Preenche o campo carac da estrutura Genetica.
	@details Recebe um ponteiro para Genetica e preenche o campo carac com o nome da caracteristica correspondente.
	@param caracteristica Variável do tipo Genetica*.
	@return A função não possui retorno.
*/ 
void preenche_carac(Genetica *caracteristica);

/** @brief Preenche a struct Genetica.
	@details Recebe parâmetros e preenche os campos da struct genética.
	@param carac Variável do tipo Genetica que será preenchida.
	@param pai Id do pai.
	@param mae Id da mae.
	@param id Id do personagem.
	@param mut Flag que indica de essa caracteristica é mutante ou não.
	@param dom Dominância do gene.
	@return A função não possui retorno.
*/
void preenche_genetica(Genetica* carac, int pai, int mae, int id, int mut, int dom);

/** @brief Sorteia um número.
	@details Sorteia um número no intervalo passado.
	@param min número mínimo que pode retornar.
	@param max número máximo que pode retornar.
	@return A função retorna o inteiro sorteado.
*/ 
int sorteia_numero(int min, int max);

/** @brief Cria um personagem aleatório.
	@details Preeenche as características do personagem com valores aleatórios, dentro do intervalo de cada características.
	@param personagem Variável do tipo Tree* que contém o personagem a ser preeenchido.
	@return A função não possui retorno.
*/
void personagem_aleatorio(Tree* personagem);

/** @brief Cria a matriz de cruzamentos.
	@details Aloca na memória heap uma matriz de inteiros com sua diagonal principal preenchida com o valor 1, e o resto com o valor 0.
	@param tam Variável do tipo int correspondente ao tamanho da matriz a ser criada.
	@return A função retorna um ponteiro pra ponteiro de inteiro.
*/
int** cria_matriz_cruzamentos(int tam);

/** @brief Apaga a matriz.
	@details Libera a memória alocada pela matriz.
	@param matriz Matriz a ser liberada.
	@param tam Tamanho da matriz a ser liberada.
	@return A função não possui retorno.
*/
void libera_matriz(int** matriz, int tam);

/** @brief Atualiza o cruzamento na matriz de cruzamantos.
	@details Preenche com o valor 1 os campos matriz[pai][mae] e matriz[mae][pai] para mostrar que aquele cruzamanto já foi feito.
	@param matriz Matriz de cruzamantos.
	@param pai Id do pai.
	@param mae Id da mãe.
	@return A função não possui retorno.
*/
void atualiza_cruzamento(int ** matriz, int pai, int mae);

/** @brief Verifica se o cruzamanto é possível.
	@details Verifica se o campo correspondente ao cruzamanto desse pai com essa mãe está preenchido com o valor 0.
	@param matriz Matriz de cruzamantos.
	@param pai Id do pai.
	@param mae Id da mãe.
	@return !0 Se o cruzamento é possível.
	@return 0 Se o cruzamento não for possível.
*/
int cruzamento_possivel(int ** matriz, int pai, int mae);

/** @brief Gera um personagem a partir do cruzamanto de dois outros.
	@details Cria um personagem preenchido com os genes dominantes do pai e da mãe, ou genes mutantes com chance de 20%.
	@param lista Variável do tipo Lista* que contém a lista com todos os personagens da população.
	@param id_pai Inteiro que corresponde ao id do pai.	
	@param id_mae Inteiro que corresponde ao id da mãe.	
	@param id_filho Inteiro que corresponde ao id do filho.
	@return Ponteiro para o novo personagem criado.
*/
Tree* gera_filho(Lista* lista, int id_pai, int id_mae, int id_filho);

/** @brief Cria os personagens descendentes.
	@details Cria os personagens com ids de 5 a 8 a partir dos cruzamentos aleatórios dos 4 personagens primordiais.
	@param lista Variável do tipo Lista* que contém a lista com todos os personagens da população.
	@param matriz_cruzamentos Variável do tipo int** que corresponde a matriz de cruzamentos.
	@return A função não possui retorno.
*/
void descendentes(Lista *lista, int **matriz_cruzamentos);

/** @brief Cria a nova geração de personagens.
	@details Cria os personagens com ids de 9 a 16 a partir dos cruzamentos aleatórios dos 8 personagens já existentes.
	@param lista Variável do tipo Lista* que contém a lista com todos os personagens da população.
	@param matriz_cruzamentos Variável do tipo int** que corresponde a matriz de cruzamentos.
	@return A função não possui retorno.
*/
void nova_geracao(Lista *lista, int **matriz_cruzamentos);

/** @brief Cria a população.
	@details Cria os personagens primordiais de forma aleatória, os decendentes e a nova geração.
	@param lista Variável do tipo Lista* que contém a lista com todos os personagens da população.
	@return A função não possui retorno.
*/
void geracoes(Lista *lista);

#endif