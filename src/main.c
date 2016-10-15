#include <stdio.h>
#include <stdlib.h>


typedef struct hTable{
	char *key;
	char *type; //1. VELKYM typ var/fce/navesti... 2. datovy typ 3. az n pro parametry F
	unsigned int id; // pro var 0-n ostatni 0-undefined 1-defined
	struct hTable *next; // kvuli konfliktum v omezenosti hashe
}HashTable;

HashTable *createHashTable();
int deleteHashTable();
int addToHashTable();
int deleteFromHashTable();
HashTable *searchInHashTable();


int main() {

	printf("hello world\n");
	return 0;
}