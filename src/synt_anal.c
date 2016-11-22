#include <string.h>
#include "headers\synt_anal.h"
#include "headers\prec_anal.h"
#include "headers\lex_anal.h"
#include "headers\collections.h"
#include "headers\error.h"

int getRuleNumber(NTType nt, TType token) {

    int rules[NT_DOLLAR+1][T_UNKNOWN+1] = {
    //    IDENT  CLASS  STATIC RETURN  IF     ELSE  WHILE   VOID  TYPE   EXPR    LB     RB     LSB    RSB   LPAR   RPAR    SC    COMMA  ASSIGN  EOF  UNKNOWN
        {  -1  ,   1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,   2  ,  -1  } , // NT_PROGRAM
        {  -1  ,   3  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_TRIDA
        {  -1  ,  -1  ,   4  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,   5  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_SEZNAM_DEFINIC_STATIC
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,   6  ,  99  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_DEFINICE_STATIC
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,   8  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_DEFINICE_PROMENNA
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  10  ,  -1  ,   9  ,  -1  ,  -1  } , // NT_DEF_PROM_KONEC
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  11  ,  11  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_DEFINICE_FUNKCE
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  12  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  13  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_SEZNAM_PARAMETRU
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  14  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_PARAMETR_PRVNI
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  16  ,  -1  ,  15  ,  -1  ,  -1  ,  -1  } , // NT_PARAMETR_DALSI
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  17  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  18  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_SEZNAM_VYRAZU
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  20  ,  -1  ,  19  ,  -1  ,  -1  ,  -1  } , // NT_VYRAZ_DALSI
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  21  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_SLOZENY_PRIKAZ
        {  22  ,  -1  ,  -1  ,  22  ,  22  ,  -1  ,  22  ,  -1  ,  22  ,  22  ,  -1  ,  23  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_BLOK_PRIKAZU
        {  25  ,  -1  ,  -1  ,  27  ,  28  ,  -1  ,  29  ,  -1  ,  24  ,  26  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_PRIKAZ
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  31  ,  -1  ,  -1  ,  -1  ,  30  ,  -1  ,  -1  } , // NT_POUZITI
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  32  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_VOLANI_FUNKCE
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  33  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  34  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_NAVRAT_KONEC
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  35  ,  -1  ,  -1  } , // NT_PRIRAZENI
        {  37  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  36  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_PRAVA_STRANA
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  39  ,  38  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  } , // NT_NAVRATOVY_TYP
        {  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  }   // NT_DOLLAR
    };

    return rules[nt][token];
}

