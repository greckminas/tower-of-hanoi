#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "Game.h"

typedef struct{
	char name[20];
	int time;
	int step;
}Player;

void ScoreboardMenu();

void SortData();

void ShowScoreboard(int difficulty);

void SaveData(Game& data);

#endif
