#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers\ial.h"
#include "headers\error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int	findSubstring(char *s, char *search) {
	if (s == NULL || search == NULL 
		|| s[0] == '\0' || search[0] == '\0') return 0;

	int sLen = strlen(s);
	int searchLen = strlen(search);
	int i,j,k=0;

	if (sLen < searchLen) return 0; // neni mozne aby byl v retezci delsi podretezec

	// pozici kurzoru nastavim na searchLen az do sLen
	for (i = searchLen - 1, j = 0; i < sLen && j < searchLen;) {
		// kontroluju jestli je znak c z S je v search
		// pokud ne 
			// posunu se o pozici c nalezenem v search -> plna delka pokud znak neni
			// jinak o pozici znaku c zprava
		//opakuju do shody nebo konce S

		if (s[i-j] == search[searchLen-j-1]) {//znak odpovida
			j++; 
		}
		else { // neshoduje se, posouvam se..
			for (k = searchLen; k > 0 && s[i-j] != search[k-1]; k--);
			j = 0;
			i += searchLen - k; 
		}
	}

	if (j == searchLen) return i - searchLen + 1;
	else return -1;
}

HashTable createHashTable(unsigned int size) {
	HashTable htab;
	htab = malloc(sizeof(struct hItem)*size);
	if (htab == NULL)
		return NULL;

	memset(htab, 0, sizeof(struct hItem)*size);

	return htab;
}

// Odstraneni tabulky
void deleteHashTable(HashTable hashTable) {

	if (hashTable == NULL) return;

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
int addToHashTable(HashTable hashTable, char *key, char *type, unsigned int data, unsigned int varIndex) {

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

	item->key = malloc(sizeof(char)*strlen(key) + 1);
	strcpy(item->key, key);

	item->type = malloc(sizeof(char)*strlen(type) + 1);
	strcpy(item->type, type);

	item->data = data;
	item->index = varIndex;
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

//Merge sort
void mergeSort(char *arr, int len) {
	if (len <= 1) return;

	int half = len / 2; // rozdelim na pul
	char *l = malloc(half);
	char *r = malloc(len - half);

	//if (!r || !l) printf("errMalloc\n");

	for (int i = 0; i < half; i++) // naplnim pod-pole
		l[i] = arr[i];
	for (int i = half; i < len; i++)
		r[i - half] = arr[i];

	mergeSort(l, half); // opakuji
	mergeSort(r, len - half);
	merge(arr, l, r, half, len - half); // spojim z5 dohromady

	free(l);
	free(r);
}

void merge(char *arr, char *l, char *r, int sizeL, int sizeR) {
	int i = 0, j = 0, k = 0;

	while (i < sizeL && j < sizeR)
		if (l[i] < r[j])
			arr[k++] = l[i++];
		else
			arr[k++] = r[j++];

	while (i < sizeL)
		arr[k++] = l[i++];

	while (j < sizeR)
		arr[k++] = r[j++];
}