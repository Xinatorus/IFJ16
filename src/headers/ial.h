#ifndef IAL_H
#define IAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valgrind.h"
#include "error.h"

//Boyer-Moore
int findSubstring(char *s, char *search);


#define HASH_TABLE_SIZE 101

//Hash table
typedef struct hItem {
	char *key;
	char *type; //1. VELKYM typ var/fce/navesti... 2. datovy typ 3. az n pro parametry F
	unsigned int data; // 0-undefined 1-defined 
	unsigned int index; // poradi promenne 0-n
	struct hItem *next; // kvuli konfliktum v omezenosti hashe
}*HashTable;

HashTable createHashTable(unsigned int size);
void deleteHashTable(HashTable hashTable);
int addToHashTable(HashTable hashTable, char *key, char *type, unsigned int data,unsigned int index);
HashTable searchInHashTable(HashTable hashTable, char *key);t
unsigned int hash(char *key);


void mergeSort(char *arr, int len);
void merge(char *arr, char *l, char*r, int sizeL, int sizeR);

#endif // include guard
