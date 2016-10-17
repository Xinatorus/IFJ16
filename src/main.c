#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*** MAIN INFO ***

	Jde mit v struct preddefinovane hodnoty? jde mi o null v key pro urciti
	jestli je dana pozice obsazena nebo ne

*/


typedef struct hTable{
	char *key; 
	char *type; //1. VELKYM typ var/fce/navesti... 2. datovy typ 3. az n pro parametry F
	unsigned int data; // pro var 0-n ostatni 0-undefined 1-defined
	struct hTable *next; // kvuli konfliktum v omezenosti hashe
}HashTable;

HashTable *createHashTable(unsigned int size);
void deleteHashTable(HashTable *hashTable);
int addToHashTable(HashTable *hashTable, char *key,char *type, unsigned int data);
int deleteFromHashTable(HashTable *HashTable, char *key);
HashTable *searchInHashTable(HashTable *hashTable, char *key);
unsigned int hash(char *key);


int main() {

	printf("hello world\n");
	return 0;
}


//TODO pridat osetreni chyb

HashTable *createHashTable(unsigned int size) {
	HashTable *htab;
	htab = malloc(sizeof(HashTable)*size);
	
	return htab;
}

void deleteHashTable(HashTable *hashTable) {
	free(hashTable);
}

int addToHashTable(HashTable *hashTable, char *key, char *type, unsigned int data) {
	//+search jesi neexistuje uz... asi podle null v key

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

HashTable *searchInHashTable(HashTable *hashTable, char *key) {
	unsigned int index = hash(key);
	if (hashTable[index].key == NULL) { // nenalezen
		return NULL; // asi?
	}
	else { //neco tam je
		if (strcmp(hashTable[index].key, key)) {

		}
		else {

		}
	}

	return &hashTable[index];
}


unsigned int hash(char *key);
