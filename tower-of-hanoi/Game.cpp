#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Game::Game(char* username, int difficulty){
	//mengalokasikan username dan memindahkannya
	this->username = (char*) malloc(strlen(username)+1);
	strcpy(this->username, username);
	
	//mengatur difficulty, step, status selesai, dan waktu awal
	this->difficulty = difficulty;
	this->step = 0;
	this->finished = false;
	time(&this->start_time);

	//menginstansiasi 3 stack sebagai tower
	this->tower[0] = Stack();
	this->tower[1] = Stack();
	this->tower[2] = Stack();
	
	//menginisialisasi tower pertama
	for(int i = 0; i < this->difficulty; i++)
		this->tower[0].push(difficulty-i);
}

Game::~Game(){
	//membebaskan memori dari username
	free(this->username);
}

bool Game::setUsername(char* username){
	//jika parameter username kosong, maka batalkan
	if(username[0] = '\0')
		return false;

	//mengatur username
	strcpy(this->username, username);
	return true;
}

char* Game::getUsername(){
	//mengembalikan username ke modul pemanggil
	return this->username;
}

bool Game::setDifficulty(int difficulty){
	//jika difficulty kurang dari 3 atau lebih dari 8, maka batalkan
	if(difficulty < 3 || difficulty > 8) 
		return false;

	//mengatur difficulty
	this->difficulty = difficulty;
	return true;
}

int Game::getDifficulty(){
	//mengembalikan difficulty ke modul pemanggil
	return this->difficulty;
}

void Game::print(){
	/* KAMUS DATA */
	int max_height = 0;
	int height[3];

	/* ALGORITMA */
	//mendapatkan tinggi dari setiap tower
	height[0] = this->tower[0].count();
	height[1] = this->tower[1].count();
	height[2] = this->tower[2].count();

	//mendapatkan tinggi maksimal dari ketiga tower
	max_height = (height[0] > max_height) ? height[0] : max_height;
	max_height = (height[1] > max_height) ? height[1] : max_height;
	max_height = (height[2] > max_height) ? height[2] : max_height;

	//print border
	printf("\xC9"); // /
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xBB\n"); // \ 

	//print status game (username, difficulty, step)
	printf("%c %-10s: %*s %c\n", '\xBA', "Username", 5-getDifficulty()*6, getUsername(), '\xBA');
	printf("%c %-10s: %1d %*s %c\n", '\xBA', "Difficulty", getDifficulty(), 7-getDifficulty()*6, "Piring", '\xBA');
	printf("%c %-10s: %*d %c\n", '\xBA', "Step", 5-getDifficulty()*6, getStep(), '\xBA');

	//print border
	printf("\xCC"); // /
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xB9\n"); // \ 

	//print tower
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

	//print border
	printf("\xC8"); // \ 
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xBC\n"); // /

}

void Game::print_blank(){
	/* KAMUS DATA */
	int max_height = 0;
	int height[3];

	/* ALGORITMA */
	//mendapatkan tinggi dari setiap tower
	height[0] = this->tower[0].count();
	height[1] = this->tower[1].count();
	height[2] = this->tower[2].count();

	//mendapatkan tinggi maksimal dari ketiga tower
	max_height = (height[0] > max_height) ? height[0] : max_height;
	max_height = (height[1] > max_height) ? height[1] : max_height;
	max_height = (height[2] > max_height) ? height[2] : max_height;

	//print border
	printf("\xC9"); // /
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xBB\n"); // \ 

	//print status game (username, difficulty, step)
	printf("%c %-10s: %*s %c\n", '\xBA', "Username", 5-getDifficulty()*6, getUsername(), '\xBA');
	printf("%c %-10s: %1d %*s %c\n", '\xBA', "Difficulty", getDifficulty(), 7-getDifficulty()*6, "Piring", '\xBA');
	printf("%c %-10s: %*d %c\n", '\xBA', "Step", 5-getDifficulty()*6, getStep(), '\xBA');

	//print border
	printf("\xCC"); // /
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xB9\n"); // \ 

	//print tower
	for(int i = 0; i < this->difficulty; i++){
		printf("\xBA"); // |
		for(int j = 0; j < 3; j++){
			int last_step = -1;
			int fill = this->tower[j].peek(i-this->difficulty+height[j], &last_step);
			if(i < this->difficulty-height[j] || last_step < this->step-2)
				printf(" %*s|%*s ", this->difficulty, "", this->difficulty, "");
			else{
				
				int empty = this->difficulty - fill;
				char* str_fill = "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
				printf(" %*s%.*s\xDB%.*s%*s ", empty, "", fill, str_fill, fill, str_fill, empty, "");
			}
		}
		printf("\xBA\n");
	}

	//print border
	printf("\xC8"); // \ 
	for(int i = 0; i < 9+this->difficulty*6; i++)
		printf("\xCD"); // -
	printf("\xBC\n"); // /

}

bool Game::isFinished(){
	//mengembalikan status kemenangan ke modul pemanggil
	return this->finished;
}

bool Game::checkTower(int tower){
	//mengecek apakah tower sudah penuh atau belum
	//mengembalikannya ke modul pemanggil
	return (this->tower[tower].count() == this->difficulty);
}

int Game::getStep(){
	//mengembalikan jumlah step ke modul pemanggil
	return this->step;
}

bool Game::move(int from, int to){
	//indeks input 1 - 3

	//mengubah indeks menjadi 0 - 2
	from--;
	to--;
	
	//cek apakah input out of range
	if(from < 0 || from > 2 || to < 0 || to > 2)
		return false;

	//cek apakah input berusaha untuk mengubah tower ke tempat yang sama
	if(from == to)
		return false;

	//cek apakah game sudah selesai atau belum
	if(isFinished())
		return false;
	
	//menampung value dari stack awal dan tujuan
	int value_from = this->tower[from].peek(0);
	int value_to = this->tower[to].peek(0);

	//jika stack tower asal kosong, maka tidak gerak
	if(value_from == -1)
		return false;

	// jika stack tower tujuan kosong
	// atau
	// jika value stack tower tujuan lebih besar dari value stack tower asal
	// maka gerak
	if(value_to == -1 || value_to > value_from){
		//pop dari stack asal dan push ke stack tujuan
		this->tower[to].push(this->tower[from].pop(), this->getStep());

		//menambah step
		this->step++;

		//jika tower tujuan bukan tower pertama, maka cek kemenangan
		if(to != 0)
			this->finished = checkTower(to);

		//jika sudah menang, maka catat waktu akhir
		if(isFinished())
			time(&this->finish_time);

		return true;
	}

	return false;
}

time_t Game::getStartTime(){
	//mengembalikan waktu awal ke modul pemanggil
	return this->start_time;
}

time_t Game::getFinishTime(){
	//mengembalikan waktu akhir ke modul pemanggil
	return this->finish_time;
}