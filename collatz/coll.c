#include<stdio.h>
#include<cs50.h>

int coll(int n);

int main(void){
    int n = get_int("n is ");

    printf("%i", coll(n));
}

int coll(int n){
    if (n == 1){
        return 0;
    }else if (n % 2 == 0){
        return 1 + coll(n/2);
    }else{
        return 1 + coll(n*3+1);
    }
}
