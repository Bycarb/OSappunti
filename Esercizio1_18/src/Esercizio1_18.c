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

/***esercizio 18 ****

 ***randomizzare le parole***

 è data una stringa di caratteri contenente parole separate dal carattere spazio

 randomizzare le parole per produrre una nuova stringa di caratteri
 vanno riutilizzate tutte le singole parole (una sola volta ciascuna)

 [generatore di numeri casuali:
 vedere esempio:
 https://github.com/marcotessarotto/exOpSys/tree/master/006.4random-number
 si può utilizzare la funzione rand()
 http://man7.org/linux/man-pages/man3/rand.3.html ]

 esempio:
 è data la stringa di caratteri:
 "hello world mi chiamo pino sono date delle stringhe"

 output:
 "mi stringhe chiamo pino sono date world delle hello"*/

char **array_shuffle(char **arr, int size){
	char *ptr;
	//srand(1);
	for (int i=0; i<size; i++){
		int newpos = ( rand() % size);
		ptr = arr[i];
		arr[i] = arr[newpos];
		arr[newpos] = ptr;
	}
	return arr;
}


char * shuffle_string(char s_input[]){
	char * s = calloc(strlen(s_input), sizeof(char));
	s = strcpy(s, s_input);
			if(s == NULL){
				perror("Error copying with input string\n");
				return NULL;
			}
	char * newstring = calloc(strlen(s), sizeof(char));
		if (newstring == NULL){
			perror("Error allocating memory");
			return NULL;
		}
	char *tmp;
	char **arr_words = calloc (20, sizeof(char*));
			if (arr_words == NULL){
				perror("Error allocating memory");
				return NULL;
			}

	//splitto s nelle varie parole e
	// memorizzo le posizioni di tutte le parole separate in un array
	tmp = strtok(s, " ");
	arr_words[0] = tmp;
	int i=1;
	while( (tmp= strtok(NULL, " ")) != NULL){
		arr_words[i] = tmp;
		i++;

	}
	// mescolo le parole
	array_shuffle(arr_words, i);
	//scrivo leparole nella stringa di destinazione
	for(int j = 0; j < i; j++){
		strcat(newstring, arr_words[j]);
		strcat(newstring, " ");
	}
	newstring[strlen(newstring) - 1] = '\0';
	return newstring;
}


int main(void) {
	char s[] = "i topi non avevano nipoti";
	char * s1;
	s1 = shuffle_string(s);
	printf("%s",s1);
	return EXIT_SUCCESS;
}
