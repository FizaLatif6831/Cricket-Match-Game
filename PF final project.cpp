#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Player structure
struct Player
{
    string name;
    int runsScored;
    int ballsFaced;
    int ballsBowled;
    int runsGiven;
    int wicketsTaken;
};

// Function prototypes
void drawScorecard(int runsScored, int wicketsFallen, int oversBowled, int target, int remainingScore, int remainingOvers);
void toss();
void findPlayerOfTheMatch(Player teamA[], Player teamB[]);
void saveMatchData(Player teamA[], Player teamB[], int overs, string batsmanOfTheMatch, string bowlerOfTheMatch);

int main()
{
    // Initializing variables
    int overs, runsScored, wicketsFallen;
    int target, remainingScore, remainingOvers;
    string batsmanOfTheMatch, bowlerOfTheMatch;
    Player teamA[7], teamB[7];
    string teamNameA, teamNameB;

    // Reading data from configuration file
    ifstream configFile;
    configFile.open("configuration.txt");
    configFile >> overs;
    configFile.close();

    // Taking team names from user
    cout << "Enter team name A: ";
    cin >> teamNameA;
    cout << "Enter team name B: ";
    cin >> teamNameB;

    // Taking player names from user
    cout << "\nEnter player names for team " << teamNameA << ":" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "Player " << i + 1 << ": ";
        cin >> teamA[i].name;
    }
    cout << "\nEnter player names for team " << teamNameB << ":" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "Player " << i + 1 << ": ";
        cin >> teamB[i].name;
    }

    // Toss
    cout << "\nTossing..." << endl;
    toss();

    // Initializing runsScored, wicketsFallen, target, remainingScore, remainingOvers
    runsScored = 0;
    wicketsFallen = 0;
    target = 0;
    remainingScore = 0;
    remainingOvers = overs;

    // Simulating match
    int currentPlayerA = 0, currentPlayerB = 0;
    while (remainingOvers > 0 && wicketsFallen < 10)
    {
        // Taking input from user
        cout << "\nPress enter to bowl...";
        cin.get();

        // Calculating score
        int score;
        srand(time(0));
        if (currentPlayerB == 5)
            score = rand() % 6 + 1;
        else
            score = rand() % 7 - 1;

        // Calculating runsScored and wicketsFallen
        if (score == -1)
        {
            wicketsFallen++;
            teamA[currentPlayerA].runsScored = runsScored;
            teamA[currentPlayerA].ballsFaced = overs * 6 - remainingOvers * 6 + 1;
            teamA[currentPlayerA].wicketsTaken = 0;
            teamB[currentPlayerB].wicketsTaken = 1;
        }
        else
        {
            runsScored += score;
        }

        // Calculating currentPlayerA and currentPlayerB
        if (score == -1 || (overs * 6 - remainingOvers * 6) % 6 == 0)
        {
            if (currentPlayerA == 4)
                currentPlayerA = 0;
            else
                currentPlayerA++;
        }
        if (currentPlayerB == 5)
            currentPlayerB = 0;
        else
            currentPlayerB++;

        // Drawing scoreboard
        drawScorecard(runsScored, wicketsFallen, overs - remainingOvers, target, remainingScore, remainingOvers);

        // Calculating remainingOvers
        remainingOvers--;
    }

    // Showing result
    cout << "\nInnings of team " << teamNameA << " finished." << endl;
    cout << "Total runs scored: " << runsScored << endl;
    cout << "Total wickets fallen: " << wicketsFallen << endl << endl;

    // Calculating target
    target = runsScored + 1;

    // Simulating second innings
    runsScored = 0;
    wicketsFallen = 0;
    remainingScore = target;
    remainingOvers = overs;
    currentPlayerA = 0;
    currentPlayerB = 0;
    while (remainingOvers > 0 && wicketsFallen < 10)
    {
        // Taking input from user
        cout << "\nPress enter to bowl...";
        cin.get();

        // Calculating score
        int score;
        srand(time(0));
        if (currentPlayerB == 5)
            score = rand() % 6 + 1;
        else
            score = rand() % 7 - 1;

        // Calculating runsScored and wicketsFallen
        if (score == -1)
        {
            wicketsFallen++;
            teamB[currentPlayerB].runsScored = runsScored;
            teamB[currentPlayerB].ballsFaced = overs * 6 - remainingOvers * 6 + 1;
            teamB[currentPlayerB].wicketsTaken = 0;
            teamA[currentPlayerA].wicketsTaken = 1;
        }
        else
        {
            runsScored += score;
            remainingScore -= score;
        }

        // Calculating currentPlayerA and currentPlayerB
        if (score == -1 || (overs * 6 - remainingOvers * 6) % 6 == 0)
        {
            if (currentPlayerB == 4)
                currentPlayerB = 0;
            else
                currentPlayerB++;
        }
        if (currentPlayerA == 5)
            currentPlayerA = 0;
        else
            currentPlayerA++;

        // Drawing scoreboard
        drawScorecard(runsScored, wicketsFallen, overs - remainingOvers, target, remainingScore, remainingOvers);

        // Calculating remainingOvers
        remainingOvers--;
    }

    // Showing result
    cout << "\nInnings of team " << teamNameB << " finished." << endl;
    cout << "Total runs scored: " << runsScored << endl;
    cout << "Total wickets fallen: " << wicketsFallen << endl << endl;

    // Finding player of the match
    findPlayerOfTheMatch(teamA, teamB);

    // Showing summary
    if (runsScored < target)
        cout << teamNameA << " won the match." << endl;
    else
        cout << teamNameB << " won the match." << endl;

    // Taking input from user
    cout << "\nDo you want to save match data (y/n)? ";
    char ch;
    cin >> ch;

    // Saving match data
    if (ch == 'y')
        saveMatchData(teamA, teamB, overs, batsmanOfTheMatch, bowlerOfTheMatch);

    return 0;
}

