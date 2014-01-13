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
	int move;
	int playerName = getPlayerName();
	while(!Game.gameOver())
	{
		while(!Game.winCondition())
		{
			getGameState(Game);
			if(Game.getCurrentPlayer() == playerName)
			{
				std::cout << "Make your move :";
				read:
					std::cin >> move;
					if(0 < move && move < 8)
					{
						write(server, &move, sizeof(move));
					}
					else
					{
						std::cout << "Invalid positon, try again:";
						goto read;
					}
			}
		}
	}
}
void networking::getGameState(game &Game){
	char* packet = new char;
	if(read(server, packet, GAME_DATA_LENGTH) == -1)
	{
		perror("Eroare la citire din socket");
	}
	Game.deserialize(packet);
	Game.draw();
}

int networking::getPlayerName(){
	char* packet = new char;
	if(read(server, packet, 30) == -1)
	{
		perror("Eroare la citire din socket");
	}
	std::cout << packet << std::endl;
	if(packet[-2] == '1')
	{
		return 1;
	}
	else
	{
		return 2;
	}

}
