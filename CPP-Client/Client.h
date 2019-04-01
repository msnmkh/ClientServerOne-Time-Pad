#pragma once
#ifndef CLIENT_CLASS
#define CLIENT_CLASS
#define   SOCKET_ERRNO   WSAGetLastError() 

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <conio.h> 
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") 
#pragma warning(disable:4996)
#define   SOCKET_ERRNO   WSAGetLastError() 

class Client
{
public:
	WSADATA WSAData;
	SOCKET server;
	SOCKADDR_IN addr;

	void configServerInfo();
	void connetToServer();
	void sendMessage(std::string);
};

#endif