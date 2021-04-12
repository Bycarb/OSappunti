#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/***esercizio 4

scrivere la seguente funzione:
find_max_even_positions() che prende come parametri un array di int e la sua dimensione (numero di celle);
cerca tra le celle in posizione pari quella avente valore massimo e ne resituisce la POSIZIONE (restituisce la prima posizione, in caso di più celle con valore massimo)
es:
per l'array { 0, 100, 7, 50, -45, 10 } restituisce 2 (cioè la posizione della cella che ha valore 7)*/

int find_max_even_positions(int array[], int array_size){
	int max=array[0], max_pos=0;
	for(int i=2; i < array_size; i+=2){
		if(array[i] > max){
			max = array[i];
			max_pos = i;
		}
	}
	return max_pos;
}

int main(void) {
	int arr[5] = { 0, 100, 7, 50, -45};
	printf("%d",find_max_even_positions(arr, 5) );
	return EXIT_SUCCESS;
}
