#pragma once

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
#include "cryptopp610\sha.h"
#include "cryptopp610\pwdbased.h"

SecByteBlock key_from_mpass(const std::string &password) {

	SecByteBlock derived(AES::MAX_KEYLENGTH);
	// KDF function
	unsigned int iterations = 25000;
	char purpose = 0;
	PKCS5_PBKDF2_HMAC<SHA256> key;
	key.DeriveKey(derived.data(), derived.size(), purpose, (byte*)password.data(), password.size(), NULL, 0, iterations);

	return derived;
}

std::string encrypt_master_key(const std::string &password, const std::string &to_be_crypt, std::ofstream &path_key, std::ofstream &ivs) {
	SecByteBlock derived(AES::MAX_KEYLENGTH);
	// KDF function
	derived = key_from_mpass(password);

	AutoSeededRandomPool prng;

	byte iv[AES::MAX_BLOCKSIZE];
	prng.GenerateBlock(iv, sizeof(iv));

	std::string cipher, recovered, out_iv;


	StringSource(iv, sizeof(iv), true,
		new HexEncoder(
			new StringSink(out_iv))
	); // StringSource
	ivs << out_iv << std::endl;


	try
	{
		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(derived, AES::MAX_KEYLENGTH, iv);
		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(to_be_crypt, true,
			new StreamTransformationFilter(e,
				new HexEncoder(
					new StringSink(cipher)
				)) // StreamTransformationFilter
		); // StringSource
		return cipher;
	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		// error pop-out insted of exit

		exit(1);
	}



}

std::string decrypt_master_key(const std::string &password, const std::string &key_s, const std::string &iv_s) {
	try {
		string  recovered;

		SecByteBlock derived(AES::MAX_KEYLENGTH);
		derived = key_from_mpass(password);

		SecByteBlock iv(AES::MAX_BLOCKSIZE);

		StringSource file(iv_s, true,
			new HexDecoder(
				new ArraySink(iv, iv.size())
			)
		);

		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(derived, AES::MAX_KEYLENGTH, iv);
		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(key_s, true,
			new HexDecoder(
				new StreamTransformationFilter(d,
					new StringSink(recovered)
				)
			)
			// StreamTransformationFilter
		); // StringSource

		return recovered;
	}

	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		return "ERROR_PASS";
	}

}


void encrypt_key(const std::string &password, const std::string &to_be_crypt, std::ofstream &path_key, std::ofstream &path_iv, std::ofstream &path_cipher, std::ofstream &ivs) {

	AutoSeededRandomPool prng;
	byte key[AES::MAX_KEYLENGTH];
	prng.GenerateBlock(key, sizeof(key));


	byte iv[AES::MAX_BLOCKSIZE];
	prng.GenerateBlock(iv, sizeof(iv));

	string cipher, iv_s, key_s;

	//save key to file
	StringSource(key, sizeof(key), true,
		new HexEncoder(
			new StringSink(key_s))
	); // StringSource
	key_s = encrypt_master_key(password, key_s, path_key, ivs);
	path_key << key_s << std::endl;

	StringSource(iv, sizeof(iv), true,
		new HexEncoder(
			new StringSink(iv_s))
	); // StringSource
	path_iv << iv_s << std::endl;

	try
	{
		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(key, AES::MAX_KEYLENGTH, iv);
		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(to_be_crypt, true,
			new StreamTransformationFilter(e,
				new HexEncoder(
					new StringSink(cipher))
			) // StreamTransformationFilter
		); // StringSource

	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		// error pop-out insted of exit

		exit(1);
	}


	path_cipher << cipher << endl;




}


std::string decrypt_key(const std::string &cipher_s, const std::string &key_s, const std::string &iv_s, const std::string &password, const std::string &ivs) {
	try {
		string recovered, derived_s;

		SecByteBlock derived(AES::MAX_KEYLENGTH);
		derived_s = decrypt_master_key(password, key_s, ivs);
		if (derived_s == "ERROR_PASS")
			return derived_s;
		StringSource key_ss(derived_s, true,
			new HexDecoder(
				new ArraySink(derived, derived.size())
			)
		);

		SecByteBlock iv(AES::MAX_BLOCKSIZE);

		StringSource iv_ss(iv_s, true,
			new HexDecoder(
				new ArraySink(iv, iv.size())
			)
		);

		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(derived, AES::MAX_KEYLENGTH, iv);
		// The StreamTransformationFilter removes
		//  padding as required.
		//cout << "Cipher is :" << cipher_s << std::endl;
		StringSource s(cipher_s, true,
			new HexDecoder(
				new StreamTransformationFilter(d,
					new StringSink(recovered)
				)
			)
			// StreamTransformationFilter
		); // StringSource

		return recovered;

	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		return "ERROR_PASS";
	}

}
