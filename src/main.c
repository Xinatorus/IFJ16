
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
	#endif



	return 0;
}

