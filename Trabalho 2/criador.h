#ifndef CRIADOR_H
#define CRIADOR_H


#include<time.h>
#include"arvore.h"



/*criacao das ultimas folhas*/
Genetica* cria_botas_membros();
Genetica* cria_calca_membros();

Genetica* cria_raca_tronco();
Genetica* cria_camisa_tronco();

Genetica* cria_tipo_cabelos();
Genetica* cria_cor_cabelos();

Genetica* cria_tipo_olhos();
Genetica* cria_cor_olhos();
Genetica* cria_folha(char* conteudo, int dominancia);
/*criacao das subclasses*/
Tree* cria_arvore_cor_olhos();
Tree* cria_arvore_tipo_olhos();
Tree* cria_arvore_olhos();
///////////
Tree* cria_arvore_botas_membros();
Tree* cria_arvore_calca_membros();
Tree* cria_arvore_membros();
////
Tree* cria_arvore_raca_tronco();
Tree* cria_arvore_camisa_tronco();
Tree* cria_arvore_tronco();
/////////
Tree* cria_arvore_cor_cabelos();
Tree* cria_arvore_tipo_cabelos();
Tree* cria_arvore_cabelos();


Tree* cria_arvore_cabeca();
Tree* cria_arvore_corpo();

Tree* cria_arvore_personagem(int id);
Tree* limpa_arvore_personagem(Tree* mangueira);

int verifica_ultimo_nivel(Tree* mangueira);
int verifica_penultimo_nivel(Tree* mangueira);
int verifica_antpenultimo_nivel(Tree* mangueira);


Genetica* dominante(Tree* folha);

void imprime_arvore(Tree *mangueira);

void imprime_dominante(Genetica* g);
void imprime_genetica(Genetica* g);

#endif
