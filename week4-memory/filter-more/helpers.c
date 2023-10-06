#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "helpers.h"

// Structure prototype
// Create a struct to store RGB value more than 255 or less than -255
typedef struct
{
    int red;
    int green;
    int blue;
} sobel;

sobel gx[3][3];
sobel gy[3][3];

// Default Gx and Gy values
const int gx_default[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int gy_default[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// For global use
float red, green, blue;
int gx_red, gx_green, gx_blue;
int gy_red, gy_green, gy_blue;

// Function prototype
int cap(float rgb);
void reset_rgb(void);
bool boundary(int r, int c, int h, int w);
void reset_gxgy(void);
void reset_sobel(void);

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

            // divide by 3.0 to make average as a float before rounding
            average = round((red + green + blue) / 3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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

    // Set RGB values to 0
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
                    // Check boundary
                    if (boundary(k, l, height, width))
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
            red = round(red / count);
            green = round(green / count);
            blue = round(blue / count);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Set Gx and Gy values to 0
    reset_gxgy();

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
            // Loop to sum all Gx and Gy values of adjacent pixels
            for (int k = i - 1, m = 0; k <= i + 1; k++)
            {
                for (int l = j - 1, n = 0; l <= j + 1; l++)
                {
                    // Check boundary
                    if (boundary(k, l, height, width))
                    {
                        // Set Gx and Gy values to 0 if current pixel is at the boundary
                        reset_sobel();
                    }
                    else
                    {
                        // Calculate Gx and Gy values with Sobel operator
                        gx[m][n].red = temp[k][l].rgbtRed * gx_default[m][n];
                        gx[m][n].green = temp[k][l].rgbtGreen * gx_default[m][n];
                        gx[m][n].blue = temp[k][l].rgbtBlue * gx_default[m][n];

                        gy[m][n].red = temp[k][l].rgbtRed * gy_default[m][n];
                        gy[m][n].green = temp[k][l].rgbtGreen * gy_default[m][n];
                        gy[m][n].blue = temp[k][l].rgbtBlue * gy_default[m][n];
                    }

                    // Sum of all Gx and Gy values
                    gx_red += gx[m][n].red;
                    gx_green += gx[m][n].green;
                    gx_blue += gx[m][n].blue;

                    gy_red += gy[m][n].red;
                    gy_green += gy[m][n].green;
                    gy_blue += gy[m][n].blue;

                    n++;
                }

                m++;
            }

            // Square root of Gx^2 and Gy^2 values
            red = sqrt(pow(gx_red, 2) + pow(gy_red, 2));
            green = sqrt(pow(gx_green, 2) + pow(gy_green, 2));
            blue = sqrt(pow(gx_blue, 2) + pow(gy_blue, 2));

            // Copy result to output pixel
            image[i][j].rgbtRed = cap(round(red));
            image[i][j].rgbtGreen = cap(round(green));
            image[i][j].rgbtBlue = cap(round(blue));

            // Reset variables
            reset_gxgy();
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

// Check boundary
bool boundary(int r, int c, int h, int w)
{
    // Check top or left boundary
    if (r < 0 || c < 0)
    {
        return true;
    }

    // Check bottom or right boundary
    if (r > h - 1 || c > w - 1)
    {
        return true;
    }

    return false;
}

// Reset global-used Gx and Gy values
void reset_gxgy(void)
{
    gx_red = 0;
    gx_green = 0;
    gx_blue = 0;

    gy_red = 0;
    gy_green = 0;
    gy_blue = 0;

    return;
}

// Reset sobel values
void reset_sobel(void)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gx[i][j].red = 0;
            gx[i][j].green = 0;
            gx[i][j].blue = 0;

            gy[i][j].red = 0;
            gy[i][j].green = 0;
            gy[i][j].blue = 0;
        }
    }

    return;
}