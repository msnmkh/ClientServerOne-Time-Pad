#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "openssl/sha.h"
#include <openssl/aes.h>
#include <ctime>

class OTP
{
public:
	std::string encrypt(std::string);
	std::string decrypt(std::string);

private:
	std::string xorString(std::string&, std::string&);
	std::string nextKey();
	std::string findKey(std::string);
	std::string createMAC(std::string&);
	int createRand();
};

