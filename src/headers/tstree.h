#ifndef TSTREE_H
#define TSTREE_H

#include "ial.h"

typedef struct tsTree{
	char *name;
	HashTable ts; //tabulka symbolu
	TsTree child; // seznam lokalnich ts
	TsTree next; // list TS akt. urovne
}*TsTree;


void tsTreeInit(TsTree root);
void tsAdd(TsTree root, char *name,HashTable ht);
void tsDel(TsTree root);
HashTable tsFind(TsTree root,char *name);
void tsWout(TsTree root);

#endif