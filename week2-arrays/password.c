// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int u, l, d, p, sum;

    for (int i = 0, length = strlen(password); i < length; i++)
    {
        // Check uppercase
        if (isupper(password[i]))
        {
            u = 1;
        }

        // Check lowercase
        if (islower(password[i]))
        {
            l = 1;
        }

        // Check digit
        if (isdigit(password[i]))
        {
            d = 1;
        }

        // Check punctuation
        if (ispunct(password[i]))
        {
            p = 1;
        }

        sum = u + l + d + p;
    }

    // Check criteria
    if (sum == 4)
    {
        return true;
    }

    return false;
}
