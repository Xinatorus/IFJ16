/* =================================================================================== */
/* Jmena:   .......                                                                    */
/* Soubor:  io.c                                                                       */
/* Faze:    Vestavene funkce                                                           */
/* Datum:   30.11.2016                                                                 */
/* =================================================================================== */
/* ------------------------------HLAVICKOVE SOUBORY----------------------------------- */
#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers\io.h"
/* ----------------------------------------------------------------------------------- */

#define STR_MAX 100000

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
                int vysledek = (int) strtol(cislo, NULL, 10);

                printf("%d\n", vysledek);
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

double readDouble()
{

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

