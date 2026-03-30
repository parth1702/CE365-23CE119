%{
#include "prac10.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+(\.[0-9]+)? { yylval.fval = atof(yytext); return NUMBER; }

[\t ]+            { /* ignore whitespace */ }

\n                { return '\n'; }

[+\-*/^()]        { return yytext[0]; }

.                 { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}