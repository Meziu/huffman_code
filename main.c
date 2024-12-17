#include <stdio.h>
#include <stdlib.h>

#include "alphabet.h"
#include "huffman.h"

int main() {
	char* message = "ciiiaaaoooo";

	Alphabet ab = create_alphabet(message);

	// Per comodità visiva.
	quicksort_alphabet(&ab);

	huffman_code(&ab);

	print_alphabet(&ab);

	printf("Somma delle probabilità: %f", sum_of_probabilities(&ab));

	return 0;
}