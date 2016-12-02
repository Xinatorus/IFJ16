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


char *readString()
{
    char slovo[STR_MAX];

    if (fgets(slovo, STR_MAX, stdin) == NULL)
    {
        fprintf(stderr, "stderr - fgets\n");
        return false;
    }

    int pocet_znaku = strlen(slovo);

    char *novy_vstup;
    novy_vstup = (char *) malloc(pocet_znaku*sizeof(char));

    if (novy_vstup == NULL)
    {
        fprintf(stderr, "stderr - malloc\n");
        return false;
    }

    novy_vstup = slovo;

    /*for (int i = 0; i < (pocet_znaku - 1) ;i++)
    {
        int j = 0;

        strcpy(novy_vstup[i], slovo[j]);

        j++;
    }*/

    printf("%d\n", strlen(novy_vstup));
    printf("%d\n", strlen(slovo));
    printf("%s\n", novy_vstup);

    return novy_vstup;
}
/*
bool readInt()
{
    char cislo[STR_MAX];
    int pocet_znaku;

    if (readString(cislo, STR_MAX))
    {
        pocet_znaku = strlen(cislo);

        for (int i = 0;i < pocet_znaku;i++)
        {
            if (i == (pocet_znaku - 1) || cislo[pocet_znaku - 1] == ' ')
            {
                int *vysledek = atoi(cislo);
                return true;
            }

            if (!isdigit(cislo[i]))
            {
                return false;
            }
        }

        return false;
    }

    else
    {
        fprintf(stderr, "stderr int - fgets\n");
        return false;
    }
}
/*
double readDouble()
{
    char cislo[STR_MAX];
    int pocet_znaku;
    int i = 0;
    int token = 0;

    if (readString(cislo, STR_MAX))
    {
        pocet_znaku = strlen(cislo);

        while (cislo[i] < pocet_znaku)
        {
            switch (token)
            {
                case 0:
                    if (isdigit(cislo[i]))
                    {
                        token = 1;
                    }

                    else
                    {
                        return false;
                    }

                    break;

                case 1:
                    if (isdigit(cislo[i]))
                    {
                        token = 1;
                    }

                    else if (cislo[i] == '.')
                    {
                        token = 10;
                    }

                    else if (cislo[i] == 'e' || cislo[i] == 'E')
                    {
                        token = 2;
                    }

                    else
                    {
                        return false;
                    }

                    break;

                case 2:
                    if (isdigit(cislo[i]) || cislo[i] == '+' || cislo[i] == '-')
                    {
                        token = 3;
                    }

                    else
                    {
                        return false;
                    }

                    break;

                case 3:
                    if (isdigit())
                    {
                            printf("Ahoj");
                    }



            }

            i++;
        }




























        /*pocet_znaku = strlen(cislo);

        if (isdigit(cislo[0]))
        {
            for (int i = 1; i < pocet_znaku; i++)
            {
                if ((!isdigit(cislo[i])) || (cislo[i] != '.') || (cislo[i] != 'e') || (cislo[i] != 'E'))
                {
                    return false;
                }

                else if (cislo[i] == '.')
                {
                    i++;

                    if (!isdigit(cislo[i]))
                    {
                        return false
                    }

                    else if (i == (pocet_znaku - 1))
                    {
                        return false;
                    }

                    else if ()
                    {

                    }

                }

                else if ((cislo[i] == 'e') || (cislo[i] == 'E'))
                {


                }

                else if (i == (pocet_znaku - 1))
                {
                    return false;
                }
            }
        }

        else
        {
            return false;
        }
    }

    else
    {
        fprintf(stderr, "stderr double - fgets\n");
        return false;
    }
}
*/
/*-------------------------------FCE LENGTH------------------------*/
// vrati delku retezce zadaneho jedinym parametrem s
int length(char* s)
{
    // chybove hlaseni v pripade nuloveho znaku
    if (s == NULL)
    {
        fprintf(stderr, "stderr - length of string\n");
        return false;
    }

    // pruchod jednotlivych znaku a prepocet pocitadla znaku
    int pocet = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {

        if (s[i] == '/')
        {
            i++;
        }

        pocet++;
    }

    // vraci pocet znkau retezce
    return pocet;
}
/*-----------------------------------------------------------------*/
/*-------------------------------FCE COMPARE------------------------*/
// porovna 2 zadane retezce s1 a s2 a vrati
// 0    ,kdyz se rovnaji
// 1    ,kdyz je s1 > s2
// -1   ,kdyz je s1 < s2

int compare(char *s1, char *s2)
{
    return (strcmp(s2,s2));
}
/*-----------------------------------------------------------------*/











int main()
{
    /*char veta[STR_MAX];
    if (readString(veta, STR_MAX))
        printf("%s\n", veta);*/

        return 0;
}


