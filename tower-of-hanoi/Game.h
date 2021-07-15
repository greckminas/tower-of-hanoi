#ifndef GAME_H
#define GAME_H
#include <time.h>
#include "Stack.h"


class Game {
	char* username;
	int difficulty;
	int step;
	bool finished;
	time_t start_time;
	time_t finish_time;
	Stack tower[3];

	bool checkTower(int tower);

public:
	Game(char* username, int difficulty);

	bool setUsername(char* username);
	char* getUsername();
	bool setDifficulty(int difficulty);
	int getDifficulty();
	void print();
	bool isFinished();
	int getStep();
	bool move(int from, int to);
};

#endif