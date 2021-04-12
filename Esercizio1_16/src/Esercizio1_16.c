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

/***esercizio 16 ***
scrivere un programma che legge da stdin una riga alla volta (la riga si considera terminata dal carattere \n).

la lunghezza della riga è arbitraria, non fare ipotesi sulla massima lunghezza di riga.
[in questo esercizio, occorre immagazzinare l'intera riga ed anche le precedenti].

confrontare la riga appena letta con tutte le precedenti righe lette:
il confronto parte dalla penultima riga e va a ritroso fino alla prima riga letta.

se la riga appena letta ha un precedente, scrivere su stdout il messaggio
"***questa riga è stata già letta %d righe fa***", dove viene indicata la posizione relativa della riga identica rispetto alla riga attuale
(può accadere che una riga si ripresenti più di una volta; scrivere tutte le volte
che si ripresenta)

il programma termina in caso di EOF su stdin.

esempio, I: significa input proveniente da stdin, O: indica l'output del programma su stdout

I: xyz0000
I: 1234
I: 0000
I: zzzzz
I: 1234
O: ***questa riga è stata già letta 3 righe fa***
I: abcdefg
I: 1234
O: ***questa riga è stata già letta 2 righe fa***
O: ***questa riga è stata già letta 5 righe fa***/


//restituisce la nuova linea presa da stdin oppure NULL quando raggiunge EOF o c'e` un errore
char * get_row(){
	char *newline = calloc(10, sizeof(char));
		if(newline == NULL){
			perror("Error allocating memory");
			return NULL;
		}
	char tmp;
	int alloc_space = 10;
	int line_length = 0;
	while(( tmp =getchar() ) != '\n'){
		if(tmp == EOF){
			return NULL;
		}
		if(line_length + 1 >= alloc_space){
			newline = realloc(newline, (alloc_space += 10) *sizeof(char) );
					if(newline == NULL){
						perror("Error allocating memory");
						return NULL;
					}
		}
		newline[line_length] = tmp;
		line_length++;
	}
	return newline;
}


int main(void) {
	int alloc_space = 5;
	char ** arr = calloc(alloc_space, sizeof(char*));
	int arr_len =0;
	while( ( arr[arr_len] = get_row()) != NULL ){
		if(arr_len +1 >= alloc_space){
			alloc_space += 5;
			arr = realloc(arr, alloc_space *sizeof(char*));
					if(arr == NULL){
						perror("Error allocating memory");
						exit(EXIT_FAILURE);
					}
		}
		for(int i=0; i<arr_len; i++){
			if( !strcmp(arr[arr_len], arr[i]) ){ // se le stringhe sono uguali
				printf("questa riga è stata già letta %d righe fa\n", arr_len - i);
			}
		}
		arr_len++;
	}
	return EXIT_SUCCESS;
}
