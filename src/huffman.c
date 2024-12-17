#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "huffman.h"
#include "alphabet.h"

void huffman_recursive(Symbol** symbols, unsigned int length);
void huffman_tree_encode(Symbol* root);

void huffman_code(Alphabet* ab) {
	// Alfabeto ordinato, alfabeto fortunato
	quicksort_alphabet(ab);

	Symbol** array_copy = malloc(ab->length * sizeof(Symbol*));
	memcpy(array_copy, ab->symbols, ab->length*sizeof(Symbol*));

	array_copy[ab->length - 1];

	huffman_recursive(array_copy, ab->length);

	free(array_copy);
}

// Richiede che l'array symbols sia già ordinato (per la probabilità)
void huffman_recursive(Symbol** symbols, unsigned int length) {
	if (symbols == NULL) {
		return;
	}

	if (length > 1) {
		//quicksort_symbols_prob(symbols, 0, length-1);

		Symbol* second_to_last = symbols[length-2];
		Symbol* last = symbols[length-1];

		// Nodo padre dei due dati (TODO; usa tipi diversi per i simboli e per i nodi di simboli, fr);
		Symbol fusion = (Symbol){
			'\0', // non-valore
			second_to_last->prob + last->prob, // Somma delle probabilità dei figli
			new_code(), // codice vuoto
			last, // A sinistra va il più piccolo
			second_to_last,
		};

		// Taglio dell'alfabeto (è una copia, non ci interessa sistemarlo alla fine)
		symbols[length-2] = &fusion; // Sostituiamo fusion al posto dei due nodi figli

		// Inserisci l'elemento fusion al punto giusto dell'array
		sort_last_symbol(symbols, length-1);

		// Il risultato del codice dato da questa chiamata è restituito.
		huffman_recursive(symbols, length-1);
	} else {
		// Non ci sono altri nodi da accorpare, è ora di fare l'encoding.
		huffman_tree_encode(symbols[0]);
	}
}

// Riempi un'albero di Huffman con i codici associati
void huffman_tree_encode(Symbol* root) {
	if (root == NULL)
		return;

	if (root->left != NULL) {
		// I codici left and right sono quello del root più una cifra data in base alla loro posizione
		root->left->code = root->code;
		push_code_digit(&root->left->code, 0); // 0 a sinistra

		huffman_tree_encode(root->left);
	}

	if (root->right != NULL) {
		root->right->code = root->code;
		push_code_digit(&root->right->code, 1); // 1 a destra

		huffman_tree_encode(root->right);
	}
}
