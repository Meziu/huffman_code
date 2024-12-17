#ifndef __ALPHABET_H__
#define __ALPHABET_H__

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALPHABET_LENGTH 50
#define MAX_MESSAGE_LENGTH 1000

typedef struct {
	unsigned long bitfield; // espandibile modificando il tipo
	char length; // lunghezza del codice (da destra verso sinistra)
} Code;

typedef struct SSymbol {
	char s;
	float prob;
	Code code;
	// Array e BinaryTree tutto in uno??? Count me in!
	struct SSymbol* left;
	struct SSymbol* right;
} Symbol;

typedef struct {
	Symbol** symbols; // Array di riferimenti a simboli, che sono allocati dinamicamente
	unsigned int length;
} Alphabet;

Alphabet create_alphabet(char* sample_message);
void destroy_alphabet(Alphabet* ab);

Symbol* find_symbol(Alphabet* ab, char c);
unsigned int sort_last_symbol(Symbol** symbols, unsigned int length);

Code new_code();
void push_code_digit(Code* code, bool d);

void print_alphabet(Alphabet* ab);
void print_symbol(Symbol* s);
void print_code(Code* code);

float sum_of_probabilities(Alphabet* ab);

void swap_symbol_references(Symbol **a, Symbol **b);
void quicksort_alphabet(Alphabet *ab);
int partition_symbols_prob(Symbol **symbols, int start, int end);
void quicksort_symbols_prob(Symbol** symbols, int start, int end);

#endif
