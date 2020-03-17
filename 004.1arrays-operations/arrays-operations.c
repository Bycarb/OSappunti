#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// allocare (creare) un array (OK)
// liberare (distruggere) un array (OK)
// ridimensionare un array (OK)
// copiare un array (OK)
// accedere ad array (OK)

// concatenare un array (TODO)

// reverse array (OK)

// sort di array (TODO)

// sottoinsieme di array (TODO)
// cercare in un array (TODO)

// array di array (TODO)

// dichiarazione di funzione definita dopo main()
void * make_copy_of_array(void * src_array, unsigned int array_length);

int main(int argc, char *argv[]) {

	int size = 10;

	char * char_array; // char_array è un puntatore a char
	// Kernighan&Ritchie pag. 93
	// un puntatore è una variabile che contiene un indirizzo di (un'altra) variabile


	char_array = NULL;

	// cosa succede?
	*char_array = 'A';

	// allocare (creare) un array
	// ogni cella ha dimensione sizeof(char)
	// l'array ha 'size' celle
	char_array = calloc(size, sizeof(char)); // inizializza a zero la memoria allocata
	// oppure
	//char_array = malloc(size * sizeof(char)); // NON inizializza a zero la memoria allocata

	// controllare se calloc ha funzionato:
	if (char_array == NULL) {
		perror("calloc error!");
		exit(EXIT_FAILURE);
	}

	printf("indirizzo contenuto in char_array: %p\n", char_array);

	// liberare (distruggere) un array
	free(char_array);
	//char_array = NULL;

	// attenzione! char_array contiene lo stesso valore di prima ma
	// non punta più ad una zona di memoria allocata!

	/////////////////////////////////////////

	int * int_array;
	// allocare (creare) un array
	int_array = malloc(size * sizeof(int)); // dimensione totale in bytes dell'array?

	size = size * 100;

	// ridimensionare un array
	int_array = realloc(int_array, size * sizeof(int));

	if (int_array == NULL) {
		perror("realloc error!");
		exit(EXIT_FAILURE);
	}

	free(int_array);

	/////////////////////////////////////////

	long * array_a;
	long * copia_array;
	size = 20;

	array_a = malloc(size * sizeof(long)); // array_a non viene inizializzato da malloc

	// che valori ha array_a?
	memset(array_a, 0, size * sizeof(long)); // inizializziamo array_a (ogni cella avrà il valore 0)

	copia_array = make_copy_of_array(array_a, size * sizeof(long)); // importante!!!

	//
	free(copia_array);

	// accediamo agli elementi dell'array:

	array_a[0] = 1;
	array_a[1] = 0xFFFF;
	// ...





	return EXIT_SUCCESS;
}

/*
 * crea una copia dell'array
 * parametri: indirizzo dell'array, dimensione totale in bytes dell'array
 * restituisce l'indirizzo della copia
 */
// il tipo dati 'void *' indica un puntatore 'generico'
void * make_copy_of_array(void * src_array, unsigned int array_total_size) {

	if (src_array == NULL || array_total_size < 0)
		return NULL;

	void * result;

	// allochiamo la memoria della copia
	result = malloc(array_total_size);

	memcpy(result, src_array, array_total_size);

	// invece di memcpy potrei fare così:
//	char * dest = result;
//	char * src = src_array;
//	for (unsigned int i = 0; i < array_total_size; i++) {
//		dest[i] = src[i];
//	}

	// chi riceve il risultato, dovrà occuparsi di liberare la memoria allocata per la copia dell'array
	return result;
}


// function to swap two char
void swap(char *x, char *y) {
	char t = *x;
	*x = *y;
	*y = t;
}

// function to reverse array[i..j]
char * reverse(char * array, unsigned int i, unsigned int j)
{
	while (i < j)
		swap(&array[i++], &array[j--]);

	return array;
}

char * full_reverse(char * array, unsigned int array_len) {
	return reverse(array, 0, array_len);
}

