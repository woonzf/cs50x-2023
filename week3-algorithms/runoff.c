#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
void sort_votes(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    int match = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            match++;
        }
    }

    if (match == 0)
    {
        return false;
    }

    return true;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    int k;

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            k = preferences[i][j];

            if (candidates[k].eliminated == 0)
            {
                candidates[k].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int votes2win = (voter_count / 2) + 1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= votes2win)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    sort_votes();

    int min;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == 0)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int count = 0;
    int valid = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            count++;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == 0)
        {
            valid++;
        }
    }

    if (count == valid)
    {
        return true;
    }

    // To fix a bug if voter_count < candidate_count
    if (voter_count < candidate_count)
    {
        int max = candidates[0].votes;
        int n = 0;

        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == max)
            {
                n++;
            }

            if (n == voter_count)
            {
                for (int j = 0; j < candidate_count; j++)
                {
                    if (candidates[j].votes != max)
                    {
                        candidates[j].eliminated = 1;
                    }
                }

                return true;
            }
        }
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = 1;
        }
    }

    return;
}

void sort_votes(void)
{
    // Bubble sort (descending order)
    int count = candidate_count;
    int tempvotes;
    string tempname;

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