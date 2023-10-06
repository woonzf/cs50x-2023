#include <cs50.h>
#include <math.h>
#include <stdio.h>

void cardtype(int cs, int cl, int fd);

int main(void)
{
    // Prompt for input
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);

    // Calculate checksum
    int ld;
    int i = 1;
    int n246 = 0;
    int n135 = 0;
    long r = n;

    while (r > 1)
    {
        // Check remainder
        ld = r % 10;

        // Remove 1 integer
        r = r / 10;

        // i = 2, 4, 6, ...
        if (i % 2 == 0)
        {
            if (ld >= 5)
            {
                // Example: 5 * 2 = 10, 1 + 0 = 1
                ld = ld * 2 % 10 + 1;
            }
            else
            {
                ld = ld * 2;
            }
            n246 = n246 + ld;
        }
        // i = 1, 3, 5, ...
        else
        {
            n135 = n135 + ld;
        }

        i++;
    }

    int cs = n246 + n135;

    // Check for card length and starting digits
    // Find card length
    int cl = log10(n) + 1;

    // Find first 2 digits
    int fd = (n * pow(10, -cl + 2));

    // Print AMEX, MASTERCARD, VISA or INVALID
    cardtype(cs, cl, fd);

    return 0;
}

void cardtype(int cs, int cl, int fd)
{
    // Check if checksum ends with 0
    if (cs % 10 == 0)
    {
        if (cl == 15 && (fd == 34 || fd == 37))
        {
            printf("AMEX\n");
        }
        else if (cl == 16 && fd >= 51 && fd <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if ((cl == 13 || cl == 16) && fd >= 40 && fd <= 42)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}