#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Menu.h"
#include "Game.h"
#include "scoreboard.h"

void howToPlay();


bool surrenderPrompt(){
	char* prompt_list[] = { "     Yes    ", "    No      "};
	Menu surrenderMenu(2, prompt_list);
	
	while(true){
		system("cls");
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

		int key = _getch();
		if (key == 224) {
			switch(_getch()) { // the real value
				case 75: //left
					surrenderMenu.up();
					break;
				case 77: //right
					surrenderMenu.down();
					break;
			}
		} 
		else if (key == 13){ //if enter key pressed
			if(surrenderMenu.get() == 1)
				return true;
			return false;
		}
	}

}

void PlayGame(char* username, int difficulty){

	Game myGame(username, difficulty);
	
	char* tower_name[3];
	tower_name[0] = (char*)malloc(40);
	tower_name[1] = (char*)malloc(40);
	tower_name[2] = (char*)malloc(40);

	sprintf(tower_name[0], " %*sTower 1%*s", myGame.getDifficulty() - 2, "", myGame.getDifficulty() - 2, "");
	sprintf(tower_name[1], "%*sTower 2%*s", myGame.getDifficulty() - 2, "", myGame.getDifficulty() - 2, "");
	sprintf(tower_name[2], "%*sTower 3%*s", myGame.getDifficulty() - 2, "", myGame.getDifficulty() - 2, "");


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

		printf("\n ");
		int* selected_tower = towerMenu.get_all();
		for (int i = 1; i < 4; i++) {
			if (i == selected_tower[0])
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
		else if (key == 27){ //if escape key pressed
			if(surrenderPrompt())
				break;
		}
	}
	SaveData(myGame);
	SortData();
	system("pause");
}

void CreateGame(char* username, int* difficulty){
	char* level_list[] = {"[] Boring (3)\n", "[] Walk in the park (4)\n", "[] Normal (5)\n", "[] Nightmare (6)\n", "[] Just Surrender Already (7)\n", "[] Literally Unplayable (8)\n"};
	Menu difficultyMenu(6, level_list);
	char tempName[255] = "";
	while(true){
		
		system("cls");
		printf("Tower of Hanoi -> Play Game\n");
		printf("Username = ");

		//minimal 4 dan maksimal 12
		if(strlen(tempName) > 12 || strlen(tempName) < 4){
			scanf("%[^\n]%*c", tempName);
			fflush(stdin);
			continue;
		} else {
			printf("%s\n",tempName);
		}

		
		printf("Difficulty = \n");
		difficultyMenu.print();
		int key = _getch();
		if (key == 224) {
			switch (_getch()) { // arrow key value
			case 72: //up
				difficultyMenu.up();
				break;
			case 80: //down
				difficultyMenu.down();
				break;
			}
		}
		else if (key == 13) {
			strcpy(username, tempName);
			*difficulty = difficultyMenu.get()+2;
			break;
		}
	}
	return;
}

int main(){
	char* menu_awal[] = { ">> Play Game\n", ">> How To Play\n", ">> Scoreboard\n", ">> Exit Game\n" };
	Menu MainMenu(4, menu_awal);
	
	while (true) {
		system("cls");
		printf("Tower of Hanoi\n");
		MainMenu.print();
		int key = _getch();
		if (key == 224) {
			switch (_getch()) { // arrow key value
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
			{
				char name[15] = {};
				int diff = 3;
				CreateGame(name, &diff);
				PlayGame(name, diff);
			}
				break;
			case 2:
				howToPlay();
				break;
			case 3:
				ScoreboardMenu();
				break;
			case 4:
				exit(0);
				break;
			}
		}
	}

	return 0;
}

