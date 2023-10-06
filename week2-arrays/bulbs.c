#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    // Prompt for "Message: "
    string message = get_string("Message: ");

    // Store text into another array in decimal
    int len = strlen(message);
    int decimal[len];

    for (int i = 0; i < len; i++)
    {
        decimal[i] = message[i];
    }

    // Turn decimal into 8-bit binary, one for each character
    int binary[len][BITS_IN_BYTE];

    for (int i = 0; i < len; i++)
    {
        while (decimal[i] >= 1)
        {
            // Start from last bit
            for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
            {
                // Determine bit as '0' or '1'
                binary[i][j] = decimal[i] % 2;

                // Move to next bit
                decimal[i] = decimal[i] / 2;
            }
        }
    }

    // Use print_bulb function to print
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(binary[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
