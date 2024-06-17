#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<cs50.h>

string compute(string text, string key);

int main (int argc, string argv[]){
    if(argc != 2){
        printf("enter 1 key");
        return 1;
    }

    int length = strlen(argv[1]);
    if(length != 26){
        printf("key must be 26 characters");
        return 1;
    }

    for(int i = 0; i < length; i++){
        if(isalpha(argv[1][i]) == 0){
            printf("key must contain only alphabeticals");
            return 1;
        }
        for(int n = 0; n < length; n++){
            if(n != i){
                if(toupper(argv[1][i]) == toupper(argv[1][n])){
                    printf("key must not contain repeated letters");
                    return 1;
                }
            }
        }
        argv[1][i] = toupper(argv[1][i]);
    }

    string key = argv[1];
    string text = get_string("text: ");
    string cipher = compute(text, key);
    printf("ciphertext: %s\n", cipher);
}

string compute(string text, string key){
    int diff = 0;
    for (int i = 0, length = strlen(text); i < length; i++){
        if(isupper(text[i]) != 0){
            diff = text[i] - 'A';
            text[i] = key[diff];
        }else if(islower(text[i]) != 0){
            diff = text[i] - 'a';
            text[i] = tolower(key[diff]);
        }
    }
    return text;
}
