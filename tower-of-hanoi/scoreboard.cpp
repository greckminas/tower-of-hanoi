#include "scoreboard.h"
#include "stdio.h"
#include <string.h>

void ScoreboardMenu(){
	
}

void SortData(){
	
}

void ShowScoreboard(int difficulty){
	
}

void SaveData(Player newdata, int difficulty){
	Player record[20];
	for(int i = 0;i<20;i++){
		strcpy(record[i].name,"");
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
		while(stricmp(record[i].name,"") != 0){
			if(stricmp(record[i].name, newdata.name) == 0){
				if(newdata.step < record[i].step){
					record[i] = newdata;
					fwrite(record, sizeof(Player), 20, data);
					return;
				}
				return;
			}
			i++;
		}
		record[i] = newdata;
		fwrite(record, sizeof(Player), 20, data);
	}
	record[0] = newdata;
	fwrite(record, sizeof(Player), 20, data);
}
