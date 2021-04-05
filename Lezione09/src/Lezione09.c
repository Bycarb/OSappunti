#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>


void funk(){
	// usiamo lseek()
	//off_t lseek(int fd, off_t offset, int whence);
	// usiamo lseek per spostarci alla posizione 100 dall'inizio del file
	char * filename = "Text01.txt";
	int fd;
	off_t current_file_offset;

	fd = open(filename, O_RDWR);
	if(fd==-1){
		perror("Error in Open");
		exit(EXIT_FAILURE);
	}
	current_file_offset = lseek(fd, 0, SEEK_CUR);
	printf("Offset attuale: %d\n", current_file_offset);

	// mi sposto alla fine del file

	current_file_offset = lseek(fd, -1, SEEK_END);
	printf("Offset attuale: %d\n", current_file_offset);

	// leggiamo 100 byte dalla posizione 100
	current_file_offset = lseek(fd, 100, SEEK_SET);
	printf("Offset attuale: %d\n", current_file_offset);

	char buff[100 + 1] = {0};
	int res = read(fd, buff, 100);
	printf("Read ha letto %d bytes\n"
			"il cui contenuto e` \n%s\n", res, buff);


	// mi posiziono 100 byte dopo la fine del file
	// non si vede dall'editor di testo che trova un EOF, ma si possono vedere da terminale
	current_file_offset = lseek(fd, 100, SEEK_END);
	printf("Offset attuale: %d\n", current_file_offset);

	memset(buff, '!', 100);
	res = write(fd, buff, 10);
	printf("Write ha scritto %d bytes\n", res);


}

int incrementa_contatore(){
	// uso di FLOCK
	//int flock(int fd, int operation);
	//Operations:
	//LOCK_SH  Place a shared lock.  More than one process may hold a shared lock for a given file  at a given time.
	//LOCK_EX  Place  an exclusive lock.  Only one process may hold an exclusive lock for a given file at a given time.
	//LOCK_UN  Remove an existing lock held by this process.

	// creiamo un file che conta il numoero di volte che e` stato aperto

	int fd;
	int res
	char * filename = "contatore.txt"; // ipotizzo che contatore.txt esista gia`
	fd = open(filename, O_RDWR);
	if(fd == -1){
		perror("Error opening file.");
		exit(EXIT_FAILURE);
	}

	// BLOCCO IL FILE ALL'ACCESSO DA PARTE DI ALTRI PROGRAMMI
	res = flock(fd, LOCK_EX);
	if(res == -1){
		perror("flock()");
		exit(EXIT_FAILURE);
	}

	// leggo il numero dal file
	int contatore;
	res = read(fd, &contatore, sizeof(contatore));
	if(fd == -1){
			perror("Error reading file.");
			exit(EXIT_FAILURE);
	} else if (res < 0){
			perror("Error: less than 4 bytes read.");
			exit(EXIT_FAILURE);
	}
	contatore++; // incremento il contaotore e  lo scrivo
	off_t offset = lseek(fd, 0 , SEEK_SET);
	if(offset == -1){
				perror("Error in lseek()");
				exit(EXIT_FAILURE);
		}
	res = write (fd, &contatore, sizeof(contatore));
	if(fd == -1){
				perror("Error reading file.");
				exit(EXIT_FAILURE);
		} else if (res < 0){
				perror("Error: less than 4 bytes read.");
				exit(EXIT_FAILURE);
		}

	// SBLOCCO IL FILE
	res = flock(fd, LOCK_UN);
	if(res == -1){
		perror("Error unlocking file\n");
		exit(EXIT_FAILURE);
	}

	if(close(fd) == -1){ // chiudo il file
		perror("close()\n");
	}

	return contatore;
}


int main(){
	//funk();
	incrementa_contatore();

	return 0;
}
