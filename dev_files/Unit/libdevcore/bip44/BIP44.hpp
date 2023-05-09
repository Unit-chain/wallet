#pragma once
#include "BIP39.hpp"
#include "BIP32.hpp"
#include "utils.hpp"

#define PHRASE_12 12
#define PHRASE_24 24
#define UNIT_COINTYPE 992
#define INTERNAL_CHANGE 1
#define EXTERNAL_CHANGE 0

struct BIP44Result
{
    std::string path;
    std::string extended_prv;
    std::string extended_pub;
    std::string prv;
    std::string pub;
    std::string address;
    BIP39Result mnemonic;
    std::string error;
    BIP44Result()
    {
        error = "unknown";
    }
    BIP44Result(std::string err)
    {
        error = err;
    }
    BIP44Result(std::string _path, std::string _ext_prv, std::string _ext_pub, std::string _prv, std::string _pub, std::string _address, BIP39Result _bip39)
    {
        path = _path;
        extended_prv = _ext_prv;
        extended_pub = _ext_pub;
        prv = _prv;
        pub = _pub;
        address = _address;
        mnemonic = _bip39;
    }
};

class BIP44
{
private:
public:
    /// @brief Generates BIP44 wallet WITHOUT additional user password.
    /// @param len Passphrase length expected. Please, use macroses PHRASE_12 and PHRASE_24 -  it will be more readable.
    /// @param account Account number. Max value is 65535.
    /// @param change Account type. Please, use macros EXTERNAL_CHANGE for external wallet and INTERNAL_CHANGE for internal wallet - it will be more readable.
    /// @return
    BIP44Result generateWallet(int len, uint16_t account, unsigned char change);

    /// @brief Generates BIP44 wallet WITH additional user password.
    /// @param len Passphrase length expected. Please, use macroses PHRASE_12 and PHRASE_24 -  it will be more readable.
    /// @param account Account number. Max value is 65535.
    /// @param change Account type. Please, use macros EXTERNAL_CHANGE for external wallet and INTERNAL_CHANGE for internal wallet - it will be more readable.
    /// @param password User password for safety.
    /// @return
    BIP44Result generateWallet(int len, uint16_t account, unsigned char change, std::string password);

    /// @brief Generates new address for provided account number.
    /// @param mnemonic Mnemonic for generation. It can be obtained from wallet generation 'mnemonic' field.
    /// @param account Account number. For this account will be generated new address.
    /// @param change Account type. Please, use macros EXTERNAL_CHANGE for external wallet and INTERNAL_CHANGE for internal wallet - it will be more readable.
    /// @param address_index Index of the new address.
    /// @return
    BIP44Result generateAddress(BIP39Result mnemonic, uint16_t account, unsigned char change, uint16_t address_index);
};

