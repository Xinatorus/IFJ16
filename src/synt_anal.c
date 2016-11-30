#include <string.h>
#include "headers\synt_anal.h"

#define SYNT_DEBUG 1    // Debug messages for syntax analysis

int synt_rules[23][20] = {
//   IDENT  FIDENT CLASS  STATIC RETURN  IF     ELSE  WHILE   VOID  TYPE   EXPR    LCB    RCB    LRB    RRB    SC    COMMA  ASSIGN  EOF  UNKNOWN
    { -1  ,  -1  ,   1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,   2  ,  -1 } , // NT_PROGRAM
    { -1  ,  -1  ,   3  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_TRIDA
    { -1  ,  -1  ,  -1  ,   4  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,   5  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_SEZNAM_DEFINIC_STATIC
    {  7  ,   6  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_DEFINICE_STATIC
    {  8  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_DEFINICE_PROMENNA
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  10  ,  -1  ,   9  ,  -1  ,  -1 } , // NT_DEF_PROM_KONEC
    { -1  ,  11  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_DEFINICE_FUNKCE
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  12  ,  -1  ,  -1  ,  -1  ,  -1  ,  13  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_SEZNAM_PARAMETRU
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  14  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_PARAMETR_PRVNI
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  16  ,  -1  ,  15  ,  -1  ,  -1  ,  -1 } , // NT_PARAMETR_DALSI
    { 18  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  17  ,  -1  ,  -1  ,  -1  ,  19  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_SEZNAM_VSTUPU
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  21  ,  -1  ,  20  ,  -1  ,  -1  ,  -1 } , // NT_VSTUP_DALSI
    { 23  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  22  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_VSTUP_KONEC
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  24  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_SLOZENY_PRIKAZ
    { 25  ,  25  ,  -1  ,  -1  ,  25  ,  25  ,  -1  ,  25  ,  -1  ,  25  ,  25  ,  -1  ,  26  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_BLOK_PRIKAZU
    { 29  ,  30  ,  -1  ,  -1  ,  31  ,  32  ,  -1  ,  33  ,  -1  ,  27  ,  28  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_PRIKAZ
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  35  ,  -1  ,  34  ,  -1  ,  -1 } , // NT_POUZITI
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  36  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_VOLANI_FUNKCE
    { 38  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  37  ,  -1  ,  -1  ,  -1  ,  -1  ,  39  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_NAVRAT_KONEC
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  40  ,  -1  ,  -1 } , // NT_PRIRAZENI
    { 42  ,  43  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  41  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_PRAVA_STRANA
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  44  ,  45  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 } , // NT_DATOVY_TYP
    { -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 }   // NT_DOLLAR
};

int getRuleNumber(NTType nt, TType t) {

    #if SYNT_DEBUG == 1
        fprintf(stdout, "[SYNT_DEBUG] getRuleNumber(%s, %s)\n", NTType_string[nt], TType_string[t]);
    #endif

    return synt_rules[nt][t];
}

void applyRule(int rule, cStack *stack) {
    if (stack == NULL) {
        return;
    }

    #if SYNT_DEBUG == 1
        fprintf(stdout, "[SYNT_DEBUG] Applying rule #%d\n", rule);
    #endif
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
            // NT_TRIDA -> T_CLASS T_IDENT T_LCB NT_SEZNAM_DEFINIC_STATIC T_RCB
            cStack_pop(stack);
            push_terminal(T_RCB, stack);
            push_nonterminal(NT_SEZNAM_DEFINIC_STATIC, stack);
            push_terminal(T_LCB, stack);
            push_terminal(T_IDENT, stack);
            push_terminal(T_CLASS, stack);
            break;
        case 4:
            // NT_SEZNAM_DEFINIC_STATIC -> T_STATIC NT_DATOVY_TYP NT_DEFINICE_STATIC NT_SEZNAM_DEFINIC_STATIC
            push_nonterminal(NT_DEFINICE_STATIC, stack);
            push_nonterminal(NT_DATOVY_TYP, stack);
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
            // NT_DEFINICE_PROMENNA -> T_IDENT NT_DEF_PROM_KONEC
            cStack_pop(stack);
            push_nonterminal(NT_DEF_PROM_KONEC, stack);
            push_terminal(T_IDENT, stack);
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
            // NT_DEFINICE_FUNKCE -> T_FIDENT T_LRB NT_SEZNAM_PARAMETRU T_RRB NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_RRB, stack);
            push_nonterminal(NT_SEZNAM_PARAMETRU, stack);
            push_terminal(T_LRB, stack);
            push_terminal(T_FIDENT, stack);
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
            // NT_SEZNAM_VSTUPU -> T_EXPRESSION NT_VSTUP_DALSI
            cStack_pop(stack);
            push_nonterminal(NT_VSTUP_DALSI, stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 18:
            // NT_SEZNAM_VSTUPU -> T_IDENT NT_VSTUP_DALSI
            cStack_pop(stack);
            push_nonterminal(NT_VSTUP_DALSI, stack);
            push_terminal(T_IDENT, stack);
            break;
        case 19:
            // NT_SEZNAM_VSTUPU -> eps
            cStack_pop(stack);
            break;
        case 20:
            // NT_VSTUP_DALSI -> T_COMMA NT_VSTUP_KONEC
            cStack_pop(stack);
            push_terminal(NT_VSTUP_KONEC, stack);
            push_terminal(T_COMMA, stack);
            break;
        case 21:
            // NT_VSTUP_DALSI -> eps
            cStack_pop(stack);
            break;
        case 22:
            // NT_VSTUP_KONEC -> T_EXPRESSION
            cStack_pop(stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 23:
            // NT_VSTUP_KONEC -> T_IDENT
            cStack_pop(stack);
            push_terminal(T_IDENT, stack);
            break;
        case 24:
            // NT_SLOZENY_PRIKAZ -> T_LCB NT_BLOK_PRIKAZU T_RCB
            cStack_pop(stack);
            push_terminal(T_RCB, stack);
            push_nonterminal(NT_BLOK_PRIKAZU, stack);
            push_terminal(T_LCB, stack);
            break;
        case 25:
            // NT_BLOK_PRIKAZU -> NT_PRIKAZ NT_BLOK_PRIKAZU
            push_nonterminal(NT_PRIKAZ, stack);
            break;
        case 26:
            // NT_BLOK_PRIKAZU -> eps
            cStack_pop(stack);
            break;
        case 27:
            // NT_PRIKAZ -> T_TYPE NT_DEFINICE_PROMENNA T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_DEFINICE_PROMENNA, stack);
            push_terminal(T_TYPE, stack);
            break;
        case 28:
            // NT_PRIKAZ -> T_EXPRESSION T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_terminal(T_EXPRESSION, stack);
        case 29:
            // NT_PRIKAZ -> T_IDENT NT_POUZITI T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_POUZITI, stack);
            push_terminal(T_IDENT, stack);
            break;
        case 30:
            // NT_PRIKAZ -> T_FIDENT NT_VOLANI_FUNKCE T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_VOLANI_FUNKCE, stack);
            push_terminal(T_FIDENT, stack);
            break;
        case 31:
            // NT_PRIKAZ -> T_RETURN NT_NAVRAT_KONEC T_SC
            cStack_pop(stack);
            push_terminal(T_SC, stack);
            push_nonterminal(NT_NAVRAT_KONEC, stack);
            push_terminal(T_RETURN, stack);
            break;
        case 32:
            // NT_PRIKAZ -> T_IF T_LRB T_EXPRESSION T_RRB NT_SLOZENY_PRIKAZ T_ELSE NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_ELSE, stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_RRB, stack);
            push_terminal(T_EXPRESSION, stack);
            push_terminal(T_LRB, stack);
            push_terminal(T_IF, stack);
            break;
        case 33:
            // NT_PRIKAZ -> T_WHILE T_LRB T_EXPRESSION T_RRB NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_terminal(T_RRB, stack);
            push_terminal(T_EXPRESSION, stack);
            push_terminal(T_LRB, stack);
            push_terminal(T_WHILE, stack);
            break;
        case 34:
            // NT_POUZITI -> NT_PRIRAZENI
            cStack_pop(stack);
            push_nonterminal(NT_PRIRAZENI, stack);
            break;
        case 35:
            // NT_POUZITI -> eps
            cStack_pop(stack);
            break;
        case 36:
            // NT_VOLANI_FUNKCE -> T_LRB NT_SEZNAM_VYRAZU T_RRB
            cStack_pop(stack);
            push_terminal(T_RRB, stack);
            push_nonterminal(NT_SEZNAM_VSTUPU, stack);
            push_terminal(T_LRB, stack);
            break;
        case 37:
            // NT_NAVRAT_KONEC -> T_EXPRESSION
            cStack_pop(stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 38:
            // NT_NAVRAT_KONEC -> T_IDENT
            cStack_pop(stack);
            push_terminal(T_IDENT, stack);
            break;
        case 39:
            // NT_NAVRAT_KONEC -> eps
            cStack_pop(stack);
            break;
        case 40:
            // NT_PRIRAZENI -> T_ASSIGN NT_PRAVA_STRANA
            cStack_pop(stack);
            push_nonterminal(NT_PRAVA_STRANA, stack);
            push_terminal(T_ASSIGN, stack);
            break;
        case 41:
            // NT_PRAVA_STRANA -> T_EXPRESSION
            cStack_pop(stack);
            push_terminal(T_EXPRESSION, stack);
            break;
        case 42:
            // NT_PRAVA_STRANA -> T_IDENT
            cStack_pop(stack);
            push_terminal(T_IDENT, stack);
        case 43:
            // NT_PRAVA_STRANA -> T_FIDENT NT_VOLANI_FUNKCE
            cStack_pop(stack);
            push_nonterminal(NT_VOLANI_FUNKCE, stack);
            push_terminal(T_FIDENT, stack);
            break;
        case 44:
            // NT_DATOVY_TYP -> T_VOID
            cStack_pop(stack);
            push_terminal(T_VOID, stack);
            break;
        case 45:
            // NT_DATOVY_TYP -> T_TYPE
            cStack_pop(stack);
            push_terminal(T_TYPE, stack);
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
        else if (strcmp(token->attr->str, "int") == 0 ||
            strcmp(token->attr->str, "double") == 0 ||
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
        terminal.type = T_LRB;
    }
    else if (token->type == PRAVA_KULATA_ZAVORKA) {
        terminal.type = T_RRB;
    }
    else if (token->type == LEVA_SLOZENA_ZAVORKA) {
        terminal.type = T_LCB;
    }
    else if (token->type == PRAVA_SLOZENA_ZAVORKA) {
        terminal.type = T_RCB;
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
    // We must decide whether this will be an expression terminal or ident or identf terminal
    else if (token->type == IDENTIFIKATOR ||
        token->type == PLNE_KVALIFIKOVANY_IDENTIFIKATOR) {
        archive = getNextToken(); // We have to use another token
        // identificator followed by operator is surely an expression
        if (archive->type == SCITANI ||
            archive->type == ODECITANI ||
            archive->type == NASOBENI ||
            archive->type == DELENI ||
            archive->type == MENSI ||
            archive->type == VETSI ||
            archive->type == ROVNO ||
            archive->type == NEROVNO ||
            archive->type == MENSI_NEBO_ROVNO ||
            archive->type == VETSI_NEBO_ROVNO) {
            terminal.type = T_EXPRESSION;
        }
        // identificator followed by left parenthesis is function identificator
        else if (archive->type == LEVA_KULATA_ZAVORKA) {
            terminal.type = T_FIDENT;
        }
        // it is single identificator, note that identificator alone is not an expression
        else {
            terminal.type = T_IDENT;
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
        #if SYNT_DEBUG == 1
            fprintf(stdout, "---------------------------------\n");
        #endif
        top = cStack_top(&stack);
        if (top.type == IT_ERROR) {
            #if SYNT_DEBUG == 1
                fprintf(stdout, "[SYNT_DEBUG] !!! Syntax error - Stack was empty???\n");
            #endif
            error(INTER_ERROR);
        }

        #if SYNT_DEBUG == 1
            char *debug_top, *debug_input;
            if (top.type == IT_TERMINAL)
                debug_top = TType_string[top.content.terminal.type];
            else if (top.type == IT_NTTYPE)
                debug_top = NTType_string[top.content.nttype];
            else
                debug_top = "ERROR - unknown type O_o";
            debug_input = TType_string[input.type];
            fprintf(stdout, "[SYNT_DEBUG] ~~~ LOOP: top = %s, input = %s\n", debug_top, debug_input);
        #endif

        // We have NT_DOLLAR on top -> success or fail
        if (top.type == IT_NTTYPE && top.content.nttype == NT_DOLLAR) {
            #if SYNT_DEBUG == 1
                fprintf(stdout, "[SYNT_DEBUG]   ~ T_EOF must be on input\n");
            #endif
            if (input.type == T_EOF) {
                return;
            }
            else {
                #if SYNT_DEBUG == 1
                    fprintf(stdout, "[SYNT_DEBUG] !!! Syntax error - NT_DOLLAR on top but no T_EOF on input\n");
                #endif
                error(SYNTA_ERROR);
            }
        }

        // We have terminal on top -> if it is the same as terminal from input, process
        if (top.type == IT_TERMINAL) {
            #if SYNT_DEBUG == 1
                fprintf(stdout, "[SYNT_DEBUG]   ~ Top must be same type like input\n");
            #endif
            if (top.content.terminal.type == input.type) {
                if (input.type == T_EXPRESSION) {
                    prec_analysis(input.token);
                }
                cStack_pop(&stack);
                input = getNextTerminal();
            }
            else {
                #if SYNT_DEBUG == 1
                    fprintf(stdout, "[SYNT_DEBUG] !!! Syntax error - Terminal on top not same like terminal on input\n");
                #endif
                error(SYNTA_ERROR);
            }
        }

        // We have non-terminal on top -> try to find and apply LL rule
        if (top.type == IT_NTTYPE) {
            #if SYNT_DEBUG == 1
                fprintf(stdout, "[SYNT_DEBUG]   ~ Try to find LL rule\n");
            #endif
            int rule = getRuleNumber(top.content.nttype, input.type);
            if (rule == -1) {
                #if SYNT_DEBUG == 1
                    fprintf(stdout, "[SYNT_DEBUG] !!! Syntax error - Rule not found\n");
                #endif
                error(SYNTA_ERROR);
            }
            else {
                applyRule(rule, &stack);
            }
        }

    } while (input.type != T_EOF);
}

