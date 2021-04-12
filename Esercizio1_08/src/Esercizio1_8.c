#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/****esercizio 8

scrivere un programma che legge da stdin tutto fino a EOF
il programma prende come parametro di riga di comando una stringa di caratteri;
il programma cerca la stringa di caratteri fornita in tutto il contenuto letto da stdin e scrive su stdout il numero
di occorrenze della stringa.

provare il programma utilizzando il file di testo che potete scaricare qui:
https://github.com/marcotessarotto/exOpSys/blob/master/res/text01.txt

"nome_programma" ipsum < text01.txt

il risultato è 4.*/


int main (int argc, char *argv[]){
	char tmp = '\0';
	int text_size = 0;
	int occurrences = 0;
	char * text = malloc(text_size);
		if(text == NULL){
			perror("Error in memory allocation malloc()\n");
			exit(EXIT_FAILURE);
		}
	char * key_word = argv[1];
		if(key_word == NULL){
			perror("Error: missing argument.\n");
			exit(EXIT_FAILURE);
		}

	while ( ( tmp = getchar()) != EOF ){
		text[text_size] = tmp;
		text_size++;
		text = realloc(text, text_size+1);
			if(text == NULL){
				perror("Error reallocating memory\n");
				exit(EXIT_FAILURE);
			}
	}
	for(int i = 1; i <= (text_size - strlen(key_word)); i++){
		int are_equal = 1;
		for(int ii = 0; ii < strlen(key_word); ii++){
			if(text[i+ii] != key_word[ii]){
				are_equal = 0;
				break;
			}
		}
		if(are_equal){
			occurrences++;
		}
	}

	printf("La parola %s e` presente %d volte.\n", key_word, occurrences);

	return 0;
}
