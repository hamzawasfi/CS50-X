#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
const int START_SIZE = 4;

int isJpg(uint8_t buffer[]);
int isLast(uint8_t buffer[], int blocksRead);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: name of card");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Cannot open %s.", argv[1]);
    }

    uint8_t buffer[BLOCK_SIZE];
    int counter = 0;
    int writing = 0;
    int blocksRead = BLOCK_SIZE;
    FILE *output;
    char imageName[10];
    sprintf(imageName, "%d.JPEG", counter);

    while (feof(card) == 0)
    {
        blocksRead = fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card);

        if(writing == 1 && isLast(buffer, blocksRead) == 1){
            fclose(output);
            writing = 0;
        }

        if (isJpg(buffer) == 1)
        {
            if (writing == 1)
            {
                fclose(output);
                counter++;
                writing = 0;
            }
            if (isJpg(buffer) == 1 || writing == 0)
            {
                writing = 1;
                sprintf(imageName, counter > 9 ? "0%d.jpg" : "00%d.jpg", counter);
                output = fopen(imageName, "w");
                if (output == NULL)
                {
                    printf("cannot write to %s.", imageName);
                }
            }
        }

        if (writing == 1)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }
    fclose(card);
}

int isLast(uint8_t buffer[], int blocksRead){
    for(int i = 0; i < blocksRead; i++){
        if (buffer[i] != 0){
            return 0;
        }
    }
    return 1;
}

int isJpg(uint8_t buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] >= 224 && buffer[3] <= 239))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
