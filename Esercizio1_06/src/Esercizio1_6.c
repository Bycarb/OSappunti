#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/****esercizio 6

per svolgere questo esercizio, occorre avere risolto esercizio 3 ed esercizio 5

provare le due funzioni scritte sopra in questo modo:

usare gen_random_array() con seed = 10 (e use_seed impostato a vero) per generare un vettore di 100 elementi
usare di nuovo gen_random_array() con seed = 20 (e use_seed impostato a vero) per generare un vettore di 100 elementi

usare join_arrays_same_length per generare il vettore "fusione".

scrivere in un file di testo denominato "prova.txt" i valori del vettore fusione, in formato testo:

esempio del contenuto del file prova.txt (i numeri non c'entrano con il valore atteso, servono soltanto ad illustrare il formato del file):
2131
-344
321
0
44541
....

una volta generato il file prova.txt, da shell eseguire il comando:
md5sum prova.txt

questo restituirà il valore:
(TODO!!!)
*/

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

#define len 100

int main(void) {
	int * arr_1, * arr_2;
	arr_1 = gen_random_array(10, 1, len);
	arr_2 = gen_random_array(20, 1, len);
	int * joined_array = join_arrays_same_length(arr_1, arr_2, len);
	free(arr_1);
	free(arr_2);

	int fd = open("test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if(fd == -1){
			perror("Error epnening new file\n");
			exit(EXIT_FAILURE);
		}

	for(int i = 0; i < len; i++){
		int res = 0;
		char buf[20];
		int siz = sprintf(buf, "%d\n", joined_array[i]);
			if(siz <= 0 || siz > 20){ // errore anche se scrivo 0 byte o se il numero e`piu` lungo del buffer
				perror("Error reading number\n");
				exit(EXIT_FAILURE);
			}
		res = write(fd, buf, siz);
			if(res <= 0){
				perror("Error writing file.\n");
				exit (EXIT_FAILURE);
			}
	}

	close(fd);

	return EXIT_SUCCESS;
}





