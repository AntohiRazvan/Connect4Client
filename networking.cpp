#include "networking.h"

networking::networking()
{
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(7834);
}

void networking::startConnection(){
	if ((server = socket (AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Eroare la socket().\n");
	}

	if (connect (server, (struct sockaddr *) &serverAddress,sizeof (struct sockaddr)) == -1)
	{
		perror ("[client]Eroare la connect().\n");
	}
}

void networking::startGame(){
	game Game;
	int playerName = getPlayerName();
	Game.setThisPlayer(playerName);
	while(!gameOverCheck())
	{
		while(!winConditionCheck())
		{
			getGameState(Game);
			makeMove(Game);
		}
		getGameState(Game);
	}
	close(server);
}

void networking::makeMove(game Game){
	bool response;
	int move = 0;
	if(Game.getCurrentPlayer() == Game.getThisPlayer())
	{
		std::cout << "Make your move :";
	try_again:
		std::cin.ignore();
		fflush(stdin);
		while(move < 1 || move > 7)
		{
			std::cin >> move;
			if(write(server, &move, sizeof(move)) == -1)
			{
				perror("[MakeMove]Eroare la scriere din socket");
			}
			if(read(server, &response, sizeof(bool)) == -1)
			{
				perror("[MakeMove]Eroare la citire din socket");
			}
			if(!response)
			{
				std::cout << "Invalid positon, try again:";
				goto try_again;
			}
		}
	}
	else
	{
		std::cout << "Waiting for the other player..." << std::endl;
	}
}

void networking::getGameState(game &Game){
	char* packet = new char;
	if(read(server, packet, GAME_DATA_LENGTH) == -1)
	{
		perror("[GAME STATE]Eroare la citire din socket");
		return;
	}
	Game.deserialize(packet);
	Game.draw();

}

int networking::getPlayerName(){
	int name;
	if(read(server, &name, sizeof(int)) == -1)
	{
		perror("[PlayerName]Eroare la citire din socket");
		return 0;
	}
	std::cout << "You are player " << name << std::endl;
	return name;
}

bool networking::gameOverCheck(){
	bool gameOver;
	if(read(server, &gameOver, sizeof(bool)) == -1)
	{
		perror("[GameOverCheck]Eroare la citire din socket");
		return 0;
	}
	return gameOver;
}

bool networking::winConditionCheck(){
	bool winCondition;
	if(read(server, &winCondition, sizeof(bool)) == -1)
	{
		perror("[WinCondtionCheck]Eroare la citire din socket");
	}
	return winCondition;
}
