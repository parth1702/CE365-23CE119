%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();
%}

%union {
    float fval;
}

%token <fval> NUMBER

%type <fval> E T F G

%left '+' '-'
%left '*' '/'
%right '^'

%start input

%%

input: E '\n' { printf("Result = %f\n", $1); }
     ;

E   : E '+' T   { $$ = $1 + $3; }
    | E '-' T   { $$ = $1 - $3; }
    | T         { $$ = $1; }
    ;

T   : T '*' F   { $$ = $1 * $3; }
    | T '/' F   { $$ = $1 / $3; }
    | F         { $$ = $1; }
    ;

F   : G '^' F   { $$ = pow($1, $3); }
    | G         { $$ = $1; }
    ;

G   : '(' E ')' { $$ = $2; }
    | NUMBER    { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}