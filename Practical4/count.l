%option noyywrap
%{
	#include<stdio.h>

    int characters = 0;
    int words = 0;
    int lines = 0;

%}

%%

\n { lines++; characters++; }
[ \t]+ { characters += yyleng; }
[^ \t\n]+ { words++; characters += yyleng; }

%%

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if(!fp){
        perror("File opening failed.\n");
        return 1;
    }

    yyin = fp;
	yylex();

    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);

	return 0;
}