/** 
	\file calculadora.h
	\author Natalia Oliveira Borges - 16/0015863
	\date 04/17
	\name Resolução de Expressōes e Calculadora
*/

#ifndef __CALCULADORA_H__
#define __CALCULADORA_H__

// Definiçōes das funçōes:

/** \brief Transforma uma entrada de caracteres numéricos em número.
	\details Recebe um vetor de caracteres numéricos e, por meio da multiplicação por base 10 dos algarismos, transforma em um ponto flutuante.
	\param número Ponteiro para o primeiro elemento de um vetor de caracteres.
	\param tamanho Número de caracteres presentes no vetor
	\return A função retorna um ponto flutuante equivalente a expressão numérica recebida.
*/
double transforma_em_numero(char *numero, int tamanho);

/** \brief Imprime o número.
	\details Caso o número seja inteiro, não imprime parte decimal. Caso seja ponto flutuante, imprime a parte decimal e muda o '.' pela ','.
	\param número Ponto flutuante
	\return Essa função não possui retorno.
*/
void imprime_numero(double numero);

/** \brief Verifica se o caractere é válido.
	\details A expressão deve aceitar apenas caracteres numéricos (0 a 9), sinais operadores (+ - * /), delimitadores de escopos ( () [] {} ), virgula indicadora de casas decimais (,) e espaços.
	\param c Caractere a ser analisado.
	\return Retorna 1 se o caractere for válido e 0 se não for.
*/
int caractere_valido(char c);

/** \brief Verifica se a equação é sintaticamente correta.
	\details Percorre toda a equação e verifica se todos os caracteres são válidos, se não há operadores ou operandos em excesso, e se a ordem entre eles foi respeitada.
	\param expressão Ponteiro para o primeiro elemento de um vetor de caracteres.
	\param tamanho Número de caracteres presentes no vetor.
	\return Retorna 1 se for válida e 0 se não for.
*/
int validacao_de_equacao(char *expressao, int tamanho);

/** \brief Verifica se os delimitadores de equação estão sintaticamente corretos.
	\details Percorre toda a equacão e verifica se todos os inicializadores de escopos foram fechados na ordem correta.
	\param expressão Ponteiro para o primeiro elemento de um vetor de caracteres.
	\param tamanho Número de caracteres presentes no vetor.
	\return Retorna 1 se for válida e 0 se não for.
*/
int validacao_de_escopo(char *expressao, int tamanho);

/** \brief Verifica se a entrada é valida
	\details Chama as funçōes que verificam a equação e os delimitadores de escopos.
	\param expressão Ponteiro para o primeiro elemento de um vetor de caracteres.
	\param tamanho Número de caracteres presentes no vetor.
	\return Retorna 1 se for válida e 0 se não for.
*/
int validacao_de_entrada(char *expressao, int tamanho);

/** \brief Cria uma expressão posfixa correspondente a expressão infixa dada.
	\details Aloca memória para uma expressão posfixa e inicializa com uma expressão correspondente a expressão dada.
	\param expressão Ponteiro para o primeiro elemento de um vetor de caracteres.
	\param tamanho Número de caracteres presentes no vetor.
	\return Retorna um ponteiro para a expressao posfixa alocada.
*/
char* forma_posfixa(char *expressao, int tamanho);

/** \brief Resolve a expressão dada.
	\details Recebe uma expressão posfixa e chega a um resultado.
	\param expressão Ponteiro para o primeiro elemento de um vetor de caracteres.
	\param tamanho Número de caracteres presentes no vetor.
	\return Retorna ponto flutuante resultado das operaçōes.
*/
double avalia_expressao(char *expressao, int tamanho);

/** \brief Atualiza a pilha da calculadora após uma entrada.
	\delais Verifica se a entrada é válida e se for atualiza a pilha com o número adicionado ou com a operção realizada.
	\param calculadora Pilha que armazena pontos flutuantes.
	\param entrada Ponteiro para o primeiro elemento de um vetor de caracteres.
	\return 0 Se a entrada for o critério de saida.
	\return 1 Se adicionar o número recebido na pilha ou realizar a operação recebida corretamente.
	\return 2 Se não houver números suficientes para realizar a operação.
	\return 3 Se a entrada for inválida
	\return 4 Se o número dado a operação copia não for inteiro positivo.
*/
int atualiza_calculadora(t_pilha *calculadora, char *entrada);

/** \brief Entra no modo resolução de expressōes.
	\return Essa função não possui retorno.
*/
void resolucao_de_expressao();

/** \brief Entra no modo calculadora.
	\return Essa função não possui retorno.
*/
void calculadora();

#endif