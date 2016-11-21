#ifndef SYNT_ANAL_H
#define SYNT_ANAL_H

#include "lex_anal.h"
#include "stack.h"

/* List of possible non-terminals */
typedef enum {
    NT_PROGRAM,
    NT_TRIDA,
    NT_SEZNAM_DEFINIC_STATIC,
    NT_DEFINICE_STATIC,
    NT_DEFINICE_PROMENNA,
    NT_DEF_PROM_KONEC,
    NT_DEFINICE_FUNKCE,
    NT_SEZNAM_PARAMETRU,
    NT_PARAMETR_PRVNI,
    NT_PARAMETR_DALSI,
    NT_SEZNAM_TERMU,
    NT_TERM_DALSI,
    NT_SLOZENY_PRIKAZ,
    NT_BLOK_PRIKAZU,
    NT_PRIKAZ,
    NT_POUZITI,
    NT_VOLANI_FUNKCE,
    NT_NAVRAT_KONEC,
    NT_PRIRAZENI,
    NT_PRAVA_STRANA,
    NT_NAVRATOVY_TYP,
    NT_DOLLAR // Vzdy posledni
}NTType;

/* List of possible terminals (excluding lex_error and all term + expression terminals) */
typedef enum {
    T_IDENTIFIKATOR,
    T_IDENTIFIKATOR_FUNKCE,
    T_PLNE_KVALIFIKOVANY_IDENTIFIKATOR,
    T_PLNE_KVALIFIKOVANY_IDENTIFIKATOR_FUNKCE,
    T_CLASS,
    T_STATIC,
    T_INT,
    T_DOUBLE,
    T_STRING,
    T_RETURN,
    T_IF,
    T_ELSE,
    T_WHILE,
    T_LEVA_SLOZENA_ZAVORKA,
    T_PRAVA_SLOZENA_ZAVORKA,
    T_LEVA_HRANATA_ZAVORKA,
    T_PRAVA_HRANATA_ZAVORKA,
    T_LEVA_KULATA_ZAVORKA,
    T_PRAVA_KULATA_ZAVORKA,
    T_STREDNIK,
    T_CARKA,
    T_PRIRAZENI,
    T_KLICOVE_SLOVO, // all other keywords
    T_REZERVOVANE_SLOVO,
    T_EOF,
    T_DOLLAR
}TType;

/* Non-terminal */
typedef struct {
    NTType type;
}NT;

// Protoze musime rozlisit pripady, kdy dostaneme napr. token klicove_slovo (if) a klicove_slovo (else), chce to vytvorit vlastni typy tokenu... a funkci, ktera nam ten typ vrati.
// Tato funkce bude schopna rozlisit i identifikatory - identifikator, plne_kvalifikovany_identifikator, identifikator_funkce, plne_kvalifikovany_identifikator_funkce
// Pro rozliseni napr. identifikatoru a identifikatoru_funkce je treba vytahnout dalsi token, kdyz tam bude zavorka, je to identifikator funkce... 
// Protoze jsme vytahli token navic, musime vytvorit neco jako zasobnik prebytecnych tokenu, ktery ty navic vytazene bude uchovavat...
// Dale bude potreba nejaka nahrada za getNextToken, ktera automaticky bude brat z uchovanych (pokud tam nejake jsou)
// Podle vlastnich typu tokenu (kde budou i ty rozlisene identifikatory) je treba prepracovat gramatiku a LL tabulku :/
// lex chyba nebude ve vlastnich typech tokenu, ty pripadne poresi ta nahradni funkce na ziskani tokenu, a veci z vyrazu tam taky nebudou
// co se tyka konfliktu se zavorkama u precedencni analyzy a syntaxe shora dolu, tak nejspis tam ke konfliktu nedojde, diky omezenim termu a tomu, ze ve vyrazu nelze mit volani fce

/* Get appropriate rule number from TT table - based on non-terminal and token */
int getRuleNumber(NTType nt, TokenType token);

/* Apply rule identified by number to stack (= expand non-terminal) */
void applyRule(int rule, Stack *stack);

/* Get next terminal (from getNextToken() OR stack for stored tokens) */
Ttoken *getNextTerminal();

#endif // include guard
