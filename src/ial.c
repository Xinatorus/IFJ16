#include "headers\ial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findSubstring(char *s, char *search) {
	if (s == NULL || search == NULL 
		|| s[0] == '\0' || search[0] == '\0') return -1;

	int sLen = strlen(s);
	int searchLen = strlen(search);
	int i,j,k=0;


	if (sLen < searchLen) return -1; // neni mozne aby byl v retezci delsi podretezec

	// pozici kurzoru nastavim na searchLen az do sLen
	//									? <= ? kontroluju posledni znak v search pokud == tak je nalezen
	for (i = 0,j=searchLen; i < sLen && j >= 0;) {
		// kontroluju jestli je znak c z S je v search
		// pokud ne 
			// posunu se o pozici c nalezenem v search -> plna delka pokud znak neni
			// jinak o pozici znaku c zprava
		//opakuju do shody nebo konce S

		if (s[searchLen - i] == search[j]) {//znak odpovida
			i++;
			j--; 
		}
		else { // neshoduje se, posouvam se..
			for (k = searchLen; k > 0 && s[searchLen - i] != search[k]; k--);
			j = searchLen;
			i += searchLen - k; 
		}
	}
	if (j < 0) return i - searchLen - 1;
	else return -1;
}