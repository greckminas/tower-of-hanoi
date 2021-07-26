#ifndef GAME_H
#define GAME_H
#include <time.h>
#include "Stack.h"


class Game {
	char* username; //username dari game
	int difficulty; //tingkat kesulitan game
	int step; //jumlah step game saat ini
	bool finished; //status kemenangan
	time_t start_time; //waktu dimulainya game
	time_t finish_time; //waktu berakhirnya game
	Stack tower[3]; //tower

	/* TOWER CHECK */
	bool checkTower(int tower);

public:
	/* CONSTRUCTOR */
	Game(char* username, int difficulty);

	/* DESTRUCTOR */
	~Game();

	/* GETTER AND SETTER USERNAME */
	bool setUsername(char* username);
	char* getUsername();

	/* GETTER AND SETTER DIFFICULTY */
	bool setDifficulty(int difficulty);
	int getDifficulty();

	/* PRINT GAME */
	void print();
	void print_blank();

	/* GET GAME STATUS */
	bool isFinished();
	int getStep();
	time_t getStartTime();
	time_t getFinishTime();

	/* MOVE NODE */
	bool move(int from, int to);
	
};

#endif