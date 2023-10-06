#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int len = strlen(input);

    // Convert the last char to integer
    int value = input[len - 1] - '0';

    // Return last char if only one char
    if (len == 1)
    {
        return value;
    }

    // Remove last char
    input[len - 1] = '\0';

    // Recursion
    return value + (10 * convert(input));
}