#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <limits.h>
#include <ctype.h>

//Ho cercato di svolgere il punto 2 full, ma ho avuto problemi con l'input, quindi leggo da una stringa predefinita in maniera simile alla versione simple

void process_line(char * line, char ** arr, int arr_len) {
	arr[arr_len] = strcpy(arr[arr_len], line);
}

char ** read_lines_from_file(char * filename, int * arr_len) {

	int fd;
	int bytes_read; // bytes letti da system call read()

	int arr_size = 0;
	int alloc_size = 1;
	char **arr = calloc(alloc_size, sizeof(char));
		if( arr == NULL){
			perror("calloc");
			exit(1);
		}

	char * buffer; // usato per i dati restituiti da system call read()
	int buffer_size = 10; // dimensione della memoria allocata dinamicamente per buffer
	buffer = malloc(buffer_size * sizeof(char));
	if (buffer == NULL) {
		perror("malloc");
		exit(1);
	}

	int buffer_len;

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	printf("reading file %s\n", filename);

	while ((bytes_read = read(fd, buffer, buffer_size)) > 0) {

		// cerchiamo la posizione della prima occorrenza di \n dentro i dati restituiti da read()
		int pos = 0;
		while (buffer[pos] != '\n' && pos < bytes_read )
			pos++;
		// se \n non è presente, la condizione è pos == bytes_read

		// se non abbiamo trovato 'n' nei dati letti E buffer_size == bytes_read,
		// allora: aumentiamo la dimensione del buffer, restituiamo i dati con lseek e rileggiamo la linea
		if (pos == bytes_read && buffer_size == bytes_read) {

			// aumentiamo la dimensione del buffer
			buffer_size = buffer_size * 2; // raddoppiamo la dimensione
			buffer = realloc(buffer, buffer_size);
			if (buffer == NULL) {
				perror("realloc");
				exit(1);
			}

			// spostiamo indietro il file offset (cioè restituiamo tutti i dati della linea corrente)
			if (lseek(fd, -bytes_read, SEEK_CUR) == -1) {
				perror("lseek");
				exit(1);
			}

			// e rileggiamo i dati (della linea corrente)
			continue;
		}

		buffer[pos] = 0; // 'terminiamo' la stringa (sostituiamo \n con \0)
		buffer_len = pos; // strlen(buffer); la lunghezza della stringa è nota (è pos)

		// la linea (stringa di caratteri) corrente si trova in buffer ed è terminata da \0
		// process_line fa "qualcosa" con il contenuto letto
		// per comodità di process_line, passiamo anche buffer_len
		alloc_size += ( buffer_len + 1 );
		arr[arr_size] = calloc(arr[arr_size], ( ( buffer_len + 1 ) * sizeof(char) ) );
				if(arr == NULL){
					perror("calloc");
					exit(1);
				}
		process_line(buffer, arr, arr_size);
		arr_size++;
		arr = realloc(arr, (arr_size+1) * sizeof(char*) );
				if( arr == NULL){
					perror("realloc");
					exit(1);
				}

		// se ci sono dati non processati in buffer, li "restituiamo"
		// spostando all'indietro l'offset del file
		// così i dati non processati saranno "ri-restituiti" nella prossima invocazione di read()
		__off_t new_offset =  pos + 1 - bytes_read; // calcoliamo lo spostamento relativo

		// invochiamo la system call se e solo se new_offset != 0
		if (new_offset != 0 && lseek(fd,new_offset , SEEK_CUR) == -1) {
			perror("lseek");
			exit(1);
		}
	} // fine while

	close(fd);
	*arr_len = arr_size;
	return arr;
}

char * read_words(){
	int res;
	int size = 256;
	char* str = malloc(size * sizeof(char));
		if(str == NULL){
			perror("malloc\n");
			exit(1);
		}
	int pos = 0;
	int tmp;
	while( (res = read (0, &tmp, 1) ) == 1){
		if(res == -1){
			perror("read");
			exit(1);
		}
		str[pos] = tmp;
		pos++;
		if(pos >= size){
			size*= 2;
			str = realloc(str, size * sizeof(char));
					if(str == NULL){
						perror("realloc\n");
						exit(1);
					}
		}
	}
	str[pos] = 0;
	return str;
}

void print_not_in_dictionary(char **input, char **dict, int input_len, int dict_len){
	pid_t res;
	int i = 0;
	for(i = 0; i<input_len; i++){
		int is_found = 0;
		res = fork();
		switch(res){
			case 0: // figlio stampa se la parola non esiste
				for(int j =0; j<dict_len; j++){
					if( !strcmp( input[i], dict[j]) ){
						is_found = 1;
						break;
					}
				}
				if(!is_found){
					printf("%s\n", input[i]);
				}
				exit(0);
				break;
			case -1:
				perror("fork");
				exit(1);
				break;
			default:  // padre aspetta la termonazione del processo figlio
				wait(NULL);
				break;
		}
	}
}

char ** split_string(char s_input[], int *elements){
	char * s = calloc(strlen(s_input), sizeof(char));
	int size =20;
	s = strcpy(s, s_input);
			if(s == NULL){
				perror("Error copying with input string\n");
				return NULL;
			}
	char * newstring = calloc(strlen(s), sizeof(char));
		if (newstring == NULL){
			perror("Error allocating memory");
			return NULL;
		}
	char *tmp;
	char **arr_words = calloc (size, sizeof(char*));
			if (arr_words == NULL){
				perror("Error allocating memory");
				return NULL;
			}

	//splitto s nelle varie parole e
	// memorizzo le posizioni di tutte le parole separate in un array
	tmp = strtok(s, " ");
	arr_words[0] = tmp;
	int i=1;
	while( (tmp= strtok(NULL, " \n")) != NULL){
		arr_words[i] = tmp;
		i++;
		if(i >= size){
			size*=2;
			arr_words = realloc (arr_words, size * sizeof(char));
				if(arr_words == NULL){
					perror("realloc");
					exit(1);
				}
		}

	}
	*elements = i;
	return arr_words;
}

int main(void) {
	char *dicname =  "/usr/share/dict/american-english";
	int dict_len;
	char **dict = read_lines_from_file(dicname, &dict_len);
	int input_len;
	char *input = read_words();
	for(int i = 0; i< strlen(input); i++){
		input[i] = tolower(input[i]);
	}
	char **input_array = split_string(input, &input_len);

	print_not_in_dictionary(input_array, dict, input_len, dict_len);
	return EXIT_SUCCESS;
}
