#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/****esercizio 10****

è dato un array di int chiamato int_array di dimensione int_array_len.

scrivere la funzione che inserisce il valore val alla posizione insert_position
(cioè le celle dalla posizione insert_position in poi vengono spostate verso destra di una posizione per fare spazio al nuovo valore)
int * insert_into_array(int * array, int array_len, int val, int insert_position)

se insert_position < 0 || insert_position > int_array_len la funzione restituisce NULL
se insert_position == int_array_len, il valore da aggiungere viene messo in coda all'array
la funzione restituisce l'indirizzo dell'array modificato

es:
int int_array[] = {0,1,2,3,4,5};
int int_array_len = 6;

int * result = insert_into_array(int_array, int_array_len, -1, 3);
// insert_into_array restituisce un array di dimensione 6+1 fatto così:
// {0,1,2, -1, 3,4,5}

// insert_into_array(int_array, int_array_len, -1, 0);
// {-1, 0,1,2,3,4,5}

// insert_into_array(int_array, int_array_len, -1, 6);
// {0,1,2,3,4,5,-1}

// insert_into_array(int_array, int_array_len, -1, 6);
// NULL
 */

int * insert_into_array(int * array, int array_len, int val, int insert_position){
	if (insert_position < 0 || insert_position > array_len){
		printf("Invalid insertion position.\n");
		return NULL;
	}
	int *newarray = malloc( (array_len + 1) * sizeof(int) );
		if(newarray == NULL){
			perror("Error in memory allocation\n");
			exit(EXIT_FAILURE);
		}

	for(int i=0; i<insert_position; i++){
		newarray[i] = array[i];
	}
	newarray[insert_position] = val;
	for(int i=insert_position; i< array_len+1; i++ ){
		newarray[i+1] = array[i];
	}

	return newarray;
}
int main(){
	int int_array[] = {0,1,2,3,4,5};
	int int_array_len = 6;

	int * result = insert_into_array(int_array, int_array_len, -1, 6);
	for(int i=0; i< int_array_len+1; i++){
		printf("%d ", result[i]);
	}

	return 0;
}
