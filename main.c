#include <stdio.h>

#include "alphabet.h"
#include "huffman.h"

int main() {
	char *message =
		"Nulla aliquam dolor optio quia eligendi aliquid quia. Illum sit velit "
		"tempora quisquam voluptatem et cumque. Laudantium aut aut quod nisi "
		"est. Sed quo iste necessitatibus distinctio tempora aut et quia. "
		"Vitae praesentium et ut veniam eum ut ut qui. Quas minus qui nisi "
		"fuga tenetur error cum asperiores. Velit praesentium minus qui aut. "
		"Quidem quibusdam dolor dolorem vel. Qui deserunt sed accusamus "
		"impedit alias. Doloremque sed cum aliquam adipisci voluptate natus "
		"ut. Voluptatem ab quo officia. Ad a veritatis et autem provident ab "
		"vero. Omnis quo itaque et dignissimos sunt est quo qui. Velit sit "
		"rerum enim ducimus quisquam harum enim. Velit corrupti exercitationem "
		"et. Qui et commodi vel distinctio dolores laboriosam. Repellat eum "
		"autem consequuntur numquam ea velit qui. Rerum ut doloremque atque "
		"tempora dolor eum. Voluptas ut quis minus nihil dicta doloribus. Quis "
		"quibusdam ex tenetur. Velit incidunt impedit voluptates voluptatem "
		"doloribus doloribus. Sint accusantium non quaerat iste neque. Omnis "
		"necessitatibus dolores aut explicabo.";

	Alphabet ab = create_alphabet(message);

	// Forse dovrebbe essere fatto direttamente con la creazione dell'alfabeto.
	huffman_code(&ab);

	print_alphabet(&ab);

	printf("Somma delle probabilità: %f\n", sum_of_probabilities(&ab));
	printf("Il codice più lungo è di %d cifre.\n", max_code_length(&ab));
	printf("Il codice più corto è di %d cifre.\n", min_code_length(&ab));

	destroy_alphabet(&ab);
	return 0;
}
