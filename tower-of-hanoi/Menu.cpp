#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib,"winmm.lib")

Menu::Menu(int count, char** list){
	//mengatur max menu yang dipilih dan mengatur jumlah menu
	max = 1;
	n = count;
	choose = 1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//mengalokasikan string menu dan memindahkannya
	string = (char**)malloc(4*count);
	for(int i = 0; i < n; i++){
		string[i] = (char*)malloc(strlen(list[i])+1);
		strcpy(string[i], list[i]);
	}
}

Menu::Menu(int count, char** list, int max_choice){
	//mengatur max menu yang dipilih dan mengatur jumlah menu
	max = max_choice;
	n = count;
	choose = 1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//mengalokasikan string menu dan memindahkannya
	string = (char**)malloc(4*count);
	for(int i = 0; i < n; i++){
		string[i] = (char*)malloc(strlen(list[i])+1);
		strcpy(string[i], list[i]);
	}
	
	//menginisialisasi selected menjadi 0
	selected = (int*)malloc(max*sizeof(int));
	for(int i = 0; i < max; i++)
		selected[i] = 0;
}

Menu::~Menu(){
	//membebaskan memori dari setiap string pada menu
	for(int i = 0; i < n; i++){
		free(string[i]);
	}
	free(string);
}

bool Menu::down(){
	//cek apakah navigate down masih memungkinkan atau tidak
	if(choose < n){
		PlaySound("sound/picking_between_option.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

		//navigate down
		choose++;
		return true;
	}
	return false;
}

bool Menu::up(){
	//cek apakah navigate up masih memungkinkan atau tidak
	if(choose > 1){
		PlaySound("sound/picking_between_option.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

		//navigate up
		choose--;
		return true;
	}
	return false;
}

bool Menu::select(){
	for(int i = 0; i < max; i++)
		//cek apakah menu telah diselect atau belum
		if(selected[i] == choose){

			//jika sudah, maka unselect
			unselect();
			return false; 
		}
	

	for(int i = 0; i < max; i++)
		//cek apakah menu masih bisa diselect lagi
		if(selected[i] == 0){

			//jika masih bisa diselect, maka select
			selected[i] = choose;
			return true; 
		}
	
	return false;
}

bool Menu::unselect(){
	for(int i = 0; i < max; i++)
		//cek apakah menu sudah diselect atau belum
		if(selected[i] == choose){

			//jika sudah, maka unselect
			selected[i] = 0;
			return true; 
		}
	
	return false;
}

void Menu::reset(){
	if(max > 1)
		//unselect semua menu
		for(int i = 0; i < max; i++)
			selected[i] = 0;
}

bool Menu::isSelected(int menu_number){
	if(max > 1)
		for(int i = 0; i < max; i++)
			//cek apakah menu dengan index menu_number diselect atau tidak
			if(selected[i] == menu_number)
				return true; 
	return false;
}

int Menu::get(){
	PlaySound("sound/after_pick_an_option.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

	//mendapatkan menu yang sedang dihighlight
	return choose;
}

int* Menu::get_all(){

	//mendapatkan semua menu yang sedang dipilih
	return selected;
}

void Menu::print(){
	for(int i = 1; i <= n; i++){

		//jika menu dipilih dan dihighlight, maka warna teks menjadi merah muda
		if(isSelected(i) && i == choose)
			SetConsoleTextAttribute(hConsole, 13); //pink

		//jika menu dipilih tetapi tidak dihighlight, maka warna teks menjadi hijau
		else if(i == choose)
			SetConsoleTextAttribute(hConsole, 10); //green

		//jika menu dihighlight tetapi tidak dipilih, maka warna teks menjadi kuning
		else if(isSelected(i))
			SetConsoleTextAttribute(hConsole, 14); //yellow

		//print 1 menu
		printf("%s", string[i-1]);

		//kembalikan warna teks ke warna putih
		if(i == choose || isSelected(i))
			SetConsoleTextAttribute(hConsole, 7);
	}
		
}