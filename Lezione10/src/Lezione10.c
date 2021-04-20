#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>

//PIPES
//

int main(void) {
	//programma che chiede al kernel una pipe
	//processo padre crea un figlio con fork e condivice la pipe
	//ilp rocesso padre manda dati al processo figlio attraverso la pipe
	int res;
	int pipefd[2];
	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(1);
	}
	printf("Pipebuf: %d\n", PIPE_BUF ); //dimensione massima buffer della pipe
	printf("Estremita` di lettura: %d\n", pipefd[0]); //3 e 4 preche` stdin e stdout sono impegnati
	printf("Estremita` di scrittura: %d\n", pipefd[1]);

	char read_buffer[32];
	char *msg = "Ciao\n";

	switch(fork()){
	case -1:
		perror("fork");
		exit(1);
		break;
	case 0:
		//figlio
		if (close(pipefd[1]) ) { // chiudo l'estremita` in scrittura, se la tenessi aperta non funzionerebbe
							perror("close");  exit(1);
						}

		while( (res = read(pipefd[0], read_buffer, sizeof(read_buffer) ) )  > 0){
			printf("Child read: %d\n", res);
			printf("Child read: %s\n", read_buffer);
		}
		if(res == 0){
			printf("Child: EOF su pipe\n");
		}else{
			perror("read");exit(1);
		}
		exit(0);
		break;
	default:
		//padre
		res = write(pipefd[1], msg, strlen(msg) + 1);
		printf("Parent: res = %d\n", res);
		if (close(pipefd[1]) ) {//l'estremita` in lettura riceve EOF
					perror("close");  exit(1);
				}
		break;
	}

	return EXIT_SUCCESS;
}
