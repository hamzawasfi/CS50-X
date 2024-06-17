#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_length(long number);
int get_digit(long number, int position);
int get_sum(long number, int length);
int is_visa(long number, int length);
int is_master(long number, int length);
int is_ae(long number, int length);

int main (void){
    long number = get_long("Number: ");
    int length = get_length(number);
    int sum = get_sum(number, length);

    if(sum % 10 == 0){
        if(is_visa(number, length) == 0){
            printf("VISA\n");
        }else if(is_master(number, length) == 0){
            printf("MASTERCARD\n");
        }else if(is_ae(number, length) == 0){
            printf("AMEX\n");
        }else{
            printf("INVALID\n");
        }
    }else{
        printf("INVALID\n");
    }
}

int is_ae(long number, int length){
    if (length == 15){
        if(get_digit(number, length) == 3){
            if(get_digit(number, length - 1) == 4 || get_digit(number, length - 1) == 7){
                return 0;
            }else{
                return 1;
            }
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int is_visa(long number, int length){
    if (length == 13 || length == 16){
        if(get_digit(number, length) == 4){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int is_master(long number, int length){
    if (length == 16){
        if(get_digit(number, length) == 5){
            if(get_digit(number, length - 1) == 1 || get_digit(number, length - 1) == 2 || get_digit(number, length - 1) == 3 || get_digit(number, length - 1) == 4 || get_digit(number, length - 1) == 5){
                return 0;
            }else{
                return 1;
            }
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int get_length(long number){
    int length = 0;
    while(number > 0){
        number /= 10;
        length ++;
    }
    return length;
}

int get_digit(long number, int position){
    while (position > 1){
        number /= 10;
        position --;
    }

    int digit = number % 10;
    return digit;
}


int get_sum(long number, int length){
    int digit = 0;
    for(int pos_even = 2; pos_even <= length; pos_even += 2){
        int d = get_digit(number, pos_even) * 2;
        int l = get_length(d);
        if(l > 1){
            for(int pos = 1; pos <= l; pos ++){
                digit += get_digit(d, pos);
            }
        }else{
            digit += d;
        }
    }
    for(int pos_odd = 1; pos_odd <= length; pos_odd += 2){
        digit += get_digit(number, pos_odd);
    }
    return digit;
}
