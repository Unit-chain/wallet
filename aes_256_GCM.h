//
// Created by sunaked on 03/03/2023.
//

#ifndef CRYPTO_AES_256_GCM_H
#define CRYPTO_AES_256_GCM_H


#include <cryptopp/config.h>


#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <cassert>

#include <string>
using std::string;

#include <cryptopp/hex.h>
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include <cryptopp/cryptlib.h>
using CryptoPP::AuthenticatedSymmetricCipher;
using CryptoPP::BufferedTransformation;

#include <cryptopp/filters.h>
using CryptoPP::AuthenticatedDecryptionFilter;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include <cryptopp/aes.h>
using CryptoPP::AES;

#include <cryptopp/gcm.h>
using CryptoPP::GCM;
using CryptoPP::GCM_TablesOption;

/*!
	\brief AES
	\author Sunaked
	\version 1.0
	\date Март 2023 y.
    \example "examples/aes.cpp"
*/
class aes_256_GCM {
public:
    /*
     * key
     */

    static std::string encode(const std::string &adata, const std::string &pdata, CryptoPP::byte key[], size_t key_size, CryptoPP::byte iv[], size_t iv_size, int TAG_SIZE = 16);
    static std::string decode(const std::string &cipher, const string &adata, CryptoPP::byte *key, size_t key_size, CryptoPP::byte *iv, size_t iv_size, int TAG_SIZE = 16);
};


#endif //CRYPTO_AES_256_GCM_H
