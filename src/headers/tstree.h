#ifndef TSTREE_H
#define TSTREE_H

#include "ial.h"
#include "valgrind.h"

typedef struct tsTree{
	char *name;
	HashTable ts; //tabulka symbolu
	struct TsTree *child; // seznam lokalnich ts
	struct TsTree *next; // list TS akt. urovne
}*TsTree;


void tsTreeInit(TsTree *root);
int tsAdd(TsTree *root, char *name,HashTable ht);
void tsDel(TsTree *root);
HashTable tsFind(TsTree root,char *name);
int isHisParent(char *name,char *parent);

#endif