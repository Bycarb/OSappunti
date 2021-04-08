#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/***esercizio 1

scrivere un programma che fa la copia di un file
il programma prende come parametro a riga di comando:
- il nome del file "sorgente"
- il nome del file "destinazione"
se il file destinazione esiste, "tronca" a zero la sua dimensione (prima di scriverlo).
il programma controlla i risultati di tutte le system call.

esempio: se il file sorgente non esiste, fornisce un messaggio opportuno.
potreste usare le seguenti system call: open, read, write, close */


int main(int argc, char * argv[]) {
	char * sr = argv[1];
	char * dst = argv[2];// puntatori ad argv per migliore leggibilita` del codice

	printf("Copying %s to %s\n",sr, dst);

	int fd_sr;
	fd_sr = open(sr, O_RDONLY);
		if(fd_sr == -1){
			perror("Error opening source file");
			exit(EXIT_FAILURE);
		}
	int fd_dst;
	fd_dst = open(dst, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if( fd_dst == -1){
		perror("Error opening destination file");
		exit(EXIT_FAILURE);
	}

	char * buff[100];
	int cnt_tot = 0;
	int cnt = 0;
	while( (cnt = read(fd_sr, buff, 100) ) != 0){
		if(cnt == -1){
			perror("Error reading file.\n");
			exit(EXIT_FAILURE);
		}
		if( write(fd_dst, buff, cnt) == -1 ){
			perror("Error writing file\n");
			exit(EXIT_FAILURE);
		}
		cnt_tot += cnt;
	}

	if( close(fd_dst) == -1 ){
				perror("Error closing file\n");
				exit(EXIT_FAILURE);
			}
	if( close(fd_sr) == -1 ){
				perror("Error closing file\n");
				exit(EXIT_FAILURE);
			}

	printf("Successfully written %d Bytes.\n", cnt_tot);


	return EXIT_SUCCESS;
}



