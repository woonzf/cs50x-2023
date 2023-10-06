#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string input);
char rotate(char p, int k);

int main(int argc, string argv[])
{
    // Check argc
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Call only_digits to check argv
    int n = argc - 1;

    if (only_digits(argv[n]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv to integer
    int key = atoi(argv[n]);

    // Prompt for plaintext
    string ptext = get_string("plaintext:  ");

    int len = strlen(ptext);

    printf("ciphertext: ");

    // Call rotate and print for each character
    for (int i = 0; i < len; i++)
    {
        printf("%c", rotate(ptext[i], key));
    }
    printf("\n");

    return 0;
}

bool only_digits(string input)
{
    int d = 0;
    int nd = 0;

    for (int i = 0, len = strlen(input); i < len; i++)
    {
        // Check digit
        if (isdigit(input[i]))
        {
            d++;
        }

        // Check non-digit
        if (!isdigit(input[i]))
        {
            nd++;
        }
    }

    // Check criteria
    if (d > 0 && nd == 0)
    {
        return true;
    }

    return false;
}

char rotate(char p, int k)
{
    int pc, c;

    // Check and preserve uppercase
    if (isupper(p))
    {
        // Caesar's algorithm with 'A' correction
        pc = (p - 'A');
        c = (pc + k) % 26 + 'A';
    }
    // Check and preserve lowercase
    else if (islower(p))
    {
        // Caesar's algorithm with 'a' correction
        pc = (p - 'a');
        c = (pc + k) % 26 + 'a';
    }
    else
    {
        // Preserve if non-alphabetical
        c = p;
    }

    return c;
}