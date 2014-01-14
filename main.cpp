#include <iostream>
#include "networking.h"
#include "game.h"

using namespace std;

void drawMenu(){
	cout << "1.Play a game" << endl;
	cout << "Enter choice: ";
	fflush(stdout);
}

int main()
{
	int choice;
	networking net;
	while(1)
	{
		drawMenu();
		fflush(stdin);
		cin >> choice;
		switch(choice)
		{
			case 1: net.startConnection();
					  net.startGame();
					  break;
			case 2: exit(1);
					  break;
			default: cout << "Invalid command";
						drawMenu();
						break;
		}
	}
}
