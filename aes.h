#ifndef AES_H
#define AES_H
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring>
#include <openssl/err.h>

//using namespace std;


// Function to generate random key of given length
void generate_random_key(unsigned char *key, int key_length);

// Function to encode data with AES256_hmac_256 in GCM mode with separate keys
// Returns encrypted data in output buffer and size of encrypted data in output_length
void encrypt_aes256_hmac_256_gcm(const unsigned char *plaintext, int plaintext_length, const unsigned char *key, const unsigned char *iv, const unsigned char *aad, int aad_length, unsigned char *output, int *output_length);



// Function to decode data with AES256_hmac_256 in GCM mode with separate keys
// Returns decrypted data in output buffer and size of decrypted data in output_length
//void decrypt_aes256_hmac_256_gcm(const unsigned char *ciphertext, int ciphertext_length, const unsigned char *key, const unsigned char *iv, const unsigned char *aad, int aad_length, unsigned char *output, int *output_length);

void decrypt_aes256_hmac_256_gcm(const unsigned char *ciphertext, int ciphertext_length, const unsigned char *key, unsigned char *iv, const unsigned char *aad, int aad_length, unsigned char *output, int *output_length);

//void decrypt(const std::string &ciphertext, const std::string &key, const std::string &iv, const std::string &aad, void *plaintext, size_t *plaintext_len);
// Function to generate a random 96-bit IV
void generate_random_iv(unsigned char *iv);

int do_crypt(FILE *in, FILE *out, int do_encrypt);

#endif // AES_H
