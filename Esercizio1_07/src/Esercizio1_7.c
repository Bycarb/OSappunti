#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/****esercizio 7

leggere dal file numeri.txt tutti i numeri in un array; non fare ipotesi sul numero di numeri contenuti nel file
fare il sort per valori crescenti (con algoritmo di sorting... quello che volete oppure bubble sort, anche se non è "efficiente": https://github.com/marcotessarotto/exOpSys/blob/master/004.5bubble-sort/bubble-sort.c )
scrivere l'array ordinato nel file numeri_ordinati.txt

il contenuto del file numeri.txt è il seguente:
5
4
3
2
1
0
-1
-2
-3
-4
-5
<fine file numeri.txt>

risultato atteso nel file numeri_ordinati.txt:
-5
-4
.... */

void quicksort(int *a,int first,int last){
   int i, j, pivot, temp;
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

int main(void) {
	// 1: apro i file
	int fd_src, fd_dst;
	int * numbers = malloc(1 * sizeof(int));
	fd_src = open("numeri.txt", O_RDONLY);
		if(fd_src == -1){
			perror ("Error opening file");
			exit(EXIT_FAILURE);
		}
	fd_dst = open("numeri_ordinati.txt", O_WRONLY | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);
		if(fd_dst == -1){
			perror ("Error opening destination file");
			exit(EXIT_FAILURE);
		}

	//2: leggo l'array da file
	int allocated_size = 1; // numero di sizeof(int) allocati
	int rows_count = 0;
	int found_end = 0; // flag raggiungimento fine del file

	while(found_end == 0){
		char buf[50] = {0};
		int i = 0;

		do{
			int res = read(fd_src, &buf[i], 1);
				if(res == -1){
						perror ("Error reading file");
						exit(EXIT_FAILURE);
					}
			if(buf[i] == EOF) {
				found_end = 1;
			}
			i++;
		}while(buf[i-1] != '\n' && !found_end);

		buf[i-1] = '\0'; // cambio \n con \0

		if (allocated_size <= rows_count){ // aumento la memoria allocata per l'array in caso di bisogno
			allocated_size = allocated_size * 2;
			numbers = realloc(numbers, allocated_size * sizeof(int));
				if(numbers == NULL){
					perror ("Error allocating memory");
					exit(EXIT_FAILURE);
				}
		}

		int num = strtol(buf,NULL,10); // scrivo il numero nell'array
		numbers[rows_count] = num;
		rows_count ++;
	}

	//3: riordino i numeri nell'array
	quicksort(numbers, 0, rows_count-1);
	for(int  i=0; i<rows_count; i++){
		printf("%d\n", numbers[i]);
	}

	close(fd_src);

	for(int i=0; i<rows_count; i++){
		char buf[50] = {0};
		sprintf(buf,"%d\n",numbers[i]);
		int res = write(fd_dst, buf, strlen(buf));
			if(res == -1){
				perror("Error writing file.\n");
				exit(EXIT_FAILURE);
			}
		printf("written %d bytes\n", res);
	}

	return EXIT_SUCCESS;
}













