#include <stdio.h>
#include <stdlib.h>

#include "alphabet.h"
#include "huffman.h"
#include "include/alphabet.h"

int main() {
	char* message = "ciiiaaaoooo";

	Alphabet ab = create_alphabet(message);

	// Per comodità visiva.
	quicksort_alphabet(&ab);

	huffman_code(&ab);

	print_alphabet(&ab);

	printf("Somma delle probabilità: %f", sum_of_probabilities(&ab));

	destroy_alphabet(&ab);
	return 0;
}
