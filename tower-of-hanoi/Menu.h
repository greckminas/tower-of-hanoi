#ifndef MENU_H
#define MENU_H
#include <Windows.h>

class Menu {
	int n;
	char** string;
	int choose;
	int max;
	int* selected;
	HANDLE hConsole;

public:
	Menu(int count, char** list);
	Menu(int count, char** list, int max_choice);
	bool down();
	bool up();
	bool select();
	bool unselect();
	void reset();
	bool isSelected(int menu_number);
	int get();
	int* get_all();
	void print();
};

#endif