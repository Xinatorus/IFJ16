#include "headers\ial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findSubstring(char *s, char *search) {
	if (s == NULL || search == NULL 
		|| s[0] == '\0' || search[0] == '\0') return 0;

	int sLen = strlen(s);
	int searchLen = strlen(search);
	int i,j,k=0;


	if (sLen < searchLen) return 0; // neni mozne aby byl v retezci delsi podretezec

	// pozici kurzoru nastavim na searchLen az do sLen
	for (i = searchLen - 1, j = 0; i < sLen && j < searchLen;) {
		// kontroluju jestli je znak c z S je v search
		// pokud ne 
			// posunu se o pozici c nalezenem v search -> plna delka pokud znak neni
			// jinak o pozici znaku c zprava
		//opakuju do shody nebo konce S

		if (s[i-j] == search[searchLen-j-1]) {//znak odpovida
			j++; 
		}
		else { // neshoduje se, posouvam se..
			for (k = searchLen; k > 0 && s[i-j] != search[k-1]; k--);
			j = 0;
			i += searchLen - k; 
		}
	}

	if (j == searchLen) return i - searchLen + 1 + 1;
	else return 0;
}