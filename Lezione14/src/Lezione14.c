
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

//semafori
// uso sem_open per creare un semaforo con nome
//faccio fare un operazione al padre, poi quando finisce faccio continuare il figlio

char * sem_name = "/my_sem";
sem_t* semaphore;

int main(void) {
	semaphore = sem_open(sem_name, O_CREAT, 0600, 0);
		if(semaphore == SEM_FAILED){
			perror("sem_open");
			exit(1);
		}

	switch(fork()){
	case -1:
		perror("fork");
		exit(1);
		break;
	case 0:
		//figlio
		if(sem_wait(semaphore) != 0){
			perror("sem_wait");
			exit(1);
		}
		printf("Ora il figlio puo` scrivere\n");
		if(sem_unlink(sem_name) != 0){
			perror("close");
			exit(1);
		}
		break;
	default:
		//padre
		sleep(5);
		printf("Ora faccio continuare mio figlio\n");
		if(sem_post(semaphore) != 0){
			perror("sem post");
			exit(1);
		}
		break;
	}
	return EXIT_SUCCESS;
}
