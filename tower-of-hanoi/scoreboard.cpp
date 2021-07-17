#include "scoreboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void Scoreboard::sort(int difficulty){
	Player record[20] = {};
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
		if(record[i].name[0] == '\0')
			continue;
		for(int j = i;j < 20;j++){
			if(record[j].name[0] == '\0')
				continue;
			if(record[i].step > record[j].step || (record[i].step == record[j].step && record[i].time > record[j].time)){
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

void Scoreboard::print(int difficulty){
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
		printf("Press any key to continue!\n");
		_getch();
		return;
	}
	fread(record, sizeof(Player), 20, data);
	printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
	printf("\xBA %-24s \xBA %-7s \xBA %-8s \xBA\n", "          Name", " Steps", "Time (s)");
	printf("\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9\n");
	for(int i = 0;i < 20;i++){
		if(record[i].name[0] == '\0')
			break;
		printf("\xBA %-24s \xBA %-7d \xBA %-8d \xBA\n", record[i].name,record[i].step,record[i].time);
	}
	printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
	fclose(data);
	printf("Press any key to continue!\n");
	_getch();
}

void Scoreboard::save(Game& prevgame){
	Player newdata;
	strcpy(newdata.name, prevgame.getUsername());
	newdata.step = prevgame.getStep();
	newdata.time = (int)difftime(prevgame.getFinishTime(),prevgame.getStartTime());
	Player record[20] = {};
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
		
		while(record[i].name[0] != 0 && i < 19){
			if(_stricmp(record[i].name, newdata.name) == 0){
				if(newdata.step < record[i].step || (newdata.step == record[i].step && newdata.time < record[i].time)){
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
