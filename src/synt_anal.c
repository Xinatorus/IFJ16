#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers\synt_anal.h"

cQueue token_archive; // Queue to store pre-used tokens
cStack stack; // Main stack for syntax analysis to hold terminals, non-terminals & prec. symbols
Ttoken *token_list = NULL; // Token list, used for second pass
bool first_analysis = true; // Whether this is first pass (static declarations)

/* Semantic variables */
TsTree root; // Main symbol table leaf
int last_rule; // Last applied rule
char *current_class; // Actual class
char *current_func; // Actual function
char *dec_types; // Actual types (var type of return type of func + params)
char *dec_id; // Actual identificator (because insert itself happens AFTER ident token)
int var_static_index; // order of saved static var in class symbol table
int var_normal_index; // order of saved normal var in function symbol table

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

Ttoken *load_next_token() {
    Ttoken *token = NULL;
    /* Get tokens from lexical analysis */
    if (first_analysis) {
        token = getNextToken();
        /* First token in token_list */
        if (token_list == NULL) {
            token_list = token;
        }
        /* Add token to the end of token_list */
        else
        {
            Ttoken *iterated = token_list;
            while (iterated->next != NULL) {
                iterated = iterated->next;
            }
            iterated->next = token;
        }
    }
    /* Get tokens from token_list */
    else {
        token = token_list;
        /* Remove loaded token from token_list */
        if (token->next != NULL) { // In the end we always want to return EOF token
            token_list = token->next;
        }
    }

    return token;
}

int getRuleNumber(NTType nt, TType t) {

    #if SYNT_DEBUG == 1
        fprintf(stdout, "[SYNT_DEBUG #%d] getRuleNumber(%s, %s)\n", first_analysis ? 1 : 2, NTType_string[nt], TType_string[t]);
    #endif

    return synt_rules[nt][t];
}

