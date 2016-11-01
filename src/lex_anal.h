/* ========================================================================== */
/* Jmena:   .......                                                           */
/* Soubor:  lex_anal.h                                                        */
/* Faze:    Lexikalni analyzator                                              */
/* Datum:   24.10.2016                                                        */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


extern int LINE;

typedef enum {
	INIT,                                   // 0

	//identifikator,retazec,integer,double
	ID,                                     // 1
  STRING_LITERAL,                         // 2
  INT,					// 3
  DBL,                                	// 4
  
  KLUC,
  REZER,
	
  //operatory
	ASSIGNMENT,                             // 22
  LSS,                                    // 23
  GTR,                                    // 24
  LESS_OR_EQUAL,                          // 25
  GREATER_OR_EQUAL,                       // 26
  EQUAL,                                  // 27
  NOT_EQUAL,                              // 28

	  LAVO,                                     // 29
    PRAVO,                                    // 30

	  ADD,                                    // 31
    SUB,                                    // 32
    MULTIPLICATION,                         // 33
    DIVISION,                               // 34

	//zatvorky
  LEFT_BRACKET,                           // 35
  RIGHT_BRACKET,                          // 36
  LEFT_SQUARE_BRACKET,                    // 37
  RIGHT_SQUARE_BRACKET,                   // 38
	LEFT_CURLY_BRACKET,                     // 39
	RIGHT_CURLY_BRACKET,                    // 40

	//komentare
	JED_RIAD_KOM,                    // 41
  VIAC_RIAD_KOM,                     // 42
  VIAC_RIAD_KOM_KONIEC,                 // 43

	//ciarka, bodkociarka
	COMMA,                                  // 44
  SEMICLN,                                // 45

	//pomocne stavy
	DBL_DOT,                                // 46
  DBL_EXPONENT,                           // 47
  DBL_EXPONENT_SIGNED,                    // 48


	END_OF_FILE,                            // 49
  LEX_ERROR                               // 50

}TokenType;

typedef struct{
	char* str;
	int length;
}string;

typedef struct{
	string* attr;
	TokenType type;
	int cisloRiadku;
}Ttoken;


int loadSourceFile(char* file);
int closeSourceFile();


int stringInit(string* s);
int addChar(string* s,char c);

Ttoken* vytvorToken();
int znicToken(Ttoken* token);

Ttoken* getNextToken();
TokenType najdiKlucoveSlovo(string* s);
