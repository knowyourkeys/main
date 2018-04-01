// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iomanip>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;
#include <fstream>
#include "cryptopp610/aes.h"
#include "cryptopp610/files.h"
#include "cryptopp610/hex.h"
#include "cryptopp610/osrng.h"
#include "cryptopp610/cryptlib.h"
#include <cstdlib>
using std::exit;

#include "cryptopp610\ccm.h"
#include <fstream>
using namespace CryptoPP;

string return_string(string cacat) {
	cout << "recovered text: " << cacat << endl;
	return cacat;
}

#include "cryptopp610\sha.h"
#include "cryptopp610\pwdbased.h"
using namespace CryptoPP;

SecByteBlock key_from_mpass(std::string password) {
	SecByteBlock derived(AES::MAX_KEYLENGTH);
	// KDF function
	unsigned int iterations = 25000;
	char purpose = 0;
	PKCS5_PBKDF2_HMAC<SHA256> key;
	key.DeriveKey(derived.data(), derived.size(), purpose, (byte*)password.data(), password.size(), NULL, 0, iterations);
	return derived;
}

void encrypt_master_key(std::string password,std::string to_be_crypt) {
	SecByteBlock derived(AES::MAX_KEYLENGTH);
	// KDF function
	derived = key_from_mpass(password);
	AutoSeededRandomPool prng;

	
	byte iv[AES::MAX_BLOCKSIZE];
	prng.GenerateBlock(iv, sizeof(iv));

	string cipher, recovered;
	std::ofstream out_iv;
	out_iv.open("iv_k.txt");
	//save key to file
	StringSource(iv, sizeof(iv), true, 
			new FileSink("iv_k.txt")
	); // StringSource
	out_iv.close();

	try
	{
		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(derived, AES::MAX_KEYLENGTH, iv);
		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(to_be_crypt, true,
			new StreamTransformationFilter(e,
				new StringSink(cipher)
			) // StreamTransformationFilter
		); // StringSource

	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	std::ofstream out_cipher;
	out_cipher.open("keys.txt");
	StringSource(cipher, true,
			new FileSink("keys.txt")
	); // StringSource

	out_cipher.close();



}

std::string decrypt_master_key(std::string password) {
	try {
		string cipher, recovered, iv_s;
		std::ifstream in_cipher;
		in_cipher.open("keys.txt");
		FileSource file_s("keys.txt", true, new StringSink(cipher));
		in_cipher.close();
		SecByteBlock derived(AES::MAX_KEYLENGTH);
		derived = key_from_mpass(password);

		in_cipher.close();
		SecByteBlock iv(AES::MAX_BLOCKSIZE);
		std::ifstream in_iv;
		in_iv.open("iv_k.txt");
		FileSource file("iv_k.txt", false);
		ArraySink a(iv, iv.size());
		file.Attach(new Redirector(a));
		file.Pump(AES::MAX_BLOCKSIZE);
		in_iv.close();

		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(derived, AES::MAX_KEYLENGTH, iv);
		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true,
			new StreamTransformationFilter(d,
				new StringSink(recovered))
			// StreamTransformationFilter
		); // StringSource
		return recovered;

	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
	
}

int main(int argc, char* argv[])
{
	
	string password = "AdrianArePulaMare156541521";
	string a = "Nicugheara";
	encrypt_master_key(password,a);
	string rec = decrypt_master_key(password);
		std::cout << rec;
		std::getchar();
		return 0;
	}


