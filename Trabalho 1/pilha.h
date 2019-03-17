/** 
	\file pilha.h
	\author Natalia Oliveira Borges - 16/0015863
	\date 04/17
	\name Resolução de Expressōes e Calculadora
*/

#ifndef __PILHA_H__
#define __PILHA_H__

// Definiçōes:

/** O tipo elemento (t_elemento) é formado por um ponto flutuante (dado) e um ponteiro (anterior) para o t_elemento anterior a ele em uma pilha.*/
typedef struct elemento{
	double dado;
	struct elemento *anterior;
}t_elemento;

/** O tipo pilha (t_pilha) é formado por um ponteiro (topo) que determina o topo da pilha.*/
typedef struct pilha{
	t_elemento *topo;
}t_pilha;

// Assinaturas das funçōes:

/** \brief Cria uma pilha.
	\details Aloca memória para uma estrutura do tipo t_pilha e inicializa o topo da pilha com NULL.
	\return A função retorna um ponteiro para o tipo t_pilha.
*/
t_pilha* get_pilha();

/** \brief Cria um elemento da pilha.
	\details Aloca memória heap para uma estrutura do tipo t_elemento e inicializa o valor de dado do elemento com o parametro passado e o ponteiro para o elemento anterior com NULL.
	\param dado Ponto flutuante que será atribuido a variável 'dado' do tipo t_elemento.
	\return A função retorna um ponteiro para o tipo t_elemento.
*/
t_elemento* get_elemento(double dado);

/** \brief Verifica se a pilha está vazia.
	\details Verifica se o ponteiro para o topo da pilha aponta para NULL, se sim, está vazia.
	\param pilha Ponteiro para uma estrutura do tipo t_pilha.
	\return A função retorna 1 se a pilha estiver vazia 0 se não estiver vazia.
*/
int pilha_vazia(t_pilha *pilha);

/** \brief Insere um elemento na pilha.
	\details Chama a função get_elemento para alocar um elemento e atualiza o topo da pilha com o endereço desse elemento.
	\param pilha Ponteiro para uma estrutura do tipo t_pilha.
	\param dado Ponto flutuante que será passado a função get_elemento.
	\return Essa função não possui retorno.
*/
void inserir_elemento(t_pilha *pilha, double dado);

/** \brief Retira um elemento da pilha.
	\details Verifica se é possível retirar um elemento da pilha e se for libera a memória do elemento alocado no topo da pilha e atualiza o topo da pilha.
	\param pilha Ponteiro para uma estrutura do tipo t_pilha.
	\return A função retorna 0 se não for possível retirar um elemento e retorna 1 se conseguir retirar esse elemento.
*/
int retirar_elemento(t_pilha *pilha);

/** \brief Libera a memória alocada para a pilha.
	\details Enquanto o topo da pilha não é NULL retira-se um elemento dela, ao final, libera-se a memória alocada pela estrutura pilha.
	\param pilha Ponteiro para uma estrutura do tipo t_pilha.
	\return Essa função não possui retorno.
*/
void libera_pilha(t_pilha *pilha);

/** \brief Verifica quantos elemento tem na pilha.
	\details Percorre a pilha e enquanto houver elementos a serem vizitados, acrescenta uma variável tamanho.
	\param pilha Ponteiro para uma estrutura do tipo t_pilha.
	\return A função retorna o número de elementos presentes na pilha.
*/
int tamanho_pilha(t_pilha *pilha);

/** \brief Imprime a pilha.
	\details Percorre a pilha e imprime os dados armazenados do começo até o topo.
	\param pilha Ponteiro para uma estrutura do tipo t_pilha.
	\return Essa função não possui retorno.
*/
void imprime_pilha(t_pilha *pilha);

#endif