#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers\strings.h"

//vytvori kopii str na nove adrese, tu vraci
char *makeString(char *str) {
	//TODO neni potreba vlozit \0 ? 
	char *s = malloc(strlen(str) + 1);
	strcpy(s, str);
	return s;
}

//spojeni dvou retezcu/znaku
char *cat(char *s1, char *s2) {
	char *str = malloc(strlen(s1) + strlen(s2) + 1);

	strcpy(str, s1);
	strcat(str, s2);
	return str;
}

//TODO Vrati string reprezentaci non-string promenne
char *varToString(Data *var) {
	char *s;
	switch (var->type) {
		case t_int: 
			
			break;
		case t_double: 
			
			break;
		default: //?
			
			break;
	}

	return "var to string not implemented yet...";
}

char *intToString(int x) {
	//TODO int toString
}
char *doubleToString(double x) {
	//TODO double toString
}

char *getSubString(char *str, int index, int size) {

}

/* ----------------------------------------------------------------------------------- */
/* ------------------------------FCE LENGTH------------------------------------------- */
// vrati delku retezce zadaneho jedinym parametrem s
int length(char* s)
{
	// chybove hlaseni v pripade nuloveho znaku
	if (s == NULL)
	{
		fprintf(stderr, "stderr - length of string\n");
		return false;
	}

	// pruchod jednotlivych znaku a prepocet pocitadla znaku
	int pocet = 0;
	for (int i = 0; s[i] != '\0'; i++)
	{

		if (s[i] == '/')
		{
			i++;
		}

		pocet++;
	}

	// vraci pocet znkau retezce
	return pocet;
}

/* ----------------------------------------------------------------------------------- */
/* ------------------------------FCE COMPARE------------------------------------------ */
// porovna 2 zadane retezce s1 a s2 a vrati
// 0    ,kdyz se rovnaji
// 1    ,kdyz je s1 > s2
// -1   ,kdyz je s1 < s2

int compare(char *s1, char *s2)
{
	return (strcmp(s2, s2));
}
/* ----------------------------------------------------------------------------------- */