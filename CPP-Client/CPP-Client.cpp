// CPP-Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Client.h"
#include <iostream>

int main()
{
	std::string message = "hello";

	// Create object of class client
	Client client;

	// Config server information
	client.configServerInfo();

	// Connect to server 
	client.connetToServer();

	// Send message to server and get response
	client.sendMessage(message);



	return 0;

}
