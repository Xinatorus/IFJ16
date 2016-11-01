/* ========================================================================== */
/* Jmena:   .......                                                           */
/* Soubor:  lex_anal.c                                                        */
/* Faze:    Lexikalni analyzator                                              */
/* Datum:   24.10.2016                                                        */
/* ========================================================================== */
#include "lex_anal.h"

/**
 * Klucove slova
 */
const char *klucoveSlova[17] =
{
    "boolean\0", "break\0", "class\0", "continue\0", "do\0", "if\0", "double\0",
    "else\0", "false\0", "for\0", "int\0", "true\0", "while\0", "return\0", 
    "String\0", "static\0", "void\0",
};

/**
 * Rezervovane slova
 */
const char *rezervovaneSlova[50] =
{
    "abstract\0", "continue\0", "for\0", "new\0", "switch\0", "assert\0", "default\0",
    "if\0", "package\0", "synchronized\0", "boolean\0", "do\0", "goto\0", "private\0",
    "this\0", "break\0", "double\0", "implements\0", "protected\0", "throw\0", "byte\0",
    "else\0", "import\0", "public\0", "throws\0", "case\0", "enum\0", "instanceof\0",
    "return\0", "transient\0", "catch\0", "extends\0", "int\0", "short\0", "try\0",
    "char\0", "final\0", "interface\0", "static\0", "void\0", "class\0", "finally\0",
    "long\0", "strictfp\0", "volatile\0", "const\0", "float\0", "native\0", "super\0", "while\0",
};


FILE* subor; // zdrojovy subor
int riadok;


