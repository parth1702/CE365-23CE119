%option noyywrap
%{
	#include<stdio.h>
%}

%%

charusat|Charusat|CHARUSAT  {printf("university");}
.|\n {printf("%s", yytext);} {/* . means single character*/}


%%
int main()
{
    printf("Enter any string: ");
	yylex();

	return 0;
}