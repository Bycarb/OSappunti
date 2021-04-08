#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/***esercizio 2

scrivere un programma che legge da stdin tutto fino a EOF e conta (separamente) i seguenti caratteri:
\n
' ' (spazio)
ed  i caratteri alfabetici minuscoli ('a'-'z')

dopo EOF, scrive su stdout il conteggio dei caratteri.

provare il programma utilizzando il file di testo che potete scaricare qui:
https://github.com/marcotessarotto/exOpSys/blob/master/res/text01.txt
"nome_programma" < text01.txt*/

int read_letters(){
	char current_letter;
	int spaces=0, newlines=0;
	int letters[26] = {0};
	while( ( current_letter = getchar() ) != EOF){
		if(current_letter == ' '){
			spaces++;
		}
		if(current_letter == '\n'){
			newlines++;
		}
		for(int i = 0; i < 26; i++){
			if(current_letter == i + 'a'){
				letters[i]++;
			}
		}
	}

	printf("%d \t spaces\n", spaces);
	printf("%d \t newlines\n", newlines);
	for(int i = 0; i < 26; i++){
		printf("%d \t %c\n",letters[i], 'a'+i);
	}

	return 0;

}

int main() {
	read_letters();
	return EXIT_SUCCESS;
}

