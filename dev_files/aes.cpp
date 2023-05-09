#include "aes.h"

using namespace std;

void generate_random_iv(unsigned char *iv)
{
    RAND_bytes(iv, 12);
}

void generate_random_key(unsigned char *key, int key_length)
{
    if (RAND_bytes(key, key_length) != 1) {
        std::cerr << "Error generating random key\n";
        exit(1);
    }
}

void encrypt_aes256_hmac_256_gcm(const unsigned char *plaintext, int plaintext_length, const unsigned char *key, const unsigned char *iv, const unsigned char *aad, int aad_length, unsigned char *output, int *output_length)
{
    EVP_CIPHER_CTX *ctx;
    int len, ciphertext_len, tag_len;

    // Create context for encryption
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        std::cerr << "Error creating encryption context\n";
        exit(1);
    }

    // Initialize encryption with AES256_hmac_256 in GCM mode with separate keys
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) {
        std::cerr << "Error initializing encryption\n";
        exit(1);
    }
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, EVP_GCM_TLS_EXPLICIT_IV_LEN, NULL) != 1) {
        std::cerr << "Error setting IV length\n";
        exit(1);
    }
    if (EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv) != 1) {
        std::cerr << "Error setting encryption key and IV\n";
        exit(1);
    }
    if (aad_length > 0) {
        if (EVP_EncryptUpdate(ctx, NULL, &len, aad, aad_length) != 1) {
            std::cerr << "Error adding additional authenticated data\n";
            exit(1);
        }
    }

    // Encrypt plaintext
    if (EVP_EncryptUpdate(ctx, output, &len, plaintext, plaintext_length) != 1) {
        std::cerr << "Error encrypting data\n";
        exit(1);
    }
    ciphertext_len = len;

    // Finalize encryption and get authentication tag
    if (EVP_EncryptFinal_ex(ctx, output + len, &len) != 1) {
        std::cerr << "Error finalizing encryption\n";
        exit(1);
    }
    ciphertext_len += len;
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, output + ciphertext_len) != 1) {
        std::cerr << "Error getting authentication tag\n";
        exit(1);
    }
    tag_len = 16;
    ciphertext_len += tag_len;

    *output_length = ciphertext_len;

    // Clean up context
    EVP_CIPHER_CTX_free(ctx);
}

void decrypt_aes256_hmac_256_gcm(const unsigned char *ciphertext, int ciphertext_length, const unsigned char *key, unsigned char *iv, const unsigned char *aad, int aad_length, unsigned char *output, int *output_length) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Error creating cipher context");

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1)
        throw std::runtime_error("Error initializing decryption");

    if (EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv) != 1)
        throw std::runtime_error("Error setting key and IV for decryption");

    if (aad_length > 0 && EVP_DecryptUpdate(ctx, NULL, NULL, aad, aad_length) != 1)
        throw std::runtime_error("Error setting AAD for decryption");

    int len;
    char buffer[1024];
    if (EVP_DecryptUpdate(ctx, output, &len, ciphertext, ciphertext_length - 16) != 1)
        throw std::runtime_error("Error decrypting ciphertext");

    *output_length = len;

    // Set the tag value explicitly before calling EVP_DecryptFinal_ex
    unsigned char tag[16];
    memcpy(tag, ciphertext + ciphertext_length - 16, 16);
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag) != 1)
        throw std::runtime_error("Error setting tag value for decryption");

    if (EVP_DecryptFinal_ex(ctx, (unsigned char *)buffer, &len) != 1)
        throw std::runtime_error("Error finalizing decryption");

    *output_length += len;
    memcpy(output + *output_length - len, buffer, len);

    EVP_CIPHER_CTX_free(ctx);
}

int do_crypt(FILE *in, FILE *out, int do_encrypt)
{
    /* Allow enough space in output buffer for additional block */
    unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int inlen, outlen;
    EVP_CIPHER_CTX *ctx;
    /*
     * Bogus key and IV: we'd normally set these from
     * another source.
     */
    unsigned char key[] = "0123456789abcdeF";
    unsigned char iv[] = "1234567887654321";

    /* Don't set key or IV right away; we want to check lengths */
    ctx = EVP_CIPHER_CTX_new();
    if (!EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(), NULL, NULL,
                            do_encrypt, NULL)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    OPENSSL_assert(EVP_CIPHER_CTX_get_key_length(ctx) == 16);
    OPENSSL_assert(EVP_CIPHER_CTX_get_iv_length(ctx) == 16);

    /* Now we can set key and IV */
    if (!EVP_CipherInit_ex(ctx, NULL, key, iv, do_encrypt, NULL)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    for (;;) {
        inlen = fread(inbuf, 1, 1024, in);
        if (inlen <= 0)
            break;
        if (!EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen)) {
            /* Error */
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
        fwrite(outbuf, 1, outlen, out);
    }
    if (!EVP_CipherFinal_ex(ctx, outbuf, &outlen)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    fwrite(outbuf, 1, outlen, out);

    EVP_CIPHER_CTX_free(ctx);
    return 1;
}
