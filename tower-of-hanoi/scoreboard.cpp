#include "scoreboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ScoreboardMenu(){
	
}

void SortData(){
	
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
			data = fopen("literally_unplayable.dat","rb");
			break;
	}
	fread(record, sizeof(Player), 20, data);
	printf("| %25s | %5s | %4s |", "Name", "Steps", "Time");
	for(int i = 0;i < 20;i++){
		printf("| %25s |  %03d  | %04s |", record[i].name,record[i].step,record[i].time);
	}
	fclose(data);
}

void SaveData(Player newdata, int difficulty){
	Player record[20];
	for(int i = 0;i<20;i++){
		strcpy(record[i].name,"");
		record[i].step = 0;
		record[i].time = 0;
	}
	FILE *data;
	switch(difficulty){
		case 1:
			data = fopen("boring.dat","rb+");
			break;
		case 2:
			data = fopen("walk_in_the_park.dat","rb+");
			break;
		case 3:
			data = fopen("normal.dat","rb+");
			break;
		case 4:
			data = fopen("nightmare.dat","rb+");
			break;
		case 5:
			data = fopen("literally_unplayable.dat","rb+");
			break;
	}
	fread(record, sizeof(Player), 20, data);
	if(data != NULL){
		int i = 0;
		while(stricmp(record[i].name,"") != 0 && i < 19){
			if(stricmp(record[i].name, newdata.name) == 0){
				if(newdata.step < record[i].step){
					record[i] = newdata;
					fwrite(record, sizeof(Player), 20, data);
					fclose(data);
					return;
				}
				return;
			}
			i++;
		}
		record[i] = newdata;
		fwrite(record, sizeof(Player), 20, data);
		fclose(data);
		return;
	}
	record[0] = newdata;
	fwrite(record, sizeof(Player), 20, data);
	fclose(data);
}
