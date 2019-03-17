#ifndef ARVORE_H
#define ARVORE_H

struct genetica
{
    int pai; /* id do pai */
    int mae; /* id da mae */
    int id; /* proprio id */
    int mutante; /* flag de mutante */
    char carac[20]; /*  caracteristica em string da dominancia; */
    int dom; /* dominancia do gene */
};
typedef struct genetica Genetica;

struct tree
{
    Genetica *info;
    struct tree* left;
    struct tree* right;
};
typedef struct tree Tree;

/*cria a arvore*/
Tree* tree_create(); // cria arovre
Tree* tree_createleaf(Genetica* criada); // cria a folha
int tree_empty(Tree* mangueira); // verifica se arvore esta vazia
Tree* tree_push(Genetica* criada, Tree* mangueira); //insere o dado na arvore




Tree* tree_free(Tree* mangueira);



#endif
