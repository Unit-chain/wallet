#pragma once
#include "string"
#include "cmath"
#include <openssl/ec.h>
#include "openssl/ecdsa.h"
#include "openssl/bn.h"
#include <openssl/obj_mac.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <openssl/hmac.h>
#include "base58.hpp"
#include "SHA256.h"
#include <boost/multiprecision/cpp_int.hpp>
#include "addresses.hpp"

inline uint8_t hex2dec(std::string hex);

inline std::string to_hex(const std::string input);

inline std::string reverse_hex_str(std::string &str);


inline std::string hmac_512(unsigned char *key, int key_length, unsigned char *message, size_t message_length);

