#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int year = 0;

    if (start != end)
    {
        do
        {
            // each year, n/3 born, n/4 pass away
            start = start + (start / 3) - (start / 4);
            year++;
        }
        while (start < end);
    }

    // TODO: Print number of years
    printf("Years: %i\n", year);

    return 0;
}
