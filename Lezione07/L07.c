
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void stringhe();
void vettori();
void funk();

int main() {
	//stringhe();
	//vettori();
	funk();
	return 0;
}

void stringhe(){
	//OPERAZIONI CON LE STRINGHE
	//Per ora sappiamo usare printf e scanf
	//STRLEN() restituisce la lunghezza della stringa
	char *stri = "12245";
	int str_len = strlen(stri);
	printf("La stringa ha lunghezza %d\n", str_len);

	// Confrontare stringhe di caratteri
	//int strncmp(const char *s1, const char *s2, size_t n);
	//restituisce 0 se sono uguali, <1 se la prima e` minore in ordine alfabetico della seconda e >1 altrimenti
	char * str_a = "Caiaa";
	char * str_b = "Caiaa";
	int res = strcmp(str_a, str_b);
	if(res == 0){
		printf("Le stringhe sono uguali\n");
	}else{
		printf("Le stringhe sono diverse\n");
	}

	//DUPLICARE UNA STRINGA
	// strdup
	// crea una copia della stringa in un nuovo spazion di memoria
	//char *strdup(const char *s);
	// restituisce l'indirizzo alla nuova stringa
	char * str_a2 = strdup(str_a);

	// COPIA DI STRINGHE
	//se voglio copiare una stringa su un altra
	// devo prima assicurarmi di avere abbastanza memoria
	// strcpy prende prima la destinazione poi la sorgente
	//  char *strcpy(char *dest, const char *src);
	// ritorna il puntatore a *dest
	char * str2 = malloc( (strlen(str_a) + 1) * sizeof(char));
	if  (str2 == NULL){
		perror("Error with malloc.\n");
		exit(1);
	}

	strcpy(str2, str_a);

	//concatenazione di stringhe
	//char *strcat(char *dest, const char *src);
	// valgono le stesse considerazioni di strcpy

	str2 = realloc(str2, strlen(str2) + strlen(str_a) + 2);
	if(str2 == NULL){perror("realloc error\n"); exit(1);}
	strcat(str2, str_a);
	printf("%s\n", str2);

}

void vettori(){
	int dim_array = 1024;
	int * arr;
	arr = malloc(dim_array * sizeof(int)); // alloco memoria heap per 1024 elementi
	if(arr == NULL){perror("malloc error.\n"); exit(1);}

	//malloc mantiene l'allocazione di memoria anche fuori dallo scopo attuale della variabile!

	//Per inizializzare la memoria posso usare memset
	//void *memset(void *s, int c, size_t n);
	// inizializza i primi n caratteri della memoria s al valore c
	arr = memset(arr, 0, dim_array);

	//posso anche usare calloc che inizializza
	//anche gli elementi nella memoria a 0
	// nmeb elementi di dimensione size
	//void *calloc(size_t nmemb, size_t size);
	free(arr);
	arr = calloc(dim_array, sizeof(int)); // alloco memoria heap per 1024 elementi
	if(arr == NULL){perror("malloc error.\n"); exit(1);}

	// una volta destinata la memoria, posso ridimensionarla con realloc

}

// funzione che prende come parametri 2 array di int con le rispettive dimensioni e li concatena
void *intcat(int *arr1, int dim1, int arr2, int dim2){
	//alloco una zona di memoria
	int * res = calloc(dim1 + dim2, sizeof(int));
	if(res == NULL){
		printf("errore nell'allocazione di memoria\n");
		return NULL;
	}

	//copio con memcpy
	memcpy(res, arr1,dim1); // riempie fino a (dim1 - 1)
	memcpy(&res[dim1], arr2, dim2); // parto dalla prima cella libera
	return res;
}

//scrivere un file
void funk(){
	// 2 casi diversi:
		// il file esiste gia`
		// il file va creato
		// il file esiste ma deve essere sovrasctitto
	char * filename = "Prova.txt";
	int fd;


	//se il file non esiste, devo crearlo
	// per creare il file, open ha bisogno di un terzo parametro per impostare i permessi
	// creo un file e imposto i permessi di lettura e scrittura per l'utente corrente
	fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	char * msg = "Hullo!";
	int msg_len = strlen(msg);
	int bytes_written = write(fd, msg, msg_len);
	printf("Scritti %d bytes\n", bytes_written);
	close(fd);

	//se il file esiste gia`, dico ad open di aprirlo in scrittura
	fd = open(filename, O_WRONLY);

	if(fd == -1){
		perror("Problema con open\n");
		exit(1);
	}
	close(fd);

}




