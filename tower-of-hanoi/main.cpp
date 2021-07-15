#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "Menu.h"
#include "Game.h"

<<<<<<< Updated upstream
=======
bool surrenderPrompt(){
	char* prompt_list[] = { "     Yes    ", "    No      "};
	Menu surrenderMenu(2, prompt_list);
>>>>>>> Stashed changes

int main(){
	bool is_play = false;
	char* menu_awal[] = {">> Play Game\n", ">> How To Play\n", ">> Scoreboard\n", ">> Exit Game\n"};
	Menu MainMenu(4, menu_awal);
	
	
	while(!is_play){
		
		system("cls");
<<<<<<< Updated upstream
		printf("Menu\n");
		MainMenu.print();
=======
		
		printf("\xC9"); // /
		for(int i = 0; i < 24; i++)
			printf("\xCD"); // -
		printf("\xBB\n"); // \ 

		printf("\xBA       Surrender?       \xBA\n\xBA");
		surrenderMenu.print();
		printf("\xBA\n\xC8");

		for(int i = 0; i < 24; i++)
			printf("\xCD"); // -
		printf("\xBC\n"); // /

>>>>>>> Stashed changes
		int key = _getch();
		if (key == 224) {
			switch(_getch()) { // the real value
				case 72: //up
					MainMenu.up();
					break;
				case 80: //down
					MainMenu.down();
					break;
			}
		} 
		else if (key == 13){ //if enter key pressed
			switch(MainMenu.get()){
				case 1:
					is_play = true;
					break;
				case 2:
					//how to play
					break;
				case 3:
					//scoreboard;
					break;
				case 4:
					exit(0);
					break;
			}
		}
		else if (key == 32){ //if space key pressed
			MainMenu.select();
		}
	}

	Game myGame("test_name",3);
	
	char* tower_name[3];
	tower_name[0] = (char*)malloc(40);
	tower_name[1] = (char*)malloc(40);
	tower_name[2] = (char*)malloc(40);
<<<<<<< Updated upstream
	sprintf(tower_name[0], "%*sTower 1%*s", myGame.getDifficulty()-2, "", myGame.getDifficulty()-2, "");
	sprintf(tower_name[1], "%*sTower 2%*s", myGame.getDifficulty()-2, "", myGame.getDifficulty()-2, "");
	sprintf(tower_name[2], "%*sTower 3%*s", myGame.getDifficulty()-2, "", myGame.getDifficulty()-2, "");
=======
	sprintf(tower_name[0], " %*sTower 1%*s", myGame.getDifficulty() - 2, "", myGame.getDifficulty() - 2, "");
	sprintf(tower_name[1], "%*sTower 2%*s", myGame.getDifficulty() - 2, "", myGame.getDifficulty() - 2, "");
	sprintf(tower_name[2], "%*sTower 3%*s", myGame.getDifficulty() - 2, "", myGame.getDifficulty() - 2, "");
>>>>>>> Stashed changes


	Menu towerMenu(3, tower_name, 2);
	free(tower_name[0]);
	free(tower_name[1]);
	free(tower_name[2]);

	while(true){
		system("cls");
		myGame.print();
		towerMenu.print();
		if(myGame.isFinished())
			break;
<<<<<<< Updated upstream
		printf("\n");
		int *selected_tower = towerMenu.get_all();
		for(int i = 1; i<4; i++){
			if(i == selected_tower[0])
=======
		printf("\n ");
		int* selected_tower = towerMenu.get_all();
		for (int i = 1; i < 4; i++) {
			if (i == selected_tower[0])
>>>>>>> Stashed changes
				printf(" %*sF%*s ", myGame.getDifficulty(), "", myGame.getDifficulty(), "");
			else if(i == selected_tower[1])
				printf(" %*sT%*s ", myGame.getDifficulty(), "", myGame.getDifficulty(), "");
			else
				printf(" %*s %*s ", myGame.getDifficulty(), "", myGame.getDifficulty(), "");
		}

		int key = _getch();
		if (key == 224) {
			switch(_getch()) { // the real value
				case 75: //left
					towerMenu.up();
					break;
				case 77: //right
					towerMenu.down();
					break;
			}
		} 
		else if (key == 13){ //if enter key pressed
			if(myGame.move(selected_tower[0], selected_tower[1]))
				towerMenu.reset();
		}
		else if (key == 32){ //if space key pressed
			towerMenu.select();
		}
	}
	printf("\n%d", myGame.getStep());
	system("pause");
<<<<<<< Updated upstream
=======
}

int main(){
	char* menu_awal[] = { ">> Play Game\n", ">> How To Play\n", ">> Scoreboard\n", ">> Exit Game\n" };
	Menu MainMenu(4, menu_awal);
	
	while (true) {
		system("cls");
		printf("Menu\n");
		MainMenu.print();
		int key = _getch();
		if (key == 224) {
			switch (_getch()) { // the real value
			case 72: //up
				MainMenu.up();
				break;
			case 80: //down
				MainMenu.down();
				break;
			}
		}
		else if (key == 13) { //if enter key pressed
			switch (MainMenu.get()) {
			case 1:
				PlayGame("myUsername",3);
				break;
			case 2:
				//how to play
				break;
			case 3:
				//scoreboard;
				break;
			case 4:
				exit(0);
				break;
			}
		}
	}

	
>>>>>>> Stashed changes
	return 0;
}