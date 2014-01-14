#ifndef NETWORKING_H
#define NETWORKING_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "game.h"

extern int errno;

class networking
{
	int server;
	struct sockaddr_in serverAddress;

	void getGameState(game &Game);
	int getPlayerName();
	bool gameOverCheck();
	bool winConditionCheck();
	void makeMove(game Game);
public:
	networking();
	void startConnection();
	void startGame();
};

#endif // NETWORKING_H