Ttoken* getNextToken()
{

	int c;
	Ttoken* token = vytvorToken();

	while(1)
  {

		c = fgetc(subor);
		token->cisloRiadku=riadok;

		switch(token->type)
		{
			case INIT:
			// pociatocny stav

				if(c=='\n')
        {
					riadok++;
					token->cisloRiadku=riadok;
					token->type=INIT;
				}
				else if(isspace(c))
        {
				// ignoruje biele znaky
					token->type=INIT;
				}
				else if(c==EOF)
        {
				// hned narazi na koniec suboru
					token->type=END_OF_FILE;
					return token;
				}
				else if(c=='=')
        {
				// =, alebo ==
					token->type=ASSIGNMENT;
				}
				else if(c=='+')
        {
					token->type=ADD;
					return token;
				}
				else if(c=='-')
        {
					token->type=SUB;
					return token;
				}
				else if(c=='*')
        {
					token->type=MULTIPLICATION;
					return token;
				}
				else if(c=='/')
        {
				// /, //, alebo /*
					token->type=DIVISION;
				}
				else if(c=='<')
        {
				// <, << alebo <=
					token->type=LSS;
				}
				else if(c=='>')
        {
				// >, >> alebo >=
					token->type=GTR;
				}
				else if(c=='!')
        {
				// !=
					token->type=NOT_EQUAL;
				}
				else if(c==';')
        {
					token->type=SEMICLN;
					return token;
				}
				else if(c==',')
        {
					token->type=COMMA;
					return token;
				}
				else if(c=='(')
        {
					token->type=LEFT_BRACKET;
					return token;
				}
				else if(c==')')
        {
					token->type=RIGHT_BRACKET;
					return token;
				}
				else if(c=='[')
        {
					token->type=LEFT_SQUARE_BRACKET;
					return token;
				}
				else if(c==']')
        {
					token->type=RIGHT_SQUARE_BRACKET;
					return token;
				}
				else if(c=='{')
        {
					token->type=LEFT_CURLY_BRACKET;
					return token;
				}
				else if(c=='}')
        {
					token->type=RIGHT_CURLY_BRACKET;
					return token;
				}
				else if(c==34)
        {
				//  dvojite uvodzovky - "
					token->type=STRING_LITERAL;
				}
				else if(isalpha(c)||(c=='_') ||(c=='$'))
        {
				// identifikator, alebo klucove slovo
					addChar(token->attr,c);
					token->type=ID;
				}
				else if(isdigit(c)){
				// INT, double
					addChar(token->attr,c);
					token->type=INT;
				}
				else{
					token->type=LEX_ERROR;
					return token;
				}
			break;

			case ASSIGNMENT:

				if(c=='='){
					// ==
					token->type=EQUAL;
					return token;
				}
				else{
					// posunie sa v subore o 1 znak dozadu a vrati =
					fseek(subor,-1,SEEK_CUR);
					return token;
				}

			break;

			case DIVISION:

				if(c=='/'){
					//  //
					token->type=JED_RIAD_KOM;

				}
				else if(c=='*'){
					// /*
					token->type=VIAC_RIAD_KOM;

				}
				else{
					// posunie sa v subore o 1 znak dozadu a vrati /
					fseek(subor,-1,SEEK_CUR);
					return token;
				}

			break;

			case JED_RIAD_KOM:

				if(c=='\n')
        {
					// koniec komentu
					riadok++;
					token->cisloRiadku=riadok;
					token->type=INIT;
				}
				else if(c==EOF)
        {
					// koniec suboru => vrati EOF token
					token->type=END_OF_FILE;
					return token;
				}
				else
        {
					token->type=JED_RIAD_KOM;
				}

			break;

			case VIAC_RIAD_KOM:

				if(c=='*')
        {

					token->type=VIAC_RIAD_KOM_END;
				}
				else if(c==EOF){
					// koniec suboru => neukonceny koment, vrati chybu
					token->type=LEX_ERROR;
					fseek(subor,-1,SEEK_CUR);
					return token;
				}
				else
        {

					if(c=='\n'){
						riadok++;
						token->cisloRiadku=riadok;
					}

					token->type=VIAC_RIAD_KOM;
				}

			break;

			case VIAC_RIAD_KOM_END:

				if(c=='/'){
					// koniec komentara */
					token->type=INIT;
				}
				else if(c==EOF){
					// koniec suboru => neukonceny koment, vrati chybu
					token->type=LEX_ERROR;
					fseek(subor,-1,SEEK_CUR);
					return token;
				}
				else{
					// po * nenasleduje / => dalej cita znaky

					if(c=='\n'){
						riadok++;
						token->cisloRiadku=riadok;
					}

					token->type=VIAC_RIAD_KOM;
				}

			break;

			case LSS:

				if(c=='='){
					// <=
					token->type=LESS_OR_EQUAL;
					return token;
				}
				else if(c=='<'){
					// <<
					token->type=PRAVO;
					return token;
				}
				else{
					// posunie sa v subore o 1 znak dozadu a vrati <
					fseek(subor,-1,SEEK_CUR);
					return token;
				}

			break;

			case GTR:

				if(c=='='){
					// >=
					token->type=GREATER_OR_EQUAL;
					return token;
				}
				else if(c=='>'){
					// >>
					token->type=LAVO;
					return token;
				}
				else{
					// posunie sa v subore o 1 znak dozadu a vrati >
					fseek(subor,-1,SEEK_CUR);
					return token;
				}

			break;

			case NOT_EQUAL:

				if(c=='='){
					// !=
					token->type=NOT_EQUAL;
					return token;
				}
				else{
					// ziaden iny token sa nemoze zacinat ! => chyba
					fseek(subor,-1,SEEK_CUR);
					token->type=LEX_ERROR;
					return token;
				}

			break;

			case ID:

				if(isalpha(c)||(c=='_') || (c=='$')||isdigit(c))
                {
					// identifikator pokracuje
					addChar(token->attr,c);
					token->type=ID;
				}
				else
				{
					fseek(subor,-1,SEEK_CUR);
					token->type=iskeyWord(token->attr);
					return token;
				}
            //TO DO dokoncit identifikatory a Term
			break;

			case STRING_LITERAL:

				if((c>31)&&(c!=34)){
					// retazec pokracuje
					addChar(token->attr,c);
					token->type=STRING_LITERAL;
				}
				/*
				else if(escape sequence){

				}
				*/
				else if(c==34){
					// koniec retazca
					token->type=STRING_LITERAL;
					return token;
				}
				else{
					// znak s ASCII hodnotou mensou ako 31 bol zadany bez escape sekvencie
					token->type=LEX_ERROR;
					return token;
				}

			break;

			case INT:

				if(isdigit(c)){
					// pokracuje cislo
					addChar(token->attr,c);
					token->type=INT;
				}
				else if(c=='.'){
					// nasleduje desatinna cast
					addChar(token->attr,c);
					token->type=DBL_DOT;
				}
				else if((c=='e')||(c=='E')){
					// nasleduje exponent
					addChar(token->attr,c);
					token->type=DBL_EXPONENT;
				}
				else{
					// koniec cisla
					fseek(subor,-1,SEEK_CUR);
					token->type=INT;
					return token;
				}

			break;

			case DBL_DOT:

				if(isdigit(c)){
					// desatinna cast cisla
					addChar(token->attr,c);
					token->type=DBL_DOT;
				}
				else if((c=='e')||(c=='E')){
					// cislo s desatinnou castou aj exponentom
					addChar(token->attr,c);
					token->type=DBL_EXPONENT;
				}
				else{
					// koniec desatinneho cisla, vracia stav DBL
					fseek(subor,-1,SEEK_CUR);
					token->type=DBL;
					return token;
				}

			break;

			case DBL_EXPONENT:

				if((c=='+')||c=='-'){
					// ak je v exponente znamienko
					addChar(token->attr,c);
					token->type=DBL_EXPONENT_SIGNED;
				}
				else if(isdigit(c)){
					// cele cislo
					addChar(token->attr,c);
					token->type=DBL_EXPONENT;
				}
				else{
					fseek(subor,-1,SEEK_CUR);
					token->type=DBL;
					return token;
				}

			break;

			case DBL_EXPONENT_SIGNED:

				if(isdigit(c)){
					// po znamienku nasleduje cislo => OK
					addChar(token->attr,c);
					token->type=DBL_EXPONENT;
				}
				else{
					// po znamienku nejde cislo => chyba
					fseek(subor,-1,SEEK_CUR);
					token->type=LEX_ERROR;
					return token;
				}

			break;

			default:
			break;
		}

	}
}

