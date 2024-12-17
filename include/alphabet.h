#ifndef __ALPHABET_H__
#define __ALPHABET_H__

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHABET_LENGTH 64
#define MAX_MESSAGE_LENGTH 4096
#define CODE_BITFIELD_TYPE unsigned long

typedef struct {
	CODE_BITFIELD_TYPE bitfield; // espandibile modificando il tipo
	char length; // lunghezza del codice (da destra verso sinistra)
} Code;

typedef struct SSymbol {
	char s;
	unsigned int prob;
	Code code;
} Symbol;

typedef struct {
	Symbol *symbols; // Array di simboli
	unsigned int length;
	unsigned int message_length;
} Alphabet;

Alphabet create_alphabet(char *sample_message);
void destroy_alphabet(Alphabet *ab);

Symbol *find_symbol(Alphabet *ab, char c);
unsigned int sort_last_symbol(Symbol *symbols, unsigned int length);
void bubble_to_last_symbol(Symbol *symbols, unsigned int index,
						   unsigned int length);

Code new_code();
void push_code_digit(Code *code, bool d);

void print_alphabet(Alphabet *ab);
void print_symbol(Alphabet *ab, Symbol *s);
void print_code(Code *code);

float sum_of_probabilities(Alphabet *ab);
char max_code_length(Alphabet *ab);
char min_code_length(Alphabet *ab);

void swap_symbols(Symbol *a, Symbol *b);
void quicksort_alphabet(Alphabet *ab);
int partition_symbols_prob(Symbol *symbols, int start, int end);
void quicksort_symbols_prob(Symbol *symbols, int start, int end);

#endif
