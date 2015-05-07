/*
 ============================================================================
 Name        : calculator.cpp
 Author      : 
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
/* Simple integer arithmetic calculator
 * according to the EBNF:
 * 
 * <exp> -> <term> { <addop> <term> }
 * <addop> -> + | -
 * <term> -> <factor> { <mulop> <factor> }
 * <mulop> -> *
 * <factor> -> { <exp> } | Number
 * 
 * Inputs a line of text from stdin
 * Ouputs "Error" or the result
 * */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char token; /* global token variable */

/* function prototypes for recursive calls */
int expression(void);
int term(void);
int factor(void);
void error(void) {
	fprintf(stderr, "Error\n");
	exit(1);
}
void match(char expectedToken) {
	if (token == expectedToken)
		token = getchar();
	else
		error();
}
int main(void) {
	int result;
	token = getchar();/* load token with first character for lookahead */

	result = expression();
	if (token=='\n')/* check for end of line */
		printf("Result = %d\n", result);
	else
		error(); /* extraneous chars on line */
	return 0;
	return EXIT_SUCCESS;
}

int expression(void) {
	int temp = term();
	while ((token == '+') || (token == '-')) {
		switch (token) {
		case '+':
			match('+');
			temp+=term();
			break;
		case '-':
			match('-');
			temp-=term();
			break;
		}
	}
	return temp;
}
int term(void) {
	int temp = factor();
	while (token=='*') {
		match('*');
		temp*=factor();
	}
	return temp;
}
int factor(void) {
	int temp;
	if (token=='(') {
		match('(');
		temp = expression();
		match(')');
	} else if (isdigit(token)) {
		ungetc(token, stdin);
		scanf("%d", &temp);
		token = getchar();
	} else
		error();
	return temp;
}
