#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float min(float n1, float n2);
void swap(RGBTRIPLE *p1, RGBTRIPLE *p2);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float new_red = min(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                    0.189 * image[i][j].rgbtBlue,
                                255.0);
            float new_green = min(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                      0.168 * image[i][j].rgbtBlue,
                                  255.0);
            float new_blue = min(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                     0.131 * image[i][j].rgbtBlue,
                                 255.0);

            image[i][j].rgbtRed = round(new_red);
            image[i][j].rgbtGreen = round(new_green);
            image[i][j].rgbtBlue = round(new_blue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - j - 1]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float new_red = 0.0;
            float new_green = 0.0;
            float new_blue = 0.0;
            int counter = 0;
            for (int x = -1; x < 2; x++)
            {
                if (i + x >= 0 && i + x < height)
                {
                    for (int y = -1; y < 2; y++)
                    {
                        if (j + y >= 0 && j + y < width)
                        {
                            new_red += new_image[i + x][j + y].rgbtRed;
                            new_green += new_image[i + x][j + y].rgbtGreen;
                            new_blue += new_image[i + x][j + y].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }
            new_red /= counter;
            new_green /= counter;
            new_blue /= counter;

            image[i][j].rgbtRed = round(new_red);
            image[i][j].rgbtGreen = round(new_green);
            image[i][j].rgbtBlue = round(new_blue);
        }
    }
    return;
}

float min(float n1, float n2)
{
    if (n1 > n2)
    {
        return n2;
    }
    else
    {
        return n1;
    }
}

void swap(RGBTRIPLE *p1, RGBTRIPLE *p2)
{
    RGBTRIPLE buffer = *p1;
    *p1 = *p2;
    *p2 = buffer;
}
