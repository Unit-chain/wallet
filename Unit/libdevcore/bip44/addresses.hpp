#pragma once
#include "utils.hpp"
#include "SHA256.h"

class Addresses
{
private:
    inline uint8_t hex2dec(std::string hex);
    

public:
    std::string pub2addr(const std::string& pub_key);
};


