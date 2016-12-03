#include "headers\testWriteOut.h"

void hashWriteOut(HashTable hashTable) {
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

void hashTest() {/*
				 printf("Create HashTable...\n");
				 HashTable table = createHashTable(HASH_TABLE_SIZE);
				 if (table == NULL) {
				 printf("Create Error");
				 error(INTER_ERROR);
				 }
				 printf("Hash adr: %p\n", table);
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
				 printf("adr: %p key: %s\n", searchInHashTable(table, "ANO"), searchInHashTable(table, "ANO")->key);
				 writeOut(table);

				 printf("Search for B\n");
				 if (searchInHashTable(table, "B") == NULL) printf("not found\n");
				 else
				 printf("adr: %p key: %s\n", searchInHashTable(table, "B"), searchInHashTable(table, "B")->key);
				 writeOut(table);

				 printf("Deleting table\n");
				 deleteHashTable(table);*/
}