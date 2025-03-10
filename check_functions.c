#include <stdio.h>
#include <string.h>
#include "lexer.h"

// Function to check for Keyword
int isKeyword(const char *str)
{
	int i = 0;
	while(keyword[i] != NULL)
	{
		if(!strcmp(keyword[i],str))
			return SUCCESS;
		i++;
	}
	return FAILURE;
}

// Function to check for Operator
int isOperator(const char ch)
{       
        int i = 0;
        while(operators[i] != '\0')
        {       
                if(operators[i++] == ch)
                        return SUCCESS;
        }       
        return FAILURE;
}

// Function to check for Symbols
int isSymbols(const char ch)
{
        int i = 0;
        while(symbols[i] != '\0')
        {
                if(symbols[i++] == ch)
                        return SUCCESS;
        }
        return FAILURE;
}

// Function to check for Number
int isNumber(char ch)
{
	if(ch >= 48 && ch <= 57)
		return SUCCESS;
	return FAILURE;
}

// Function to check for Functions
int isFunction(const char *str)
{
	int i = 0;
	while(function[i] != NULL)
	{
		if(!strcmp(function[i],str))
			return SUCCESS;
		i++;
	}
	return FAILURE;
}

// Function to check for Preprocessor Directive
int isPreDirective(const char *str)
{
	int i = 0;
	while(pre_directives[i] != NULL)
	{
		if(strcmp(pre_directives[i],str) == 0)
			return SUCCESS;
		i++;
	}
	return FAILURE;
}

// Function to check for Pointer Variable
int isPointer(char ch)
{
	if(ch == '*')
		return SUCCESS;
	return FAILURE;
}
