//#include "headers\io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "headers\ial.h"
//#include "headers\instructions.h"
//#include "headers\lex_anal.h"
//#include "headers\error.h"
//#include "headers\framework.h"
//#include "headers\interpret.h"
#include <stdbool.h>


#define STR_MAX 100000


bool readString(char *slovo, size_t max_size)
{
     return (fgets(slovo, max_size, stdin) != NULL);
}

bool readInt()
{
    char cislo[STR_MAX];

    if (readString(cislo, STR_MAX))
    {
        int cis = atoi(cislo);

        printf("%d\n", cis);
        return true;

    }
    else
    {
        fprintf(stderr, "stderr - fgets\n");
        return false;
    }
}

double readDouble()
{

}

int main()
{
    /*char veta[STR_MAX];
    if (readString(veta, STR_MAX))
        printf("%s\n", veta);*/


        readInt();

        return 0;
}


