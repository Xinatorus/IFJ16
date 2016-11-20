#ifndef IAL
#define IAL


//Boyer-Moore
int findSubstring(char *s, char *search);


#define HASH_TABLE_SIZE 200

//Hash table
typedef struct hItem {
	char *key;
	char *type; //1. VELKYM typ var/fce/navesti... 2. datovy typ 3. az n pro parametry F
	unsigned int data; // pro var 0-n ostatni 0-undefined 1-defined
	struct hItem *next; // kvuli konfliktum v omezenosti hashe
}*HashTable;

HashTable createHashTable(unsigned int size);
void deleteHashTable(HashTable hashTable);
int addToHashTable(HashTable hashTable, char *key, char *type, unsigned int data);
HashTable searchInHashTable(HashTable hashTable, char *key);
unsigned int hash(char *key);
void testWriteOut(HashTable hashTable);
void hashTest();


void mergeSort(char *arr, int len);
void merge(char *arr, char *l, char*r, int sizeL, int sizeR);

#endif // !IAL

