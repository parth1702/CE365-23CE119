%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line = 1;

char symtab[100][100];
int symcount = 0;

int isDuplicate(char *str) {
    for(int i=0;i<symcount;i++)
        if(strcmp(symtab[i],str)==0)
            return 1;
    return 0;
}

void addSymbol(char *str){
    if(!isDuplicate(str)){
        strcpy(symtab[symcount++],str);
    }
}
%}


digit       [0-9]
letter      [a-zA-Z_]
id          {letter}({letter}|{digit})*
intconst    {digit}+
floatconst  {digit}+"."{digit}+
charconst   \'(.|\\.)\'
string      \"([^\\\"]|\\.)*\"
invalid     {digit}+{letter}+

keyword     int|char|float|double|long|short|void|return|if|else|for|while|do|struct|break|continue

operator    \+|\-|\*|\/|%|==|!=|<=|>=|<|>|=|&&|\|\||!
punct       [\(\)\{\}\[\];,]

scomment    "//".*
mcomment    "/*"([^*]|\*+[^*/])*\*+"/"

%%

\n              { line++; }
[ \t]+          { }

{keyword}       { printf("Keyword: %s\n", yytext); }

{id}            { printf("Identifier: %s\n", yytext);
                  addSymbol(yytext); }

{floatconst}    { printf("Constant: %s\n", yytext); }

{intconst}      { printf("Constant: %s\n", yytext); }

{charconst}     { printf("Constant: %s\n", yytext); }

{string}        { printf("String: %s\n", yytext); }

{operator}      { printf("Operator: %s\n", yytext); }

{punct}         { printf("Punctuation: %s\n", yytext); }

{scomment}      { }

{mcomment}      { }

{invalid}       { printf("\nLEXICAL ERROR\nLine %d : %s invalid lexeme\n", line, yytext); }

.               { printf("\nLEXICAL ERROR\nLine %d : %s invalid symbol\n", line, yytext); }

%%

int main(int argc, char *argv[]) {

    if(argc < 2){
        printf("Usage: ./a.out <sourcefile.c>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if(!fp){
        printf("Cannot open file\n");
        return 1;
    }

    yyin = fp;

    printf("TOKENS\n\n");
    yylex();

    printf("\n\nSYMBOL TABLE ENTRIES\n");
    for(int i=0;i<symcount;i++)
        printf("%d) %s\n", i+1, symtab[i]);

    fclose(fp);
    return 0;
}
