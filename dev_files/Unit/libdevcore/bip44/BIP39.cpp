#include "BIP39.hpp"

BIP39Result BIP39::generateMnemonic(std::string passphrase)
{
    // defining random
    unsigned char r_buf[256];
    if (!RAND_priv_bytes(r_buf, 256)) return BIP39Result("","");

    // init bitset for 24 words
    std::bitset<264> bits;
    for (int i = 0; i < 256; i++)
    {
        // randomize 256 bits
        bits[i] = (r_buf[i]) % 2;
    }

    uint8_t split_bits_for_sha[32];
    for (int j = 0; j < 32; ++j)
    {
        std::bitset<8> t_bits;
        uint8_t t = 0;
        for (int i = j * 8; i < j * 8 + 8; i++)
        {
            t_bits[7 - t] = bits[i];
            t++;
        }
        // std::cout << t_bits << std::endl;
        split_bits_for_sha[j] = static_cast<uint8_t>(t_bits.to_ulong());
    }
    SHA256_Legacy sha;
    std::string mySHA = sha(split_bits_for_sha, 32);
    unsigned long last_sha_digest = hex2dec(mySHA.substr(0, 2));
    std::bitset<8> sign_bits;
    uint8_t i = 0;
    while (last_sha_digest > 0 && i < 8)
    {
        if (last_sha_digest % 2)
            sign_bits.set(i);
        last_sha_digest = last_sha_digest / 2;
        i++;
    }
    // std::cout << sign_bits << std::endl;
    bits[256] = sign_bits[7];
    bits[257] = sign_bits[6];
    bits[258] = sign_bits[5];
    bits[259] = sign_bits[4];
    bits[260] = sign_bits[3];
    bits[261] = sign_bits[2];
    bits[262] = sign_bits[1];
    bits[263] = sign_bits[0];

    std::vector<std::string> words = bitsToWords(bits);
    std::string final_mnemonic = "";
    for (int i = 0; i < 24; ++i)
    {
        final_mnemonic.append(words[i] + (i == 23 ? "" : " "));
    }
    return BIP39Result(final_mnemonic, phraseToSeed(final_mnemonic, passphrase));
}
std::vector<std::string> BIP39::bitsToWords(std::bitset<264> bits)
{
    std::vector<std::string> finalWords;
    for (int i = 0; i < 24; ++i)
    {
        std::bitset<11> t;
        uint8_t c = 0;
        for (int j = 11 * i; j < 11 * i + 11; j++)
        {
            t[10 - c] = bits[j];
            c++;
        }
        finalWords.push_back(words[t.to_ulong()]);
    }
    return finalWords;
}
BIP39Result BIP39::generateMnemonic_12(std::string passphrase)
{
    // defining random
    unsigned char r_buf[128];
    if (!RAND_priv_bytes(r_buf, 128)) return BIP39Result("","");

    // init bitset for 24 words
    std::bitset<132> bits;
    for (int i = 0; i < 128; i++)
    {
        // randomize 128 bits
        bits[i] = ((uint8_t)r_buf[i]) % 2;
    }

    uint8_t split_bits_for_sha[16];
    for (int j = 0; j < 16; ++j)
    {
        std::bitset<8> t_bits;
        uint8_t t = 0;
        for (int i = j * 8; i < j * 8 + 8; i++)
        {
            t_bits[7 - t] = bits[i];
            t++;
        }
        split_bits_for_sha[j] = static_cast<uint8_t>(t_bits.to_ulong());
    }
    SHA256_Legacy sha;
    std::string mySHA = sha(split_bits_for_sha, 16);
    unsigned long last_sha_digest = hex2dec(mySHA.substr(0, 1));
    std::bitset<4> sign_bits;
    uint8_t i = 0;
    while (last_sha_digest > 0 && i < 4)
    {
        if (last_sha_digest % 2)
            sign_bits.set(i);
        last_sha_digest = last_sha_digest / 2;
        i++;
    }
    // std::cout << sign_bits << std::endl;
    bits[128] = sign_bits[3];
    bits[129] = sign_bits[2];
    bits[130] = sign_bits[1];
    bits[131] = sign_bits[0];

    std::vector<std::string> words = bitsToWords_12(bits);
    std::string final_mnemonic;
    for (int i = 0; i < 12; ++i)
    {
        final_mnemonic.append(words[i] + (i == 11 ? "" : " "));
    }
    return BIP39Result(final_mnemonic, phraseToSeed(final_mnemonic, passphrase));
}

std::vector<std::string> BIP39::bitsToWords_12(std::bitset<132> bits)
{
    std::vector<std::string> finalWords;
    for (int i = 0; i < 12; ++i)
    {
        std::bitset<11> t;
        uint8_t c = 0;
        for (int j = 11 * i; j < 11 * i + 11; j++)
        {
            t[10 - c] = bits[j];
            c++;
        }
        finalWords.push_back(words[t.to_ulong()]);
    }
    return finalWords;
}

std::string BIP39::phraseToSeed(std::string phrase, std::string password)
{
    std::string mnemonic_salt = "mnemonic"+password;
    unsigned char slt[mnemonic_salt.length()];
    strcpy((char*)slt, mnemonic_salt.c_str());
    unsigned char result[64];
    PKCS5_PBKDF2_HMAC(phrase.c_str(), phrase.length(), slt, mnemonic_salt.length(), 2048, EVP_sha512(), 64, result);

    BIGNUM* bn_seed = BN_new();
    BN_bin2bn(result, 64, bn_seed);
    std::string res(BN_bn2hex(bn_seed));
    BN_free(bn_seed);
    return res;
}
