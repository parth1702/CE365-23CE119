%option noyywrap
%{
	#include<stdio.h>
    int lower = 0, upper = 0, digit = 0, symbol = 0, length = 0;
%}

%%

[a-z] { lower++; length++; }
[A-Z] { upper++; length++; }
[0-9] { digit++; length++; }
[* , ; # $ @ ( )] { symbol++; length++; }
.     { length++; } 
\n    { }

%%

int main()
{
    printf("Enter your password: ");
    
	yylex();

    if(length >= 9 && length <= 15 && symbol >= 1 && digit >= 1 && upper >= 1 && lower >= 1)
        printf("Valid Password.\n");
    else
        printf("Invalid Password\n");

	return 0;
}