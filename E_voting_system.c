// Including Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------- Module 1: Voter & Candidate Management -------------------- */

typedef struct candidate 
{
    char name[20];
    char party[20];
    int age;
    int vote_count;
} candidate;

typedef struct voter 
{
    char name[20];
    int age;
    char address[50];
    long long int voterid;
    long long int aadhar;
    int voted;
    char voted_to_party[20];
} voter;

// Updates vote counts based on voter’s chosen party
void push(candidate *c, voter *v, int N) 
{
    if (strcmp(v->voted_to_party, "None") == 0)
        return;

    for (int i = 0; i < N; i++)
     {
        if(c[i].age<25)
        {
            continue;
        }

        // Comparing the name of party and name of the party to which voters have chosen
        if (strcmp(c[i].party, v->voted_to_party) == 0) {
            c[i].vote_count++;
            break;
        }
    }
}

/* -------------------- Module 3: Vote Counting & Results -------------------- */

void display_results(candidate *c, int N)
 {
    printf("\n================= ELECTION RESULTS =================\n");
    printf("%-15s %-15s %-10s %-10s\n", "Candidate", "Party", "Age", "Votes");
    printf("----------------------------------------------------\n");

    int total_votes = 0, max_votes = -1;

    for (int i = 0; i < N; i++) 
    {
        printf("%-15s %-15s %-10d %-10d\n",
               c[i].name, c[i].party, c[i].age, c[i].vote_count);
        total_votes += c[i].vote_count;
        if (c[i].vote_count > max_votes)
            max_votes = c[i].vote_count;
    }

    if (total_votes == 0)
    {
        printf("\nNo votes cast.\n");
        return;
    }

    printf("\nTotal votes cast: %d\n", total_votes);
    printf("\n\nWinner:\n");
    for (int i = 0; i < N; i++)
     {
        if (c[i].vote_count == max_votes && max_votes > 0) 
        {
            printf("\n %s (%s)  :  %d votes\n", c[i].name, c[i].party, c[i].vote_count);
        }
    }
}

/* -------------------- Main Function -------------------- */

int main()
 {
    int N, i, voter_count = 0, ch = 1;

    printf("Enter the Number of Candidates: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Invalid number.\n");
        return 1;
    }
// Dynamically allocating the memory using malloc
    candidate *c = (candidate *)malloc(N * sizeof(candidate));
    if (!c)
    {
        printf("Memory Allocation Failed.\n");
        return 1;
    }

    // Candidate registration
    for (i = 0; i < N; i++)
    {
        printf("\nEnter details of Candidate %d:\n", i + 1);

        printf("Name: ");
        scanf(" %[^\n]", c[i].name);

        printf("Party: ");
        scanf(" %[^\n]", c[i].party);

        printf("Age: ");
        scanf("%d", &c[i].age);

// If any Candidate's age is less than 25 then he/she is not able to form a party
        if (c[i].age < 25)
        {
            printf(" Not eligible to form a party (Age < 25)\n");
            c[i].vote_count = 0;
            continue;
        }
        c[i].vote_count = 0;
    }
	  printf("\n----------------------------------------------------\n");
    // Voting process
    while(ch)
    {
        voter *v = (voter *)malloc(sizeof(voter));
        if (!v)
        {
            printf("Memory Allocation Failed.\n");    
            //If Memory is not allocated to v, then we also have to free the memory allocated to c
            free(c);     
            return 1;
        }

        printf("\nEnter Voter %d details:\n", voter_count+1);
        printf("Name: ");
        scanf(" %[^\n]", v->name);

        printf("Age: ");
        scanf("%d", &v->age);

        //Age shold be greater then or equal to 18 to give vote
        if (v->age < 18) 
        {
            printf(" Not eligible to vote (Age < 18)\n");
            //Freeing the memory if voter is not eligiblee to give vote
            free(v); 
            // Goto statement will move to NEXT_VOTER
            goto NEXT_VOTER;
        }

        printf("Address: ");
        scanf(" %[^\n]", v->address);

        printf("Voter ID: ");
        scanf("%lld", &v->voterid);

        printf("Aadhar Number: ");
        scanf("%lld", &v->aadhar);

        printf("Party to vote (or type 'None'): ");
        scanf(" %[^\n]", v->voted_to_party);

        // If Voter is not voting to any party
        if (strcmp(v->voted_to_party, "None") != 0)
        {
            // Pushing the count of voters of the parties
            push(c, v, N);
            // Voted is used to verify if anyone has not given the vote
            v->voted = 1;
            printf("Vote recorded for party: %s\n", v->voted_to_party);
        } 
        else
        {
            v->voted = 0;
            printf("No vote cast.\n");
        }
        // Counting the number of voters
	voter_count++;

    // Freeing the memory, after completion of vote counting process
        free(v);

    NEXT_VOTER:
    // Repeating the process to Add new voters
        printf("\nEnter 1 to Add Next Voter, 0 to Stop: ");
        scanf("%d", &ch);
       
    }

    // Display vote counts and winner(s)
    display_results(c, N);
	
    // Free memory located to candidate
    free(c);
    return 0;
}