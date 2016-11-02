#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\hash.h"

//TODO pridat osetreni chyb

// Vytvoreni tab
HashTable createHashTable(unsigned int size) {
	HashTable htab;
	htab = malloc(sizeof(struct hItem)*size);
	if (htab == NULL)
		return NULL;

	//TODO add pre-set val?
	memset(htab, 0, sizeof(struct hItem)*size);

	return htab;
}

// Odstraneni tabulky
//TODO procistit jednotlive polozky/seznamy 
void deleteHashTable(HashTable hashTable) {
	
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		if (hashTable[i].next != NULL) {
			for (HashTable item = hashTable[i].next; item != NULL; ) {
				HashTable tmp = item;
				item = item->next;
				free(tmp);
			}
		}	
	}

	free(hashTable);
}

// Pridavani zaznamu do tabulky
int addToHashTable(HashTable hashTable, char *key, char *type, unsigned int data) {

	if (searchInHashTable(hashTable, key) != NULL) //prvek uz existuje!
		return 1;

	unsigned int index = hash(key);

	HashTable item = &(hashTable[index]);
	
	if (item->key != NULL) {//pokud neco jiz existuje
		for (; item->next != NULL; item = item->next); //najdu konec
		// vytvorim novou polozku
		HashTable tmp = malloc(sizeof(struct hItem));
		//pridam do seznamu
		item->next = tmp;
		//zmenim odkaz na polozku
		item = tmp;
	}

	item->key = malloc(sizeof(char)*strlen(key)+1);
	strcpy(item->key, key);

	item->type = malloc(sizeof(char)*strlen(type)+1);
	strcpy(item->type, type);

	item->data = data;
	item->next = NULL;
	

	return 0;
}


// Vyhledavani v tabulce
HashTable searchInHashTable(HashTable hashTable, char *key) {
	unsigned int index = hash(key);

	// prochazim zaznam, pokud je key = 0 neexistuje v tabulce, pokud je zaznam nullovy = neexistuje v seznamu
	for (HashTable item = &(hashTable[hash(key)]); item != NULL && item->key != NULL; item = item->next) {
		if (!strcmp(key, item->key))
			return item; //vracim odkaz na zaznam
	}

	// nenalezen
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

void writeOut(HashTable hashTable) {
	printf("+----------------------------\n");
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		//sloupec
		if (hashTable[i].key != NULL) {
			printf("[%3d]: %s",i,hashTable[i].key);
			if (hashTable[i].next != NULL) {
				for (HashTable item = hashTable[i].next; item != NULL; item = item->next) {
					printf(", %s", item->key);
				}
			}
			printf("\n");
		}
	}
	printf("+----------------------------\n");
}