// Function to draw scoreboard
void drawScorecard(int runsScored, int wicketsFallen, int oversBowled, int target, int remainingScore, int remainingOvers)
{
    // Drawing scoreboard
    cout << "\n\n\t\tScoreBoard:\n\n";
    cout << "\t\t\tRuns scored: " << runsScored << endl;
    cout << "Wickets fallen: " << wicketsFallen << endl;
    cout << "Overs bowled: " << oversBowled << endl;
    if (target != 0)
    {
        cout << "Target: " << target << endl;
        cout << "Remaining score: " << remainingScore << endl;
        cout << "Remaining overs: " << remainingOvers << endl;
    }
}

// Function to toss
void toss()
{
    srand(time(0));
    int toss = rand() % 2;
    if (toss == 0)
        cout << "Team A won the toss." << endl;
    else
        cout << "Team B won the toss." << endl;
}

// Function to find player of the match
void findPlayerOfTheMatch(Player teamA[], Player teamB[])
{
    // Initializing variables
    int maxWicketsA = 0, maxWicketsB = 0;
    int maxRunsA = 0, maxRunsB = 0;
    string bowlerOfTheMatch, batsmanOfTheMatch;

    // Finding bowler of the match
    for (int i = 0; i < 7; i++)
    {
        if (teamA[i].wicketsTaken > maxWicketsA)
        {
            maxWicketsA = teamA[i].wicketsTaken;
            bowlerOfTheMatch = teamA[i].name;
        }
        if (teamB[i].wicketsTaken > maxWicketsB)
        {
            maxWicketsB = teamB[i].wicketsTaken;
            bowlerOfTheMatch = teamB[i].name;
        }
    }

    // Finding batsman of the match
    for (int i = 0; i < 7; i++)
    {
        if (teamA[i].runsScored > maxRunsA)
        {
            maxRunsA = teamA[i].runsScored;
            batsmanOfTheMatch = teamA[i].name;
        }
        if (teamB[i].runsScored > maxRunsB)
        {
            maxRunsB = teamB[i].runsScored;
            batsmanOfTheMatch = teamB[i].name;
        }
    }

    // Showing player of the match
    cout << "\nPlayer of the match:" << endl;
    cout << "Batsman of Match: " << batsmanOfTheMatch << endl;
    cout << "Bowler of Match: " << bowlerOfTheMatch << endl;
}

// Function to save match data
void saveMatchData(Player teamA[], Player teamB[], int overs, string batsmanOfTheMatch, string bowlerOfTheMatch)
{
    int maxWicketsA = 0, maxWicketsB = 0;
    int maxRunsA = 0, maxRunsB = 0;

    // Finding bowler of the match
    for (int i = 0; i < 7; i++)
    {
        if (teamA[i].wicketsTaken > maxWicketsA)
        {
            maxWicketsA = teamA[i].wicketsTaken;
            bowlerOfTheMatch = teamA[i].name;
        }
        if (teamB[i].wicketsTaken > maxWicketsB)
        {
            maxWicketsB = teamB[i].wicketsTaken;
            bowlerOfTheMatch = teamB[i].name;
        }
    }

    // Finding batsman of the match
    for (int i = 0; i < 7; i++)
    {
        if (teamA[i].runsScored > maxRunsA)
        {
            maxRunsA = teamA[i].runsScored;
            batsmanOfTheMatch = teamA[i].name;
        }
        if (teamB[i].runsScored > maxRunsB)
        {
            maxRunsB = teamB[i].runsScored;
            batsmanOfTheMatch = teamB[i].name;
        }
    }
    // Writing data to file
    ofstream matchData;
    matchData.open("matchData.txt");
    matchData << "Overs: " << overs << endl;
    matchData << "Batsman of Match: " << batsmanOfTheMatch << endl;
    matchData << "Bowler of Match: " << bowlerOfTheMatch << endl;
    matchData.close();

    // Showing message
    cout << "\nMatch data saved successfully." << endl;
}
