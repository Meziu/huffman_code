#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphabet.h"
#include "huffman.h"

void huffman_recursive(Symbol *symbols, unsigned int length);

void huffman_code(Alphabet *ab) {
	// Alfabeto ordinato, alfabeto fortunato
	quicksort_alphabet(ab);

	huffman_recursive(ab->symbols, ab->length);
}

void huffman_recursive(Symbol *symbols, unsigned int length) {
	if (symbols == NULL || length <= 1) {
		return;
	}

	symbols[length - 2].prob += symbols[length - 1].prob;

	unsigned int pos = sort_last_symbol(symbols, length - 1);

	huffman_recursive(symbols, length - 1);

	bubble_to_last_symbol(symbols, pos, length - 1);

	symbols[length - 2].prob -= symbols[length - 1].prob;

	symbols[length - 1].code = symbols[length - 2].code;
	push_code_digit(&symbols[length - 2].code, 1);
	push_code_digit(&symbols[length - 1].code, 0);
}
