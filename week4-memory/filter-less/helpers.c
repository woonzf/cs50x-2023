#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// For global use
int red, green, blue;

// Function prototype
int cap(float rgb);
void reset_rgb(void);
bool edge(int r, int c, int h, int w);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            // / 3.0 to make average as a float before rounding
            average = round((red + green + blue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepia_red, sepia_green, sepia_blue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            // Sepia algorithm with cap function
            sepia_red = cap(round(.393 * red + .769 * green + .189 * blue));
            sepia_green = cap(round(.349 * red + .686 * green + .168 * blue));
            sepia_blue = cap(round(.272 * red + .534 * green + .131 * blue));

            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtBlue = sepia_blue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int reflect;

    // Copy RGB value to temporary arrays
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Determine the mirrored position
            reflect = abs(j - width + 1);

            image[i][j].rgbtRed = temp[i][reflect].rgbtRed;
            image[i][j].rgbtGreen = temp[i][reflect].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][reflect].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int count = 0;

    reset_rgb();

    // Copy RGB values to another RGBTRIPLE struct
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Loop to sum all RGB values of adjacent pixels
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (edge(k, l, height, width))
                    {
                        continue;
                    }

                    red += temp[k][l].rgbtRed;
                    green += temp[k][l].rgbtGreen;
                    blue += temp[k][l].rgbtBlue;
                    count++;
                }
            }

            // Calculate average RGB of adjacent pixels
            red = round(red / (float) count);
            green = round(green / (float) count);
            blue = round(blue / (float) count);

            // Copy average RGB to output pixel
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;

            // Reset variables
            reset_rgb();
            count = 0;
        }
    }

    return;
}

// Cap RGB value as 255
int cap(float rgb)
{
    if (rgb > 255)
    {
        return 255;
    }

    return rgb;
}

// Reset global-used RGB values
void reset_rgb(void)
{
    red = 0;
    green = 0;
    blue = 0;

    return;
}

// Check edge
bool edge(int r, int c, int h, int w)
{
    if (r < 0 || c < 0)
    {
        return true;
    }

    if (r > h - 1 || c > w - 1)
    {
        return true;
    }

    return false;
}