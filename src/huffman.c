#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "huffman.h"
#include "alphabet.h"

void huffman_recursive(Symbol** symbols, unsigned int length);

void huffman_code(Alphabet* ab) {
	// Alfabeto ordinato, alfabeto fortunato
	quicksort_alphabet(ab);

	huffman_recursive(ab->symbols, ab->length);
}

// Richiede che l'array symbols sia già ordinato (per la probabilità)
void huffman_recursive(Symbol** symbols, unsigned int length) {
	if (symbols == NULL || length <= 1) {
		return;
	}

	if (length > 2) {
		Symbol* second_to_last = symbols[length-2];
		Symbol* last = symbols[length-1];

		// L'elemento second_to_last si presta come fusione di se stesso e dell' "ultimo"
		second_to_last->prob += last->prob;

		unsigned int spot = sort_last_symbol(symbols, length-1);
		second_to_last = symbols[spot];

		// Il risultato del codice dato da questa chiamata è restituito.
		huffman_recursive(symbols, length-1);

		second_to_last->prob -= last->prob;

		// Propagazione del codice associato
		last->code = second_to_last->code;

		push_code_digit(&second_to_last->code, 1);
		push_code_digit(&last->code, 0);
	} else { // Caso in cui ci siano esattamente due elementi nella lista.
		// È sempre valido il presupposto che la lista sia ordinata, quindi il primo avrà probabilità maggiore.
		symbols[0]->code = new_code();
		push_code_digit(&symbols[0]->code, 1);

		symbols[1]->code = new_code();
		push_code_digit(&symbols[1]->code, 0);
	}
}
