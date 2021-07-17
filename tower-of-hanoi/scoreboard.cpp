#include "scoreboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "Menu.h"

void ScoreboardMenu(){
	char* difficulty[] = { ">> Boring\n", ">> Walk In The Park\n", ">> Normal\n", ">> Nightmare\n", ">> Just Surrender Already\n", ">> Literally Unplayable\n", ">> Back\n" };
	Menu scoreboard(7, difficulty);

	while (true) {
		system("cls");
		printf("Select Difficulty:\n");
		scoreboard.print();
		int key = _getch();
		if (key == 224) {
			switch (_getch()) { // the real value
			case 72: //up
				scoreboard.up();
				break;
			case 80: //down
				scoreboard.down();
				break;
			}
		}
		else if (key == 13) { //if enter key pressed
			int difficulty = scoreboard.get();
			switch(difficulty){
			case 7:
				return;
			default:
				ShowScoreboard(difficulty);
				break;
			}
		}
	}
}

void SortData(int difficulty){
	Player record[20];
	Player temp;
	FILE *data;
	switch(difficulty){
		case 1:
			data = fopen("boring.dat","rb");
			break;
		case 2:
			data = fopen("walk_in_the_park.dat","rb");
			break;
		case 3:
			data = fopen("normal.dat","rb");
			break;
		case 4:
			data = fopen("nightmare.dat","rb");
			break;
		case 5:
			data = fopen("just_surrender_already.dat","rb");
			break;
		case 6:
			data = fopen("literally_unplayable.dat","rb");
			break;
	}
	if (data == NULL) {
		return;
	}
	fread(record, sizeof(Player), 20, data);
	for(int i = 0; i < 19 ; i++){
		for(int j = i;j < 20;j++){
			if(record[i].step > record[j].step){
				temp = record[i];
				record[i] = record[j];
				record[j] = temp;
			}
		}
	}
	fclose(data);
	switch (difficulty) {
	case 1:
		data = fopen("boring.dat", "wb");
		break;
	case 2:
		data = fopen("walk_in_the_park.dat", "wb");
		break;
	case 3:
		data = fopen("normal.dat", "wb");
		break;
	case 4:
		data = fopen("nightmare.dat", "wb");
		break;
	case 5:
		data = fopen("just_surrender_already.dat", "wb");
		break;
	case 6:
		data = fopen("literally_unplayable.dat", "wb");
		break;
	}
	fwrite(record, sizeof(Player), 20, data);
	fclose(data);
}

void ShowScoreboard(int difficulty){
	system("cls");
	Player record[20];
	FILE *data;
	switch(difficulty){
		case 1:
			data = fopen("boring.dat","rb");
			break;
		case 2:
			data = fopen("walk_in_the_park.dat","rb");
			break;
		case 3:
			data = fopen("normal.dat","rb");
			break;
		case 4:
			data = fopen("nightmare.dat","rb");
			break;
		case 5:
			data = fopen("just_surrender_already.dat","rb");
			break;
		case 6:
			data = fopen("literally_unplayable.dat","rb");
			break;
	}
	if (data == NULL) {
		printf("No Record Found!!!\n");
		system("pause");
		return;
	}
	fread(record, sizeof(Player), 20, data);
	printf("| %25s | %5s | %4s |\n", "Name", "Steps", "Time");
	for(int i = 0;i < 20;i++){
		printf("| %25s |  %03d  | %04d |\n", record[i].name,record[i].step,record[i].time);
	}
	fclose(data);
	system("pause");
}

void SaveData(Game& prevgame){
	Player newdata;
	strcpy(newdata.name, prevgame.getUsername());
	newdata.step = prevgame.getStep();
	newdata.time = 0;
	Player record[20] = {};
	for(int i = 0;i<20;i++){
		strcpy(record[i].name,"");
		record[i].step = 0;
		record[i].time = 0;
	}
	FILE *data = NULL;
	switch(prevgame.getDifficulty()-2){
		case 1:
			data = fopen("boring.dat","rb");
			break;
		case 2:
			data = fopen("walk_in_the_park.dat","rb");
			break;
		case 3:
			data = fopen("normal.dat","rb");
			break;
		case 4:
			data = fopen("nightmare.dat","rb");
			break;
		case 5:
			data = fopen("just_surrender_already.dat","rb");
			break;
		case 6:
			data = fopen("literally_unplayable.dat","rb");
			break;
	}
	if(data != NULL){
		fread(record, sizeof(Player), 20, data);
		int i = 0;
		while(strcmp(record[i].name,"") != 0 && i < 19){
			if(strcmp(record[i].name, newdata.name) == 0){
				if(newdata.step < record[i].step){
					record[i] = newdata;
					fclose(data);
					switch (prevgame.getDifficulty() - 2) {
					case 1:
						data = fopen("boring.dat", "wb");
						break;
					case 2:
						data = fopen("walk_in_the_park.dat", "wb");
						break;
					case 3:
						data = fopen("normal.dat", "wb");
						break;
					case 4:
						data = fopen("nightmare.dat", "wb");
						break;
					case 5:
						data = fopen("just_surrender_already.dat", "wb");
						break;
					case 6:
						data = fopen("literally_unplayable.dat", "wb");
						break;
					}
					fwrite(record, sizeof(Player), 20, data);
					fclose(data);
				}
				return;
			}
			i++;
		}
		record[i] = newdata;
		fclose(data);
		switch (prevgame.getDifficulty() - 2) {
		case 1:
			data = fopen("boring.dat", "wb");
			break;
		case 2:
			data = fopen("walk_in_the_park.dat", "wb");
			break;
		case 3:
			data = fopen("normal.dat", "wb");
			break;
		case 4:
			data = fopen("nightmare.dat", "wb");
			break;
		case 5:
			data = fopen("just_surrender_already.dat", "wb");
			break;
		case 6:
			data = fopen("literally_unplayable.dat", "wb");
			break;
		}
		fwrite(record, sizeof(Player), 20, data);
		fclose(data);
		return;
	}
	record[0] = newdata;
	switch (prevgame.getDifficulty() - 2) {
	case 1:
		data = fopen("boring.dat", "wb");
		break;
	case 2:
		data = fopen("walk_in_the_park.dat", "wb");
		break;
	case 3:
		data = fopen("normal.dat", "wb");
		break;
	case 4:
		data = fopen("nightmare.dat", "wb");
		break;
	case 5:
		data = fopen("just_surrender_already.dat", "wb");
		break;
	case 6:
		data = fopen("literally_unplayable.dat", "wb");
		break;
	}
	fwrite(record, sizeof(Player), 20, data);
	fclose(data);
}
