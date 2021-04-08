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


int main(void) {
	puts("Hullo"); /* prints Hullo */
	return EXIT_SUCCESS;
}
