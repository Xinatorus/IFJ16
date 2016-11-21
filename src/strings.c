#include "headers\strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//vytvori kopii str na nove adrese, tu vraci
char *makeString(char *str) {
	//TODO implementace makeString
	return 0;
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

}

char *intToString(int x) {
	//TODO int toString
}
char *doubleToString(double x) {
	//TODO double toString
}