#include <stdio.h>
#include <string.h>
#include <ctype.h>


int isKeyword(char word[]) {
    const char *keywords[] = {"int", "float", "double", "char", "void", "if", "else", "for", "while", "return", "struct", "include", "define", "long",
        "printf", "scanf", "switch", "case", "break", "continue"};

    int count = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < count; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isIdentifier(char word[]) {

    if (!(isalpha(word[0]) || word[0] == '_'))
        return 0;

    for (int i = 1; word[i] != '\0'; i++) {
        if (!(isalnum(word[i]) || word[i] == '_'))
            return 0;
    }

    return 1;
}
char symbolTable[50][50];
int symbolCount = 0;

int isPresent(char id[]) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i], id) == 0)
            return 1;
    }
    return 0;
}

void addToSymbolTable(char id[]) {
    if (!isPresent(id)) {
        strcpy(symbolTable[symbolCount], id);
        symbolCount++;
    }
}


int isOperator(char ch) {
    char operators[] = "+-*/%=<>!&|^";

    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}


int isSpecialSymbol(char ch) {
    char symbols[] = "(),;{}[]";

    for (int i = 0; i < strlen(symbols); i++) {
        if (ch == symbols[i])
            return 1;
    }
    return 0;
}


int main() {

    FILE *fp;
    char filename[50];
    char ch, buffer[100];
    int i = 0, line = 1;
    
    printf("Enter File Name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("\n<--------TOKENS-------->\n");

    while ((ch = fgetc(fp)) != EOF) {

        //line counting
        if (ch == '\n')
            line++;

        //skip whitespace
        if (isspace(ch))
            continue;

        //handling comments
        if (ch == '/') {
            char next = fgetc(fp);

            //single-line comment
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n');
                line++;
                continue;
            }

            //multi-line comments
            else if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '\n') line++;
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
                continue;
            }
            else {
                fseek(fp, -1, SEEK_CUR);
            }
        }

        //keywords and identifiers
        if (isalpha(ch) || ch == '_') {

            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_')) {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';
            i = 0;

            if (isKeyword(buffer))
                printf("Keyword      : %s\n", buffer);
            else{
                printf("Identifier   : %s\n", buffer);
                addToSymbolTable(buffer);
            }

            fseek(fp, -1, SEEK_CUR);
        }

        //constants
        else if (isdigit(ch)) {
            int dotcount = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '.') ) {
                
                if (ch == '.')
                {
                    dotcount++;
                }
                
                buffer[i++] = ch;
            }

            buffer[i] = '\0';
            i = 0;

            //handling invalid lexemes (errors)
            if (isalpha(buffer[strlen(buffer)-1]) || dotcount > 1)
                printf("***LEXICAL ERROR (Line %d): %s invalid lexeme***\n",line, buffer);
            else
                printf("Constant     : %s\n", buffer);

            fseek(fp, -1, SEEK_CUR);
        }

        //string constants 
        else if (ch == '"') {

            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && ch != '"') {

                if (ch == '\n') {
                    printf("LEXICAL ERROR (Line %d): unterminated string constant\n", line);
                    i = 0;
                    break;
                }

                buffer[i++] = ch;
            }

            if (ch == '"') {
                buffer[i++] = ch;
                buffer[i] = '\0';
                printf("Constant     : %s\n", buffer);
            }

            i = 0;
        }


        //operators
        else if (isOperator(ch)) {
            printf("Operator     : %c\n", ch);
        }

        //special symbols
        else if (isSpecialSymbol(ch)) {
            printf("Punctuation  : %c\n", ch);
        }
    }
    
    fclose(fp);

    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i]);
    }


    printf("\nAaryan Chavda - 23CE013\n");


    return 0;
}

