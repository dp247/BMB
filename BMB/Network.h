#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Include the Winsock functions and headers
#include <WinSock2.h>
#include <WS2tcpip.h>

//Include game files
#include "game.h"
#include "rules.h"

//Include the headers for multi-threading
#include <Windows.h>
#include <process.h>

//Include vector header file
#include <vector>
#include <stdint.h>

#pragma comment(lib, "Ws2_32.lib")

class Network
{
private:
	static Network* pInstance;			//Instance of the network
	int currentConnections;				//Number of current connections
	char IPAddress;						//IP Address
	int portNumber;						//Current port number
	sockaddr_in serverAddress;			//The address of the server
	DWORD thread;						//Thread that waits for connections
	std::vector<sockaddr_in> clients;	//List of clients connected
	WSAData	wsaData;
	GameTimer NetTimer;

public:
	//Constructor and destructor
	Network();
	~Network();

	//GetInstance()
	static Network* GetInstance();


};

