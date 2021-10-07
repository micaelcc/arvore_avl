#include "GerarVetores.h"
#include <stdlib.h>
#include <time.h>

/*
 * Função que gera vetor aleatorio.
 * Recebe um tamanho "n", e os "limites"
 * do range, "min" e "max"
 */
int * vet_random_n(int n, int min, int max){

    srand(time(NULL));
    int *vet = malloc(n*sizeof(int));
    int num;
    int i;

    for(i=0; i<n; i++){

        do{
            num = rand() % max;
        }while(busca(vet, num,i));

        vet[i] = num;
    }

    return vet;
}

/*
 * Busca valor em vetor. Recebe o vetor
 * vet, um numero num e o tamanho da lista
 * tam_max.
 */
int busca(int *vet, int num, int tam_max){
    int i;

    for(i=0;i<tam_max; i++){
        if(vet[i] == num)
            return 1;
    }

    return 0;
}