TokenType najdiKlucoveSlovo(string* s)
{

	int j;

    // prejdeme klucove slova
    for (j = 0; j < 17; j++)
        if (!(strcmp(s->str, klucoveSlova[j])))
            return KLUC;

    // prejdeme prezervovane slova
    for (j = 0; j < 50; j++)
        if (!(strcmp(s->str, rezervovaneSlova[j])))
            return REZER;

		return ID;

}

int addChar(string* s,char c){ // prida char na koniec stringu
	char* new;
	if(!(new = (char *) realloc(s->str,s->length+2))){
		return 1;
	}
	else{
		s->str=new;
	}

	s->str[s->length]=c;
	s->str[s->length+1]='\0';
	s->length++;

	return 0;
}

int stringInit(string* s){

	s->str = (char *) malloc(sizeof(char));

	if(!s->str){
		return 1;
	}
	else{
		s->str[0]='\0';
		s->length=0;
		return 0;
	}
}

Ttoken* vytvorToken(){

	Ttoken* token;

	token = (Ttoken *) malloc(sizeof(Ttoken));
	token->attr = (string *)malloc(sizeof(string));
	token->type = INIT;

	stringInit(token->attr);

	return token;
}

int znicToken(Ttoken* token){

	free(token->attr->str);
	free(token->attr);
	free(token);

	return 0;
}

int loadSourceFile(char* file){
	subor=fopen(file,"r");

	riadok = 1;

	if (subor==NULL){
		return 1;
	}
	else{
		return 0;
	}
}

int closeSourceFile(){
	if(fclose(subor)){
		return 1;
	}
	else{
		return 0;
	}
}
