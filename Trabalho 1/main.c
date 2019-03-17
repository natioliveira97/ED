/** 
	\file main.c
	\author Natalia Oliveira Borges - 16/0015863
	\date 04/17
	\name Resolução de Expressōes e Calculadora
*/

#include <stdio.h> 
#include <stdlib.h>
#include "pilha.h" /* Biblioteca de funçōes para tipo pilha. */
#include "calculadora.h" /* Biblioteca de funçōes para calculadora */

/** \brief Executa a calculadora.
	\details Menu para as funcionalidades resolução de expressōes e calculadora.
	\return A função retorna 0.
*/

int main(){
	char opcao = '0';

	while(opcao != '3'){
		system("clear");
		printf("****************************************************\n");
		printf("*                        Menu                      *\n");
		printf("****************************************************\n\n");
		printf("1-Resolução de Expressōes\n");
		printf("2-Calculadora\n");
		printf("3-Sair\n\n");
		printf("Digite a sua opção:\n");

		opcao = getchar();
		while(getchar() != '\n');

		if(opcao == '1'){
			resolucao_de_expressao();
		}
		if(opcao == '2'){
			calculadora();
		}
	}
	return 0;
}