#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "printPersonagem.h"
#include "arvore.h"
#include "criador.h"
#include "Lista.h"


int main()
{
	Lista *lista;
	lista = cria_lista();
	printf("%d\n", vazia_lista(lista));
	free_lista(lista);

	/*Criamos uma arvore de personagem para testes */
	/*Lembre-se que ela recebe o id do personagem */
	Tree* personagem = cria_arvore_personagem(0);
	imprime_arvore(personagem);
	printf("\nO personagem impresso graficamente nao corresponde ao personagem vazio impresso de forma textual");
	printf("\n\n");

	/*Caso queira testar a biblioteca grafica */
	imprime_personagem_aleatorio();

	tree_free(personagem);
    return 0;
}
