#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h>

//creo un semaforo unnamed in una zona di memoria condivisa tra proceso padre e processo figlio
//uso il spamforo per sincronizzare i 2 processi

#define MMAP_SIZE 1024
char * memorymap;
int * global_counter;
sem_t * shared_semaphore;

int main(void) {
	memorymap = mmap(NULL, MMAP_SIZE,
			PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS,
			-1, 0);
		if(memorymap == MAP_FAILED){
			perror("mmap");
			exit(1);
		}

		global_counter = (int*) memorymap;
		shared_semaphore = (sem_t *)memorymap + sizeof(int);

		if(sem_init(shared_semaphore, 1, 0) == -1){ // 1 = semaforo condiviso tra processi
			perror("sem_init");
			exit(1);
		}

		//creo padre e figlio
		int pid;
		switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			//figlio
			for(int i = 1; i<1000000000; i++){}
			printf("Figlio lancia sem_post\n");
			if(sem_post(shared_semaphore) != 0){
				perror("sem_post");
				exit(1);
			}
			printf("Figlio esce\n");
			break;
		default:
			//pardre aspetta il semaforo dal figlio
			printf("Parent waiting\n");
			if(sem_wait(shared_semaphore) != 0){
				perror("sem_wait");
				exit(1);
			}
			if(sem_destroy(shared_semaphore) != 0){
				perror("sem_post");
				exit(1);
			}
			break;
		}
	return EXIT_SUCCESS;
}
