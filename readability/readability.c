#include<cs50.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

int count_letters(string p);
int count_words(string p);
int count_sentences(string p);
int compute(int letters, int sentences, int words);

int main (void){
    string paragraph = get_string("Write the paragraph: ");
    int letters = count_letters(paragraph);
    int words = count_words(paragraph);
    int sentences = count_sentences(paragraph);
    int index = compute(letters, sentences, words);

    if(index < 1){
        printf("Before Grade 1\n");
    }else if(index > 16){
        printf("Grade 16+\n");
    }else{
        printf("Grade %i\n", index);
    }
}

int compute(int letters, int sentences, int words){
    float avg_letters = (float)letters / (float)words * 100.0;
    float avg_sentences = (float)sentences / (float)words * 100.0;
    float index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;
    return round(index);
}

int count_sentences(string p){
    int sentences = 0;
    for(int i = 0; p[i]; i++){
        p[i] = tolower(p[i]);
    }
    for(int i = 0, length = strlen(p); i < length; i++){
        if (p[i] >= 'a' || p[i] <= 'z'){
            sentences ++;
            while((p[i] != '.' || p[i] != '!' || p[i] != '?') && i < length){
                i++;
            }
        }
    }
    return sentences - 1;
}

int count_words(string p){
    int words = 0;
    for(int i = 0; p[i]; i++){
        p[i] = tolower(p[i]);
    }
    for(int i = 0, length = strlen(p); i < length; i++){
        if (p[i] >= 'a' || p[i] <= 'z'){
            words ++;
            while(p[i] != ' ' && i < length){
                i++;
            }
        }
    }
    return words + 1;
}

int count_letters(string p){
    int letters = 0;
    for(int i = 0; p[i]; i++){
        p[i] = tolower(p[i]);
    }
    for(int length = strlen(p), i = 0; i < length; i++){
        if(p[i] >= 'a' && p[i] <= 'z'){
            letters++;
        }
    }
    return letters;
}
