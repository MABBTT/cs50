#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool validate(int n, int w, int l);

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            // its possible that instead of name above the rank array should show the postion of the candidate array
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = 0; j < (candidate_count - 1); j++)
        {
            preferences[ranks[i]][ranks [j+1]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = 0; j < (candidate_count - 1); j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count -1].loser = j;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int tempwinner;
    int temploser;
    int swap = 1;
    while (swap !=0)
    {
        swap = 0;
        for (int i = 0; i < (pair_count - 1); i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i+1].winner][pairs[i+1].loser])
            {
                tempwinner = pairs[i+1].winner;
                pairs[i+1].winner = pairs[i].winner;
                pairs[i].winner = tempwinner;
                temploser = pairs[i+1].loser;
                pairs[i+1].loser = pairs[i].loser;
                pairs[i].loser = temploser;
                swap +=1;
            }
        }
    }
    return;
}

// Validate no cycle n = pair index w = winner l = loser
bool validate(int n, int w, int l)
{
    if (n <= 0)
    {
        return true;
    }
    for (int i = 1; i <= n; i++)
    {
        if (pairs[n - i].loser == w)
        {
            if (pairs[n - i].winner == l)
                return false;
            else
                validate(n-1, pairs[n - 1].winner, l);
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        if (validate((i), pairs[i].winner, pairs[i].loser) == true)
            locked[pairs[i].winner][pairs[i].loser] = true;
        else
            locked[pairs[i].winner][pairs[i].loser] = false;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int k = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
                break;
            else
                k++;
        }
        if (k == (candidate_count - 1))
            printf("%s\n", candidates[i]);
    }
    return;
}
