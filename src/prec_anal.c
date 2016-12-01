#include "headers\synt_anal.h"

int prec_rules[14][14] = {
//     i     (     )     +     -     *     /     <     >     <=    >=    ==    !=    $
    { 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_VALUE
    { '<' , '<' , '=' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' } , // PS_LRB
    { 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' } , // PS_RRB
    { '<' , '<' , '>' , '>' , '>' , '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_PLUS
    { '<' , '<' , '>' , '>' , '>' , '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_MINUS
    { '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_STAR
    { '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_SLASH
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_LTHAN
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_RTHAN
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_LTHANEQ
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_RTHANEQ
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , '>' } , // PS_EQ
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , '>' } , // PS_NEQ
    { '<' , 'X' , 'X' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '>' }   // PS_DOLLAR
};

char getPrecedenceOperation(PType p, TType t) {

    return prec_rules[p][t];
}

Psymbol getNextPrecSymbol() {
    Ttoken *token = NULL; // Token to work with
    Psymbol symbol; // Symbol to return
    static int par_level = 0; // Level of parenthesis

    // Something is left in token archive, we must use that
    if (cStack_isempty(&token_archive)) {
        token = cStack_top(&token_archive).content.token;
        cStack_pop(&token_archive);
    }
    // Read token from input
    else {
        token = getNextToken();
    }

    symbol.token = token;
    symbol.type = PS_DOLLAR;

    if (token->type == IDENTIFIKATOR ||
        token->type == PLNE_KVALIFIKOVANY_IDENTIFIKATOR ||
        token->type == RETEZEC ||
        token->type == CELOCISELNY_LITERAL ||
        token->type == CELOCISELNY_LITERAL_EXPONENT ||
        token->type == DESETINNY_LITERAL ||
        token->type == DESETINNY_LITERAL_EXPONENT) {
        symbol.type = PS_VALUE
    }
    else if (token->type == LEVA_KULATA_ZAVORKA) {
        symbol.type = PS_LRB;
    }
    else if (token->type == PRAVA_KULATA_ZAVORKA) {
        symbol.type = PS_RRB;
    }
    else if (token->type == SCITANI) {
        symbol.type = PS_PLUS;
    }
    else if (token->type == ODECITANI) {
        symbol.type = PS_MINUS;
    }
    else if (token->type == NASOBENI) {
        symbol.type = PS_STAR;
    }
    else if (token->type == DELENI) {
        symbol.type = PS_SLASH;
    }
    else if (token->type == MENSI) {
        symbol.type = PS_LTHAN;
    }
    else if (token->type == VETSI) {
        symbol.type = PS_RTHAN;
    }
    else if (token->type == MENSI_NEBO_ROVNO) {
        symbol.type = PS_LTHANEQ;
    }
    else if (token->type == VETSI_NEBO_ROVNO) {
        symbol.type = PS_RTHANEQ;
    }
    else if (token->type == ROVNO) {
        symbol.type = PS_EQ;
    }
    else if (token->type == NEROVNO) {
        symbol.type = PS_NEQ;
    }
    /* Precedencni analyza vrati PS_DOLLAR kdyz konci - tzn bud v pripade, kdy je token znak, ktery nepatri do vyrazu
    nebo v pripade, kdy je token prava zavorka ) ale uz jsou vsechny uzavreny...
    NEPOUZITY TOKEN JE TREBA VRATIT DO ARCHIVU */


    // uroven zanoreni zavorek (par_level) musi menit tato funkce a pri zaviraci zavorce a urovni 0 to vrati PS_DOLLAR (+ archiv)

    return symbol;

}

void applyPrecedenceOperation(char operation, cStack *stack) {
    if (operation == '<') {
        // za symbol ve stacku dat PS_LSYS (bude treba zmenit stack za seznam? nebo to bude vzdy jen push PS_LSYS ? )
        // pushni vstup do stacku
        // precti dalsi vstup
        // (ten kdo vola pak musi overit, ze dalsim vstupem neni konecny PS_DOLLAR)
    }
    else if (operation == '>') {
        // pushni PS_RSYS do stacku
        // popuj stack, postupuj ve stavovem automatu az dojdes k PS_LSYS
        // podle typu stavoveho automatu proved push leve strany pravidla
        // stavovy automat detekuje neplatne (chybove) stavy
    }
    else if (operation == '=') {
        // pushni vstup do stacku
        // precti dalsi vstup
    }
    else {
        // operace je X nebo nejaka neznama (asi ne)
        // takze chyba
    }
}

void push_psymbol(PType type, cStack *stack) {
    cItem item;
    Psymbol symbol;
    symbol.token = NULL;
    symbol.type = type;
    item.type = IT_PSYMBOL;
    item.content.psymbol = symbol;
    if (!cStack_push(stack, item)) {
        error(INTER_ERROR);
    }
}

void prec_analysis() {
    return;
}