void applyRule(int rule, cStack *stack) {
    if (stack == NULL) {
        return;
    }

    // The reason for not automating this process is precedence analysis
    switch (rule) {
        case 1:
            // NT_PROGRAM -> NT_TRIDA NT_PROGRAM
            push_nonterminal(NT_TRIDA, stack);
            break;
        case 2:
            // NT_PROGRAM -> NT_DOLLAR
            cStack_pop(stack);
            push_nonterminal(NT_DOLLAR, stack);
            break;
        case 3:
            // NT_TRIDA -> T_CLASS T_IDENT T_LB NT_SEZNAM_DEFINIC_STATIC T_RB
            cStack_pop(stack);
            push_terminal(T_RB, stack);
            push_nonterminal(NT_SEZNAM_DEFINIC_STATIC, stack);
            push_terminal(T_LB, stack);
            push_terminal(T_IDENT, stack);
            push_terminal(T_CLASS, stack);
            break;
        case 4:
            // NT_SEZNAM_DEFINIC_STATIC -> T_STATIC NT_DEFINICE_STATIC NT_SEZNAM_DEFINIC_STATIC
            push_nonterminal(NT_DEFINICE_STATIC, stack);
            push_terminal(T_STATIC, stack);
            break;
        case 5:
            // NT_SEZNAM_DEFINIC_STATIC -> eps
            cStack_pop(stack);
            break;
        case 6:
            // NT_DEFINICE_STATIC -> NT_DEFINICE_FUNKCE
            cStack_pop(stack);
            push_nonterminal(NT_DEFINICE_FUNKCE, stack);
            break;
        case 7:
            // NT_DEFINICE_STATIC -> NT_DEFINICE_PROMENNA T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_DEFINICE_PROMENNA, stack);
            break;
        case 8:
            // NT_DEFINICE_PROMENNA -> T_TYPE T_IDENT NT_DEF_PROM_KONEC
            cStack_pop(stack);
            push_nonterminal(NT_DEF_PROM_KONEC, stack);
            push_terminal(T_IDENT, stack);
            push_terminal(T_TYPE, stack);
            break;
        case 9:
            // NT_DEF_PROM_KONEC -> NT_PRIRAZENI
            cStack_pop(stack);
            push_nonterminal(NT_PRIRAZENI, stack);
            break;
        case 10:
            // NT_DEF_PROM_KONEC -> eps
            cStack_pop(stack);
            break;
        case 11:
            // NT_DEFINICE_FUNKCE -> NT_NAVRATOVY_TYP T_IDENT T_LPAR NT_SEZNAM_PARAMETRU T_RPAR NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_RPAR, stack);
            push_nonterminal(NT_SEZNAM_PARAMETRU, stack);
            push_terminal(T_LPAR, stack);
            push_terminal(T_IDENT, stack);
            push_nonterminal(NT_NAVRATOVY_TYP, stack);
            break;
        case 12:
            // NT_SEZNAM_PARAMETRU -> NT_PARAMETR_PRVNI NT_PARAMETR_DALSI
            cStack_pop(stack);
            push_nonterminal(NT_PARAMETR_DALSI, stack);
            push_nonterminal(NT_PARAMETR_PRVNI, stack);
            break;
        case 13:
            // NT_SEZNAM_PARAMETRU -> eps
            cStack_pop(stack);
            break;
        case 14:
            // NT_PARAMETR_PRVNI -> T_TYPE T_IDENT
            cStack_pop(stack);
            push_terminal(T_IDENT, stack);
            push_terminal(T_TYPE, stack);
            break;
        case 15:
            // NT_PARAMETR_DALSI -> T_COMMA T_TYPE T_IDENT NT_PARAMETR_DALSI
            push_terminal(T_IDENT, stack);
            push_terminal(T_TYPE, stack);
            push_terminal(T_COMMA, stack);
            break;
        case 16:
            // NT_PARAMETR_DALSI -> eps
            cStack_pop(stack);
            break;
        case 17:
            // NT_SEZNAM_VYRAZU -> T_EXPRESSION NT_VYRAZ_DALSI
            cStack_pop(stack);
            push_nonterminal(NT_VYRAZ_DALSI, stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 18:
            // NT_SEZNAM_VYRAZU -> eps
            cStack_pop(stack);
            break;
        case 19:
            // NT_VYRAZ_DALSI -> T_COMMA T_EXPRESSION
            cStack_pop(stack);
            push_terminal(T_EXPRESSION, stack);
            push_terminal(T_COMMA, stack);
            break;
        case 20:
            // NT_VYRAZ_DALSI -> eps
            cStack_pop(stack);
            break;
        case 21:
            // NT_SLOZENY_PRIKAZ -> T_LB NT_BLOK_PRIKAZU T_RB
            cStack_pop(stack);
            push_terminal(T_RB, stack);
            push_nonterminal(NT_BLOK_PRIKAZU, stack);
            push_terminal(T_LB, stack);
            break;
        case 22:
            // NT_BLOK_PRIKAZU -> NT_PRIKAZ NT_BLOK_PRIKAZU
            push_nonterminal(NT_BLOK_PRIKAZU, stack);
            push_nonterminal(NT_PRIKAZ, stack);
            break;
        case 23:
            // NT_BLOK_PRIKAZU -> eps
            cStack_pop(stack);
            break;
        case 24:
            // NT_PRIKAZ -> NT_DEFINICE_PROMENNA T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_DEFINICE_PROMENNA, stack);
            break;
        case 25:
            // NT_PRIKAZ -> T_IDENT NT_POUZITI T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_POUZITI, stack);
            push_terminal(T_IDENT, stack);
            break;
        case 26:
            // NT_PRIKAZ -> T_EXPRESSION T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 27:
            // NT_PRIKAZ -> T_RETURN NT_NAVRAT_KONEC T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_NAVRAT_KONEC, stack);
            push_terminal(T_RETURN, stack);
            break;
        case 28:
            // NT_PRIKAZ -> T_IF T_LPAR T_EXPRESSION T_RPAR NT_SLOZENY_PRIKAZ T_ELSE NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_ELSE, stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_RPAR, stack);
            push_terminal(T_EXPRESSION, stack);
            push_terminal(T_LPAR, stack);
            push_terminal(T_IF, stack);
            break;
        case 29:
            // NT_PRIKAZ -> T_WHILE T_LPAR T_EXPRESSION T_RPAR NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_RPAR, stack);
            push_terminal(T_EXPRESSION, stack);
            push_terminal(T_LPAR, stack);
            push_terminal(T_WHILE, stack);
            break;
        case 30:
            // NT_POUZITI -> NT_PRIRAZENI
            cStack_pop(stack);
            push_nonterminal(NT_PRIRAZENI, stack);
            break;
        case 31:
            // NT_POUZITI -> NT_VOLANI_FUNKCE
            cStack_pop(stack);
            push_nonterminal(NT_VOLANI_FUNKCE, stack);
            break;
        case 32:
            // NT_VOLANI_FUNKCE -> T_LPAR NT_SEZNAM_VYRAZU T_RPAR
            cStack_pop(stack);
            push_terminal(T_RPAR, stack);
            push_nonterminal(NT_SEZNAM_VYRAZU, stack);
            push_terminal(T_LPAR, stack);
            break;
        case 33:
            // NT_NAVRAT_KONEC -> T_EXPRESSION
            cStack_pop(stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 34:
            // NT_NAVRAT_KONEC -> eps
            cStack_pop(stack);
            break;
        case 35:
            // NT_PRIRAZENI -> = NT_PRAVA_STRANA
            cStack_pop(stack);
            push_nonterminal(NT_PRAVA_STRANA, stack);
            break;
        case 36:
            // NT_PRAVA_STRANA -> T_EXPRESSION
            cStack_pop(stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 37:
            // NT_PRAVA_STRANA -> T_IDENT NT_VOLANI_FUNKCE
            cStack_pop(stack);
            push_nonterminal(NT_VOLANI_FUNKCE, stack);
            push_terminal(T_IDENT, stack);
            break;
        case 38:
            // NT_NAVRATOVY_TYP -> T_TYPE
            cStack_pop(stack);
            push_terminal(T_TYPE, stack);
            break;
        case 39:
            // NT_NAVRATOVY_TYP -> T_VOID
            cStack_pop(stack);
            push_terminal(T_VOID, stack);
            break;
        default:
            break;
    }
}

Terminal getNextTerminal() {
    Ttoken *token = NULL; // Token to work with
    Terminal terminal; // Terminal to return

    // Something is left in token archive, we must use that
    if (archive != NULL) {
        token = archive;
        archive = NULL;
    }
    else {
        token = getNextToken();
    }

    terminal.token = token;
    terminal.type = T_UNKNOWN;

    if (token->type == KLICOVE_SLOVO) {
        if (strcmp(token->attr->str, "class") == 0) {
            terminal.type = T_CLASS;
        }
        else if (strcmp(token->attr->str, "static") == 0) {
            terminal.type = T_STATIC;
        }
        else if (strcmp(token->attr->str, "return") == 0) {
            terminal.type = T_RETURN;
        }
        else if (strcmp(token->attr->str, "if") == 0) {
            terminal.type = T_IF;
        }
        else if (strcmp(token->attr->str, "else") == 0) {
            terminal.type = T_ELSE;
        }
        else if (strcmp(token->attr->str, "while") == 0) {
            terminal.type = T_WHILE;
        }
        else if (strcmp(token->attr->str, "void") == 0) {
            terminal.type = T_VOID;
        }
        else if (strcmp(token->attr->str, "int") == 0 &&
            strcmp(token->attr->str, "double") == 0 &&
            strcmp(token->attr->str, "String") == 0) {
            terminal.type = T_TYPE;
        }
        else {
            terminal.type = T_UNKNOWN;
        }
    }
    else if (token->type == PRIRAZENI) {
        terminal.type = T_ASSIGN;
    }
    else if (token->type == KONEC_SOUBORU) {
        terminal.type = T_EOF;
    }
    else if (token->type == LEVA_KULATA_ZAVORKA) {
        terminal.type = T_LPAR;
    }
    else if (token->type == PRAVA_KULATA_ZAVORKA) {
        terminal.type = T_RPAR;
    }
    else if (token->type == LEVA_HRANATA_ZAVORKA) {
        terminal.type = T_LSB;
    }
    else if (token->type == PRAVA_HRANATA_ZAVORKA) {
        terminal.type = T_RSB;
    }
    else if (token->type == LEVA_SLOZENA_ZAVORKA) {
        terminal.type = T_LB;
    }
    else if (token->type == PRAVA_SLOZENA_ZAVORKA) {
        terminal.type = T_RB;
    }
    else if (token->type == STREDNIK) {
        terminal.type = T_SC;
    }
    else if (token->type == CARKA) {
        terminal.type = T_COMMA;
    }
    else if (token->type == RETEZEC ||
        token->type == DESETINNY_LITERAL ||
        token->type == DESETINNY_LITERAL_EXPONENT ||
        token->type == CELOCISELNY_LITERAL ||
        token->type == CELOCISELNY_LITERAL_EXPONENT) {
        terminal.type = T_EXPRESSION;
    }
    // We must decide whether this will be an expression...
    else if (token->type == IDENTIFIKATOR ||
        token->type == PLNE_KVALIFIKOVANY_IDENTIFIKATOR) {
        archive = getNextToken(); // We have to use another token
        // identificator followed by operator is surely an expression
        if (archive->type != SCITANI &&
            archive->type != ODECITANI &&
            archive->type != NASOBENI &&
            archive->type != DELENI &&
            archive->type != MENSI &&
            archive->type != VETSI &&
            archive->type != ROVNO &&
            archive->type != NEROVNO &&
            archive->type != MENSI_NEBO_ROVNO &&
            archive->type != VETSI_NEBO_ROVNO) {
            terminal.type = T_IDENT;
        }
        else {
            terminal.type = T_EXPRESSION;
        }
    }
    else {
        // Other possibilities - like ODECITANi outside expression are not possible
        terminal.type = T_UNKNOWN;
    }

    return terminal;
}

void push_terminal(TType type, cStack *stack) {
    cItem item;
    Terminal terminal;
    terminal.token = NULL;
    terminal.type = type;
    item.type = IT_TERMINAL;
    item.content.terminal = terminal;
    if (!cStack_push(stack, item)) {
        error(INTER_ERROR);
    }
}

void push_nonterminal(NTType type, cStack *stack) {
    cItem item;
    item.type = IT_NTTYPE;
    item.content.nttype = type;
    if (!cStack_push(stack, item)) {
        error(INTER_ERROR);
    }
}

void execute() {
    cStack stack;
    cStack_init(&stack, 50);
    /* First step - push NT_DOLLAR (NT version of EOF) and NT_PROGRAM to stack */
    push_nonterminal(NT_DOLLAR, &stack);
    push_nonterminal(NT_PROGRAM, &stack);

    /* Second step - loop :o */
    Terminal input = getNextTerminal(); // Actual terminal from input
    cItem top; // Top of the stack
    do {
        top = cStack_top(&stack);

        // We have NT_DOLLAR on top -> success or fail
        if (top.type == IT_NTTYPE && top.content.nttype == NT_DOLLAR) {
            if (input.type == T_EOF) {
                return;
            }
            else {
                error(SYNTA_ERROR);
            }
        }

        // We have terminal on top -> if it is the same as terminal from input, process
        if (top.type == IT_TERMINAL && top.content.terminal.type == input.type) {
            if (input.type == T_EXPRESSION) {
                prec_analysis(input.token);
            }
            cStack_pop(&stack);
            input = getNextTerminal();
        }
        else {
            error(SYNTA_ERROR);
        }

        // We have non-terminal on top -> try to find and apply LL rule
        if (top.type == IT_NTTYPE) {
            int rule = getRuleNumber(top.type, input.token->type);
            if (rule == -1) {
                error(SYNTA_ERROR);
            }
            else {
                applyRule(rule, &stack);
            }
        }

    } while (input.type != T_EOF);
}