#pragma once
#include "utils.hpp"

/// @brief Result of signing message with secp256k1 curve. Contains r-value, s-value and messages hash (SHA256)
struct ECDSASignResult
{
    std::string r;
    std::string s;
    std::string message_hash;
    ECDSASignResult(std::string _r, std::string _s, std::string _msghash)
    {
        r = _r;
        s = _s;
        message_hash = _msghash;
    }
};

/// @brief Signing message with private key (not extended)
/// @param message message as string
/// @param prv_key private key in hex representaion
/// @return r value, s value and message hash
ECDSASignResult ecdsa_sign_message(std::string msg, std::string prv_key);



/// @brief Method to verify signature with r value, s value, message and wallet address
/// @param r r value from signature. It is X-coord of point R
/// @param s s value from signature. It is signature proof
/// @param message message wich we decide to check
/// @param address address of the wallet signer in base58 encoding
/// @return result of verification (bool)
bool ecdsa_verify_signature(std::string r, std::string s, std::string msg, std::string address);
