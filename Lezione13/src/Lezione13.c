
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// multithreading


typedef struct {
	int a;
	char *msg;

}thread_parameter_t;

typedef struct{
	int a;
	char*buffer;
}thread_result;

void *thread_entry_point(void * arg){ // la funzione di ingresso al thread deve essere un void e avere come parametro d'ingresso un puntaore generico
	printf("[thread1]: hullo!\n");
	thread_parameter_t * param = arg; // assegno alla variabile param l'indirizzo che mi viene passato
	printf("[thread1]: Received message: %s\n", param->msg);

	return param->msg;
}

void *thread_entry_point_2(void * arg){ // la funzione di ingresso al thread deve essere un void e avere come parametro d'ingresso un puntaore generico
	printf("[thread1]: hullo!\n");
	thread_parameter_t * param = arg; // assegno alla variabile param l'indirizzo che mi viene passato
	printf("[thread1]: Received message: %s\n", param->msg);

	return param->msg;
}


int main(void) {
	pthread_t t1;
	int res;
	thread_parameter_t param;
		param.a = 12345;
		param.msg = "Hola mundo!";
	void *returned;

	res = pthread_create(&t1, //salva il thread id in t1
			NULL,		//nessuna opzione
			thread_entry_point, //funzione d'ingresso
			&param);  // argomewnto della funzione d'ingresso
		if(res!=0){
			perror("pthread");
			exit(1);
		}

	res = pthread_join(t1,&returned);		//thread principale aspetta la conclusione del thread
		if (res != 0){
			perror("join");
			exit(1);
		}

	printf("[thread_main]: thread result: %s\n", returned);
	printf("[thread_main]: bye!\n");
	return EXIT_SUCCESS;
}
