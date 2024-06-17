#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>

int compute(string word);
string make_upper(string word);
string only_char(string word);

int main (void){
    string player1 = only_char(make_upper(get_string("Enter word 1: ")));
    string player2 = only_char(make_upper(get_string("Enter word 2: ")));

    int score1 = compute(player1);
    int score2 = compute(player2);

    if (score1 > score2){
        printf("Player 1 wins");
    }else if (score1 < score2){
        printf("Player 2 wins");
    }else{
        printf("Tie!\n");
    }
}

int compute(string word){
    int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;
    for (int i = 0, length = strlen(word); i < length; i++){
        if(word[i] == ' '){
            score += 0;
        }else{
            score += scores[word[i] - 65];
        }
    }
    return score;
}

string make_upper(string word){
    for (int i = 0, length = strlen(word), diff = 'a' - 'A'; i < length; i++){
        if (word[i] <= 'z' && word[i] >= 'a'){
            word[i] -= diff;
        }
    }
    return word;
}

string only_char(string word){
    int length = strlen(word);
    for(int i = 0; i < length; i++){
        if(word[i] > 'Z' || word[i] < 'A'){
            word[i] = ' ';
        }
    }
    return word;
}
