#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cwchar>
#include "Menu.h"
#include "Game.h"
#include "scoreboard.h"


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

void PlayGame(char* username, int difficulty, bool is_blank = false){

	Game myGame(username, difficulty);
	bool isSurrender = false;
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
		if(is_blank)
			myGame.print_blank();
		else
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
			if(surrenderPrompt()){
				PlaySound("sound/losing_game.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
				isSurrender = true;
				system("cls");
				myGame.print();
				printf("You surrendered the game!");
				break;
			}
				
		}
	}
	if(is_blank && !isSurrender){
		PlaySound("sound/video_win.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		system("cls");
		myGame.print();
	} else if (!isSurrender){
		PlaySound("sound/video_win.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		Scoreboard::save(myGame);
		Scoreboard::sort(myGame.getDifficulty());
	}
	printf("\nGame ended!\nPress any key to continue!\n");
	_getch();
}

void PlayGame_ImAlive(char* username, int difficulty){

	Game myGame(username, difficulty);
	char* tower_name[3];
	char message[255] = "";
	bool isSurrender = false;
	bool is_blank = false;
	int last_from = 0;
	int last_to = 0;
	int move_type = 0;

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
		if(is_blank)
			myGame.print_blank();
		else
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
		if(message[0] != '\0')
			printf("\n%s\n",message);

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
			int randomNumber = (rand() % 5) + 1;
			while(move_type == 3 && move_type == randomNumber){
				randomNumber = (rand() % 5) + 1;
			}
			move_type = randomNumber;
			switch(move_type){
			case 1:
			{
				//move ke tower yang ga dipilih
				if(myGame.move(selected_tower[0], 6-(selected_tower[0]+selected_tower[1]))){
					is_blank = false;
					last_from = selected_tower[0];
					last_to = 6-(selected_tower[0]+selected_tower[1]);
					towerMenu.reset();
					strcpy(message, "nah, nevermind i'm going this way~ :>\n");
				} else if(myGame.move(selected_tower[0], selected_tower[1])){
					is_blank = false;
					last_from = selected_tower[0];
					last_to = selected_tower[1];
					towerMenu.reset();
					strcpy(message, "you're lucky this time, i can't move to other tower. >:(\n");
				}
				break;
			}
			case 2:
				//undo move
				if(myGame.move(last_to, last_from)){
					is_blank = false;
					last_from = last_to;
					last_to = last_from;
					towerMenu.reset();
					printf("i don't want to move\n");
					Sleep(800);
					printf(".");
					Sleep(800);
					printf(".");
					Sleep(800);
					printf(".");
					Sleep(800);
					printf("You know what\n");
					Sleep(1600);
					strcpy(message, "Let's just go back\n");
				}
				break;
			case 3:
				//sleep terus move
				printf("\nZzz");
				Sleep(800);
				printf(".");
				Sleep(800);
				printf(".");
				Sleep(800);
				printf(".");
				Sleep(800);
				printf(" o.o");
				Sleep(400);
				printf("\b\b\bO.o");
				Sleep(400);
				printf("\b\b\bo.0");
				Sleep(600);
				printf("\b\b\b0.o");
				Sleep(800);
				printf("\b\b\b\b, ha?");
				Sleep(1500);
				printf(" you want me to move?\n");
				Sleep(1700);
				printf("come on, i'm still sleepy\n");
				Sleep(2700);
				printf("are you still waiting for me?\n");
				Sleep(2300);
				printf("ok fine, i'm moving >:(\n");
				Sleep(1700);
				if(myGame.move(selected_tower[0], selected_tower[1])){
					is_blank = false;
					last_from = selected_tower[0];
					last_to = selected_tower[1];
					towerMenu.reset();
					strcpy(message, "satisfied, huh?\n");
				}
				break;
			case 4:
				//blind
				if(myGame.move(selected_tower[0], selected_tower[1])){
					is_blank = true;
					last_from = selected_tower[0];
					last_to = selected_tower[1];
					towerMenu.reset();
					strcpy(message, "HEHEHEHE, CAN'T SEE ME NOW!\n");
				}
				break;
			case 5:
				//normal
				if(myGame.move(selected_tower[0], selected_tower[1])){
					is_blank = false;
					last_from = selected_tower[0];
					last_to = selected_tower[1];
					towerMenu.reset();
					message[0] = '\0';
				}
				break;


			}
			if(myGame.move(selected_tower[0], selected_tower[1]))
				towerMenu.reset();
		}
		else if (key == 32){ //if space key pressed
			towerMenu.select();
		}
		else if (key == 27){ //if escape key pressed
			if(surrenderPrompt()){
				PlaySound("sound/losing_game.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
				isSurrender = true;
				system("cls");
				myGame.print();
				printf("You surrendered the game!");
				break;
			}
				
		}
	}
	if (!isSurrender){
		PlaySound("sound/video_win.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		Scoreboard::save(myGame);
		Scoreboard::sort(myGame.getDifficulty());
	}
	printf("\nGame ended!\nPress any key to continue!\n");
	_getch();
}

void CreateGame(char* username, int* difficulty){
	char* level_list[] = {"[] Boring (3)\n", "[] Walk in the park (4)\n", "[] Normal (5)\n", "[] Nightmare (6)\n", "[] Just Surrender Already (7)\n", "[] Literally Unplayable (8)\n"};
	Menu difficultyMenu(6, level_list);
	char tempName[255] = "";
	while(true){
		
		system("cls");
		printf("Temple Trouble -> Play Game\n\n");
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

void HowToPlay() {

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
				printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
				printf("\xBA%-80s\xBA\n", "HOW TO PLAY");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "In this game, you will use arrow key on your keyboard to navigate also enter or ", "space button to confirm your action.");
				printf("\xBA%-80s\xBA\n", "In the main menu, you have 4 choices :");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1. Play the game, you will play the game with the rules and how to as mentioned ", "   below");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.1. After you choose to play the game, you have to insert your name. This will ", "     be used later in the scoreboard");
				printf("\xBA%-80s\xBA\n", "1.2. Picking your difficulty, there will be 6 difficulties you can pick");
				printf("\xBA%-80s\xBA\n", "       - Boring, consist of 3 tower and 3 stacks");
				printf("\xBA%-80s\xBA\n", "       - Walk in the park, consist of 3 tower and 4 stacks");
				printf("\xBA%-80s\xBA\n", "       - Normal, consist of 3 tower and 5 stacks");
				printf("\xBA%-80s\xBA\n", "       - Nightmare, consist of 3 tower and 6 stacks");
				printf("\xBA%-80s\xBA\n", "       - Just Surrender Already, consist of 3 tower and 7 stacks");
				printf("\xBA%-80s\xBA\n", "       - Literally Unplayable, consist of 3 tower and 8 stacks");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.3. Playing the game, the rule is the same like other Hanoi Tower game. To put ", "     it short, you have to move the stacks from its original tower to another ", "     tower.");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "      - You can move the stack by choosing the tower where the stack reside and ", "        press space.'F' will appear below the tower the tower you pick.");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "      - You can move the stack to the tower you want and press space. 'T'  will ", "        appear below the tower the tower you pick");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "      - One thing you should know, smaller stack can't be placed under a bigger ", "        stack.");
				printf("\xBA%-80s\xBA\n", "      - Don't forget to have fun :)");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.4. Repeat the 1.3 step until you finish the game, remember that every move you","     make is counted");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.5. Just in case you realize you suck at the game and can't finish the game, ","     you may press 'esc' button and pick 'yes' to confirm your resignation of ","     the game.");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "2. How to play, you will be brought here, reading boring stuff like what you are","   doing right now");
				printf("\xBA%-80s\xBA\n", "3. Scoreboard, let you see your record on how good(or bad) you are at the game");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "3.1. There will be 6 scoreboards you can access after you finish all the 6 game ","     difficulties");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "3.2. The scoreboard will ONLY show the top 10 who beat the game better than ","     anyone else who have played before");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "3.3. 'Better' as mentioned above mean how fast you are at beating the game, both","     in time and move count");
				printf("\xBA%-80s\xBA\n", "4. Exit Game, really? i have to explain this you?");
				printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
				printf("Press any key to continue!\n");

				_getch();
				break;
			case 2: //bahasa
				system("cls");
				printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
				printf("\xBA%-80s\xBA\n", "CARA BERMAIN");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "Dalam permainan ini, anda akan menggunakan tonbol panah pada keyboard serta ", "tombol enter atau spasi untuk mengkonfirmasi aksi yang anda lakukan.");
				printf("\xBA%-80s\xBA\n", "Di dalam menu utama, anda memmiliki 4 pilihan");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1. Play the game, anda akan memainkan permainan dengan aturan dan cara sesuai ","   dengan apa yang dituliskan di bawah");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.1. Anda akan diminta untuk menginput username anda. Username akan digunakan ","     nanti pada fitur Scoreboard");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.2. Memilih tingkat kesulitan, akan ada 6 tingkat kesulitan yang dapat anda ","     pilih, yaitu:");
				printf("\xBA%-80s\xBA\n", "       - Boring, terdiri dari 3 menara dan 3 piring");
				printf("\xBA%-80s\xBA\n", "       - Walk in the park, terdiri dari 3 menara dan 4 piring");
				printf("\xBA%-80s\xBA\n", "       - Normal, terdiri dari 3 menara dan 5 piring");
				printf("\xBA%-80s\xBA\n", "       - Nightmare, terdiri dari 3 menara dan 6 piring");
				printf("\xBA%-80s\xBA\n", "       - Just Surrender Already, terdiri dari 3 menara dan 7 piring");
				printf("\xBA%-80s\xBA\n", "       - Literally Unplayable, terdiri dari 3 menara dan 8 piring");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.3. Permainan dimulai, Aturan dari game tidak berbeda dengan game Hanoi Tower","       pada umumnya, anda harus memindahkan tumpukan piring pada tower awal ke ","       tower lain");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "      - Anda dapat memindahkan suatu piring dengan cara memilih tower mana ","        piring yang akan dipindahkan lalu menekan tombol spasi. 'F' akan muncul ","        dibawah tower yang anda pilih");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "      - Anda dapat memindahkan suatu piring ke tower mana piring akan ","        dipindahkan lalu menekan tombol spasi. 'T' akan muncul di bawah tower ","        yang anda pilih");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "      - Satu hal yang perlu anda ingat, piring yang lebih kecil tidak bisa ","        berada di bawah piring yang lebih besar");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "      - Dan jangan lupa untuk bersenang-senang dan berikan tantangan terbaik ","        pada diri anda");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.4. Ulangi langkah 1.3 sampai anda menyelesaikan permainan, ingat bahwa semua","     langkah yang anda buat dihitung!");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "1.5. Jika anda sudah merasa tidak kuat dan tidak sanggup, anda tidak perlu ","     melambaikan tangan anda ke kamera. Cukup tekan tombol 'esc' dan pilih 'yes'");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "2. How to play, Anda akan dibawa ke layar ini dan membaca aturan-aturan seperti ","   ini.");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "3. Scoreboard, Melihat peringkat serta histori dari pemain yang memainkan ","   permainan. Menampilkan 10 pemain terhebat pada tingkat kesulitan yang berbeda");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "3.1. Terdapat 6 scoreboard yang dapat diakses jika semua tingkat kesulitan ","     permainan telah diselesaikan");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "3.2. Sccoreboard HANYA akan menampilkan 10 pemain terbaik yang menyelesaikan ","     permainan lebih cepat dibanding pemain lain");
				printf("\xBA%-80s\xBA\n\xBA%-80s\xBA\n\xBA%-80s\xBA\n", "3.3. Pemeringkatan dilakukan berdasarkan jumlah langkah yang dibutuhkan pemain","     untuk menyelesaikan permainan serta berapa lama waktu yang dibuthkan untuk","     pemain menyelesaikan permainan");
				printf("\xBA%-80s\xBA\n", "4. Exit Game, siapa yang tidak tahu fitur exit permainan, bukan anda pastinya");
				printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
				printf("Press any key to continue!\n");
				_getch();
				break;
			case 3: //cancel, back to menu
				return;
			}
		}
	}
}

