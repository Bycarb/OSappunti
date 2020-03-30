#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char * argv[]) {


	// parametri per il programma che invocheremo con execve
	char * new_arguments[] = { "000hello-world", NULL };

	// variabili di environment per il programma che invocheremo con execve
	char * new_environment_variables[] = { NULL };

	char * current_working_directory = getcwd(NULL,0);

	printf("cartella corrente: %s\n", current_working_directory);


	printf("ora proviamo ad eseguire 000hello-world (fate il build del progetto)\n\n\n");


	/*
	 * execve()  executes  the  program referred to by pathname.
	 *
	 * This causes the program that is currently being run by
	 * the calling process to be replaced with a new program ...
	 *
	 */

	execve("../000hello-world/build/default/000hello-world", new_arguments, new_environment_variables);

	// On success, execve() does not return, on error -1 is returned, and errno is set appropriately.

	perror("execve");
	// The perror() function produces a message on standard error describing the last error
	// encountered during a call to a system or library function.

	// https://www.tldp.org/LDP/abs/html/exitcodes.html

	return 1;
}
