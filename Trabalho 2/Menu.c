/** 
	@file Menu.c
	@author Lívia Gomes Costa Fonseca - 16/0034078
	@author Natalia Oliveira Borges - 16/0015863
	@date 06/2017
	@name SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "printPersonagem.h"
#include "arvore.h"
#include "criador.h"
#include "Lista.h"
#include "Cruzamentos.h"
#include "Interface.h"


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

		opcao = verifica_entrada();

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
				print_populacao(lista);
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
