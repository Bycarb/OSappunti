#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/***esercizio 3

scrivere la seguente funzione:

int * gen_random_array(unsigned int seed, int use_seed, unsigned int number_elements);
se use_seed è true, utilizza il parametro seed con la funzione srand()
	per impostare il "seed" della sequenza di interi pseudo-casuali.
number_elements è il numero di celle dell'array che la funzione restituirà
il valore di ogni elemento dell'array è ottenuto invocando rand()

esempio:
gen_random_array(-100, 1, 10) cioè con seed pari a -100 restituisce un array di 10 elementi pari a:*/


void * gen_random_array(unsigned int seed, int use_seed, unsigned int number_elements){
	int * array = malloc(number_elements * sizeof(int));
		if(array == NULL){
			perror("Error in memory allocation");
			exit(EXIT_FAILURE);
		}
	if(use_seed){
		srand(seed);
	}
	for(int i =0; i<number_elements; i++){
		array[i] = rand();
	}
	return array;
}

int main(void) {
	int * prova;
	prova = gen_random_array(-100, 1, 10);
	for(int i =0; i<10; i++){
						printf("%d\n", prova[i]);
					}
	return EXIT_SUCCESS;
}
