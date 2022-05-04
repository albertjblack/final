#include<stdio.h>

#include<stdlib.h>

#include<string.h>
#include<time.h>

// .txt file structure

// player year team yards touchdowns interceptions rating

// We have a database of the stats of 4 players.

// The year range is from 2018 to 2021; thus having 4 scores in total

// The first index will be the most recent year and the last index will be the oldest year

// We are defining a constant pair of variables so that we can use them in the program to start our arrays.

static const int NUM_PLAYERS = 4, NUM_YEARS = 4, YEAR_OFFSET = 1;

static int currentYear;

// Declaring a type 'struct' so that we can get the stats of each player

typedef struct {int year; char * team[5]; int yards; int touchdowns; int interceptions; double rating;} stats;

// Declaring a struct to store each player's information

typedef struct {char * name[20]; stats * stats;} player;


// This function will get information from stats.txt and return a database of players

player** getDatabase() {

player** players;
players=(player**)malloc(sizeof(player*)*NUM_PLAYERS);
for(int i=0;i<NUM_PLAYERS;i++) players[i]=(player*)malloc(sizeof(player)*NUM_YEARS);
player player;

stats stats;

char line[100];

FILE * file = fopen("stats.txt", "r");

if (file == NULL) {

printf("Error opening file\n");

return players;

}

int fileIdx = 0;

int playerIdx = 0;

int yearIdx = 0;

while (!feof(file)) {

fgets(line, 100, file);

int read = sscanf(line, "%s %d %s %d %d %lf", players[playerIdx][yearIdx].name, &(*players[playerIdx][yearIdx].stats).year, (*players[playerIdx][yearIdx].stats).team, &(*players[playerIdx][yearIdx].stats).yards, &(*players[playerIdx][yearIdx].stats).touchdowns, &(*players[playerIdx][yearIdx].stats).rating);

if (read != -1){

printf("%s %d %s %d %d %.2lf\n", players[playerIdx][yearIdx].name, players[playerIdx][yearIdx].stats->year, players[playerIdx][yearIdx].stats->team, players[playerIdx][yearIdx].stats->yards, players[playerIdx][yearIdx].stats->touchdowns, players[playerIdx][yearIdx].stats->rating);

} else {

printf("Error while reading file.\n");

return players;

}

printf("%d %d | %d\n", playerIdx, yearIdx, fileIdx);

fileIdx++;

playerIdx = fileIdx / 4;

yearIdx = fileIdx-(3*playerIdx)-(playerIdx);

}

fclose(file);

return players;

}

// This function will return the current year

int getCurrentYear() {

time_t t = time(NULL);

struct tm *tm = localtime(&t);

return tm->tm_year + 1900 - YEAR_OFFSET;

}

// This function will list the players in the database

void listPlayers(player * players){

player player;

int playerCount = sizeof(*players) / sizeof(player);

for(int i = 0; i < playerCount; i++){

player = players[i];

//printf("%s\n", player.name);

}

};

// This function will list the years we have data for based on the current year and the years constant

void listYears(){

for (int i = 0; i < NUM_YEARS; i++){

printf("%d\n", currentYear - i);

}

}

void printStats(player player, int year){

};

// Main entry point for the c program

int main(){

// Say hi to the user

printf("Welcome to the 2018-2021 Stats Program!\n");

char playing = 'y';

while (playing == 'y'){

// Set the current year

currentYear = getCurrentYear();

// Setting the database

player ** players = getDatabase();

// List players names so that the user can choose which player to view

// listPlayers(players);

// List years so that the user can choose which year to view

// listYears();

// Print the stats of the chosen player and year

// printStats(player, year);

// Ask the user if they want to play again

printf("Would you like to keep going? (enter 'y' to play again):\n");

scanf(" %c", &playing);

}

return 0;

}