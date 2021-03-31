

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

// creare una struct
struct point{
	int x;
	int y;
};

//creare un tipo dati con typedef
typedef char* my_string; // my_string e` un tipo dati puntatore a carattere
typedef struct point punto; // in questo modo posso chiamare point senza dover scrivere ogni volta struct


// esempio calcola la distanza tra 2 punti
double distance(punto p1, punto p2){
	double dist = 0;
	int x = p1.x - p2.x;
	int y = p1.y - p2.y;
	dist = sqrt( (double)(x*x) + (double)(y*y) );

	return dist;
}

//rifacciamo distance ma con i puntaotri
double distance2(struct point *p1, struct point *p2){
	double dist = 0;
	//per indirizzare elementi interni alla struct indicata da un puntatore uso ->
	int x = p1->x - p2->x;
	int y = p1->y - p2->y;
	dist = sqrt( (double)(x*x) + (double)(y*y) );

	return dist;
}

void funk(){
	struct point a = {0 , 0 };
	struct point b ={ 10 , 10};
	// posso anche definire un puntatore a una struct
	struct point *c = &a;

	printf("%f\n",distance(a,b));

}

//uso di fork()
//processo padre e figlio lavorano sullo stesso standard in e out
void funk_fork(){
	printf("Sono il processo padre %d!!\n",getpid());
	pid_t res;
	res = fork();
	switch (res){
		case -1 :
			perror("Errore nel fork\n");
			exit(EXIT_FAILURE);
			break;
		case 0: // sono nel processo figlio
			sleep(1);
			printf("F:Sono il figlio numero %d!\n",getpid());
			printf("F:Mio padre e` %u\n",getppid()); //getppid() restituisce il numero di processo del proc. padre
			// se il processo padre termina, il processo figlio resta orfano e viene "preso in carico" dal padre del padre
			//il padre di tutti e` il processo init con pid = 1
			break;
		default: // sono nel processo padre
			printf("P:%d, sono tuo padre!\n",res);
			printf("P:Ora aspetto la morte di mio figlio :'(\n");
			wait(NULL);
			printf("P:Mio figlio e` morto. \nOra la mia anima in pena restera` ad infestare questo computer per l'eternita`\n");
			break;
	}
}



// la funzione main quando viene invocata riceve un array di stringhe (argv) e la lunghezza di tale array (argc)
// di default il primo e unico argomento di argv e` il path del programma
// se all'invocazione inserisco altri parametri dopo il nome del programma e separati da spazi,
//saranno aggiunti ad argv
int main(int argc, char * argv[]) {
	//funk();

	int i=0;
	while(argv[i] != NULL){
		printf("%s \n",argv[i]);
		i++;
	}
	funk_fork();
	return EXIT_SUCCESS;
}



