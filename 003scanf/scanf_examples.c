#include <stdio.h>

/*

da https://en.wikipedia.org/wiki/Scanf_format_string

    %a : Scan a floating-point number in its hexadecimal notation.
    %d : Scan an integer as a signed decimal number.
    %i : Scan an integer as a signed number. Similar to %d,
         but interprets the number as hexadecimal when preceded by 0x and octal
         when preceded by 0. For example, the string 031 would be read
         as 31 using %d, and 25 using %i. The flag h in %hi indicates conversion
         to a short and hh conversion to a char.
    %u : Scan for decimal unsigned int (Note that in the C99 standard the input value minus sign is optional, so if a minus sign is read, no errors will arise and the result will be the two's complement of a negative number, likely a very large value. See strtoul().[failed verification])
    Correspondingly, %hu scans for an unsigned short and %hhu for an unsigned char.

    %f : Scan a floating-point number in normal (fixed-point) notation.
    %g, %G : Scan a floating-point number in either normal or exponential notation. %g uses lower-case letters and %G uses upper-case.

    %x, %X : Scan an integer as an unsigned hexadecimal number.
    %o : Scan an integer as an octal number.

    %s : Scan a character string. The scan terminates at whitespace. A null character is stored at the end of the string, which means that the buffer supplied must be at least one character longer than the specified input length.
    %c : Scan a character (char). No null character is added.

    whitespace: Any whitespace characters trigger a scan for zero or more whitespace characters. The number and type of whitespace characters do not need to match in either direction.
    %lf : Scan as a double floating-point number. "Float" format with the "long" specifier.
    %Lf : Scan as a long double floating-point number. "Float" format the "long long" specifier.
*/

void altri_esempi_scanf() {

	char ch;
	int a, b;
	unsigned int ua, ub;
	long la, lb;

	float c;
	double d;

	int result;

	printf("scrivi un char: ");
	scanf("%c", &ch);

	// ch = getchar();

	printf("ho letto il seguente char: %c (il valore numerico ?? %d)\n", ch, ch);

	printf("scrivi un int: ");
	result = scanf("%d", &a);

	if (result == 1) {
		printf("ho letto il seguente int: %d\n", a);
	} else {
		printf("scanf ha restituito %d\n", result);
		scanf("%*s"); // scartiamo i caratteri che sono rimasti in stdin
	}

	printf("scrivi un unsigned int: ");
	result = scanf("%u", &ub);
	printf("ho letto il seguente unsigned int: %u\n", ub);

	printf("scrivi un int in base 16: ");
	result = scanf("%x", &a);
	printf("ho letto il seguente int: %x, in base 10: %d\n", a, a);

}


int main(int argc, char **argv) {

	int a,b;
	int sum;
	int res;

	if (1) {

		altri_esempi_scanf();

		return 0;
	}

	if (1) {

		printf("scrivi due numeri interi: ");

		res = scanf("%d %d", &a, &b);

		printf("scanf ha restituito: %d (numero di valori letti)\n", res);

		if (res == EOF) {
			printf("EOF! bye!");
			return -1;
		}

		if (res < 2) {
			printf("non ho letto due valori (me ne servono due), esco\n");
			return -1;
		}


		sum = a + b;

		printf("sum = %d\n", sum);

	}

	/*
	 * ESERCIZIO DA FARE:
	 *
	 * soluzione: vedere progetto 003.1calculator
	 *
	 * chiedere all'utente tre input:
	 * l'operazione da fare e due numeri (i due operandi)
	 * eseguire l'operazione richiesta e scrivere il risultato
	 * le operazioni ammesse sono: + - * /
	 *
	 * esempio:
	 *
	 * input:
	 * + 10 20
	 *
	 * risultato:
	 * 30
	 *
	 * * 2 2
	 * risultato:
	 * 4
	 *
	 * per chi vuole condividere la soluzione con me (e la classe):
	 *
	 * 1 - mi potete mandate la soluzione via telegram (o email), entro la prossima lezione
	 * oppure:
	 *
	 * 2- create un account su github
	 * create una repository su github contenente il progetto Eclipse
	 * e poi mi mandate l'indirizzo della repo (via telegram o email)
	 */

	return 0;
}
