#include <stdio.h>
#include <cs50.h>

int main (void){
    int change;
    int coins = 0;

    do{
        change = get_int("Change: ");
    }while(change < 1);

    while (change != 0){
        if(change >= 25){
            coins += change / 25;
            change = change % 25;
        }else if(change >= 10){
            coins += change / 10;
            change = change % 10;
        }else if(change >= 5){
            coins += change / 5;
            change = change % 5;
        }else{
            coins += change;
            change = 0;
        }
    }
    printf("%i\n", coins);
}
