#include "pch.h"
#include "AES.h"

AES_KEY key;
unsigned char IV[] = { 1, 64, 119, 95, 10, 132, 5, 137, 103, 8, 100, 14, 91, 34, 81, 197 };
unsigned char userkey[] = { 182,131,35,156,149, 66, 53, 237, 238, 163, 214, 71, 31, 10, 30, 124, 156, 226, 105, 111, 253, 124, 38, 72, 234, 126,230 ,5 ,39 ,37 ,121 , 230 };
unsigned char outdata[AES_BLOCK_SIZE];


std::string AESENC::Encryption(char *message) {
	// Set encryption key
	AES_set_encrypt_key(userkey, 256, &key);

	unsigned char ivec[AES_BLOCK_SIZE];
	memcpy(ivec, IV, AES_BLOCK_SIZE);

	// Start bit to encrypt
	int postion = 0;

	// Get len of message
	int bytes_read = strlen(message);

	// Encrypt Message .
	AES_cbc_encrypt((unsigned char *)message, outdata, bytes_read, &key, ivec, AES_ENCRYPT);
	
	std::stringstream as;
	
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
		as << outdata[i];

	return as.str();
}

std::string AESENC::Decryption(std::string message) {
	// Set encryption key
	AES_set_decrypt_key(userkey, 256, &key);
	unsigned char ivec[AES_BLOCK_SIZE];
	memcpy(ivec, IV, AES_BLOCK_SIZE);

	// Start bit to encrypt
	int postion = 0;

	char *k = new char[message.size() + 1];
	message.copy(k, message.size() + 1);
	k[message.size()] = '\n';

	int bytes_read = sizeof(message)-1;

	// Encrypt Message .
	AES_cbc_encrypt((unsigned char *)k, outdata, bytes_read, &key, ivec, AES_DECRYPT);

	std::stringstream enc;
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
		enc << outdata[i];

	return enc.str();
}