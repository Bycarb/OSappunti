#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/****esercizio 9****

usare l'esempio:
https://replit.com/@MarcoTessarotto/find-substring

typedef char * char_p;

struct risultato_ricerca {
    int numero_occorrenze; // dimensione del vettore posizione_occorrenza
    char_p * posizione_occorrenza; // vettore delle occorrenze; ogni occorrenza è riportata nel vettore
    // posizione_occorrenza è un vettore di char_p (o char *)

};

scrivere la funzione che restituisce tutte le occorrenze di substr in str:

struct risultato_ricerca trova_occorrenze(char * str, char * substr);*/

typedef char * char_p;
struct risultato_ricerca {
    int numero_occorrenze; // dimensione del vettore posizione_occorrenza
    char_p * posizione_occorrenza; // vettore delle occorrenze; ogni occorrenza è riportata nel vettore
    // posizione_occorrenza è un vettore di char_p (o char *)

};

struct risultato_ricerca trova_occorrenze(char * str, char * substr){

	char * pos = str;
	struct risultato_ricerca posizioni;
	posizioni.numero_occorrenze = 0;
	posizioni.posizione_occorrenza = malloc(1 * 8);
	posizioni.posizione_occorrenza[0] = NULL;

	while ((pos = strstr(pos, substr)) != NULL) {
		printf("ho trovato substr in str alla posizione %ld\n", pos - str);
		posizioni.posizione_occorrenza = realloc(posizioni.posizione_occorrenza, (posizioni.numero_occorrenze + 2) * 8);
		posizioni.posizione_occorrenza[posizioni.numero_occorrenze] = pos;
		posizioni.numero_occorrenze++;
		pos++;
	}

	return posizioni;
}

int main(void) {
	char * str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididuntemememeememememeemememeememememeememeememem";
	char * substr = "em";
	struct risultato_ricerca ricerca;
	ricerca = trova_occorrenze(str, substr);
	for(int i=0; i < ricerca.numero_occorrenze; i++){
		printf("Occorrenza %d = %.10s \n", i, ricerca.posizione_occorrenza[i]);
	}
	return EXIT_SUCCESS;
}
