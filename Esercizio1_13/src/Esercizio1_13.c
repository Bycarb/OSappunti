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

/****Esercizio 13 ****
il programma svolge le attività sotto descritte fino a quando incontra EOF su stdin.

1: il programma legge caratteri da stdin.
Quando incontra EOF, il programma scrive quanti processi figli ha lanciato in tutto e poi termina.

Il programma accumula i caratteri letti da stdin in un array di dimensione 80 chiamato char_array.
(introdurre nel codice un #define NUM_CHARS 80).

Quando char_array è pieno, passa tutto l'array ad un nuovo processo figlio
che fa delle analisi che scrive su stdout (analisi sotto riportate).

Dopo aver lanciato il processo figlio, il processo principale azzera char_array ed il programma continua da 1:


*analisi svolte dai processi figlio (sull'array di 80 caratteri ricevuto)*
carattere minimo (mostrare il primo minimo, si applica a chi risolve dal 3/4)
carattere massimo (mostrare il primo massimo, si applica a chi risolve dal 3/4)
carattere con più occorrenze (il primo, a parità di occorrenze, si applica a chi risolve dal 3/4)
carattere con meno occorrenze (il primo, a parità di occorrenze, si applica a chi risolve dal 3/4)

fatta l'analisi e scritto i risultati , il processo figlio termina.
*/

#define NUM_CHARS 80

char * char_min(char * arr, int size){
	char min = 127;
	int min_pos=0;
	for(int i=0; i<size; i++){
		if(arr[i] < min){
			min = arr[i];
			min_pos = i;
		}
	}
	return &arr[min_pos];
}

char * char_max(char * arr, int size){
	char max = 0;
	int max_pos=0;
	for(int i=0; i<size; i++){
		if(arr[i] > max){
			max = arr[i];
			max_pos = i;
		}
	}
	return &arr[max_pos];
}

char * occorrenze_min(char * arr, int size){
	char * min_pos;
	int min_occ=80;
	for(int j=0; j<size; j++){
		int cnt = 0;
		for(int i=0; i<size; i++){
			if(arr[i]  == arr[j]){
				cnt ++;
			}
		}
		if(cnt < min_occ){
			min_pos = &arr[j];
			min_occ = cnt;
		}
	}
	return min_pos;
}

char * occorrenze_max(char * arr, int size){
	char * max_pos;
	int max_occ=0;
	for(int j=0; j<size; j++){
		int cnt = 0;
		for(int i=0; i<size; i++){
			if(arr[i]  == arr[j]){
				cnt ++;
			}
		}
		if(cnt > max_occ){
			max_pos = &arr[j];
			max_occ = cnt;
		}
	}
	return max_pos;
}

int main(void) {
	int cnt = 0, fork_calls = 0;
	char tmp;
	char char_array[NUM_CHARS];
	pid_t fpid;

	while( ( tmp = getchar() ) != EOF){
		char_array[cnt] = tmp;
		cnt++;
		if(cnt == 80){
			fpid = fork();
			fork_calls++;
			switch(fpid){
			case -1:
				perror("Error forking\n");
				exit(EXIT_FAILURE);
				break;
			case 0:
				printf("Min char: %c\n", *char_min(char_array, NUM_CHARS));
				printf("Max char: %c\n",*char_max(char_array, NUM_CHARS));
				printf("Min occurrences: %c\n",*occorrenze_min(char_array, NUM_CHARS));
				printf("Max occurrences: %c\n",*occorrenze_max(char_array, NUM_CHARS));
				exit(EXIT_SUCCESS);
				break;
			default:
				wait(NULL);
				cnt = 0;
				break;
			}
		}
	}
	printf("\n%d calls in total\n", fork_calls);
	return EXIT_SUCCESS;
}
