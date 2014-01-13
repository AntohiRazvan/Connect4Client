#include <iostream>
#include "networking.h"
#include "game.h"

using namespace std;

void drawMenu(){
	cout << "1.Play a game" << endl;
	cout << "2.Quit" << endl << endl;
	cout << "Enter choice: ";
}

int main()
{
	int choice;
	networking net;

	drawMenu();
	cin >> choice;
	while(1)
	{
		switch(choice)
		{
			case 1: net.startConnection();
					  net.startGame();

			case 2: exit(1);

			default: cout << "Invalid command";
						drawMenu();
		}
	}
}

