#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/wait.h>

/****esercizio 11****

usare l'esempio:
https://replit.com/@MarcoTessarotto/get-load-average

scrivere un programma in C che faccia quanto segue:

il programma prevede come parametri a linea di comando due valori (int):
numero di cicli (default: 10)
intervallo (secondi) (default: 5)

se i parametri non sono forniti, usare i valori di default indicati sopra.

crea il file log.txt per scriverci di dati ottenuti sotto; il file viene sovrascritto, se esiste già.

per 'numero di cicli' volte, a distanza di 'intervallo' secondi, rileva il 'load average over 1 minute' (vedi getloadavg() ed esempio fornito);
ad ogni interazione scrive il valore in formato testo all'interno di un file 'log.txt'.


alla fine del ciclo:
- il processo padre crea un processo figlio che calcola e scrive su stdout il valor medio dei valori di 'load average over 1 minute' ottenuti nel ciclo sopra
- il processo figlio scrive il valor medio calcolato in un file 'result.txt' ; il numero è scritto in formato testo
- il processo padre aspetta la terminazione del processo figlio; poi legge il valore calcolato dal processo figlio dal file 'result.txt'

seconda parte dell'esercizio:

il processo padre fa il sort crescente dei valori rilevati nel ciclo principale;
poi inserisce il valore medio calcolato dal processo figlio nella posizione opportuna dell'array ordinato, per mantenere l'ordinamento del nuovo array.*/

void log_loadavg(int cycles, int time_interval, char *name){ // crea file di log
	int res;
	double sample[3];
	char *buf = calloc(100, 1);
	int fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		if(fd == -1){
			perror("error creating file.\n");
			exit(EXIT_FAILURE);
		}
	for(int i=0; i<cycles; i++){
		res = getloadavg(sample, 1); // prendo il valore
			if(res == -1){
				perror("Error using getloadavg()\n");
				exit(EXIT_FAILURE);
			}
		sprintf(buf, "%10.5f\n", sample[0]);
		res = write(fd, buf, strlen(buf)); // scrivo la srtinga su file
			if(res == -1){
				perror("Error writing log\n");
				exit(EXIT_FAILURE);
			}
		sleep(time_interval);
	}
	res = close(fd);
		if(res == -1){
			perror("error closing file\n");
			exit(EXIT_FAILURE);
		}
	free(buf);
}

void quicksort(double *a,int first,int last){
   int i, j, pivot;
   double temp;
   if(first < last){
	  rand(); //randomizzo per evitare il worst case
      pivot=first + rand()%(last - first );
      i=first;
      j=last;


      while(i<j){
         while(a[i]<=a[pivot]&&i<last)
            i++;
         while(a[j]>a[pivot])
            j--;
         if(i<j){
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
         }
      }

      temp=a[pivot];
      a[pivot]=a[j];
      a[j]=temp;
      quicksort(a,first,j-1);
      quicksort(a,j+1,last);
   }
}

double * insert_into_array(double * array, int array_len, double val, int insert_position){
	if (insert_position < 0 || insert_position > array_len){
		printf("Invalid insertion position.\n");
		return NULL;
	}
	double *newarray = malloc( (array_len + 2) * sizeof(double) );
		if(newarray == NULL){
			perror("Error in memory allocation\n");
			exit(EXIT_FAILURE);
		}

	for(int i=0; i<insert_position; i++){
		newarray[i] = array[i];
	}
	newarray[insert_position] = val;
	for(int i=insert_position; i< array_len+1; i++ ){
		newarray[i+1] = array[i];
	}

	return newarray;
}

int array_doubles_from_file(double arr[], char *file_name){
	int fd;
	char *buf = calloc(20, sizeof(char));
	fd = open(file_name, O_RDONLY);
		if(fd == -1){
			perror("Error opening file\n");
			exit(EXIT_FAILURE);
		}
	//arr = malloc(sizeof(double));
	int size=-1;
	while( read(fd, buf, 10 + 1) > 0 ){
		size++;
		arr[size] = strtod(buf, NULL);
		//arr = realloc(arr, ( size + 2*sizeof(double) ) );
		//	if(arr == NULL){
		//		perror("error memory allocation\n");
		//		exit(-1);
		//	}
	}

	close(fd);
	free(buf);
	return size + 1;
}

double get_avg_from_arr(double *arr, int size){
	double sum = 0;
	double avg = 0;
	for(int i=0; i<size; i++){
		sum += arr[i];
	}
	avg = sum / (double) size;

	return avg;
}

int main(int argc, char *argv[]) {
	int cycles = 10;
	int time_interval = 5;
	char *name = "log.txt";
	char *nameavg = "result.txt";
	pid_t processo;

	if(argc >= 2){
		cycles = strtol(argv[1], NULL, 10);
	}
	if(argc >= 3){
		time_interval = strtol(argv[2], NULL, 10);
	}

	log_loadavg(cycles, time_interval, name); //creo file di log

	// creo padre e figlio

	processo = fork();
		if(processo == -1){
			perror("Error in fork()\n");
			exit(EXIT_FAILURE);
		}
	if(processo == 0){
		// figlio: leggo i risultati dal file e calcolo la media
		double *arr = malloc(cycles * sizeof(double));
		int size;
		double avg;
		char *buf = calloc(20, sizeof(char));

		size = array_doubles_from_file(arr, name);
		avg = get_avg_from_arr(arr, size);
		sprintf(buf,"%10.5f", avg);

		int fd = open("result.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
				if(fd == -1){
					perror("error creating file.\n");
					exit(EXIT_FAILURE);
				}
		if (write(fd, buf, 10+1) < 1 ){
			perror("Error writing result file\n");
			exit(EXIT_FAILURE);
		}
		if(close(fd)){
			perror("Error closing file\n");
		}
		free(buf);
		exit(EXIT_SUCCESS);
	}else{
		// processo padre stampa avg dal file

		wait(NULL);
		char *buf = calloc(20, sizeof(char));
		double avg;
		int res;


		int fd = open(nameavg, O_RDONLY);
			if(fd == -1){
				perror("error opening non existent file.\n");
				exit(EXIT_FAILURE);
			}
		res = read(fd, buf, 10 + 1);
			if(res < 1){
				perror("Error reading file\n");
				exit(EXIT_FAILURE);
			}
		avg = strtod(buf, NULL);
		printf("La media e` %10.5f\n", avg);

		//parte 2 :  ordino array
		int size;
		double *arr = calloc(cycles + 1, sizeof(double));
		size = array_doubles_from_file(arr, name);
		quicksort(arr, 0, size - 1);
		for(int i = 1; i<size; i++){
			if(arr[i]>= avg && arr[i-1]<=avg){
				arr = insert_into_array(arr, size, avg, i);
				break;
			}
		}
		printf("Final result = \n");
		for(int i=0; i< size+1; i++){
			printf("%10.5f\n", arr[i]);
		}
	}

	return EXIT_SUCCESS;
}
