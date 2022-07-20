#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    /*
    printf("%i\n", preferences[0][0]);
    printf("%i\n", preferences[0][1]);
    printf("%i\n", preferences[0][2]);
    printf("%i\n", preferences[1][0]);
    printf("%i\n", preferences[1][1]);
    printf("%i\n", preferences[1][2]);
    printf("%i\n", preferences[2][0]);
    printf("%i\n", preferences[2][1]);
    printf("%i\n", preferences[2][2]);
    */

    add_pairs();

    printf("%i, %i, %i, %i, %i, %i\n", pairs[0].winner, pairs[0].loser, pairs[1].winner, pairs[1].loser, pairs[2].winner, pairs[2].loser);

    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Checks to make sure the vote is a valid name, then populates the ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update each voter's preferences one at a time.
    for(int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Populate the pairs array with winners and losers depending who is preferred. Ignore all other cases (tie)
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 1 + i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    int strength[pair_count];
    int smalleststrength = 100000;

    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser];
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (strength[j] < smalleststrength)
            {
                smalleststrength = strength[j];
            }
        }
        strength[i] = smalleststrength;
        
    }


    printf("%i, %i, %i\n", strength[0], strength[1], strength[2]);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}


    /*
    string candidates[] = [Alice, Bob, Charlie, David]
    int ranks[] = [1, 2, 0, 3]
    Bob is better than everyone else. Therefore update preferences by giving him one point at the following:
    preferences[1][0], preferences[1][2], and preferences[1][3], but NOT at preferences[1][1]
    give one point to
    preferences[2][0], preferences[2][3]
    give one point to
    preferences [0][3]
    so, preferences[i][j] =
    */