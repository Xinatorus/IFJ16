
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\ial.h"
#include "headers\instructions.h"
#include "headers\lex_anal.h"
#include "headers\error.h"

#define LEX_TEST 1 // Lexical analysis test

int main(int argc, char* argv[]) {

	// Missing parameter
	if (argc < 2) {
		error(INTER_ERROR);
	}

	// Load source file
	loadSource(argv[1]);

	/* Lexical analysis test (print all found tokens) */
	#if LEX_TEST == 1
		fprintf(stdout, "=== TEST LEXIKALNI ANALYZY ===\n");
		Ttoken *token = NULL;
		int num = 0;
		do {
			token = getNextToken();
			fprintf(stdout, "#%d -> Typ: %d, Data: %s\n", num, token->type, token->attr->str);
			num++;
		} while (token != NULL && token->type != KONEC_SOUBORU && token->type != LEXIKALNI_CHYBA);
	#endif

	return 0;
}