void ScoreboardMenu(){
	char* difficulty[] = { ">> Boring\n", ">> Walk In The Park\n", ">> Normal\n", ">> Nightmare\n", ">> Just Surrender Already\n", ">> Literally Unplayable\n", ">> Back to Main Menu\n" };
	Menu scoreboardMenu(7, difficulty);
	while (true) {
		system("cls");
		printf("Select Difficulty : \n");
		scoreboardMenu.print();
		int key = _getch();
		if (key == 224) {
			switch (_getch()) { // arrow key value
			case 72: //up
				scoreboardMenu.up();
				break;
			case 80: //down
				scoreboardMenu.down();
				break;
			}
		}
		else if (key == 13) { //if enter key pressed
			int difficulty = scoreboardMenu.get();
			switch(difficulty){
			case 7:
				return;
			default:
				Scoreboard::sort(difficulty);
				Scoreboard::print(difficulty);
				break;
			}
		}
	}
}

int GameModeMenu(){
	char* mode_list[] = { ">> Competitive\n", ">> Ghost Mode\n", ">> Double Trouble\n" };
	Menu modeMenu(3, mode_list);
	while (true) {
		system("cls");
		printf("Select Mode : \n\n");
		modeMenu.print();
		int key = _getch();
		if (key == 224) {
			switch (_getch()) { // arrow key value
			case 72: //up
				modeMenu.up();
				break;
			case 80: //down
				modeMenu.down();
				break;
			}
		}
		else if (key == 13) { //if enter key pressed
			return modeMenu.get();
		}
	}
}

int main(){
	char* menu_awal[] = { ">> Play Game\n", ">> How To Play\n", ">> Scoreboard\n", ">> Exit Game\n" };
	Menu MainMenu(4, menu_awal);
	
	while (true) {
		system("cls");
		printf("Temple Trouble\n\n");
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
				bool blank = false;
				int mode = GameModeMenu();
				switch(mode){
				case 2:
					blank = true;
				case 1:
					CreateGame(name, &diff);
					PlayGame(name, diff, blank);
					break;
				case 3:
					CreateGame(name, &diff);
					PlayGame_ImAlive(name, diff);
					break;
				}
				
			}
				break;
			case 2:
				HowToPlay();
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

