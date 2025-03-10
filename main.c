#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
	if(argc != 2)
	{
		printf("Usage : ./a.out  <file.c>[C file] \n");
		return -1;
	}
	if(initializeLexer(argv[1]))
	{
		printf("\n");
		if(Lexer(argv[1]))
			printf("INFO : Lexical Analysis success !\n");
		else
			printf("INFO : Lexical Analysis failed !\n");
	}
	else
	{
		printf("INFO : Lexical Analyser initialisation failed !\n");
	}
    	return 0;
}
