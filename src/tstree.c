#include "headers\tstree.h"
#include "headers\strings.h"
#include "headers\ial.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void tsTreeInit(TsTree *root) {
	*root = NULL;
}
/*
	prida TS do stromu na zaklade jmena, 
	nekontroluje strapvnost jmen
	name = plny identifikator
	ht = predem vytvorena TS
*/
int tsAdd(TsTree *root, char *name, HashTable ht) {
	TsTree tmp;
	tmp = malloc(sizeof(struct tsTree));
	if (tmp == NULL) {
		fprintf(stderr, "Malloc Err\n");
		return 1;
	}
	else {
		tmp->name = makeString(name);
		tmp->ts = ht;
		tmp->next = NULL;
		tmp->child = NULL;
	}

	if (*root == NULL) { // prvni	
		*root = tmp;
	}
	else { //najdu kam
		//printf("find for global\n");
		if (findSubstring(tmp->name, ".") < 0) { //global
			for (TsTree x = *root; x != NULL; x = x->next) { //najdu konec
				if (x->next == NULL) {
					x->next = tmp;
					//printf("added");
					return 1;
				}
			}
		}
		else {//local
			// najdu rodice 
			//printf("find for local\n");
			for (TsTree x = *root; x != NULL; x = x->next) {
				if (findSubstring(name, x->name) == 0) { // nasel rodice
					//najdu konec seznamu childs
					if (x->child == NULL) { //prvni child
						x->child = tmp;
					}
					else {
						for (TsTree t = x->child; t != NULL; t = t->next) {
							if (t->next == NULL) { //konec
								t->next = tmp;	// priradim na konec
								return 1;
							}
						}
					}
					break;
				}
			}
		}
	}
	return 1;
}

void tsDel(TsTree root) {

}

HashTable tsFind(TsTree root, char *name) {

}
