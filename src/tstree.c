#include "headers\tstree.h"
#include "headers\strings.h"
#include "headers\ial.h"
#include <stdlib.h>
#include <stdio.h>

void tsTreeInit(TsTree *root) {
	*root = NULL;
}

int tsAdd(TsTree *root, char *name, HashTable ht) {
	TsTree dest; //cil
	dest = malloc(sizeof(struct tsTree));
	if (dest == NULL) {
		fprintf(stderr, "Malloc Err\n");
		return 1;
	}
	else {
		dest->name = makeString(name);
		dest->ts = ht;
		dest->next = NULL;
		dest->child = NULL;
	}

	if (*root = NULL) { // prvni	
		(*root) = dest;
	}
	else { //najdu kam
		if (findSubstring(name, '.') < 0) { //global
			for (TsTree x = *root; x != NULL; x = x->next) { //najdu konec
				if (x->next == NULL) {
					x->next = dest;
					break;
				}
			}
		}
		else {//local

		}
	}
	

	
}

void tsDel(TsTree root) {

}

HashTable tsFind(TsTree root, char *name) {

}

//testovaci vypis struktury TS
void tsWout(TsTree root) {

}