void applyRule(int rule, cStack *stack) {
    if (stack == NULL) {
        return;
    }

    #if SYNT_DEBUG == 1
        fprintf(stdout, "[SYNT_DEBUG #%d] Applying rule #%d\n", first_analysis ? 1 : 2, rule);
    #endif
    
    last_rule = rule;
    // The reason for not automating this process is precedence analysis
    switch (rule) {
        case 1:
            // NT_PROGRAM -> NT_TRIDA NT_PROGRAM
            push_cstack_nonterminal(NT_TRIDA, stack);
            break;
        case 2:
            // NT_PROGRAM -> NT_DOLLAR
            cStack_pop(stack);
            push_cstack_nonterminal(NT_DOLLAR, stack);
            break;
        case 3:
            // NT_TRIDA -> T_CLASS T_IDENT T_LCB NT_SEZNAM_DEFINIC_STATIC T_RCB
            cStack_pop(stack);
            push_cstack_terminal(T_RCB, stack);
            push_cstack_nonterminal(NT_SEZNAM_DEFINIC_STATIC, stack);
            push_cstack_terminal(T_LCB, stack);
            push_cstack_terminal(T_IDENT, stack);
            push_cstack_terminal(T_CLASS, stack);
            break;
        case 4:
            // NT_SEZNAM_DEFINIC_STATIC -> T_STATIC NT_DATOVY_TYP NT_DEFINICE_STATIC NT_SEZNAM_DEFINIC_STATIC
            push_cstack_nonterminal(NT_DEFINICE_STATIC, stack);
            push_cstack_nonterminal(NT_DATOVY_TYP, stack);
            push_cstack_terminal(T_STATIC, stack);
            break;
        case 5:
            // NT_SEZNAM_DEFINIC_STATIC -> eps
            cStack_pop(stack);
            break;
        case 6:
            // NT_DEFINICE_STATIC -> NT_DEFINICE_FUNKCE
            cStack_pop(stack);
            push_cstack_nonterminal(NT_DEFINICE_FUNKCE, stack);
            break;
        case 7:
            // NT_DEFINICE_STATIC -> NT_DEFINICE_PROMENNA T_SC
            cStack_pop(stack);
            push_cstack_terminal(T_SC, stack);
            push_cstack_nonterminal(NT_DEFINICE_PROMENNA, stack);
            break;
        case 8:
            // NT_DEFINICE_PROMENNA -> T_IDENT NT_DEF_PROM_KONEC
            cStack_pop(stack);
            push_cstack_nonterminal(NT_DEF_PROM_KONEC, stack);
            push_cstack_terminal(T_IDENT, stack);
            break;
        case 9:
            // NT_DEF_PROM_KONEC -> NT_PRIRAZENI
            cStack_pop(stack);
            push_cstack_nonterminal(NT_PRIRAZENI, stack);
            break;
        case 10:
            // NT_DEF_PROM_KONEC -> eps
            cStack_pop(stack);
            break;
        case 11:
            // NT_DEFINICE_FUNKCE -> T_FIDENT T_LRB NT_SEZNAM_PARAMETRU T_RRB NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_cstack_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_cstack_terminal(T_RRB, stack);
            push_cstack_nonterminal(NT_SEZNAM_PARAMETRU, stack);
            push_cstack_terminal(T_LRB, stack);
            push_cstack_terminal(T_FIDENT, stack);
            break;
        case 12:
            // NT_SEZNAM_PARAMETRU -> NT_PARAMETR_PRVNI NT_PARAMETR_DALSI
            cStack_pop(stack);
            push_cstack_nonterminal(NT_PARAMETR_DALSI, stack);
            push_cstack_nonterminal(NT_PARAMETR_PRVNI, stack);
            break;
        case 13:
            // NT_SEZNAM_PARAMETRU -> eps
            cStack_pop(stack);
            break;
        case 14:
            // NT_PARAMETR_PRVNI -> T_TYPE T_IDENT
            cStack_pop(stack);
            push_cstack_terminal(T_IDENT, stack);
            push_cstack_terminal(T_TYPE, stack);
            break;
        case 15:
            // NT_PARAMETR_DALSI -> T_COMMA T_TYPE T_IDENT NT_PARAMETR_DALSI
            push_cstack_terminal(T_IDENT, stack);
            push_cstack_terminal(T_TYPE, stack);
            push_cstack_terminal(T_COMMA, stack);
            break;
        case 16:
            // NT_PARAMETR_DALSI -> eps
            cStack_pop(stack);
            break;
        case 17:
            // NT_SEZNAM_VSTUPU -> T_EXPRESSION NT_VSTUP_DALSI
            cStack_pop(stack);
            push_cstack_nonterminal(NT_VSTUP_DALSI, stack);
            push_cstack_terminal(T_EXPRESSION, stack);
            break;
        case 18:
            // NT_SEZNAM_VSTUPU -> T_IDENT NT_VSTUP_DALSI
            cStack_pop(stack);
            push_cstack_nonterminal(NT_VSTUP_DALSI, stack);
            push_cstack_terminal(T_IDENT, stack);
            break;
        case 19:
            // NT_SEZNAM_VSTUPU -> eps
            cStack_pop(stack);
            break;
        case 20:
            // NT_VSTUP_DALSI -> T_COMMA NT_VSTUP_KONEC
            cStack_pop(stack);
            push_cstack_nonterminal(NT_VSTUP_KONEC, stack);
            push_cstack_terminal(T_COMMA, stack);
            break;
        case 21:
            // NT_VSTUP_DALSI -> eps
            cStack_pop(stack);
            break;
        case 22:
            // NT_VSTUP_KONEC -> T_EXPRESSION NT_VSTUP_DALSI
            cStack_pop(stack);
            push_cstack_nonterminal(NT_VSTUP_DALSI, stack);
            push_cstack_terminal(T_EXPRESSION, stack);
            break;
        case 23:
            // NT_VSTUP_KONEC -> T_IDENT NT_VSTUP_DALSI
            cStack_pop(stack);
            push_cstack_nonterminal(NT_VSTUP_DALSI, stack);
            push_cstack_terminal(T_IDENT, stack);
            break;
        case 24:
            // NT_SLOZENY_PRIKAZ -> T_LCB NT_BLOK_PRIKAZU T_RCB
            cStack_pop(stack);
            push_cstack_terminal(T_RCB, stack);
            push_cstack_nonterminal(NT_BLOK_PRIKAZU, stack);
            push_cstack_terminal(T_LCB, stack);
            break;
        case 25:
            // NT_BLOK_PRIKAZU -> NT_PRIKAZ NT_BLOK_PRIKAZU
            push_cstack_nonterminal(NT_PRIKAZ, stack);
            break;
        case 26:
            // NT_BLOK_PRIKAZU -> eps
            cStack_pop(stack);
            break;
        case 27:
            // NT_PRIKAZ -> T_TYPE NT_DEFINICE_PROMENNA T_SC
            cStack_pop(stack);
            push_cstack_terminal(T_SC, stack);
            push_cstack_nonterminal(NT_DEFINICE_PROMENNA, stack);
            push_cstack_terminal(T_TYPE, stack);
            break;
        case 28:
            // NT_PRIKAZ -> T_EXPRESSION T_SC
            cStack_pop(stack);
            push_cstack_terminal(T_SC, stack);
            push_cstack_terminal(T_EXPRESSION, stack);
        case 29:
            // NT_PRIKAZ -> T_IDENT NT_POUZITI T_SC
            cStack_pop(stack);
            push_cstack_terminal(T_SC, stack);
            push_cstack_nonterminal(NT_POUZITI, stack);
            push_cstack_terminal(T_IDENT, stack);
            break;
        case 30:
            // NT_PRIKAZ -> T_FIDENT NT_VOLANI_FUNKCE T_SC
            cStack_pop(stack);
            push_cstack_terminal(T_SC, stack);
            push_cstack_nonterminal(NT_VOLANI_FUNKCE, stack);
            push_cstack_terminal(T_FIDENT, stack);
            break;
        case 31:
            // NT_PRIKAZ -> T_RETURN NT_NAVRAT_KONEC T_SC
            cStack_pop(stack);
            push_cstack_terminal(T_SC, stack);
            push_cstack_nonterminal(NT_NAVRAT_KONEC, stack);
            push_cstack_terminal(T_RETURN, stack);
            break;
        case 32:
            // NT_PRIKAZ -> T_IF T_LRB T_EXPRESSION T_RRB NT_SLOZENY_PRIKAZ T_ELSE NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_cstack_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_cstack_terminal(T_ELSE, stack);
            push_cstack_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_cstack_terminal(T_RRB, stack);
            push_cstack_terminal(T_EXPRESSION, stack);
            push_cstack_terminal(T_LRB, stack);
            push_cstack_terminal(T_IF, stack);
            break;
        case 33:
            // NT_PRIKAZ -> T_WHILE T_LRB T_EXPRESSION T_RRB NT_SLOZENY_PRIKAZ
            cStack_pop(stack);
            push_cstack_nonterminal(NT_SLOZENY_PRIKAZ, stack);
            push_cstack_terminal(T_RRB, stack);
            push_cstack_terminal(T_EXPRESSION, stack);
            push_cstack_terminal(T_LRB, stack);
            push_cstack_terminal(T_WHILE, stack);
            break;
        case 34:
            // NT_POUZITI -> NT_PRIRAZENI
            cStack_pop(stack);
            push_cstack_nonterminal(NT_PRIRAZENI, stack);
            break;
        case 35:
            // NT_POUZITI -> eps
            cStack_pop(stack);
            break;
        case 36:
            // NT_VOLANI_FUNKCE -> T_LRB NT_SEZNAM_VYRAZU T_RRB
            cStack_pop(stack);
            push_cstack_terminal(T_RRB, stack);
            push_cstack_nonterminal(NT_SEZNAM_VSTUPU, stack);
            push_cstack_terminal(T_LRB, stack);
            break;
        case 37:
            // NT_NAVRAT_KONEC -> T_EXPRESSION
            cStack_pop(stack);
            push_cstack_terminal(T_EXPRESSION, stack);
            break;
        case 38:
            // NT_NAVRAT_KONEC -> T_IDENT
            cStack_pop(stack);
            push_cstack_terminal(T_IDENT, stack);
            break;
        case 39:
            // NT_NAVRAT_KONEC -> eps
            cStack_pop(stack);
            break;
        case 40:
            // NT_PRIRAZENI -> T_ASSIGN NT_PRAVA_STRANA
            cStack_pop(stack);
            push_cstack_nonterminal(NT_PRAVA_STRANA, stack);
            push_cstack_terminal(T_ASSIGN, stack);
            break;
        case 41:
            // NT_PRAVA_STRANA -> T_EXPRESSION
            cStack_pop(stack);
            push_cstack_terminal(T_EXPRESSION, stack);
            break;
        case 42:
            // NT_PRAVA_STRANA -> T_IDENT
            cStack_pop(stack);
            push_cstack_terminal(T_IDENT, stack);
            break;
        case 43:
            // NT_PRAVA_STRANA -> T_FIDENT NT_VOLANI_FUNKCE
            cStack_pop(stack);
            push_cstack_nonterminal(NT_VOLANI_FUNKCE, stack);
            push_cstack_terminal(T_FIDENT, stack);
            break;
        case 44:
            // NT_DATOVY_TYP -> T_VOID
            cStack_pop(stack);
            push_cstack_terminal(T_VOID, stack);
            break;
        case 45:
            // NT_DATOVY_TYP -> T_TYPE
            cStack_pop(stack);
            push_cstack_terminal(T_TYPE, stack);
            break;
        default:
            break;
    }
}

