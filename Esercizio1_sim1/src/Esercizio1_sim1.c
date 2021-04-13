#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* str_1 = "prima-";
char* str_2 = "seconda-";
char *str_3 = "terza!";
//
int main(void) {
	char *str_new = calloc( ( strlen(str_1) + strlen(str_2) + strlen(str_3) + 1) , sizeof(char) ); // alloco memoria pari alla lunghezza dei 3 array + \0
			if(str_new == NULL){
				perror("Error allocating memory\n");
				exit(EXIT_FAILURE);
			}
	str_new = strcpy(str_new, str_1); 					//copio la prima stringa
	strcpy(str_new + strlen(str_new), str_2);	//accodo la seconda stringa in fondo alla precendente
	strcpy(str_new + strlen(str_new), str_3);	//accodo la terza stringa in fondo alla precendente
	printf("%s", str_new);
	free(str_new);		// libero memoria anche se in questo caso e` una procedura inutile perche` verra` liberata comunque al termine del processo
	return EXIT_SUCCESS;
}
