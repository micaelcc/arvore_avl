//
// Created by micael on 29/07/2021.
//

#include "ArvoreAVL.h"
#include "GerarVetores.h"
#include <stdio.h>

int main() {

    int i;


    for (i = 0; i < 1; i++) {
        int *vet;
        int *vet_2;
        int j;
        int aux = 0;

        //Ponteiro para arvore
        NO *arv = NULL;

        //Vetor de numeros aleatorios, tamanho 10000, range (0/100000)
        vet = vet_random_n(10000, 0, 100000);

        //Inserindo valores aleatorios de "vet" em arv
        for (j = 0; j < 10000; j++)
            insere(&arv, vet[j], &aux);


        //Verificando se os nos foram inseridos
        if (count_no(arv) != 10000) {
            printf("Numero de nos incorreto.\n");
            return 0;
        }

        //Verificando se arv é avl apos as inserções
        if (!is_avl(arv)){
            printf("Arvore nao eh AVL");
            return 0;
        }

        //Criando vetor de indices, para remover nos da arvore
        vet_2 = vet_random_n(1000, 0, 10000);

        //Removendo nos da arvore
        for(j = 0; j < 1000; j++){
            //Pegando index atual
            int index = vet_2[j];

            //Removendo index aleatorio da arvore
            delete(vet[index], &arv, &aux);
        }

        //Verificando se os nos foram removidos
        if (count_no(arv) != 9000) {
            printf("Numero de nos incorretos.\n");
            return 0;
        }

        //Verificando se arvore é avl apos remoções
        if (!is_avl(arv)) {
            printf("Arvore nao eh AVL");
            return 0;
        }

        //Progresso de criacao/verificacao das arvores
        printf("%lf %%\n", (double) (i*100.0)/1000.0 );
    }

    printf("Todas as arvores foram criadas com sucesso!\n");

    return 0;

}

