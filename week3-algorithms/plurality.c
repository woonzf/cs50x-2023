#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void sort_votes(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    int match = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            match++;
        }
    }

    if (match == 0)
    {
        return false;
    }

    return true;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    sort_votes();

    int maxvotes = candidates[0].votes;
    int match = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maxvotes)
        {
            match++;
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < match; i++)
    {
        printf("%s\n", candidates[i].name);
    }

    return;
}

void sort_votes(void)
{
    // Bubble sort (descending order)
    int count = candidate_count;
    string tempname;
    int tempvotes;

    while (count > 1)
    {
        int sort = 0;

        for (int i = 1; i < count; i++)
        {
            if (candidates[i].votes > candidates[i - 1].votes)
            {
                // Copy i into temporary
                tempname = candidates[i].name;
                tempvotes = candidates[i].votes;

                // Replace i with i - 1
                candidates[i].name = candidates[i - 1].name;
                candidates[i].votes = candidates[i - 1].votes;

                // Replace i - 1 with temporary (original i)
                candidates[i - 1].name = tempname;
                candidates[i - 1].votes = tempvotes;

                sort++;
            }
        }

        if (sort == 0)
        {
            break;
        }

        count--;
    }

    return;
}