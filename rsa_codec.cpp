// ============================================================================
// Andres Imperial
// ============================================================================

#include "rsa_codec.hpp"
// #include <iostream>

namespace rsa
{
  mp::mpz_int encryptOrDecrypt(mp::mpz_int value, Key key)
  {
    return mp::powm(value, key.exponent, key.mod);
  }

  mp::mpz_int stringToMpz_int(std::string value) 
  {
    std::string tempString = "";

    for (int i = 0; i < value.length(); i++)
    {
        char x = value.at(i);
        // std::cout << "x: " << x << ", num: " << (int)x << std::endl;
        tempString += std::to_string((int)x);
    }

    mp::mpz_int num; 
    mpz_t tempNum;
    mpz_init_set_str(tempNum, tempString.c_str(), 10);
    num = tempNum;

    return num;
  }
}
