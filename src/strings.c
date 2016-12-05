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

//Vrati string reprezentaci non-string promenne
char *varToString(Data var) {
	char *s;
	switch (var.type) {
		case t_int: 
			
			break;
		case t_double: 
			
			break;
		default: 
			
			break;
	}

	return s;
}

char *intToString(int x) {
	//TODO int toString
}
char *doubleToString(double x) {
	//TODO double toString
}

char *getSubString(char *str, int index, int size) {

}