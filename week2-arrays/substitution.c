#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid_key(string input);
char substitute(char p, string k);

int main(int argc, string argv[])
{
    // Check argc
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Call valid_key to check argv
    int n = argc - 1;

    if (valid_key(argv[n]) == false)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Copy argv to key
    int lenargv = strlen(argv[n]);
    char key[lenargv];

    for (int i = 0; i < lenargv; i++)
    {
        key[i] = argv[n][i];
    }

    // Prompt for plaintext
    string ptext = get_string("plaintext:  ");

    printf("ciphertext: ");

    // Call substitute and print for each character
    for (int i = 0, len = strlen(ptext); i < len; i++)
    {
        printf("%c", substitute(ptext[i], key));
    }
    printf("\n");

    return 0;
}

bool valid_key(string input)
{
    int len = strlen(input);
    int uinput[len];
    int u = 0;
    int m = 0;

    for (int i = 0; i < len; i++)
    {
        // Copy and convert to uppercase to detect repeat alphabet
        uinput[i] = toupper(input[i]);

        // Check uppercase
        if (isupper(uinput[i]))
        {
            u++;
        }

        for (int j = 0; j < len; j++)
        {
            // Check match
            if (uinput[j] == uinput[i])
            {
                m++;
            }
        }
    }

    // Check criteria
    if (u == 26 && m == 26)
    {
        return true;
    }

    return false;
}

char substitute(char p, string k)
{
    char c;

    for (int i = 0, len = strlen(k); i < len; i++)
    {
        // Check and preserve uppercase
        if (isupper(p))
        {
            if (i == p - 'A')
            {
                c = toupper(k[i]);
            }
        }
        // Check and preserve lowercase
        else if (islower(p))
        {
            if (i == p - 'a')
            {
                c = tolower(k[i]);
            }
        }
        else
        {
            // Preserve if non-alphabetical
            c = p;
        }
    }

    return c;
}