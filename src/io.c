/* =================================================================================== */
/* Jmena:   .......                                                                    */
/* Soubor:  io.c                                                                       */
/* Faze:    Vestavene funkce                                                           */
/* Datum:   30.11.2016                                                                 */
/* =================================================================================== */
/* ------------------------------HLAVICKOVE SOUBORY----------------------------------- */
#include "headers\io.h"

/* ------------------------------READ STRING------------------------------------------ */
// ze standartiho vstupu nacte retezec ukonceny koncem radkem, nebo koncem
// vstupu, kdy symbol konce radku, nebo vstupu jiz do nacteneho retezce nepatri
char *readString()
{
    char slovo[STR_MAX];

    // nacitani ze stdin (resp. chyba)
    if (fgets(slovo, STR_MAX, stdin) == NULL)
    {
        fprintf(stderr, "stderr - fgets\n");
        return false;
    }

    // ukazatel na char -> fce vraci ukazatel na char
    char * slovo1;
    // oddeli konec radku od nactene posloupnosti znaku ze stdin
    slovo1 = strtok(slovo, "\n");
    // spocita pocet znaku pro dynamickou alokaci
    int pocet_znaku = strlen(slovo1);

    // ukazatel na char -> fce vraci ukazatel na char
    char *novy_vstup = NULL;
    novy_vstup = (char *) malloc(pocet_znaku*sizeof(char));

    if (novy_vstup == NULL)
    {
        fprintf(stderr, "stderr - malloc\n");
        return false;
    }

    novy_vstup = slovo1;

    // vraci ukazatel na nacteny retezec ze stdin
    return novy_vstup;
}
/* ----------------------------------------------------------------------------------- */
/* ------------------------------READ INT--------------------------------------------- */
// nacte retezec, ktery prevede na cele cislo, nebo vrati chybu, pokud retezec neodpovida
bool readInt()
{
    // nacteni ze stdin
    char *cislo = readString();

    // nacteni ze stdin
    if (cislo != NULL)
    {
        // zjisteni poctu znaku v retezci
        int pocet_znaku;
        pocet_znaku = strlen(cislo);

        // cyklus pro pruchod retezce
        for (int i = 0;i < pocet_znaku; i++)
        {
            // v pripade chyby retezce vraci false
            if (!isdigit(cislo[i]))
            {
                fprintf(stderr, "stderr int - string is not a int\n");
                return false;
            }

            // v pripade posledniho znaku rovnu cislu
            else if (i == (pocet_znaku - 1))
            {
                // prevod na cislo
                int *vysledek = (int) strtol(cislo, NULL, 10);
                return true;
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
/* ----------------------------------------------------------------------------------- */
/* ------------------------------READ DOUBLE------------------------------------------ */
// nacte retezec, ktery prevede na realne cislo, nebo vrati chybu, pokud retezec neodpovida
double readDouble()
{
    // nacteni ze stdin
    char *cislo = readString();
    int stav = 0;

    int pocet_znaku = strlen(cislo);

    // nacteni ze stdin
    if (cislo != NULL)
    {
        for (int i = 0; i <= pocet_znaku; i++)
        {
            switch (stav)
            {
                case 0:

                    if (isdigit(cislo[i]))
                    {
                        stav = 01;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 01:

                    if (isdigit(cislo[i]))
                    {
                        stav = 01;
                    }

                    else if (cislo[i] == '.')
                    {
                        stav = 20;
                    }

                    else if (cislo[i] == 'e' || cislo[i] == 'E')
                    {
                        stav = 10;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 10:

                    if (cislo[i] == '+' || cislo[i] == '-')
                    {
                        stav = 11;
                    }

                    else if (isdigit(cislo[i]))
                    {
                        stav = 17;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 17:

                    if (isdigit(cislo[i]))
                    {
                        stav = 17;
                    }

                    else if (cislo[i] == '\0')
                    {
                        double vysledek = strtod(cislo, NULL);
                        return true;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;


                case 11:

                    if (isdigit(cislo[i]))
                    {
                        stav = 12;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 12:

                    if (isdigit(cislo[i]))
                    {
                        stav = 12;
                    }

                    else if (cislo[i] == '\0')
                    {
                        double vysledek = (double) strtod(cislo, NULL);
                        return true;
                    }

                    else
                    {
                        stav = 99;
                    }

                case 20:

                    if (isdigit(cislo[i]))
                    {
                        stav = 22;
                    }

                    else
                    {
                       stav = 99;
                    }

                    break;

                case 22:

                    if (isdigit(cislo[i]))
                    {
                        stav = 22;
                    }

                    else if (cislo[i] == 'e' || cislo[i] == 'E')
                    {
                        stav = 23;
                    }

                    else if (cislo[i] == '\0')
                    {
                        double vysledek = (double) strtod(cislo, NULL);
                        return true;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 23:

                    if (cislo[i] == '+' || cislo[i] == '-')
                    {
                        stav = 24;
                    }

                    else if (isdigit(cislo[i]))
                    {
                        stav = 25;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 24:

                    if (isdigit(cislo[i]))
                    {
                        stav = 25;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 25:

                    if (isdigit(cislo[i]))
                    {
                        stav = 25;
                    }

                    else if (cislo[i] == '\0')
                    {
                        double vysledek = (double) strtod(cislo, NULL);
                        return true;
                    }

                    else
                    {
                        stav = 99;
                    }

                    break;

                case 99:

                    return false;
            }
        }
    }

    else
    {
        fprintf(stderr, "stderr int - fgets\n");
        return false;
    }
}
/* ----------------------------------------------------------------------------------- */
/* ------------------------------FCE LENGTH------------------------------------------- */
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
/* ----------------------------------------------------------------------------------- */
/* ------------------------------FCE COMPARE------------------------------------------ */
// porovna 2 zadane retezce s1 a s2 a vrati
// 0    ,kdyz se rovnaji
// 1    ,kdyz je s1 > s2
// -1   ,kdyz je s1 < s2

int compare(char *s1, char *s2)
{
    return (strcmp(s2,s2));
}
/* ----------------------------------------------------------------------------------- */
