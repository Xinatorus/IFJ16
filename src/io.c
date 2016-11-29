#include "headers\io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\ial.h"
#include "headers\instructions.h"
#include "headers\lex_anal.h"
#include "headers\error.h"
#include "headers\framework.h"
#include "headers\interpret.h"


#define STR_MAX 100000

bool readString(char *buffer, size_t max_size)
{
    return (fgets(buffer, max_size, stdin) != NULL);
}
/*****
int main(int argc, char* argv[]) {

    char veta[MAX];

    if (readString(veta, STR_MAX))
        printf("%s\n", veta);
    else
        printf("-- CHYBA --");

    return 0;

}
*****/

int readInt() {

}

double readDouble() {

}

char *readString() {

}