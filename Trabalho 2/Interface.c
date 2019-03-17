/** 
	@file Interface.c
	@author Lívia Gomes Costa Fonseca - 16/0034078
	@author Natalia Oliveira Borges - 16/0015863
	@date 06/2017
	@name SUPER ULTRA MEGA ÁRVORE GENEALÓGICA DRAGON BALL Z
*/

#include <stdio.h>
#include <stdlib.h>
#include "printPersonagem.h"
#include "Cruzamentos.h"
#include "Interface.h"

int verifica_entrada(){
	char entrada[20];
	scanf("%20s", entrada);
	while(getchar()!='\n');
	int i, valor = 0;

	for(i = 0; entrada[i] != '\0'; i++){
		if(entrada[i] <= '9' && entrada[i] >= '0'){
			valor = valor*10 + (entrada[i]-'0');
		}
		else {
			return -1;
		}
	}
	return valor;
}

void mensagens(int m){
	if(m == 1){
		system("clear");
		printf("********************************************************************\n");
		printf("*                        DESENHA PERSONAGEM                        *\n");
		printf("********************************************************************\n\n\n");
	}
	if(m == 2){
		system("clear");
		printf("Fio! Imprimir o que? Você precisa criar uma população primeiro.\n");
		mensagens(4);
	}
	if(m == 3){
		printf("Id inválido!\n");
	}
	if(m == 4){
		printf("\nAperte 'enter' para voltar ao menu.\n");
		while(getchar()!='\n');
	}
	if(m == 5){
		printf("Entrada inválida!\n");
	}
}

void print_personagem(Tree *personagem){
	char caracteristica[20];
	int dominante;

	/* Cria-se uma lista de ponteiros para Genetica com os nós folhas da árvore do personagem. */
	Lista_g *lista = cria_lista_g(TAM);
	preenche_lista_carac(personagem, lista); 

	
	printf("-Identificacao: %d--Pai: %d--Mae: %d-----\n", personagem->info->id, personagem->info->pai, personagem->info->mae);

	/* Cor do olho*/
	(lista->vetor[0]->dom > lista->vetor[1]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[1]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[0]->carac));
	printf("olhos cor: ");
	if(lista->vetor[0]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Formato do olho */
	(lista->vetor[2]->dom > lista->vetor[3]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[3]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[2]->carac));
	printf("formato: ");
	if(lista->vetor[2]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Cor do cabelo */
	(lista->vetor[4]->dom > lista->vetor[5]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[5]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[4]->carac));
	printf("cabelos cor: ");
	if(lista->vetor[4]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Tipo do cabelo */
	(lista->vetor[6]->dom > lista->vetor[7]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[7]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[6]->carac));
	printf("tipo: ");
	if(lista->vetor[6]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Calças */
	(lista->vetor[8]->dom > lista->vetor[9]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[9]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[8]->carac));
	printf("membros calca: ");
	if(lista->vetor[8]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Botas */
	(lista->vetor[10]->dom > lista->vetor[11]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[11]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[10]->carac));
	printf("botas cor: ");
	if(lista->vetor[10]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Raça */
	(lista->vetor[12]->dom > lista->vetor[13]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[13]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[12]->carac));
	printf("tronco raca: ");
	if(lista->vetor[12]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	/* Camisa */
	(lista->vetor[14]->dom > lista->vetor[15]->dom) ? (sprintf(caracteristica, "%s", lista->vetor[15]->carac)) : (sprintf(caracteristica, "%s", lista->vetor[14]->carac));
	printf("camisa: ");
	if(lista->vetor[14]->mutante == 1){
		printf("MUTANTE ");
	}
	printf("%s\n",caracteristica);

	free_lista_g(lista);
}

void print_populacao(Lista *lista){
	int i;
	Nodo *ptr = lista->cabeca;

	while(ptr != NULL){
		print_personagem(ptr->personagem);
		printf("\n\n");
		ptr = ptr->prox;
	}
	mensagens(4);
}

void desenha_personagem(Lista *lista){
	int opcao;
	int invalida = 0;

	do{
		mensagens(1);
		printf("1- Visualizar personagem único\n");
		printf("2- Visualizar conjunto de personagens\n");
		printf("3- Visualizar todos os personagens\n");
		printf("4- Voltar para o menu\n\n");

		if(invalida){
			mensagens(5);
			invalida = 0;
		}
		printf("\nDigite sua opção: ");
		opcao = verifica_entrada();

		if(opcao == 1){
			int id;
			Tree* personagem;

			mensagens(1);
			do{
				printf("Digite o id do personagem: ");
				id = verifica_entrada();
				if(id >= 1 && id <= TAM){
					personagem = busca_personagem(lista, id);
					printf("\nDesenhando personagem %d...\n", id);
					imprime_personagem(personagem);
					mensagens(4);
				}
				else{
					mensagens(3);
				}
			}while(id < 1 || id > TAM);
		}

		else if(opcao == 2){
			int i, n;
			Tree* personagem;

			do{
				printf("Digite quantos personagens deseja visualizar: ");
				n = verifica_entrada();

				if(n >= 1 && n <= TAM){
					int id[TAM];
					mensagens(1);

					printf("Digite os ids:\n");
					for(i = 0; i < n; i++){
						do{
							printf("%d. ", i+1);
							id[i] = verifica_entrada();
							if(id[i] < 1 || id[i] > TAM){
								mensagens(3);
							}
						}while(id[i] < 1 || id[i] > TAM);
					}

					for(i = 0; i < n; i++){
						mensagens(1);
						personagem = busca_personagem(lista, id[i]);
						printf("\nDesenhando personagem %d...\n", id[i]);
						imprime_personagem(personagem);
					}
					mensagens(4);
				}
				else if (n != 0){
					mensagens(5);
				}
			}while(n < 0 || n > TAM);
		}

		else if(opcao == 3){
			Nodo* ptr = lista->cabeca;
			while(ptr != NULL){
				mensagens(1);
				printf("Desenhando personagem %d...\n", ptr->personagem->info->id);
				imprime_personagem(ptr->personagem);
				ptr = ptr->prox;
			}
			mensagens(4);
		}

		else{
			invalida = 1;
		}

	}while(opcao != 4);
}