#include "alphabet.h"
#include <stdio.h>
#include <unistd.h>

Alphabet create_alphabet(char *sample_message) {
	unsigned int message_len = strnlen(sample_message, MAX_MESSAGE_LENGTH);

	unsigned int max_alphabet_len =
		(message_len < MAX_ALPHABET_LENGTH) ? message_len : MAX_ALPHABET_LENGTH;

	Symbol **s_array = (Symbol **)malloc(
		max_alphabet_len *
		sizeof(Symbol*)); // Worst case scenario, agli allocatori fa più piacere
						 // se chiedi tanto e subito

	assert(s_array != NULL);

	Alphabet ab = (Alphabet){
		s_array,
		0,
	};

	for (int i = 0; i < message_len; i++) {
		Symbol *s = find_symbol(&ab, sample_message[i]);

		if (s == NULL) { // non trovato
			Symbol* new_sym = malloc(sizeof(Symbol));

			assert(new_sym != NULL);

			*new_sym = (Symbol){
				sample_message[i],
				1.0, // Non mi piace l'utilizzo di float per numeri interi,
					 // considera il type casting/union
				new_code(),	 // Default, viene modificato in seguito con altre funzioni.
				NULL,
				NULL,
			};

			ab.symbols[ab.length++] = new_sym;
		} else { // trovato
			s->prob +=
				1.0; // rifarsi al commento sopra riguardo l'uso dei float
		}
	}

	// Normalizzazione delle probabilità
	for (int i = 0; i < ab.length; i++) {
		ab.symbols[i]->prob /= message_len;
	}

	// Resize dell'array a seconda della lunghezza effettiva
	ab.symbols = (Symbol**)realloc(ab.symbols, ab.length * sizeof(Symbol*));

	return ab;
}

void destroy_alphabet(Alphabet* ab) {
	for (int i = 0; i < ab->length; i++) {
		free(ab->symbols[i]);
	}

	ab->length = 0;

	free(ab->symbols);
}

Symbol *find_symbol(Alphabet *ab, char c) {
	for (int i = 0; i < ab->length; i++) {
		if (c == ab->symbols[i]->s) {
			return ab->symbols[i];
		}
	}

	return NULL;
}

// Presupponendo una lista ordinata eccetto per l'ultimo simbolo
unsigned int sort_last_symbol(Symbol** symbols, unsigned int length) {
	assert(symbols != NULL);

	for (int i = length-2; i >= 0; i--) {
		if (symbols[i]->prob < symbols[i+1]->prob) {
			swap_symbol_references(&symbols[i], &symbols[i+1]);
		} else {
			return i+1;
		}
	}

	return 0;
}

Code new_code() {
	return (Code){0, 0};
}

void push_code_digit(Code* code, bool d) {
	assert(code != NULL);

	assert(code->length <= sizeof(code->bitfield) * 8 - 1); // Se è già al massimo abbiamo bisogno di più spazio

	code->bitfield = (code->bitfield << 1) | (d && 1);
	code->length++;
}

void print_alphabet(Alphabet *ab) {
	for (int i = 0; i < ab->length; i++) {
		printf("--- Simbolo #n %d\n", i + 1);
		print_symbol(ab->symbols[i]);
		printf("---\n");
	}
}

void print_symbol(Symbol *s) {
	assert(s != NULL);

	printf("Carattere: \"%c\"\n", s->s);
	printf("Probabilità: %f\n", s->prob);
	printf("Codice:");
	print_code(&s->code);
	printf("\n");
}

void print_code(Code* code) {
	assert(code != NULL);

	for (int i = code->length - 1; i >= 0; i--) {
		printf("%d", (code->bitfield & (1 << i)) ? 1 : 0);
	}
}

float sum_of_probabilities(Alphabet *ab) {
	float sum = 0.0;

	for (int i = 0; i < ab->length; i++) {
		sum +=
			ab->symbols[i]
				->prob; // C'è chi direbbe che sommare in questo modo barbaro dei
					   // float accumuli un grosso errore, non sono uno di loro.
	}

	return sum;
}

float node_probability(Symbol* sym) {
	if (sym == NULL) {
		return 0.0;
	}

	// Il NUL character è ufficialmente il simbolo di un nodo "fittizio"
	if (sym->s != '\0') {
		return sym->prob;
	}

	return node_probability(sym->left) + node_probability(sym->right);
}

/* LOGICA DEL QUICKSORT, IT JUST WORKS TM */

void quicksort_alphabet(Alphabet *ab) {
	assert(ab != NULL);

	quicksort_symbols_prob(ab->symbols, 0, ab->length - 1);
}

void swap_symbol_references(Symbol **a, Symbol **b) {
	Symbol* temp = *a;
	*a = *b;
	*b = temp;
}

void quicksort_symbols_prob(Symbol **symbols, int start, int end) {
	assert(symbols != NULL);

	if (start < end) {
		int pivot = partition_symbols_prob(symbols, start, end);
		quicksort_symbols_prob(symbols, start, pivot - 1);
		quicksort_symbols_prob(symbols, pivot + 1, end);
	}
}

int partition_symbols_prob(Symbol **symbols, int start, int end) {
	float pivot = symbols[end]->prob;
	int i = start - 1;

	for (int j = start; j < end; j++) {
		if (symbols[j]->prob >= pivot) {
			i++;
			swap_symbol_references(&symbols[i], &symbols[j]);
		}
	}

	swap_symbol_references(&symbols[i + 1], &symbols[end]);
	return i + 1;
}
