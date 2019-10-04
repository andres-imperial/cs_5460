// ============================================================================
// Andres Imperial
// ============================================================================

#include "rsa_codec.hpp"

namespace rsa
{
  mp::mpz_int encryptOrDecrypt(mp::mpz_int value, Key key)
  {
    return mp::powm(value, key.exponent, key.mod);
  }

  mp::mpz_int stringToMpz_int(std::string value)
  {
    std::string tempString = "";
    transform(value.begin(), value.end(), value.begin(), ::toupper);

    for (int i = 0; i < value.length(); i++)
    {
        char x = value.at(i);
        tempString += std::to_string((int)x);
    }

    mp::mpz_int num;
    mpz_t tempNum;
    mpz_init_set_str(tempNum, tempString.c_str(), 10);
    num = tempNum;

    return num;
  }

  mp::mpz_int stringToMpz_int_2(std::string value)
  {
    mp::mpz_int num;
    mpz_t tempNum;
    mpz_init_set_str(tempNum, value.c_str(), 10);
    num = tempNum;

    return num;
  }

  std::string mpz_intToString(mp::mpz_int value)
  {
    std::string tempString = value.convert_to<std::string>();
    std::string finalString = "";

    for (int i = 0; i < tempString.length(); i+= 2)
    {
        finalString += (char)std::stoi(tempString.substr(i, 2));
    }

    return finalString;
  }
}
