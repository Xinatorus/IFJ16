#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\hash.h"

//TODO pridat osetreni chyb

// Vytvoreni tab
HashTable *createHashTable(unsigned int size) {
	HashTable *htab;
	htab = malloc(sizeof(HashTable)*size);
	if (htab == NULL)
		return NULL;
	//TODO add pre-set val?
	return htab;
}

// Odstraneni tabulky
void deleteHashTable(HashTable *hashTable) {
	//TODO procistit jednotlive polozky/seznamy 
	free(hashTable);
}

// Pridavani zaznamu do tabulky
int addToHashTable(HashTable *hashTable, char *key, char *type, unsigned int data) {
	//TODO search jesi uz neexistuje

	unsigned int index = hash(key);
	hashTable[index].key = malloc(sizeof(char)*strlen(key));
	strcpy(hashTable[index].key, key);

	hashTable[index].type = malloc(sizeof(char)*strlen(type));
	strcpy(hashTable[index].type, type);

	hashTable[index].data = data;

	return 0;
}

// je vubec potreba??
int deleteFromHashTable(HashTable *HashTable, char *key) {

}


// Vyhledavani v tabulce
HashTable *searchInHashTable(HashTable *hashTable, char *key) {
	unsigned int index = hash(key);

	// prochazim zaznam, pokud je key = 0 neexistuje v tabulce, pokud je zaznam nullovy = neexistuje v seznamu
	for (HashTable *item = hash(key); item != NULL && item->key != NULL; item = item->next) {
		if (!strcmp(key, item->key))
			return item; //vracim odkaz na zaznam
	}

	// nenaezen
	return NULL;
}

// Hashovaci fce
unsigned int hash(char *key) {
	unsigned int h = 0;
	const unsigned char *p;
	for (p = (const unsigned char*)key; *p != '\0'; p++)
		h = 65599 * h + *p;
	return h % HASH_TABLE_SIZE;
}

