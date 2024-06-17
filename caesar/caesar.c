#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

char stoc(string text, int length);
char compute(char text_c, int key, int length);

int main (int argc, string argv[]){
    if(argc != 2){
        printf("Usage: ./caesar key");
        return 1;
    }
    for(int i = 0, length = strlen(argv[1]); i < length; i++){
        if(isdigit(argv[1][i]) == 0){
            printf("Usage: ./caesar key");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    if(key < 1){
       printf("Usage: ./caesar key");
       return 1;
    }

    string text = get_string("Text: ");
    int length = strlen(text);

    char text_after[length];
    printf("ciphertext: ");
    for(int i = 0; i < length; i ++){
        text_after[i] = compute(text[i], key, length);
        printf("%c", text_after[i]);
    }
    printf("\n");
}

char compute(char text_c, int key, int length){
    char text_after = '\0';
    int n = 0;
    if(isalpha(text_c) != 0){
       if(islower(text_c) != 0){
            n = ((text_c - 97) + key) % 26;
            text_after = n + 97;
        }else if(isupper(text_c) != 0){
            n = ((text_c - 65) + key) % 26;
            text_after = n + 65;
        }
    }else{
            text_after = text_c;
    }
    return text_after;
}
