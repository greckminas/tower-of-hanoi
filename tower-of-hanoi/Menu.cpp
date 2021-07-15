#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Menu::Menu(int count, char** list){
	max = 1;
	n = count;
	string = (char**)malloc(4*count);
	for(int i = 0; i < n; i++){
		string[i] = (char*)malloc(strlen(list[i]));
		strcpy(string[i], list[i]);
	}
	choose = 1;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(int count, char** list, int max_choice){
	max = max_choice;
	n = count;
	string = (char**)malloc(4*count);
	for(int i = 0; i < n; i++){
		string[i] = (char*)malloc(strlen(list[i]));
		strcpy(string[i], list[i]);
	}
	choose = 1;

	selected = (int*)malloc(max*sizeof(int));
	for(int i = 0; i < max; i++)
		selected[i] = 0;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

bool Menu::down(){
	if(choose < n){
		choose++;
		return true;
	}
	return false;
}

bool Menu::up(){
	if(choose > 1){
		choose--;
		return true;
	}
	return false;
}

bool Menu::select(){
	for(int i = 0; i < max; i++)
		if(selected[i] == choose){ //already selected
			unselect(); //then unselect
			return false; 
		}
	

	for(int i = 0; i < max; i++)
		if(selected[i] == 0){
			selected[i] = choose;
			return true; 
		}
	
	return false;
}

bool Menu::unselect(){
	for(int i = 0; i < max; i++)
		if(selected[i] == choose){
			selected[i] = 0;
			return true; 
		}
	
	return false;
}

void Menu::reset(){
	if(max > 1)
		for(int i = 0; i < max; i++)
			selected[i] = 0;
}

bool Menu::isSelected(int menu_number){
	if(max > 1)
		for(int i = 0; i < max; i++)
			if(selected[i] == menu_number)
				return true; 
	return false;
}

int Menu::get(){
	return choose;
}

int* Menu::get_all(){
	return selected;
}

void Menu::print(){
	for(int i = 1; i <= n; i++){
		if(isSelected(i) && i == choose)
			SetConsoleTextAttribute(hConsole, 13); //pink
		else if(i == choose)
			SetConsoleTextAttribute(hConsole, 10); //green
		else if(isSelected(i))
			SetConsoleTextAttribute(hConsole, 14); //yellow

		printf("%s", string[i-1]);

		if(i == choose || isSelected(i))
			SetConsoleTextAttribute(hConsole, 7);
	}
		
}