Terminal getNextTerminal() {
    Ttoken *token = NULL; // Token to work with
    Terminal terminal; // Terminal to return

    #if SYNT_DEBUG == 1
        fprintf(stdout, "[SYNT_DEBUG #%d] getNextTerminal()\n", first_analysis ? 1 : 2);
    #endif

    // Something is left in token archive, we must use that
    if (!cQueue_isempty(&token_archive)) {
        token = cQueue_first(&token_archive).content.token;
        #if SYNT_DEBUG == 1
            fprintf(stdout, "[SYNT_DEBUG #%d]  -> get from token archive (TA %d->", first_analysis ? 1 : 2, token_archive.size);
        #endif
        cQueue_pop(&token_archive);
        #if SYNT_DEBUG == 1
            fprintf(stdout, "%d)\n", token_archive.size);
        #endif
    }
    else {
        #if SYNT_DEBUG == 1
            fprintf(stdout, "[SYNT_DEBUG #%d]  -> get from load_next_token()\n", first_analysis ? 1 : 2);
        #endif
        token = load_next_token();
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
        Ttoken *following = load_next_token(); // We have to use another token
        cItem toinsert;
        toinsert.content.token = following;
        toinsert.type = IT_TOKEN;
        #if SYNT_DEBUG == 1
            fprintf(stdout, "[SYNT_DEBUG #%d]  -> Using another token! (TA %d->", first_analysis ? 1 : 2, token_archive.size);
        #endif
        cQueue_insert(&token_archive, toinsert);
        #if SYNT_DEBUG == 1
            fprintf(stdout, "%d)\n", token_archive.size);
        #endif
        // identificator followed by operator is surely an expression
        if (following->type == SCITANI ||
            following->type == ODECITANI ||
            following->type == NASOBENI ||
            following->type == DELENI ||
            following->type == MENSI ||
            following->type == VETSI ||
            following->type == ROVNO ||
            following->type == NEROVNO ||
            following->type == MENSI_NEBO_ROVNO ||
            following->type == VETSI_NEBO_ROVNO) {
            terminal.type = T_EXPRESSION;
        }
        // identificator followed by left parenthesis is function identificator
        else if (following->type == LEVA_KULATA_ZAVORKA) {
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

void push_cstack_terminal(TType type, cStack *stack) {
    cItem item;
    Terminal terminal;
    terminal.token = NULL;
    terminal.type = type;
    item.type = IT_TERMINAL;
    item.content.terminal = terminal;
    if (!cStack_push(stack, item)) {
        error(ERR_INTER);
    }
}

void push_cstack_nonterminal(NTType type, cStack *stack) {
    cItem item;
    item.type = IT_NTTYPE;
    item.content.nttype = type;
    if (!cStack_push(stack, item)) {
        error(ERR_INTER);
    }
}

void execute() {

    /* SEMANTIC ACTIONS IN FIRST PASS
        If fist pass is executed,
        only classes & static vars + functions are saved
    */

    #if SYNT_DEBUG == 1
    fprintf(stdout, "---------------------------------\n");
    if (first_analysis) {
        token_list = NULL;
        fprintf(stdout, "[SYNT_DEBUG #%d] FIRST Syntax analysis started\n", first_analysis ? 1 : 2);
    }
    else
        fprintf(stdout, "[SYNT_DEBUG #%d] SECOND Syntax analysis started\n", first_analysis ? 1 : 2);
    fprintf(stdout, "---------------------------------\n");
    #endif

    last_rule = -1;
    current_class = makeString("");
    current_func = makeString("");
    dec_types = makeString("");
    dec_id = makeString("");
    cStack_init(&stack, 50);
    cQueue_init(&token_archive);

    if (first_analysis) {
        /* @SEM - Create symbol table for default if16 class */
        #if SEM_DEBUG == 1
        fprintf(stdout, "\t@ Declaring default ifj16 class\n");
        #endif
        tsTreeInit(&root);
        HashTable ht_ifj16 = createHashTable(HASH_TABLE_SIZE);
        tsAdd(&root, "ifj16", 0, NULL, ht_ifj16);
        addToHashTable(ht_ifj16, "ifj16.readInt", "FI", true, 0);
        addToHashTable(ht_ifj16, "ifj16.readString", "FS", true, 0);
        addToHashTable(ht_ifj16, "ifj16.print", "FVS", true, 0);
        addToHashTable(ht_ifj16, "ifj16.length", "FIS", true, 0);
        addToHashTable(ht_ifj16, "ifj16.substr", "FSSIN", true, 0);
        addToHashTable(ht_ifj16, "ifj16.compare", "FISS", true, 0);
        addToHashTable(ht_ifj16, "ifj16.find", "FISS", true, 0);
        addToHashTable(ht_ifj16, "ifj16.sort", "FSS", true, 0);
    }

    /* First step - push NT_DOLLAR (NT version of EOF) and NT_PROGRAM to stack */
    push_cstack_nonterminal(NT_DOLLAR, &stack);
    push_cstack_nonterminal(NT_PROGRAM, &stack);

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
                fprintf(stdout, "[SYNT_DEBUG #%d] !!! Syntax error - Stack was empty???\n", first_analysis ? 1 : 2);
            #endif
            error(ERR_INTER);
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
            fprintf(stdout, "[SYNT_DEBUG #%d] ~~~ LOOP: top = %s, input = %s\n", first_analysis ? 1 : 2, debug_top, debug_input);
        #endif

        // We have NT_DOLLAR on top -> success or fail
        if (top.type == IT_NTTYPE && top.content.nttype == NT_DOLLAR) {
            #if SYNT_DEBUG == 1
                fprintf(stdout, "[SYNT_DEBUG #%d]   ~ T_EOF must be on input\n", first_analysis ? 1 : 2);
            #endif
            if (input.type == T_EOF) {
                return;
            }
            else {
                #if SYNT_DEBUG == 1
                    fprintf(stdout, "[SYNT_DEBUG #%d] !!! Syntax error - NT_DOLLAR on top but no T_EOF on input\n", first_analysis ? 1 : 2);
                #endif
                error(ERR_SYNT);
            }
        }

        // We have terminal on top -> if it is the same as terminal from input, process
        else if (top.type == IT_TERMINAL) {
            #if SYNT_DEBUG == 1
                fprintf(stdout, "[SYNT_DEBUG #%d]   ~ Top must be same type as input type\n", first_analysis ? 1 : 2);
            #endif
            if (top.content.terminal.type == input.type) {
                if (input.type == T_IDENT) {
                    if (last_rule == 3) {
                        /* @SEM1 - Declaring class */
                        if (first_analysis) {
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ User is declaring class %s\n", input.token->attr->str);
                            #endif
                            if (get_declared_class(input.token->attr->str) != NULL) {
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ Class %s is already declared!\n", input.token->attr->str);
                                #endif
                                error(ERR_SEM_DEF);
                            }
                            else {
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ Declaring class %s\n", input.token->attr->str);
                                #endif
                                tsAdd(&root, input.token->attr->str, 0, NULL, createHashTable(HASH_TABLE_SIZE));
                            }
                        }
                        /* @SEM12 - Entering class */
                        #if SEM_DEBUG == 1
                            fprintf(stdout, "\t@ Entering class %s\n", input.token->attr->str);
                        #endif
                        current_class = makeString(input.token->attr->str);
                        var_static_index = 0;
                    }
                    else if (last_rule == 8) {
                        /* @SEM1 - Declaring static variable */
                        if (strlen(current_func) == 0) {
                            if (first_analysis) {
                                char *full_name = cat(cat(current_class, "."), input.token->attr->str);
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ User is declaring static variable %s\n", full_name);
                                #endif
                                TsTree class_tree = get_declared_class(current_class);
                                if (searchInHashTable(class_tree->ts, full_name) != NULL) {
                                    #if SEM_DEBUG == 1
                                        fprintf(stdout, "\t@ Static variable %s is already declared!\n", full_name);
                                    #endif
                                    error(ERR_SEM_DEF);
                                }
                                else {
                                    #if SEM_DEBUG == 1
                                        fprintf(stdout, "\t@ Declaring static variable %s of type %s\n", full_name, dec_types);
                                    #endif
                                    addToHashTable(class_tree->ts, full_name, cat("V", dec_types), 0, var_static_index++);
                                }
                            }
                        }
                        /* @SEM2 - Declaring normal variable */
                        else {
                            if (!first_analysis) {
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ User is declaring normal variable %s in function %s\n", input.token->attr->str, current_func);
                                #endif
                                TsTree func_tree = get_declared_function(current_func, NULL);
                                if (searchInHashTable(func_tree->ts, input.token->attr->str) != NULL) {
                                    #if SEM_DEBUG == 1
                                        fprintf(stdout, "\t@ Normal variable %s in function %s is already declared!\n", input.token->attr->str, current_func);
                                    #endif
                                    error(ERR_SEM_DEF);
                                }
                                else {
                                    #if SEM_DEBUG == 1
                                        fprintf(stdout, "\t@ Declaring normal variable %s of type %s in function %s\n", input.token->attr->str, dec_types, current_func);
                                    #endif
                                    addToHashTable(func_tree->ts, input.token->attr->str, cat("V", dec_types), 0, var_normal_index++);
                                }
                            }
                        }
                    }
                    /* @SEM2 - Declaring normal variables (parameters) */
                    else if (last_rule == 14 || last_rule == 15) {
                        if (!first_analysis) {
                            char *full_name = cat(cat(current_class, "."), dec_id);
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ User is declaring normal variable (parameter) %s of function %s\n", input.token->attr->str, full_name);
                            #endif
                            TsTree func_tree = get_declared_function(full_name, NULL);
                            if (searchInHashTable(func_tree->ts, input.token->attr->str) != NULL) {
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ Normal variable (parameter) %s of function %s is already declared!\n", input.token->attr->str, full_name);
                                #endif
                                error(ERR_SEM_DEF);
                            }
                            else {
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ Declaring normal variable (parameter) %s of type %s in function %s\n", input.token->attr->str, dec_types, full_name);
                                #endif
                                addToHashTable(func_tree->ts, input.token->attr->str, cat("V", dec_types), 0, var_normal_index++);
                            }
                        }
                    }
                }
                else if (input.type == T_FIDENT) {
                    /* @SEM12 - Save function identificator for later use */
                    if (last_rule == 11) {
                        #if SEM_DEBUG == 1
                        fprintf(stdout, "\t@ Saving function identificator %s for later use\n", input.token->attr->str);
                        #endif
                        dec_id = makeString(input.token->attr->str);
                    }
                }
                else if (input.type == T_RRB) {
                    if (last_rule == 16 || last_rule == 13) {
                        char *full_name = cat(cat(current_class, "."), dec_id);
                        /* @SEM1 - Declaring function */
                        if (first_analysis) {
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ User is declaring static function %s\n", full_name);
                            #endif
                            if (get_declared_function(full_name, NULL) != NULL) {
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ Static function %s is already declared!\n", full_name);
                                #endif
                                error(ERR_SEM_DEF);
                            }
                            else {
                                #if SEM_DEBUG == 1
                                    fprintf(stdout, "\t@ Declaring static function %s with types %s\n", full_name, dec_types);
                                #endif
                                HashTable ht = createHashTable(HASH_TABLE_SIZE);
                                tsAdd(&root, full_name, 0, NULL, ht);
                                addToHashTable(ht, full_name, cat("F", dec_types), 0, 0);
                            }
                        }
                        /* @SEM12 - Entering function */
                        #if SEM_DEBUG == 1
                            fprintf(stdout, "\t@ Entering static function %s\n", full_name);
                        #endif
                        current_func = makeString(full_name);
                        var_normal_index = 0;
                    }
                }
                else if (input.type == T_RCB) {
                    /* @SEM12 - Leaving class */
                    if (last_rule == 5) {
                        #if SEM_DEBUG == 1
                            fprintf(stdout, "\t@ Leaving class %s\n", current_class);
                        #endif
                        current_class = makeString("");
                    }
                    /* @SEM12 - Leaving function */
                    if (last_rule == 26) {
                        #if SEM_DEBUG == 1
                            fprintf(stdout, "\t@ Leaving static function %s\n", current_func);
                        #endif
                        current_func = makeString("");
                    }
                }
                else if (input.type == T_TYPE) {
                    bool save_type = false;
                    /* @SEM12 - Save first primitive type of static func/var for later use */
                    if (last_rule == 45 || last_rule == 27) {
                        #if SEM_DEBUG == 1
                            fprintf(stdout, "\t@ Saving first type %s for later use\n", input.token->attr->str);
                        #endif
                        dec_types = makeString("");
                        save_type = true;
                    }
                    if (first_analysis) {
                        /* @SEM1 - Save first parameter type of static func for later use */
                        if (last_rule == 14) {
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ Saving first static function parameter type %s for later use\n", input.token->attr->str);
                            #endif
                            save_type = true;
                        }
                        /* @SEM1 - Save another parameter type of static func for later use */
                        else if (last_rule == 15) {
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ Saving another static function parameter type %s for later use\n", input.token->attr->str);
                            #endif
                            save_type = true;
                        }
                    }
                    else {
                        /* @SEM2 - Save parameter type for later use */
                        if (last_rule == 14 || last_rule == 15) {
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ Saving normal variable (parameter) type %s for later use\n", input.token->attr->str);
                            #endif
                            dec_types = makeString("");
                            save_type = true;
                        }
                    }
                    if (save_type) {
                        if (strcmp(input.token->attr->str, "int") == 0)
                            dec_types = cat(dec_types, "I");
                        else if (strcmp(input.token->attr->str, "double") == 0)
                            dec_types = cat(dec_types, "D");
                        else if (strcmp(input.token->attr->str, "String") == 0)
                            dec_types = cat(dec_types, "S");
                        #if SEM_DEBUG == 1
                            fprintf(stdout, "\t@ (dec_types is now: %s)\n", dec_types);
                        #endif
                    }
                }
                else if (input.type == T_VOID) {
                    /* @SEM1 - Save first void type of static func/var for later use */
                    if (first_analysis) {
                        if (last_rule == 44) {
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ Saving first static type %s for later use\n", input.token->attr->str);
                            #endif
                            dec_types = makeString("V");
                            #if SEM_DEBUG == 1
                                fprintf(stdout, "\t@ (dec_types is now: %s)\n", dec_types);
                            #endif
                        }
                    }
                }
                if (input.type == T_EXPRESSION) {
                    #if SYNT_DEBUG == 1
                        fprintf(stdout, "[SYNT_DEBUG #%d] ~~~~ > Calling precedence analysis... < ~~~~\n", first_analysis ? 1 : 2);
                    #endif
                    prec_analysis(input.token);
                }
                else {
                    cStack_pop(&stack);
                }
                input = getNextTerminal();
            }
            else {
                #if SYNT_DEBUG == 1
                    fprintf(stdout, "[SYNT_DEBUG #%d] !!! Syntax error - Terminal on top not same like terminal on input\n", first_analysis ? 1 : 2);
                #endif
                error(ERR_SYNT);
            }
        }

        // We have non-terminal on top -> try to find and apply LL rule
        else if (top.type == IT_NTTYPE) {
            #if SYNT_DEBUG == 1
                fprintf(stdout, "[SYNT_DEBUG #%d]   ~ Try to find LL rule\n", first_analysis ? 1 : 2);
            #endif
            int rule = getRuleNumber(top.content.nttype, input.type);
            if (rule == -1) {
                #if SYNT_DEBUG == 1
                    fprintf(stdout, "[SYNT_DEBUG #%d] !!! Syntax error - Rule not found\n", first_analysis ? 1 : 2);
                #endif
                error(ERR_SYNT);
            }
            else {
                applyRule(rule, &stack);
            }
        }

    } while (input.type != T_EOF);

    #if SYNT_DEBUG == 1
        fprintf(stdout, "---------------------------------\n");
        if (first_analysis)
            fprintf(stdout, "[SYNT_DEBUG #%d] FIRST Syntax analysis finished\n", first_analysis ? 1 : 2);
        else
            fprintf(stdout, "[SYNT_DEBUG #%d] SECOND Syntax analysis finished\n", first_analysis ? 1 : 2);
        fprintf(stdout, "---------------------------------\n");
    #endif

    cStack_free(&stack);
    cQueue_free(&token_archive);

    if (first_analysis) {
        /* @SEM1 - Check for class main & function run presence & check correct types */
        #if SEM_DEBUG == 1
            fprintf(stdout, "\t@ Checking whether class main exists\n");
        #endif
        if (get_declared_class("main") == NULL) {
            #if SEM_DEBUG == 1
                fprintf(stdout, "\t@ Class main not declared!\n");
            #endif
            error(3);
        }
        #if SEM_DEBUG == 1
            fprintf(stdout, "\t@ Checking whether function main.run exists\n");
        #endif
        TsTree main_run = get_declared_function("main.run", NULL);
        if (main_run == NULL) {
            #if SEM_DEBUG == 1
                fprintf(stdout, "\t@ Function main.run not declared!\n");
            #endif
            error(3);
        }
        #if SEM_DEBUG == 1
            fprintf(stdout, "\t@ Checking whether function main.run is void without params\n");
        #endif
        if (strcmp(searchInHashTable(main_run->ts, "main.run")->type, "FV") != 0) {
            #if SEM_DEBUG == 1
                fprintf(stdout, "\t@ Function main.run has incorrect types!\n");
            #endif
            error(3);
        }

        first_analysis = false;
        execute();
    }
}

TsTree get_declared_class(char *name) {
    return tsFind(root, name);
}

TsTree get_declared_function(char *name, char *p_class) {
    /* Full identifier - definitely static */
    if (strchr(name, '.') != NULL) {
        return tsFind(root, name);
    }
    /* Short identifier - look into class */
    else {
        return tsFind(root, cat(cat(p_class, "."), name));
    }
}

HashTable get_declared_variable(char *name, char *p_class, char *p_function) {
    /* Full identifier - definitely static */
    if (strchr(name, '.') != NULL) {
        return searchInHashTable(tsFind(root, explodeFullIdentifier(name, true))->ts, explodeFullIdentifier(name, false));
    }
    /* Short identifier - look into function and then into class */
    else {
        HashTable returned = NULL;
        /* Search in function */
        if (strchr(p_function, '.') != NULL) { // Long function identifier
            returned = searchInHashTable(tsFind(root, p_function)->ts, name);
        }
        else { // Short function identifier
            returned = searchInHashTable(tsFind(root, cat(cat(p_class, "."), p_function))->ts, name);
        }
        /* Search in class */
        if (returned == NULL) {
            returned = searchInHashTable(tsFind(root, p_class)->ts, name);
        }

        return returned;
    }
}
