#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1;

void push(char c){
    stack[++top] = c;
}

char pop(){
    return stack[top--];
}

int main(){

    printf("Grammar is LL(1)\n");

    printf("Enter string: ");
    scanf("%s",input);

    int i=0;
    push('$');
    push('S');

    while(top != -1){
        char topSymbol = pop();

        if(topSymbol == input[i]){
            i++;
        }
        else if(topSymbol == 'S'){
            if(input[i]=='a' || input[i]=='b' || input[i]=='(' || input[i]=='c'){
                push('C');
                push('B');
                push('A');
            }
        }
        else if(topSymbol == 'A'){
            if(input[i]=='a'){
                push('a');
            }
        }
        else if(topSymbol == 'B'){
            if(input[i]=='b'){
                push('b');
            }
        }
        else if(topSymbol == 'C'){
            if(input[i]=='('){
                push(')');
                push('S');
                push('(');
            }
            else if(input[i]=='c'){
                push('c');
            }
        }
        else{
            printf("Invalid string\n");
            return 0;
        }
    }

    if(input[i]=='\0')
        printf("Valid string\n");
    else
        printf("Invalid string\n");

    return 0;
}
