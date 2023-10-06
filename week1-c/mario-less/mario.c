#include <cs50.h>
#include <stdio.h>

void print_grid(int height);

int main(void)
{
    // get height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    print_grid(n);

    return 0;
}

void print_grid(int height)
{
    for (int i = 0; i < height; i++)
    {
        // print space
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // print block
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // to next line
        printf("\n");
    }
}