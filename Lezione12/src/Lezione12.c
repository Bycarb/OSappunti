#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

//usiamo mmap() per mappare un file nella memoria


int funkmap(void) {
	//apro un file con open e voglio averlo sotto forma di memory map in memoria

	int fd;
	struct stat sb;
	char* address;
	fd = open("prova.txt", O_RDONLY);
		if(fd ==-1){
			perror("opne\n");
			exit(1);
		}
	//devo specificare la dimensione della memory map
	if( fstat(fd, &sb) == -1){ // cerco le statistiche del file per trovare la dimensione
		perror("fstat\n");
		exit(1);
	}
	int bytes_to_read = sb.st_size;
	printf("file size = %ld\n", sb.st_size);
	address = mmap(NULL, bytes_to_read, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
		if( address == MAP_FAILED){
				perror("mmap\n");
				exit(1);
			}
	close(fd); // mmap si crea una "copia" del fd, quindi posso liberarlo
	write(1, address, sb.st_size); // scrivo il contenuto del mapping su stdout, printf non funziona perche manca /0

	if( munmap (address, sb.st_size) == -1 ){ // libero la memoria mappata
		perror("munmap");
		exit(1);
	}
	return EXIT_SUCCESS;
}


int main(void){
	//creo una memory map condivisa tra padre e filgio
	// processo figlio modifica la memory map e quando termina il padre legge le modifiche apportate
	//le modifiche alla memory map dovranno essere riportate anche su file
	int fd;
	struct stat sb;
	char* address;
	fd = open("prova.txt", O_RDWR); // ipotizzo che il file esista gia'
		if(fd ==-1){
			perror("opne\n");
			exit(1);
		}
	//devo specificare la dimensione della memory map
	if( fstat(fd, &sb) == -1){ // cerco le statistiche del file per trovare la dimensione
		perror("fstat\n");
		exit(1);
	}
	int bytes_to_read = sb.st_size;
	printf("file size = %ld\n", sb.st_size);
	address = mmap(NULL,
			bytes_to_read,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			fd, 0);
		if( address == MAP_FAILED){
				perror("mmap\n");
				exit(1);
			}
	close(fd); // mmap si crea una "copia" del fd, quindi posso liberarlo

	//creo padre e figlio
	switch( fork()) {
	case -1:
		perror("fork");
		exit(1);
		break;
	case 0:
		address[0] = 'M';
		exit(0);
		break;
	default:
		if( wait(NULL) == -1 ){
			perror("wait");
			exit(1);
		}
		break;
	}

	write(1, address, sb.st_size); //stampo

	if( munmap (address, sb.st_size) == -1 ){ // libero la memoria mappata
		perror("munmap");
		exit(1);
	}
	return EXIT_SUCCESS;
}
