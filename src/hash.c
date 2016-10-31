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
	memset(htab, 0, sizeof(HashTable)*size);

	return htab;
}

// Odstraneni tabulky
void deleteHashTable(HashTable *hashTable) {
	//TODO procistit jednotlive polozky/seznamy 


	free(hashTable);
}

// Pridavani zaznamu do tabulky
int addToHashTable(HashTable *hashTable, char *key, char *type, unsigned int data) {

	if (searchInHashTable(hashTable, *key) != NULL) //prvek uz existuje!
		return 1;

	unsigned int index = hash(key);
	
	//TODO pokud na dane pozici neni nejaky prvek, zaradim ho do seznamu

	HashTable *item = &(hashTable[index]);

	if (item->key != NULL) {//pokud neco jiz existuje
		for (; item->next != NULL; item = item->next); //najdu konec
		// vytvorim novou polozku
		HashTable *tmp = malloc(sizeof(HashTable));
		//pridam do seznamu
		item->next = tmp;
		//zmenim odkaz na polozku
		item = tmp;
	}

	item->key = malloc(sizeof(char)*strlen(key));
	strcpy(item->key, key);

	item->type = malloc(sizeof(char)*strlen(type));
	strcpy(item->type, type);

	item->data = data;

	

	return 0;
}

// je vubec potreba??
int deleteFromHashTable(HashTable *HashTable, char *key) {

}


// Vyhledavani v tabulce
HashTable *searchInHashTable(HashTable *hashTable, char *key) {
	unsigned int index = hash(key);

	// prochazim zaznam, pokud je key = 0 neexistuje v tabulce, pokud je zaznam nullovy = neexistuje v seznamu
	// WTF? proc ten item!=0 ... uz je moc pozde....
	for (HashTable *item = hash(key); item != NULL && item->key != NULL; item = item->next) {
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

