#include "headers\ial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 200;

int findSubstring(char *s, char *search) {
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

	if (j == searchLen) return i - searchLen + 1 + 1;
	else return 0;
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

	item->key = malloc(sizeof(char)*strlen(key) + 1);
	strcpy(item->key, key);

	item->type = malloc(sizeof(char)*strlen(type) + 1);
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
			printf("[%3d]: %s", i, hashTable[i].key);
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

void hashTest() {
	printf("Create HashTable...\n");
	HashTable table = createHashTable(HASH_TABLE_SIZE);
	if (table == NULL) {
		printf("Create Error");
		return 1;
	}
	printf("Hash adr: %d\n", table);
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
	printf("adr: %d key: %s\n", searchInHashTable(table, "ANO"), searchInHashTable(table, "ANO")->key);
	writeOut(table);

	printf("Search for B\n");
	if (searchInHashTable(table, "B") == NULL) printf("not found\n");
	else
		printf("adr: %d key: %s\n", searchInHashTable(table, "B"), searchInHashTable(table, "B")->key);
	writeOut(table);

	printf("Deleting table\n");
	deleteHashTable(table);
}