#include <stdio.h>
#include <stdlib.h>

#define debug

void swap (int *a, int *b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
int int_cmp(int *a, int *b){
	if (*a == *b) return 0;
	if(*a > *b) return 1;
	else return -1;
}
int main(void) {
	int a = 0;
	int b[] = { 1, 23, 54235, 1, 42, 456, 52, 1, 5154, 674,21 };
	//char c[BUFSIZ];
	swap(&a,b);
	int c[5];
	realloc(c, 10 *sizeof(int));
	for(int i = 0; i<40; i++){
		printf("%d %d\n", a, b[i]);
	}
#if defined (debug)
	qsort(b, 11, sizeof(int), int_cmp);
	for(int i =0; i<11; i++){
		printf("%d\n", b[i]);
	}
#endif
	return EXIT_SUCCESS;
}
