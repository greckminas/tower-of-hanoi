#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "Game.h"

class Scoreboard {
	typedef struct{
		char name[20];
		int time;
		int step;
	} Player;

public:
	static void print(int difficulty);
	static void sort(int difficulty);
	static void save(Game& data);
};

#endif
