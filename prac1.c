#include <stdio.h>
#include <string.h>

int main() {
    // Write C code here
    char str1[100];
    
    printf("Enter any String: ");
    scanf("%[^\n]", &str1);

    int len = strlen(str1);
    
    if(len < 2){
        printf("Invalid String.\n");
        printf("Made by Aaryan Chavda - 23CE013");
        return 0;
    }
    
    if(str1[len-2] != 'b' || str1[len-1] != 'b'){
        printf("Invalid String.\n");
        printf("Made by Aaryan Chavda - 23CE013");
        return 0;
    }
    
    for(int i=0; i<len-2; i++){
        if(str1[i] != 'a'){
            printf("Invalid String.\n");
            printf("Made by Aaryan Chavda - 23CE013");
            return 0;
        }
    }

    printf("Valid String.\n");
    printf("Made by Aaryan Chavda - 23CE013");
    return 0;
}