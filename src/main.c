/*******************************************************
*
*						IFJ_2016
*					Autor: xsztef02
*						 main.c
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\hash.h"
#include "headers\mergesort.h"


int main() {
	char *x = "eacbhfgd";

	printf("%s", x);

	mergeSort(x, strlen(x));

	printf("\noutput: ");
	printf("%s\n", x);

	system("pause");
	return 0;
}

