
#include "headers\ial.h"
#include "headers\testWriteOut.h"

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
        error(ERR_INTER);

	memset(htab, 0, sizeof(struct hItem)*size);

	return htab;
}

// Odstraneni tabulky
void deleteHashTable(HashTable hashTable) {

	if (hashTable == NULL) return;

	debug(" [HASHTABLE] Deleting table:");
	hashWriteOut(hashTable);

	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		if (hashTable[i].next != NULL) {
			for (HashTable item = hashTable[i].next; item != NULL; ) {
				HashTable tmp = item;
				item = item->next;
				free(tmp->key);
				free(tmp->type);
				free(tmp);
			}
			hashTable[i].next = NULL;
		}
	}
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		if (hashTable[i].key) {
			free(hashTable[i].key);
			free(hashTable[i].type);
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

/*
repeat(*Pøedpokládá se pole o nenulové délce - alespoò jeden seznam *)
	CopyFirst(L, Zac1); (*Ètení zaèátku prvního seznamu *)
	DeleteFirst(L); First(L);
	if Active(L)
		then begin(*ve frontì jsou alespoò dva seznamy, lze èíst druhý *)
		CopyFirst(L, Zac2); (*Ètení zaèátku druhého seznamu *)
		DeleteFirst(L); First(L);
		if A[Zac1] < A[Zac2]
			then InsertLast(L, Zac1)(*Uložení výsledného zaèátku do fronty*)
		else InsertLast(L, Zac2) (*Uložení výsledného zaèátku do fronty*)
	end(*if *)
until not Active(L)*/
void listMergeSort(char *arr) {
	printf("%s\n",arr);
	int size = strlen(arr);
	int *pom = malloc(sizeof(int)*size);

	
	for (int i = 0; i < size; i++)
		printf("%3d| ", i);
	printf("\n");

	for (int i = 0; i < size; i++)
		printf("%3c| ", arr[i]);
	printf("\n");

	//zretezeni posloupnosti
	for (int i = 0; i < size-1; i++) {
		if (arr[i] < arr[i + 1]) {
			pom[i] = i+1;
		}
		else {
			pom[i] = 0;
		}
		printf("%3d| ", pom[i]);
	}

	pom[size-1] = 0;
	printf("%3d| ", pom[size-1]);
	printf("\n");

	listZacatku L;

	int tmpSize=1;
	for (int i = 0; i < size; i++) {
		
	}



}


void init(listZacatku L) {
	L.active = NULL;
	L.first = NULL;
	L.last = NULL;
}
void add(listZacatku L, neklPos zac) {
	if (L.first == NULL) {
		L.first = zac;
		L.last = zac;
	}
	else {
		L.last->next = zac;
		L.last = zac;
	}
}
void copyFirst(listZacatku L, neklPos zac) {
	zac = L.first;
}
void deleteFirst(listZacatku L) {
	neklPos tmp;
	tmp = L.first;
	if (tmp == L.active) {
		L.active = NULL;
	}
	L.first = tmp->next;
	free(tmp);
}
void first(listZacatku L) {
	L.active = L.first;
}
int active(listZacatku L) {
	return L.active;
}
void insertLast(listZacatku L, neklPos zac) {
	if (L.last) {
		L.last->next = zac;
		L.last = zac;
	}
	else {
		L.first = zac;
		L.last = zac;
	}
}