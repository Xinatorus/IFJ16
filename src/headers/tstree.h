#ifndef TSTREE_H
#define TSTREE_H

#include "ial.h"

typedef struct {
	char *name;
	HashTable parent;
	HashTable child; // seznam lokalnich TS
	HashTable next; // seznam globalnich TS
}TsTree;

#endif