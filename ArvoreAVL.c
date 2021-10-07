#include "ArvoreAVL.h"
#include <stdio.h>
#include <stdlib.h>
#define E 2
#define D 3

/*
 * Funções da parte Inserção
 */

/*
 * Funcao que insere valor na lista.
 * Recebe um ponteiro para ponteiro
 * para a raiz da arvore, uma chave a
 * ser inserida e uma variavel auxiliar
 * h, que servirá para verificar se o
 * tamanho da lista foi alterado.
 */
void insere(NO ** pt, int key, int *h){
    if((*pt) == NULL){
        (*pt) = malloc(sizeof(NO));
        (*pt)->chave = key;
        (*pt)->esq = NULL;
        (*pt)->dir = NULL;
        (*pt)->bal = 0;
        *h = 1;

    }else if(key == (*pt)->chave){
        printf("Chave ja existe.\n");

    }else if(key < (*pt)->chave){
        insere(&(*pt)->esq, key, h);

        if(*h){
            switch((*pt)->bal){
                case -1: caso1(&(*pt), h); *h = 0; break;
                case 0: (*pt)->bal = -1; break;
                case 1: (*pt)->bal = 0; *h = 0; break;
            }
        }
    }else if(key > (*pt)->chave){
        insere(&(*pt)->dir, key, h);

        if(*h){
            switch((*pt)->bal){
                case 1: caso2(&(*pt), h); *h = 0; break;
                case 0: (*pt)->bal = 1; break;
                case -1: (*pt)->bal = 0; *h = 0; break;
            }
        }
    }

}

//Função para fazer rotações a direita
void caso1(NO ** pt, int *h){

    NO * ptu = (*pt)->esq;

    if(ptu->bal == -1){

        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt)->bal = 0;
        (*pt) = ptu;

    }else{
        NO * ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

        if(ptv->bal == -1){
            ptu->bal = 0;
            (*pt)->bal = 1;
        }else if(ptv->bal == 1){
            (*pt)->bal = 0;
            ptu->bal = -1;
        }else{
            (*pt)->bal = 0;
            ptu->bal = 0;
        }

        (*pt) = ptv;
    }

    (*pt)->bal = 0;
    *h = 0;
}

//Função que faz rotações a esquerda
void caso2(NO ** pt, int *h){
    NO * ptu = (*pt)->dir;

    if(ptu->bal == 1){
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt)->bal = 0;
        (*pt) = ptu;
    }else{
        NO * ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

        if(ptv->bal == 1){
            ptu->bal = 0;
            (*pt)->bal = -1;
        }else if(ptv->bal == -1){
            (*pt)->bal = 0;
            ptu->bal = 1;
        }else{
            (*pt)->bal = 0;
            ptu->bal = 0;
        }

        (*pt) = ptv;
    }

    (*pt)->bal = 0;
    *h = 0;
}


/*
 *
 */


/*
 * Funções da parte de Remover
 */

/*
 * Função para remover no da lista, recebe
 * uma chave, um ponteiro para ponteiro da
 * raiz da lista, e uma variavel auxiliar h.
 */
void delete(int key, NO ** pt, int *h){
    if((*pt) == NULL){
        printf("Esse NO nao existe!\n");
        *h = 0;
    }else{
        if(key < (*pt)->chave){
            delete(key, &(*pt)->esq, h);
            balancear(&(*pt), E, h);
        }else{
            if(key > (*pt)->chave){
                delete(key, &(*pt)->dir, h);
                balancear(&(*pt), D, h);
            }else{
                NO * aux = (*pt);

                if((*pt)->esq == NULL){
                    (*pt) = (*pt)->dir;

                    *h = 1;
                }else {
                    if ((*pt)->dir == NULL) {
                        (*pt) = (*pt)->esq;
                        *h = 1;
                    } else {
                        NO *s = (*pt)->dir;

                        if (s->esq == NULL) {
                            s->esq = (*pt)->esq;
                            s->bal = (*pt)->bal;

                            (*pt) = s;
                            *h = 1;
                        } else {
                            NO *PaiS;

                            while (s->esq != NULL) {
                                PaiS = s;
                                s = s->esq;
                            }

                            int temp = (*pt)->chave;

                            (*pt)->chave = PaiS->esq->chave;

                            PaiS->esq->chave = temp;

                            delete(key, &(*pt)->dir, h);
                        }
                        balancear(&(*pt), D, h);

                    }
                }

            }
        }
    }
}

