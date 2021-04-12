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
char * shuffle(char *s){

}

int main(void) {
	char *s = "hello world mi chiamo pino sono date delle stringhe";
	char * s1;
	s1 = shuffle(s);
	return EXIT_SUCCESS;
}
