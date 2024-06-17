#include <cs50.h>
#include <stdio.h>

void print_line(int width, int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("What is the height? \n");
    }
    while (height < 1);

    for (int j = 0; j < height; j++)
    {
        print_line(j, height);
        printf("\n");
    }
}

void print_line(int width, int height)
{
    for (int r = 0; r < height - width; r++)
    {
        printf(" ");
    }

    for (int i = 0; i < width + 1; i++)
    {
        printf("#");
    }

    printf(" ");

    for (int e = 0; e < width + 1; e++){
        printf("#");
    }
}
