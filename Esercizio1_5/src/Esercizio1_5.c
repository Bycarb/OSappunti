#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/***esercizio 5

sono dati due vettori di int, aventi lo stesso numero di elementi array_len

int array1[], int array2[], int array_len

scrivere una funzione join_arrays_same_length che prende i tre parametri sopra e crea e restituisce l'vettore "fusione", costituito da array_len elementi, costruito in questo modo:
l'elemento i-mo di array_fusion è dato dal maggiore tra i due elementi i-mi dei due array.

la funzione restituisce il puntatore all'array fusione.

esempio:
i due array { 10, 100, 1000 } e { 200, -1, 90 } fusi assieme daranno come risultato:
{ 200, 100, 1000 }    */


int *join_arrays_same_length(int array1[], int array2[], int array_len){
	int *array3 = malloc(array_len * sizeof(int));
		if(array3 == NULL){
			perror("error in memory allocation \nCannot allocate array of dimension 0\n");
			exit(EXIT_FAILURE);
		}
	for(int i = 0; i < array_len; i++){
		array3[i] = ( array1[i] > array2[i] ) ? array1[i] : array2[i];
	}
	return array3;
}

int main(void) {
	int *array3;
	int array1[3] = { 10, 100, 1000 },
		array2[3] = { 200, -1, 90 };

	array3 = join_arrays_same_length(array1, array2, 3);
	for(int i=0; i<3; i++){
		printf("%d\n", array3[i]);
	}
	return EXIT_SUCCESS;
}
