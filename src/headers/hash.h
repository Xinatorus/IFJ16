/*******************************************************
*
*						IFJ_2016
*					Autor: xsztef02
*						hash.h
*
*******************************************************/

#ifndef HASHTABLE
#define HASHTABLE


#define HASH_TABLE_SIZE 500;


/*** MAIN INFO ***

Jde mit v struct preddefinovane hodnoty? jde mi o null v key pro urciti
jestli je dana pozice obsazena nebo ne

*/
typedef struct hTable {
	char *key;
	char *type; //1. VELKYM typ var/fce/navesti... 2. datovy typ 3. az n pro parametry F
	unsigned int data; // pro var 0-n ostatni 0-undefined 1-defined
	struct hTable *next; // kvuli konfliktum v omezenosti hashe
}HashTable;

HashTable *createHashTable(unsigned int size);
void deleteHashTable(HashTable *hashTable);
int addToHashTable(HashTable *hashTable, char *key, char *type, unsigned int data);
int deleteFromHashTable(HashTable *HashTable, char *key);
HashTable *searchInHashTable(HashTable *hashTable, char *key);
unsigned int hash(char *key);

#endif