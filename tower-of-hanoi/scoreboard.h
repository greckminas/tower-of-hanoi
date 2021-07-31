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
	/* PRINT SCOREBOARD */
	static void print(int difficulty);

	/* SORT SCOREBOARD */
	static void sort(int difficulty);

	/* APPEND SCOREBOARD */
	static void save(Game& data);
};

#endif
