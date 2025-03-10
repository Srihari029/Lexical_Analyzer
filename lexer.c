#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

/* Initialize Lexical Analyser */
int initializeLexer(const char *filename)
{
	char *c;
	c = strstr(filename,".c");
        if((c != NULL) && (strcmp(c,".c") == 0))
        {
		printf("INFO : File extension valid\n");
	}
	else
	{
		printf("INFO : File extension invalid\n");
		printf("Usage : ./a.out  <file.c>[C file] \n");
		return FAILURE;
	}
	// Open file in read mode
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
	{
		printf("INFO : Open Failed !\n");
		return FAILURE;
	}
	else
		printf("INFO : Open Success !\n");
	fseek(fp,0,SEEK_END);
	// Check file is not empty
	if(!ftell(fp))
	{
		printf("INFO : File Empty !\n");
                return FAILURE;
	}
	rewind(fp);
	return SUCCESS;
}

/* Lexer */
int Lexer(const char* filename)
{
	char ch,buffer[MAX_TOKEN_SIZE];
	FILE *fp = fopen(filename,"r"); // Open file in read mode
	if(fp == NULL)
        {
                printf("INFO : Open Failed !\n");
                return FAILURE;
        }
	while((ch = getc(fp)) != EOF)
	{
		int i = 0;
		if(ch == ' ' || ch == '\n')
		       continue;
		// Check for Preprocessor Directive
		else if(ch == '#')
		{
			i = 0;
			buffer[i++] = ch;
			while((ch = fgetc(fp)) != EOF && (ch != ' '))
			{
				buffer[i++] = ch;
			}
			buffer[i] = '\0';
			fseek(fp,-1,SEEK_CUR);
			if(isPreDirective(buffer) == SUCCESS)
				printf("Preprocessor Directive   : %s\n",buffer);
			else
				printf("%s : Unknown Preprocessor Directive (Compiler error)!\n",buffer);
		}
		// Check for Number
		else if(isNumber(ch))
		{
			buffer[i++] = ch;
			while(((ch = fgetc(fp)) != EOF) && (isNumber(ch) || ch == '.'))
			{
				buffer[i++] = ch;
			}
			buffer[i] = '\0';
			fseek(fp,-1,SEEK_CUR);
			printf("Numeric Constant         : %s\n",buffer);
		}
		// Character
		else if(ch == '\'')
		{
			int single_flag = 1;
			int char_count = 0;
			buffer[i++] = ch;
			while((ch = fgetc(fp)) != '\n')
			{
				buffer[i++] = ch;
				if(ch == '\'') // check for closed single quotes
				{
					single_flag = 2;
					break;
				}
				char_count++;
			}
			buffer[i] = '\0';
			if(char_count != 1)
				printf("%s : Invalid Character constant (Compiler error)!\n",buffer);
			else if(single_flag != 2)
				printf("%s : Invalid Character constant. Missing closed quotes (Compiler error)!\n",buffer);
			else
				printf("Character constant       : %s\n",buffer);
		}
		// Strings
		else if(ch == '"')
		{
			int double_flag = 1;
			buffer[i++] = ch;
			while((ch = fgetc(fp)) != EOF)
			{
				buffer[i++] = ch;
				if(ch == '"')
				{
					double_flag = 2;
					break;
				}
			}
			buffer[i] = '\0';
			if(double_flag != 2)
                                printf("%s : Invalid String literal. Missing closed quotes (Compiler error)!\n",buffer);
                        else
                                printf("String literal           : %s\n",buffer);
		}
		// Words
		else if(isalpha(ch))
		{
			i = 0;
			buffer[i++] = ch;
			while((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
			{
				buffer[i++] = ch;
			}
			buffer[i] = '\0';
			// Keyword
			if(isKeyword(buffer) == SUCCESS)
				printf("Keyword                  : %s\n",buffer);
			// Built-in Functions
			else if(isFunction(buffer) == SUCCESS)
				printf("Function                 : %s\n",buffer);
			else
				printf("Identifier / Variable    : %s\n",buffer);
		}
		// Pointer
		else if(isPointer(ch))
		{
			buffer[i++] = ch;
			while((ch = fgetc(fp)) != EOF && (ch != ' '))
			{
				if(ch == '(' || ch == ')')
					break;
				buffer[i++] = ch;
			}
			buffer[i] = '\0';
			printf("Pointer variable         : %s\n",buffer);
		}
		// Comments / Operator
		else if(ch == '/')
		{
			buffer[i++] = ch;
			// Single line comment
			if((ch = fgetc(fp)) == '/')
			{
				buffer[i++] = ch;
				while((ch = fgetc(fp)) != '\n')
					buffer[i++] = ch;
				buffer[i] = '\0';
				printf("Single-line comment      : %s\n",buffer);
			}
			// Multiline comment
			else if(ch == '*')
			{
				buffer[i++] = ch;
				int cls_flag = 1;
				while(cls_flag)
				{
					while((ch = fgetc(fp)) != '*')
						buffer[i++] = ch;
					buffer[i++] = ch;
					if((ch = fgetc(fp)) == '/')
					{
						cls_flag = 0;
						buffer[i++] = ch;
						buffer[i] = '\0';
						printf("Multiple-line comment    : %s\n",buffer);
					}
					else
					{
						buffer[i++] = ch;
					}
				}
			}
			else
			{
				fseek(fp,-1,SEEK_CUR);
				printf("Operator                 : %c\n",buffer[0]);
			}
		}
		// Operator
		else if(isOperator(ch))
			printf("Operator                 : %c\n",ch);
		// Symbol
		else if(isSymbols(ch))
			printf("Symbol                   : %c\n",ch);
		// Comma
		else if(ch == ',')
			printf("Comma                    : %c\n",ch);
		// Semicolon indicates end of statement
		else if(ch == ';')
			printf("End of Statement         : %c\n",ch);
			
	}
	printf("\n");
	return SUCCESS;	
}

