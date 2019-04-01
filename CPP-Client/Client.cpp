#include "pch.h"
#include "Client.h"
#include "OTP.h"

void Client::configServerInfo()
{
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 0), &WSAData);
	if (iResult != NO_ERROR) {
		printf("Error at WSAStartup()\n");
		exit(1);
	}

	// Create a listening socket
	//server = socket(AF_INET, SOCK_STREAM, 0);
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET)
	{
		printf("socket() error %d\n", SOCKET_ERRNO);
		exit(1);
	}

	ZeroMemory(&addr, sizeof(addr));

	// Ininilize sServer IP address , port .
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12000);
}

// Implement of connect to server.
void Client::connetToServer() {

	// Try to connect to server 
	if (connect(server, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR) {
		// As we are in non-blocking mode we'll always have the error 
		// WSAEWOULDBLOCK whichis actually not one 
		if (SOCKET_ERRNO != WSAEWOULDBLOCK)
		{
			printf("connect() error (%d)\n", SOCKET_ERRNO);
			exit(1);
		}
	}
	std::cout << "Connected to server!\n";
}

void Client::sendMessage(std::string message) {
	// Object of OTP class
	OTP otp;

	// Encrypt message
	std::string encrypt = otp.encrypt(message);

	// Send request to server
	if(send(server, encrypt.c_str(), encrypt.size(), 0))
		std::cout << "Request message is :\t" << message << std::endl;
	else
		std::cout << "ERROR" << std::endl;

	// Preprocessing to receive response
	char temp[63];
	ZeroMemory(temp, sizeof(temp));

	// Receive response of server
	int inDataLength = recv(server,temp,sizeof(temp),0);

	// Decrypt response
	std::string decryptedResponse = otp.decrypt(temp);
	std::cout << "Response message is :\t";
	for (int j = 0; j < decryptedResponse.length(); j++)
		std::cout << decryptedResponse[j];
	std::cout << "\n";

	// Disconnect server.
	closesocket(server);
	WSACleanup();
}

