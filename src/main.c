/*******************************************************
*
*						IFJ_2016
*					Autor: xsztef02
*						 main.c
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\hash.h"



int main() {
	printf("Create HashTable...\n");
	HashTable table = createHashTable(HASH_TABLE_SIZE);
	if (table == NULL) {
		printf("Create Error");
		return 1;
	}
	printf("Hash adr: %d\n",table);
	writeOut(table);
	

	printf("Add \"A\" to table...\n");
	addToHashTable(table, "A", "0", 0);
	writeOut(table);

	printf("Add \"ANO\" to table...\n");
	addToHashTable(table, "ANO", "0", 1);
	writeOut(table);

	printf("Add \"NE\" to table...\n");
	addToHashTable(table, "NE", "0", 1);
	writeOut(table);
	
	printf("Search for ANO\n");
	printf("adr: %d key: %s\n",searchInHashTable(table,"ANO"), searchInHashTable(table,"ANO")->key);
	writeOut(table);

	printf("Search for B\n");
	if (searchInHashTable(table, "B") == NULL) printf("not found\n");
	else
		printf("adr: %d key: %s\n", searchInHashTable(table, "B"), searchInHashTable(table, "B")->key);
	writeOut(table);
	
	printf("Deleting table\n");
	deleteHashTable(table);

	system("pause");
	return 0;
}

