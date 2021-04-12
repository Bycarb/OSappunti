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

/***esercizio 15 ***

scrivere un programma che legge da stdin una riga alla volta (la riga si considera terminata dal carattere \n).

non è richiesto di conservare il contenuto della riga, ma soltanto di contarne la lunghezza.

la lunghezza della riga è arbitraria, non fare ipotesi sulla massima lunghezza di riga.
[in questo esercizio, non occorre immagazzinare l'intera riga].

calcolare la media della lunghezza (=numero di caratteri) delle righe lette che vengono lette da stdin.

dopo ogni riga letta, mostrare la lunghezza della riga e la media "parziale" fino a quel momento.

il programma termina in caso di EOF su stdin. */


int main(void) {
	int sum = 0;
	int reads_cnt = 0;
	char tmp;
	int line_length = 0;
	while(( tmp =getchar() ) != EOF){
		if(tmp == '\n'){
			reads_cnt++;
			sum+= line_length;
			printf("Length of the last line: %d\n", line_length);
			printf("Avg length up to now: %.2f\n", (double)sum / (double)reads_cnt);
			line_length = 0;
		}else{
			line_length++;
		}
	}

	return EXIT_SUCCESS;
}
