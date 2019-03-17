#ifndef printPersonagem_H
#define printPersonagem_H

#include "arvore.h"


typedef struct personagem
{
    char olhos_formato[20];
    char olhos_cor[20];
    char camisa[20];
    char calca[20];
    char cabelo_formato[20];
    char cabelo_cor[20];
    char raca[20];
    char bota[20];
} Personagem;

int imprime_personagem (Tree *);
int imprime_personagem_aleatorio();
Personagem* personagem_create();
void getPersonagem(Tree* ,Personagem*);
#endif