//Função auxiliar para fazer rotações
void caso1R(NO ** pt, int *h){
    NO * ptu = (*pt)->esq;

    if(ptu->bal <= 0){
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;

        if(ptu->bal == -1){
            ptu->bal = (*pt)->dir->bal = 0;
            *h = 1;
        }else{
            ptu->bal = 1;
            (*pt)->dir->bal = -1;
            *h = 0;
        }
    }else{
        NO * ptv = ptu->dir;
        ptu->dir = ptv->esq;

        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

        (*pt) = ptv;

        switch(ptv->bal){
            case -1: ptu->bal = 0; (*pt)->dir->bal = 1; break;
            case 0: ptu->bal = 0; (*pt)->dir->bal = 0; break;
            case 1: ptu->bal = -1; (*pt)->dir->bal = 0; break;
        }

        (*pt)->bal = 0;
        *h = 1;
    }
}

//Função auxiliar para fazer rotações
void caso2R(NO ** pt, int *h){
    NO * ptu = (*pt)->dir;

    if(ptu->bal >= 0){
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;

        if(ptu->bal == 1){
            (*pt)->bal = (*pt)->esq->bal = 0;
            *h = 1;
        }else{
            (*pt)->bal = -1;
            (*pt)->esq->bal = 1;
            *h = 0;
        }
    }else{
        NO * ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);


        switch(ptv->bal){
            case -1: ptu->bal = 1; (*pt)->bal = 0; break;
            case 0: ptu->bal = 0; (*pt)->bal = 0; break;
            case 1: ptu->bal = 0; (*pt)->bal = -1; break;
        }

        (*pt) = ptv;

        (*pt)->bal = 0;
        *h = 1;
    }
}

//Função auxiliar que faz o balanceamento
//de uma subarvore.
void balancear(NO ** pt, int R, int *h){
    if(*h == 1){
        if(R == D){
            switch((*pt)->bal){
                case 1: (*pt)->bal = 0; break;
                case 0: (*pt)->bal = -1; *h = 0; break;
                case -1: caso1R(&(*pt), h);
            }
        }else{
            switch((*pt)->bal){
                case -1: (*pt)->bal = 0; break;
                case 0: (*pt)->bal = 1; *h = 0; break;
                case 1: caso2R(&(*pt), h);
            }
        }
    }
}



/*
 * Funções auxiliares de AVL
 */

/*
 *
 */

//Função para verificar altura de um NO
int altura(NO * pt){
    if(pt != NULL) {
        int a = altura(pt->esq);
        int b = altura(pt->dir);

        if(a>b)
            return a + 1;
        else
            return b + 1;
    }

}

//Função que conta nos de uma arvore
int count_no(NO * pt){
    if(pt != NULL){
        int a = count_no(pt->esq);
        int b = count_no(pt->dir);

        return a + b + 1;
    }
}

//Função que verifica se arvore é avl
int is_avl(NO *pt){
    if (pt!=NULL){
        //Recursao
        is_avl(pt->esq);
        is_avl(pt->dir);

        int alt_esq, alt_dir;

        //Calcula altura da subarvore esquerda e direita
        alt_esq = altura(pt->esq);
        alt_dir = altura(pt->dir);

        //Calcula o balanceamento
        int bal = alt_dir - alt_esq;

        //Verifica se o campo bal esta correto
        if(bal != pt->bal){
            printf("Campo bal do NO nao esta correto!");
            return 0;
        }

        if(bal > 1 || bal < -1){
            return 0;
        }
    }

    return 1;
}

/*
 *
 */



