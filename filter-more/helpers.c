#include "helpers.h"
#include<math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //copy image to new image
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = image[i][j];
        }
    }

    //check from new image and apply the filter to image
    const int gxWeight[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int gyWeight[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxNewRed = 0;
            int gxNewGreen = 0;
            int gxNewBlue = 0;
            int gyNewRed = 0;
            int gyNewGreen = 0;
            int gyNewBlue = 0;
            for (int x = -1; x < 2; x++)
            {
                if (i + x >= 0 && i + x < height)
                {
                    for (int y = -1; y < 2; y++)
                    {
                        if (j + y >= 0 && j + y < width)
                        {
                            gxNewRed += new_image[i + x][j + y].rgbtRed * gxWeight[x + 1][y + 1];
                            gxNewGreen += new_image[i + x][j + y].rgbtGreen * gxWeight[x + 1][y + 1];
                            gxNewBlue += new_image[i + x][j + y].rgbtBlue * gxWeight[x + 1][y + 1];

                            gyNewRed += new_image[i + x][j + y].rgbtRed * gyWeight[x + 1][y + 1];
                            gyNewGreen += new_image[i + x][j + y].rgbtGreen * gyWeight[x + 1][y + 1];
                            gyNewBlue += new_image[i + x][j + y].rgbtBlue * gyWeight[x + 1][y + 1];
                        }
                    }
                }
            }
            int new_red = round(sqrt(pow(gxNewRed, 2) + pow(gyNewRed, 2)));
            int new_green = round(sqrt(pow(gxNewGreen, 2) + pow(gyNewGreen, 2)));
            int new_blue = round(sqrt(pow(gxNewBlue, 2) + pow(gyNewBlue, 2)));

            image[i][j].rgbtRed = new_red <= 255 ? new_red : 255;
            image[i][j].rgbtGreen = new_green <= 255 ? new_green : 255;
            image[i][j].rgbtBlue = new_blue <= 255 ? new_blue : 255;
        }
    }
    return;
}
