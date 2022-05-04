#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

// .txt file structure
// player year team yards touchdowns interceptions rating
// We have a database of the stats of 4 players. 
// The year range is from 2018 to 2021; thus having 4 scores in total
// The first index will be the most recent year and the last index will be the oldest year
// We are defining a constant pair of variables so that we can use them in the program to start our arrays.
static const int NUM_PLAYERS = 4, NUM_YEARS = 4, YEAR_OFFSET = 1;
static int latestYear;

// helper 
typedef struct {char name[20];} playerName;
typedef struct {char team[5];} playerTeam;

// Declaring a type 'struct' so that we can get the stats of each player
typedef struct {int year; playerTeam team; int yards; int touchdowns; int interceptions; double rating;} stats;
// Declaring a struct to store each player's information
typedef struct {playerName name; stats stats;} player;


// This function will get information from stats.txt and return a database of players
player ** getDatabase() {
    player** players;
    players=(player**)malloc(sizeof(player*)*NUM_PLAYERS);
    for(int i=0;i<NUM_PLAYERS;i++) players[i]=(player*)malloc(sizeof(player)*NUM_YEARS);
    FILE * file = fopen("stats.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return players;
    }

    int fileIdx = 0;
    int playerIdx = 0;
    int yearIdx = 0;
    
    playerName name;
    playerTeam team;
    stats stats;
    player player;
    char n[20];
    char t[5];
    int yards, year, touchdowns, interceptions; 
    double rating;
    
    char line[100];

    while (!feof(file)) {

        fgets(line, 100, file);
        int read = sscanf(line, "%s %d %s %d %d %lf", n, &year, t, &yards, &touchdowns, &rating); 
        if (read != -1){
            strcpy(name.name, n);
            strcpy(team.team, t);

            strcpy(player.name.name, name.name);
            strcpy(stats.team.team, team.team);

            stats.year = year;
            stats.yards = yards;
            stats.touchdowns = touchdowns;
            stats.interceptions = interceptions;
            stats.rating = rating;

            player.stats = stats;
            players[playerIdx][yearIdx] = player;

/* 
            printf("%s %d %s %d %d %.2lf\n", 
            players[playerIdx][yearIdx].name.name,
            players[playerIdx][yearIdx].stats.year, 
            players[playerIdx][yearIdx].stats.team.team,
            players[playerIdx][yearIdx].stats.yards,
            players[playerIdx][yearIdx].stats.touchdowns,
            players[playerIdx][yearIdx].stats.rating); 

 */
        } else {
            printf("Error while reading file.\n");
            
            
        }
        
        // printf("%d %d | %d\n", playerIdx, yearIdx, fileIdx);

        fileIdx++;
        playerIdx = fileIdx / 4;
        yearIdx = fileIdx-(3*playerIdx)-(playerIdx);

   } 

/* 
            printf("%s %d %s %d %d %.2lf\n", 
            players[0][0].name.name,
            players[0][0].stats.year, 
            players[0][0].stats.team.team,
            players[0][0].stats.yards,
            players[0][0].stats.touchdowns,
            players[0][0].stats.rating); 

            printf("%s %d %s %d %d %.2lf\n", 
            players[3][0].name.name,
            players[3][0].stats.year, 
            players[3][0].stats.team.team,
            players[3][0].stats.yards,
            players[3][0].stats.touchdowns,
            players[3][0].stats.rating); 

*/

    fclose(file);
    return players;

}

// This function will return the current year
int getlatestYear() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);  
    return tm->tm_year + 1900 - YEAR_OFFSET;
}

// This function will list the players in the database
int listPlayers(player  ** players) {
    int op = 1;
    printf("These are the players in the database:\n\n");
    do
    {
    for(int i=0;i<NUM_PLAYERS;i++) {
    printf("%d) %s\n",i+1,players[i][0].name.name);}
    printf("\n");
    printf("Enter a number to pick a player:\n");
    scanf("%d", &op);
    } while (op < 1 || op > 4);
    return op;

};

// This function will list the years we have data for based on the current year and the years constant
int listYears(){ 
    int op = 1;
    printf("These are the years in the database:\n\n");
    do
    {
    for(int i=0;i<NUM_PLAYERS;i++) {
    printf("%d) %d\n",i+1,latestYear-i);}
    printf("\n");
    printf("Enter a number to pick a year:\n");
    scanf("%d", &op);
    } while (op < 1 || op > 4);
    return op;
}

// function to prints stats based on our 2d array of player objects and the selection of the user using indexes
void printStats(player ** players ,int playerOp, int yearOp){
    printf("Stats for %s (%d):\n",players[playerOp-1][yearOp-1].name.name,players[playerOp-1][yearOp-1].stats.year);
    printf("Team: %s  | Yards: %d | Touchdowns: %d | Rating: %.2lf\n", 
            players[playerOp-1][yearOp-1].stats.team.team,
            players[playerOp-1][yearOp-1].stats.yards,
            players[playerOp-1][yearOp-1].stats.touchdowns,
            players[playerOp-1][yearOp-1].stats.rating); 
};


// Main entry point for the c program
int main(){

    // Say hi to the user
    printf("Welcome to the 2018-2021 Stats Program!\n");
    char playing = 'y';
    while (playing == 'y'){
        
        // Set the current year
        latestYear = getlatestYear();
        
        // Setting the database
        player ** players = getDatabase();
        
        // List players names so that the user can choose which player to view
        int op = listPlayers(players);

        // List years so that the user can choose which year to view
        int yop = listYears();

        // Print the stats of the chosen player and year
        printStats(players, op, yop);

        // Ask the user if they want to play again

        printf("Would you like to keep going? (enter 'y' to play again | any other key to exit):\n");
        scanf(" %c", &playing);

    }
    return 0;
}