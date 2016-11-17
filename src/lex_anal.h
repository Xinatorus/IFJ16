/* ========================================================================== */
/* Jmena:   .......                                                           */
/* Soubor:  lex_anal.h                                                        */
/* Faze:    Lexikalni analyzator                                              */
/* Datum:   24.10.2016                                                        */
/* ========================================================================== */

// hlavickove soubory 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// vyctovy typ obsahujici seznam tokenu
typedef enum {
  
  // pocatecni stav
  POC_STAV,
  
  // komentare
  JEDNORADKOVY_KOMENTAR,
  VICERADKOVY_KOMENTAR,
  VICERADKOVY_KOMENTAR_2,
  
  // operandy (operace)
  SCITANI,
  DELENI,
  ODECITANI,
  NASOBENI,

  // relacni operatory
  MENSI,
  VETSI,
  NEROVNO,
  
  PRIRAZENI,
  STREDNIK,
  CARKA,
  
  // zavorky
  LEVA_KULATA_ZAVORKA,
  PRAVA_KULATA_ZAVORKA,
  LEVA_HRANATA_ZAVORKA,
  PRAVA_HRANATA_ZAVORKA,
  LEVA_SLOZENA_ZAVORKA,
  PRAVA_SLOZENA_ZAVORKA,
  
  
  // identifikatory
  IDENTIFIKATOR,
  PLNE_KVALIFIKOVANY_IDENTIFIKATOR,
  PLNE_KVALIFIKOVANY_IDENTIFIKATOR_2,
  
  // retezec
  RETEZEC,
  
  // cisla
  CELOCISELNY_LITERAL,
  DESETINNY_LITERAL,
  DESETINNY_LITERAL_2,
  DESETINNY_LITERAL_EXPONENT,
  DESETINNY_LITERAL_EXPONENT_2,
  CELOCISELNY_LITERAL_EXPONENT,
  CELOCISELNY_LITERAL_EXPONENT_2,
  CELOCISELNY_LITERAL_EXPONENT_3,
  
  // konec souboru (EOF)
  KONEC_SOUBORU,
  // lexikalni chyba (lex_error)
  LEXIKALNI_CHYBA                             

}TokenType;

// struktury reprezentujici token
typedef struct{
	char* str;
	int length;
}string;

typedef struct{
	string* attr;
	TokenType type;
	int cisloRiadku;
}Ttoken;

// funkce vytvarejici token 
Ttoken* vytvorToken();
// funkce pro inicializaci retezce a inicializaci tokenu
int stringInit(string* s);
// funkce pro rozsireni daneho retezce o znak
int addChar(string* s,char c);

// funkce vracejici token (podle stavu konecneho automatu)
Ttoken* getNextToken();
// funkce pro pruchod tabulkou klicovych a rezervovanych slov
TokenType najdiKlucoveSlovo(string* s);

/*=========================KONEC HLAVICKOVEHO SOUBORU=========================*/