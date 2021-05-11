#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h>

/*
processo padre controlla il figlio tramite segnali
sigusr1 -> avvia produzione
sigusr2 -> ferma produzione
sigterm -> termina processo figlio
processo padre riceve i comandi da stdin: +/-/q(uit)
 */


pid_t child_pid;
int cookie_machine_state;

void child_process_signal_handler(int signum){
	if(signum == SIGUSR1){
		//accendo la cookie machine
		cookie_machine_state = 1;
	}else if(signum == SIGUSR2){
		//spengola cookie machine
		cookie_machine_state = 0;
	}else if(signum == SIGTERM){
		printf("Term received");
		exit(0);// exit provoca la terminazione del processo figlio
	}
}

void child_process(){
	if(signal(SIGUSR1, child_process_signal_handler) == SIG_ERR){
		perror("signal");exit(1);
	}
	if(signal(SIGUSR2, child_process_signal_handler) == SIG_ERR){
		perror("signal");exit(1);
	}
	if(signal(SIGTERM, child_process_signal_handler) == SIG_ERR){
		perror("signal");exit(1);
	}

	while(1){
		while(cookie_machine_state){
			printf("Cookie produced\n");
			sleep(3);
		}
		pause();
	}
}

void parent_process(){
	while(1){
		char in = getchar();
		switch (in){
		case '+':
			if(kill(child_pid, SIGUSR1) == -1 ){
				perror("kill");exit(1);
			}
			break;
		case '-':
			if(kill(child_pid, SIGUSR2) == -1 ){
				perror("kill");exit(1);
			}
			break;
		case 'q':
			if(kill(child_pid, SIGTERM) == -1 ){
				perror("kill");exit(1);
			}
			exit(0);
			break;
		default:
			break;
		}
	}
}

int main(void) {


	switch(child_pid = fork()){
	case -1:
		perror("fork");
		break;
	case 0:
		child_process();
		break;
	default:
		parent_process();
		break;
	}
	return EXIT_SUCCESS;
}
