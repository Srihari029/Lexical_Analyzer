#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 20
#define MAX_TOKEN_SIZE 100

#define SUCCESS 1
#define FAILURE 0


// Indentifiers, Keyword, Symbols, Operators
static char *function[] = {"printf","scanf","fprintf","fscanf","fgets","fputs","main","fgetc"};
static char *keyword[] = {"const","volatile","extern","auto","register","static","signed","unsigned","short","long","double","char","int","float","struct","union","enum","typedef","void","goto","return","continue","break","if","else","for","while","do","switch","case","default","sizeof"};
static char *operators = "/+-*%=<>&|!^";
static char *symbols = "{}[]():?";
static char *pre_directives[] = {"#include","#define","#if","#else","elif","#endif","undef","#ifndef","#error","#pragma","#line","#warning"};

// Function Prototypes
int Lexer(const char* filename);
int initializeLexer(const char* filename);

int isKeyword(const char* str);
int isOperator(const char ch);
int isSymbols(const char ch);
int isFunction(const char *str);
int isPreDirective(const char *str);
int isNumber(char ch);
int isPointer(char ch);

#endif
