/** 
	@file Interface.h
	@author Lívia Gomes Costa Fonseca - 16/0034078
	@author Natalia Oliveira Borges - 16/0015863
	@date 06/2017
	@name SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z
*/

#ifndef __INTERFACE_H__
#define __INTERFACE_H__ 

#include "arvore.h"
#include "Lista.h"

/** @brief Lê uma entrada verificando se é válida.
    @details Lê uma entrada, com limitação de 20 caracteres, verifica se a entrada é válida e retorna o inteiro correspondente.
	@return A função retorna o inteiro correspondente quando a entrada é válida.
	@return A função retorna -1 quando a entrada é inválida. 
*/
int verifica_entrada();

/** @brief Imprime mensagens na tela.
	@details A função contém alguns conjuntos de mensagens que poderão ser impressos na tela. O conjunto a ser impresso é definido
	pelo parâmetro recebido.
	@param m Parâmetro do tipo inteiro que determina qual conjunto de mensagens será impresso na tela.
	@return A função não possui retorno.
*/
void mensagens(int m);

/** @brief Imprime na tela as características de um personagem.
	@details Imprime na tela o id do personagem, os ids do pai e da mãe, o gene dominante de cada caracterśtica
	e mostra se esse gene é mutante.
	@param personagem Variável do tipo Tree* que indica o personagem a ser impresso.
	@return A função não possui retorno.
*/
void print_persongem(Tree *personagem);

/** @brief Imprime na tela a população criada.
	@details Imprime na tela as características de todos os personagens da população.
	@param lista Variável do tipo Lista* que contém a lista com todos os personagens da população.
	@return A função não possui retorno.
*/
void print_populacao(Lista *lista);

/** @brief Desenha, em uma interface gráfica, os personagens.
	@details A função exibe um menu com as opções para se desenhar um personagem, um conjunto de personagens, a população inteira ou para sair.
	Caso o usuário escolha desenhar um śo personagem, um id é pedido e o personagem correspondente é desenhado.
	Caso o usuário escolha desenhar um conjunto de personagens, a quantidade a ser desenhada é pedida, e, em seguida, os ids. 
	Os personagens são mostrados na ordem dos ids fornecidos.
	Caso o usuário escolha desenhar toda a população, os personagens serão desenhados na ordem crescente de seus ids.
	A função encerra quando o usuário seleciona a opção sair.
	@param lista Variável do tipo Lista* que contém a lista com todos os personagens da população.
	@return A função não possui retorno.
*/
void desenha_personagem(Lista *lista);

#endif