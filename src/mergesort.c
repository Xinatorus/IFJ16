#include "headers\mergesort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//TODO: FASTEST

void mergeSort(char *arr,int len) {
	if (len <= 1) return;

	int half = len / 2;
	char *l = malloc(half);
	char *r = malloc(len - half);

	//if (!r || !l) printf("errMalloc\n");

	for (int i = 0; i < half; i++)
		l[i] = arr[i];
	for (int i = half; i < len; i++)
		r[i-half] = arr[i];

	mergeSort(l, half);
	mergeSort(r, len - half);
	merge(arr, l, r, half, len - half);

	free(l);
	free(r);
}

void merge(char *arr,char *l, char *r, int sizeL, int sizeR) {
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