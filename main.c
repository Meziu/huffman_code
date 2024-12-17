#include <stdio.h>
#include <stdlib.h>

#include "alphabet.h"
#include "huffman.h"
#include "include/alphabet.h"

int main() {
	char *message =
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
		"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
		"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
		"aliquip ex ea commodo consequat. Duis aute irure dolor in "
		"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
		"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
		"culpa qui officia deserunt mollit anim id est laborum.";

	Alphabet ab = create_alphabet(message);

	// Per comodità visiva.
	quicksort_alphabet(&ab);

	huffman_code(&ab);

	print_alphabet(&ab);

	printf("Somma delle probabilità: %f", sum_of_probabilities(&ab));

	destroy_alphabet(&ab);
	return 0;
}
