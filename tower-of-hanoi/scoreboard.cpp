#include "scoreboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void Scoreboard::sort(int difficulty){
	Player record[20] = {};
	Player temp;
	FILE *data;

	// membuka file berdasarkan difficultynya
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

	// jika file tidak ada, maka batalkan
	if (data == NULL) {
		return;
	}

	// baca 20 record Player
	fread(record, sizeof(Player), 20, data);

	// melakukan sorting berdasarkan step dan time
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

	//menutup file handle
	fclose(data);

	// membuka file berdasarkan difficultynya
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

	// menulis 20 record Player ke dalam file
	fwrite(record, sizeof(Player), 20, data);

	//menutup file handle
	fclose(data);
}

void Scoreboard::print(int difficulty){
	system("cls");
	Player record[20];
	FILE *data;

	// membuka file berdasarkan difficultynya
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

	// jika file tidak ditemukan
	if (data == NULL) {
		printf("No Record Found!!!\n");
		printf("Press any key to continue!\n");
		_getch();
		return;
	}

	// membaca 20 record Player pada file
	fread(record, sizeof(Player), 20, data);

	// print header tabel
	printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
	printf("\xBA %-24s \xBA %-7s \xBA %-8s \xBA\n", "          Name", " Steps", "Time (s)");
	printf("\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9\n");
	
	// print isi tabel
	for(int i = 0;i < 20;i++){
		if(record[i].name[0] == '\0')
			break;
		printf("\xBA %-24s \xBA %-7d \xBA %-8d \xBA\n", record[i].name,record[i].step,record[i].time);
	}

	// print footer tabel
	printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
	
	// menutup file handle
	fclose(data);
	printf("Press any key to continue!\n");
	_getch();
}

void Scoreboard::save(Game& prevgame){
	Player newdata;
	Player record[20] = {};
	FILE *data = NULL;

	// memindahkan data daro prevgame ke newdata
	strcpy(newdata.name, prevgame.getUsername());
	newdata.step = prevgame.getStep();
	newdata.time = (int)difftime(prevgame.getFinishTime(),prevgame.getStartTime());

	// membuka file handle berdasarkan difficultynya
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

	// jika file ditemukan
	if(data != NULL){
		// membaca 20 record Player dari file
		fread(record, sizeof(Player), 20, data);
		int i = 0;
		
		// jika file tidak kosong dan selama pointer belum mencapai baris 20, maka
		while(record[i].name[0] != 0 && i < 19){
			// jika nama sama, maka
			if(_stricmp(record[i].name, newdata.name) == 0){
				// bandingkan step dan waktu, jika lebih kecil maka
				if(newdata.step < record[i].step || (newdata.step == record[i].step && newdata.time < record[i].time)){
					// overwrite record
					record[i] = newdata;
					// menutup file handle
					fclose(data);
					// membuka file berdasarkan difficultynya
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
					// menulis 20 record Player ke file
					fwrite(record, sizeof(Player), 20, data);
				}
				// menutup file handle
				fclose(data);
				return;
			}
			i++;
		}
		// overwrite record
		record[i] = newdata;
		// menutup file handle
		fclose(data);
		// membuka file berdasarkan difficultynya
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
		// menulis 20 record Player ke file
		fwrite(record, sizeof(Player), 20, data);
		// menutup file handle
		fclose(data);
		return;
	}
	// overwrite record
	record[0] = newdata;
	// membuka file berdasarkan difficultynya
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
	// menulis 20 record Player ke file
	fwrite(record, sizeof(Player), 20, data);
	// menutup file handle
	fclose(data);
}
