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
    int pocet_znaku;

    if (readString(cislo, STR_MAX))
    {
        pocet_znaku = strlen(cislo);

        for (int i = 0;i < pocet_znaku;i++)
        {
            if (i == (pocet_znaku - 1) || cislo[pocet_znaku - 1] == ' ')
            {
                int vysledek = atoi(cislo);
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
        }*/
    }

    else
    {
        fprintf(stderr, "stderr double - fgets\n");
        return false;
    }
}

int main()
{
    /*char veta[STR_MAX];
    if (readString(veta, STR_MAX))
        printf("%s\n", veta);*/


        //readInt();


        return 0;
}


