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

/**** esercizio 14 ***
è dato il tipo dati contact_type, dovrebbe servire ad implementare una rubrica telefonica molto semplice:

#define NAME_LEN 64
#define PHONE_LEN 20

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

scrivere le seguenti funzioni:

// crea un oggetto di tipo contact_type e lo inizializza con name e phone
contact_type * create_contact(char * name, char * phone);

// scrive su stdout i contenuti dell'oggetto
void print_contact(contact_type * person);

.....

// utilizzare questa implementazione di main:

int main(int argc, char *argv[]) {

	contact_type * pino = create_contact("pino rossi", "+393331234567");

	if (pino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * gino = create_contact("gino verdi", "+393487654321");

	if (gino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	print_contact(pino);

	print_contact(gino);

	return 0;
}


il risultato dell'esecuzione del programma sarà questo:

person: id=0, name='pino rossi', phone='+393331234567'
person: id=1, name='gino verdi', phone='+393487654321'    */

#define NAME_LEN 64
#define PHONE_LEN 20
int total_entries = 0;

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

// crea un oggetto di tipo contact_type e lo inizializza con name e phone
contact_type * create_contact(char * name, char * phone){
	contact_type *new_contact = malloc(sizeof(contact_type));
	new_contact->id = total_entries++;
	sprintf(new_contact->name, "%s", name);
	sprintf(new_contact->phone, "%s", phone);
	return new_contact;
}

// scrive su stdout i contenuti dell'oggetto
void print_contact(contact_type * person){
	printf("person: id=%d, name='%s', phone='%s'\n", person->id, person->name, person->phone);
}

int main(int argc, char *argv[]) {
	contact_type * pino = create_contact("pino rossi", "+393331234567");

	if (pino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * gino = create_contact("gino verdi", "+393487654321");

	if (gino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	print_contact(pino);

	print_contact(gino);

	return 0;
}
