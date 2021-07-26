#ifndef MENU_H
#define MENU_H
#include <Windows.h>

class Menu {
	int n; //jumlah menu
	char** string; //array of string, berisi string dari menu
	int choose; //menu yang sedih dihighlight
	int max; //jumlah maksimal dari pilihan
	int* selected; //array of integer, berisi menu-menu yang dipilih
	HANDLE hConsole; //handle dari console output

public:
	/* CONSTRUCTOR */
	Menu(int count, char** list);
	Menu(int count, char** list, int max_choice);

	/* DESTRUCTOR */
	~Menu();

	/* NAVIGATING MENU*/
	bool down();
	bool up();

	/* SELECTING MENU */
	bool select();
	bool unselect();
	void reset();

	/* GET MENU STATUS */
	bool isSelected(int menu_number);
	int get();
	int* get_all();

	/* PRINT MENU*/
	void print();
};

#endif