#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the colour is black #000000
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                // Change to light-purple #CC99FF
                image[i][j].rgbtRed = 0xCC;
                image[i][j].rgbtGreen = 0x99;
                image[i][j].rgbtBlue = 0xFF;
            }
        }
    }

    return;
}
