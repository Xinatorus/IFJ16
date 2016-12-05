#ifndef TSTREE_H
#define TSTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ial.h"
#include "valgrind.h"
#include "strings.h"
#include "ial.h"

typedef struct tsTree{
	char *name; //identifikator
	unsigned int varCount; // pocet promennych
	void *addr; //adresa instrukce
	HashTable ts; //tabulka symbolu
	struct TsTree *child; // seznam lokalnich ts
	struct TsTree *next; // list TS akt. urovne
}*TsTree;


void tsTreeInit(TsTree *root);
int tsAdd(TsTree *root, char *name,unsigned int varCount,void *addr, HashTable ht);
void tsDel(TsTree *root);
TsTree tsFind(TsTree root,char *name);
int isHisParent(char *name,char *parent);

#endif