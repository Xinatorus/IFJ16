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
  POC_STAV, // 0
  
  // komentare
  JEDNORADKOVY_KOMENTAR, // 1
  VICERADKOVY_KOMENTAR, // 2
  VICERADKOVY_KOMENTAR_2, // 3
  
  // operandy (operace)
  SCITANI, // 4
  DELENI, // 5
  ODECITANI, // 6
  NASOBENI, // 7

  // relacni operatory
  MENSI, // 8
  VETSI, // 9
  ROVNO, // 10
  NEROVNO, // 11
  MENSI_NEBO_ROVNO, // 12
  VETSI_NEBO_ROVNO, // 13
  
  PRIRAZENI, // 14
  STREDNIK, // 15
  CARKA, // 16
  
  // zavorky
  LEVA_KULATA_ZAVORKA, // 17
  PRAVA_KULATA_ZAVORKA, // 18
  LEVA_HRANATA_ZAVORKA, // 19
  PRAVA_HRANATA_ZAVORKA, // 20
  LEVA_SLOZENA_ZAVORKA, // 21
  PRAVA_SLOZENA_ZAVORKA, // 22
  
  
  // identifikatory
  IDENTIFIKATOR, // 23
  PLNE_KVALIFIKOVANY_IDENTIFIKATOR, // 24
  PLNE_KVALIFIKOVANY_IDENTIFIKATOR_2, // 25
  KLICOVE_SLOVO, // 26
  REZERVOVANE_SLOVO, // 27
  
  // retezec
  RETEZEC, // 28
  
  // cisla
  CELOCISELNY_LITERAL, // 29
  DESETINNY_LITERAL, // 30
  DESETINNY_LITERAL_2, // 31
  DESETINNY_LITERAL_EXPONENT, // 32
  DESETINNY_LITERAL_EXPONENT_2, // 33
  DESETINNY_LITERAL_EXPONENT_3, // 34
  CELOCISELNY_LITERAL_EXPONENT, // 35
  CELOCISELNY_LITERAL_EXPONENT_2, // 36
  CELOCISELNY_LITERAL_EXPONENT_3, // 37
  
  // konec souboru (EOF)
  KONEC_SOUBORU, // 38
  // lexikalni chyba (lex_error)
  LEXIKALNI_CHYBA // 39                        

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
// funkce pro otevreni zdrojoveho souboru
void loadSource(char* path);

// funkce vracejici token (podle stavu konecneho automatu)
Ttoken* getNextToken();
// funkce pro pruchod tabulkou klicovych a rezervovanych slov pro identifikator
TokenType najdiKlucoveSlovo(string* s);
// funkce pro pruchod tabulkou klicovych a rezervovanych slov pro plne_kvalifikovany_identifikator
TokenType najdiKlucoveSlovo2(string* s);

/*=========================KONEC HLAVICKOVEHO SOUBORU=========================*/