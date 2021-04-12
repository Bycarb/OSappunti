#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <limits.h>

/*** esercizio 2020-03-30*** (deve risultare un unico programma in C, scrivete tutto il codice sorgente in src/esercizio20200330.c)

A - scrivere la seguente funzione:

implementare una funzione che calcola la serie di Fibonacci:

unsigned long fibonacci(unsigned int n);

dove:
fibonacci(0) = 0
fibonacci(1) = 1
fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)  per n > 1

provare a scoprire quale è il valore massimo di n per cui fibonacci(n) restituisce un valore della serie corretto*/

unsigned long fibonacci(unsigned long n){
	if(n  == 0){
		return 0;
	}if(n == 1){
		return 1;
	}else{
		return fibonacci(n-1) + fibonacci(n-2);
	}
}

/*B - scrivere la seguente funzione:

unsigned long * fibonacci_array(unsigned int n);

questa funzione restituisce un array di unsigned long di dimensione n+1 (n è l'argomento della funzione)
dove la cella i-ma contiene il valore di fibonacci(i).*/

unsigned long * fibonacci_array(unsigned long n){
	unsigned long *arr = malloc(n * sizeof(unsigned long));
	for(unsigned long i = 0; i <= n; i++){
		arr[i] = fibonacci(i);
	}
	return arr;
}

/*C - main() fa queste operazioni:

calcola fibonacci_array(39) e lo assegna alla varibile 'fibonacci_result'  // fibonacci(39) = 63245986

fare una copia dell'array fibonacci_result in 'fibonacci_result_copy' (i due array devono avere aree di memoria distinte)

fibonacci_result_copy: fare il 'reverse' dell'array ('copiare' da esempio 004.1arrays-operations)

su fibonacci_result_copy: applicare bubble_sort ('copiare' da esempio 004.1arrays-operations)

confrontare fibonacci_result e fibonacci_result_copy, verificare che i due array siano uguali (scrivere su stdout il risultato).*/
void swap(unsigned long *x, unsigned long *y) {
	int t = *x;
	*x = *y;
	*y = t;
}

unsigned long * reverse(unsigned long * array, unsigned long i, unsigned long j)
{
	while (i < j)
		swap(&array[i++], &array[--j]);

	return array;
}

void bubble_sort(unsigned long * array, int array_dimension) {
	int n = array_dimension;
	int newn;
	do {
		newn = 0;
		for (int i = 1; i < n; i++) {
			if (array[i-1] > array[i]) {
				swap(&array[i-1], &array[i]);
				newn = i;
			}

		}
		n = newn;
	} while (n > 1);
}

int main(void) {
	int n = 37;
	unsigned long *arr, *arr_copy = calloc(n+1, sizeof(unsigned long));
	arr =  fibonacci_array(n);
	memcpy(arr_copy, arr, (n +1 ) *sizeof(unsigned long));
	arr_copy = reverse(arr_copy, 0, n+1);
	bubble_sort(arr_copy, n+1);

	for(int i = 0; i <= n; i++){
		printf("%d \t %d\n", arr[i],arr_copy[i]);
	}

	return EXIT_SUCCESS;
}
