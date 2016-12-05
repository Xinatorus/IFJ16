#define _CRT_SECURE_NO_WARNINGS  pro zruseni warningu visual studia
#include "headers\valgrind.h"
#include "headers\testWriteOut.h"
#include "headers\synt_anal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEX_TEST 0       //Lexical analysis test
#define VALGRIND_TEST 0  //Valgrind test

int main(int argc, char* argv[]) {
	
	// Missing parameter
	if (argc < 2) {
		error(INTER_ERROR);
	}

	// Load source file
	loadSource(argv[1]);

#if LEX_TEST == 1
    /* Lexical analysis test (print all found tokens) */
	fprintf(stdout, "=== TEST LEXIKALNI ANALYZY ===\n");
	Ttoken *token = NULL;
	int num = 0;
	do {
		token = getNextToken();
		fprintf(stdout, "#%-5d Typ: %-11s Data: %-12s\n", num, getTokenName(token->type), token->attr->str);
		num++;
	} while (token != NULL && token->type != KONEC_SOUBORU && token->type != LEXIKALNI_CHYBA);
#elif VALGRIND_TEST == 1
    /* Valgrind test */
    tsTest();
    valgrind();
    printf("\n\nhit enter to end\n");
    getchar();
#else
    /* Regular syntax analysis */
    execute();
#endif

return 0;

}
