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
		//	s = intToString(var->value.v_int);
			break;
		case t_double: 
		//	s = intToString(var->value.v_double);
			break;
		default: //?
			break;
	}

	//printf("conv to %s\n", s);
	return "tohle vubec nefunguje";
}

char *intToString(int x) {
	char tmp[50];
	sprintf(tmp, "%d", x);
	printf("conv to %s\n", tmp);
	return tmp;
}
char *doubleToString(double x) {
	char tmp[50];
	sprintf(tmp,"%g",x);
	return tmp;
}

//vytvori pod retezec od indexu startindex o velikosti size
char *getSubString(char *str, int startindex, int size) {

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