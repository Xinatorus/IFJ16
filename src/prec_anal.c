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
    /* Precedencni analyza vrati PS_DOLLAR kdyz konci - tzn bud v pripade, kdy je token znak, ktery nepatri do vyrazu
       nebo v pripade, kdy je token prava zavorka ) ale uz jsou vsechny uzavreny... 
       NEPOUZITY TOKEN JE TREBA VRATIT DO ARCHIVU */
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

void prec_analysis(Ttoken *token) {
    return;
}