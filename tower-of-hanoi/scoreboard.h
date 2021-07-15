#ifndef SCOREBOARD_H
#define SCOREBOARD_H

typedef struct{
	char *name;
	int time;
	int step;
}Player;

void ScoreboardMenu();

void SortData();

void ShowScoreboard(char *difficulty);

void SaveData(Player newdata);
