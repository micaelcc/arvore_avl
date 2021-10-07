#ifndef EDAP2_ARVOREAVL_H
#define EDAP2_ARVOREAVL_H

#endif //EDAP2_ARVOREAVL_H

/*
 * Definição da TAD No
*/
struct no{
    int chave;
    struct no* dir;
    struct no* esq;
    int bal;
};

typedef struct no NO;

//Assinaturas das funções de Arvore
void caso1(NO **, int *);
void caso2(NO **, int *);
void insere(NO **, int, int *);

int altura(NO *);
int count_no(NO *);
int is_avl(NO *);
void caso1R(NO **, int *);
void caso2R(NO **, int *);
void delete(int, NO **, int *);
void in_order(NO *);
void balancear(NO **, int, int *);
