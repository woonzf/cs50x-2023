// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int N = 1;

string replace(string argv[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    replace(argv);
    printf("%s\n", argv[N]);

    return 0;
}

string replace(string argv[])
{
    for (int i = 0, length = strlen(argv[N]); i < length; i++)
    {
        switch (argv[N][i])
        {
            case 'a':
                argv[N][i] = '6';
                break;

            case 'e':
                argv[N][i] = '3';
                break;

            case 'i':
                argv[N][i] = '1';
                break;

            case 'o':
                argv[N][i] = '0';
                break;

            default:
                break;
        }
    }

    return argv[N];
}