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

//testovaci vypis struktury TS
void tsWriteOutTree(TsTree root) {
	if (root == NULL) {
		printf("Tree is empty\n");
		return;
	}

	printf("---------TREE---------\n");
	for (TsTree x = root; x != NULL; x = x->next) {
		printf("%c %s\n",195, x->name);
		for (TsTree t = x->child; t != NULL; t = t->next)
			printf("%c %c%c %s\n",179,192,196, t->name);
	}
	printf("----------------------\n");
}

void tsWriteOutTreeTS(TsTree root) {

}

void tsTest() {
	printf("TsTree Test...\n");
	TsTree root;
	tsTreeInit(&root);

	printf("Add Main\n");
	tsAdd(&root, "Main", NULL);
	tsWriteOutTree(root);

	printf("Add Bain\n");
	tsAdd(&root, "Bain", NULL);
	tsWriteOutTree(root);

	printf("Add Main.run\n");
	tsAdd(&root, "Main.run", NULL);
	tsWriteOutTree(root);

	printf("Add Main.main\n");
	tsAdd(&root, "Main.main", NULL);
	tsWriteOutTree(root);

	printf("Add Dain\n");
	tsAdd(&root, "Dain", NULL);
	tsWriteOutTree(root);

	printf("Add Bain.foo\n");
	tsAdd(&root, "Bain.foo", NULL);
	tsWriteOutTree(root);

	printf("TsTree Test END...\n");
	getchar();
}