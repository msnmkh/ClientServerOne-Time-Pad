// CPP-Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Client.h"
#include <iostream>
#include "AES.h"

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


//	AESENC aes;
//
//	
//	char *charMessage = new char[message.size() + 1];
//	strcpy(charMessage, message.c_str());
//
//    std::string f = aes.Encryption(charMessage);
//   std::string fsa = aes.Decryption(f);
//	std::cout << fsa;

	return 0;

}