void howToPlay() {

	char* language[] = { ">> English\n", ">> Bahasa Indonesia\n", ">> Back to Main Menu\n" };
	Menu HTPMenu(3, language);

	while (1) {
		system("cls");
		
		printf("What language do you want to read?\n");
		HTPMenu.print();
		int ch = _getch();
		if (ch == 224) {
			switch (_getch()) { // arrow key value
			case 72: //up
				HTPMenu.up();
				break;
			case 80: //down
				HTPMenu.down();
				break;
			}
		}
		else if (ch == 13) { //if enter key pressed
			switch (HTPMenu.get()) {
			case 1: //english
				system("cls");
				printf("HOW TO PLAY\n");
				printf("In this game, you will use arrow key on your keyboard to navigate also enter/space button to confirm your action\n");
				printf("In the main menu, you have 4 choices:\n");
				printf("1. Play the game, you will play the game with the rules and how to as mentioned below\n");
				printf("\t 1.1. After you choose to play the game, you have to insert your name. This will be used later in the scoreboard \n");
				printf("\t 1.2. Picking your difficulty, there will be 6 difficulties you can pick\n");
				printf("\t\t -Boring, consist of 3 tower and 3 stacks\n");
				printf("\t\t -Walk in the park, consist of 3 tower and 4 stacks\n");
				printf("\t\t -Normal, consist of 3 tower and 5 stacks\n");
				printf("\t\t -Nightmare, consist of 3 tower and 6 stacks\n");
				printf("\t\t -Just Surrender Already, consist of 3 tower and 7 stacks\n");
				printf("\t\t -Literally Unplayable, consist of 3 tower and 8 stacks\n");
				printf("\t 1.3. Playing the game, the rule is the same like other Hanoi Tower game. To put it short, you have to move the stacks from its original tower to another tower. \n");
				printf("\t      You can move the stack by choosing the tower where the stack reside and press space.'F' will appear below the tower the tower you pick.\n");
				printf("\t      You can move the stack to the tower you want and press space. 'T'  will appear below the tower the tower you pick\n");
				printf("\t      One thing you should know, smaller stack can't be placed under a bigger stack\n");
				printf("\t      Don't forget to have fun :)\n");
				printf("\t 1.4. Repeat the 1.3 step until you finish the game, remember that every move you make is counted\n");
				printf("\t 1.5. Just in case you realize you suck at the game and can't finish the game, you may press 'esc' button and pick 'yes' to confirm your resignation of the game.\n");
				printf("2. How to play, you will be brought here, reading boring stuff like what you are doing right now\n");
				printf("3. Scoreboard, let you see your record on how good(or bad) you are at the game\n");
				printf("\t 3.1. There will be 6 scoreboards you can access after you finish all the 6 game difficulties\n");
				printf("\t 3.2. The scoreboard will ONLY show the top 10 who beat the game better than anyone else who have played before\n");
				printf("\t 3.3. 'Better' as mentioned above mean how fast you are at beating the game, both in time and move count\n");
				printf("4. Exit Game, really? i have to explain this you? \n");
				system("pause");
				break;
			case 2: //bahasa
				system("cls");
				printf("HOW TO PLAY\n");
				printf("Dalam permainan ini, anda akan menggunakan tonbol panah pada keyboard serta tombol enter/spasi untuk mengkonfirmasi aksi yang anda lakukan\n");
				printf("Di dalam menu utama, anda memmiliki 4 pilihan\n");
				printf("1. Play the game, anda akan memainkan permainan dengan aturan dan cara sesuai dengan apa yang dituliskan di bawha\n");
				printf("\t 1.1. Anda akan diminta untuk menginput username anda. Username akan digunakan nanti pada fitur Scoreboard \n");
				printf("\t 1.2. Memilih tingkat kesulitan, akan ada 6 tingkat kesulitan yang dapat and pilih\n");
				printf("\t\t -Boring, terdiri dari 3 menara dan 3 piring\n");
				printf("\t\t -Walk in the park, terdiri dari 3 menara dan 4 piring\n");
				printf("\t\t -Normal, terdiri dari 3 menara dan 5 piring\n");
				printf("\t\t -Nightmare, terdiri dari 3 menara dan 6 piring\n");
				printf("\t\t -Just Surrender Already, terdiri dari 3 menara dan 7 piring\n");
				printf("\t\t -Literally Unplayable, terdiri dari 3 menara dan 8 piring\n");
				printf("\t 1.3. Permainan dimulai, Aturan dari game tidak berbeda dengan game Hanoi Tower pada umumnya, anda harus memindahkan tumpukan piring pada tower awal ke tower lain\n");
				printf("\t      Anda dapat memindahkan suatu piring dengan cara memilih tower mana piring yang akan dipindahkan lalu menekan tombol spasi. 'F' akan muncul dibawah tower yang anda pilih\n");
				printf("\t      Anda dapat memindahkan suatu piring ke tower mana piring  akan dipindahkan lalu menekan tombol spasi. 'T' akan muncul dibawah tower yang anda pilih\n");
				printf("\t      You can move the stack to the tower you want and press space. 'T'  will appear below the tower the tower you pick\n");
				printf("\t      Satu hal yang perlu anda ingat, piring yang lebih kecil tidak bisa berada di bawah piring yang lebih besar\n");
				printf("\t      Dan jangan lupa untuk bersenang-senang dan berikan tantangan terbaik pada diri anda\n");
				printf("\t 1.4. Ulangi langkah 1.3 sampai anda menyelesaikan permainan, ingat bahwa semua langkah yang anda buat dihitung!\n");
				printf("\t 1.5. Jika anda sudah merasa tidak kuat dan tidak sanggup, anda tidak perlu melambaikan tangan anda ke kamera. Cukup tekan tombol 'esc' dan pilih 'yes'\n");
				printf("2. How to play, Anda akan dibawa ke layar ini dan membaca aturan-aturan seperti ini.\n");
				printf("3. Scoreboard, Melihat peringkat serta histori dari pemain yang memainkan permainan. Menampilkan 10 pemain terhebat pada tingkat kesulitan yang berbeda\n");
				printf("\t 3.1. Terdapat 6 scoreboard yang dapat diakses jika semua tingkat kesulitan permainan telah diselesaikan\n");
				printf("\t 3.2. Sccoreboard HANYA akan menampilkan 10 pemain terbaik yang menyelesaikan permainan lebih cepat dibanding pemain lain\n");
				printf("\t 3.3. Pemeringkatan dilakukan berdasarkan jumlah langkah yang dibutuhkan pemain untuk menyelesaikan permainan serta berapa lama waktu yang dibuthkan untuk pemain menyelesaikan permainan\n");
				printf("4. Exit Game, siapa yang tidak tahu fitur exit permainan, bukan anda pastinya\n");
				system("pause");
				break;
			case 3: //cancel, back to menu
				return;
			}
		}
	}
}