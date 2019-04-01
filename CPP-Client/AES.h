#pragma once
#ifndef AESENC_CLASS
#define AESENC_CLASS
#include <openssl/aes.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>


class AESENC
{
public:
	std::string Decryption(std::string);
};

#endif