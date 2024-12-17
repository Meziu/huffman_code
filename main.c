#include <stdio.h>
#include <stdlib.h>

#include "alphabet.h"
#include "huffman.h"
#include "include/alphabet.h"

int main() {
	char* message = "buongiorno mondo!";

	Alphabet ab = create_alphabet(message);

	huffman_code(&ab);

	// Per comodità visiva.
	quicksort_alphabet(&ab);

	print_alphabet(&ab);

	printf("Somma delle probabilità: %f", sum_of_probabilities(&ab));

	destroy_alphabet(&ab);
	return 0;
}
