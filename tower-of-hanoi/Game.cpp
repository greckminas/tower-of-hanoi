#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Game::Game(char* username, int difficulty){
	this->username = (char*)malloc(strlen(username));
	strcpy(this->username, username);
	
	this->difficulty = difficulty;
	this->step = 0;
	this->finished = false;
	time(&this->start_time);

	this->tower[0] = Stack();
	this->tower[1] = Stack();
	this->tower[2] = Stack();

	for(int i = 0; i < this->difficulty; i++)
		this->tower[0].push(difficulty-i);
}

bool Game::setUsername(char* username){
	if(username[0] = '\0')
		return false;
	strcpy(this->username, username);
	return true;
}

char* Game::getUsername(){
	return this->username;
}

bool Game::setDifficulty(int difficulty){
	if(difficulty < 3 || difficulty > 8) //kurang dr 3 atau lebih dari 8
		return false;
	this->difficulty = difficulty;
	return true;
}

int Game::getDifficulty(){
	return this->difficulty;
}

void Game::print(){
	int max_height = 0;
	int height[3];

	//get height of all towers
	height[0] = this->tower[0].count();
	height[1] = this->tower[1].count();
	height[2] = this->tower[2].count();

	//get max height between all towers
	max_height = (height[0] > max_height) ? height[0] : max_height;
	max_height = (height[1] > max_height) ? height[1] : max_height;
	max_height = (height[2] > max_height) ? height[2] : max_height;

	printf("\xC9"); // /
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xBB\n"); // \ 

	printf("%c %-9s : %*s %c\n", '\xBA', "Username", 5-getDifficulty()*6, getUsername(), '\xBA');
	printf("%c %-9s : %*d %c\n", '\xBA', "Diff.", 5-getDifficulty()*6, getDifficulty(), '\xBA');
	printf("%c %-9s : %*d %c\n", '\xBA', "Step", 5-getDifficulty()*6, getStep(), '\xBA');

	printf("\xCC"); // /
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xB9\n"); // \ 

	for(int i = 0; i < this->difficulty; i++){
		printf("\xBA"); // |
		for(int j = 0; j < 3; j++)
			if(i < this->difficulty-height[j])
				printf(" %*s|%*s ", this->difficulty, "", this->difficulty, "");
			else{
				int fill = this->tower[j].peek(i-this->difficulty+height[j]);
				int empty = this->difficulty - fill;
				char* str_fill = "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
				printf(" %*s%.*s\xDB%.*s%*s ", empty, "", fill, str_fill, fill, str_fill, empty, "");
			}

		printf("\xBA\n");
	}
	printf("\xC8"); // \ 
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xBC\n"); // /

}

bool Game::isFinished(){
	return this->finished;
}

bool Game::checkTower(int tower){
	return (this->tower[tower].count() == this->difficulty);
}

int Game::getStep(){
	return this->step;
}

bool Game::move(int from, int to){
	//index 1-3

	//change index to 0-2
	from--;
	to--;
	
	//out of range
	if(from < 0 || from > 2 || to < 0 || to > 2)
		return false;

	//change to the same position
	if(from == to)
		return false;

	//game already finished, can't move
	if(isFinished())
		return false;

	int value_from = this->tower[from].peek(0);
	int value_to = this->tower[to].peek(0);
	//source tower is empty
	if(value_from == -1)
		return false;

	//destination is empty or valid move
	if(value_to == -1 || value_to > value_from){
		this->tower[to].push(this->tower[from].pop());

		this->step++;

		if(to != 0)
			this->finished = checkTower(to);

		if(isFinished())
			time(&this->finish_time);

		return true;
	}

	return false;
}

