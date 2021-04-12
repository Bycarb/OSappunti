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

/****esercizio 17 ****
***convertire in codice C il seguente programma in Java***

tratto da:
https://algorithms.tutorialhorizon.com/find-the-only-element-in-array-which-appears-only-once/

trova l'unico elemento dell'array che appare una volta sola
IPOTESI: tutti gli elementi dell'array compaiono esattamente due volte, tranne un unico elemento che compare una volta sola.

Esempio:

int [] a = { 1,5,6,2,1,6,4,3,2,5,3};
output: 4


scrivere in C la versione "forza bruta" dell'algoritmo (il sito web riporta altre due versioni, facciamo questa come esercizio).
usare cicli annidati e confrontare ciascun elemento dell'array con tutti gli altri elementi per tracciare l'elemento che è non-ripetuto.


Time Complexity: O(n^2)

public class EveryElementsRepeatedButOne {

    public static void findBruteForce(int [] a){
        boolean [] visited = new boolean[a.length];
        for (int i = 0; i <a.length ; i++) {
            int x = a[i];
            if(visited[i]==false) {
                boolean isDuplicate = false;
                for (int j = i + 1; j < a.length; j++) {
                    if (x == a[j]) {
                        isDuplicate = true;
                        visited[j] = true;
                    }
                }
                if (!isDuplicate)
                    System.out.println("Element appear only once in array - " + x);
            }
        }
    }

    public static void main(String[] args) {
        int [] a = { 1,5,6,2,1,6,4,3,2,5,3};
        findBruteForce(a);
    }
}
*/

void find_brute_force (int a[], int a_len){
	int visited[a_len];
	for (int i = 0; i <a_len ; i++) {
		int x = a[i];
		if(visited[i]==0) {
			int isDuplicate = 0;
			for (int j = i + 1; j < a_len; j++) {
				if (x == a[j]) {
					isDuplicate = 1;
					visited[j] = 1;
				}
			}
			if (!isDuplicate)
				printf("Element appear only once in array - %d\n", x);
		}
	}
}

int main(void) {
	int len = 11;
	int  a[] = { 1,5,6,2,1,6,4,3,2,5,3};
	find_brute_force(a, len);
	return EXIT_SUCCESS;
}
