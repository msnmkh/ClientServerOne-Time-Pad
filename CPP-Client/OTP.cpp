#include "pch.h"
#include "OTP.h"
#include "AES.h"
#include <iostream>
#include <string>

// Encrypt with xor plain text and key (key => is random of even number id key in keys.txt)
std::string OTP::encrypt(std::string plainText) {
	std::string encrypt, MAC, id, result, key, line = "";
	std::ifstream keyFile;
	int j, i;

	// Get random next key in keys.txt(with even id)
	key = nextKey();

	// Split id and key
	for (i = 0; i < key.length(); i++) 
		if (key[i] == '#') {
			id = key.substr(0, i);
			break;
		}

	key = key.substr(i+1, key.length() - i-1);


	// Decrypt key
//	AESENC aes;
//	key = aes.Decryption(key);

	// Encrypt message
	encrypt = xorString(plainText, key);

	// Create MAC
	MAC = createMAC(encrypt);

	//  Message to send server
	result = "ID:" + id + "enc:" + encrypt + "MAC:" + MAC;
	
	return result;
}

// Decrypt with xor cipher text and key
std::string OTP::decrypt(std::string cipherText) {
	std::string decrypt,ServerMAC, ClientMAC, id, cipher, key, line = "";
	std::ifstream keyFile;
	int j,i;

	// Separate MAC,CipherText,ID of key
	for (i = 0; i < cipherText.length(); i++) {
		if (cipherText[i] == 'e' && cipherText[i + 1] == 'n')
		{
			id = cipherText.substr(3, i - 3);
			j = i+4;
		}
		if (cipherText[i] == 'M' && cipherText[i + 1] == 'A')
		{
			cipher = cipherText.substr(j, i - j);
			j = i + 4;
		}
	}
	ServerMAC = cipherText.substr(j, i - j);

	// Find key in keys.txt
	key = findKey(id);

	// Decrypt key
//	AESENC aes;
//	key = aes.Decryption(key);

	// Decrypt response with xor key and cipher text
	decrypt = xorString(cipher, key);

	// Get mac of message
	ClientMAC = createMAC(cipher);

	// Check integerity of message
	if(ClientMAC == ServerMAC)
		std::cout << std::endl <<"server mac and client mac match :)) \t" << std::endl;
	else
		std::cout << std::endl << "server mac and client does not match :||| \t" << std::endl;

	return decrypt;
}

// XOR two String
std::string OTP::xorString(std::string& str1, std::string& str2) {
	// Length of xor output
	int strLength = str1.length() < str2.length() ? str1.length() : str2.length();
	if (str1.length() != str2.length())
		std::cout << "Input sizes do not match! Using the lower one.";
	std::string output;
	
	// Xor char by char
	for (int i = 0; i < strLength; i++)
		output += (str1[i] ^ str2[i]);
	return output;
}

// Get next key even key number (with even id)
std::string OTP::nextKey() {
	std::string key, line = "",lne,rndstr,sharp="#";
	std::ifstream keyFile, keyReadClientFile;
	std::ofstream keyWriteClientFile;
	bool flag = false;
	std::stringstream ss;
	int rnd;
	rnd = createRand();
	rnd = 2;
	ss << rnd;
	rndstr = ss.str();
	rndstr.append("#");
	rndstr.insert(0, "#");
	while (!flag) 
	{
		keyFile.open("C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\keys.txt");
		keyReadClientFile.open("C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\clientSelectedKeys.txt");
		while (getline(keyFile, line)) { 
			//while (getline(keyReadClientFile, lne))if (lne == line) continue;
			if (line.find(rndstr, 0) != std::string::npos) {
				key = line.substr(1, line.length()-1);
				flag = true;

				keyWriteClientFile.open("C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\clientSelectedKeys.txt");
				keyWriteClientFile << line << std::endl;
				keyWriteClientFile.close();
			///	key = line.substr(rnd.length() + 1, line.length() - 1 - rnd.length());
				break;
			}
		}
		keyReadClientFile.close();
		keyFile.close();
	}
	return key;
}

// Find key in keys.txt that use in server
std::string OTP::findKey(std::string id) {
	std::string  key, line = "";
	std::ifstream keyFile;
	id = "#" +id + "#";
	keyFile.open("C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\keys.txt");
	while (getline(keyFile, line)) { // I changed this, see below
		if (line.find(id, 0) != std::string::npos) {
			key = line.substr(id.length(), line.length() - id.length());
		}
	}
	return key;
}

// Mac of input
std::string OTP::createMAC(std::string& str) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	if (!SHA256_Init(&sha256))return false;
	if (!SHA256_Update(&sha256, str.c_str(), str.size()))return false;
	if (!SHA256_Final(hash, &sha256))return false;
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << hash[i];
	}
	return ss.str();
}

// Rand number generator
int OTP::createRand() {
//	return 2 * (rand() % 2);
	return 2;
}