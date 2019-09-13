// ============================================================================
// Computer Security
// Assignment 1
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// ============================================================================

#include <cstdio>
#include <stdexcept>

#include "codec.hpp"

namespace
{
  std::string checkLower(std::string value)
  {
    for (int i = 0; i < value.size(); ++i)
    {
      if (std::islower(value[i]))
      {
        value[i] = toupper(value[i]);
      }
    }
    return value;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    throw std::runtime_error(
        "Program expected two arguments: composite key, plaintext message.");
  }

  std::string compositeKey = argv[1];
  std::string plaintext = argv[2];
  std::string firstKey = compositeKey.substr(0, compositeKey.size() - 2);
  std::string secondKey = compositeKey.substr(compositeKey.size() - 2);
  
  plaintext = checkLower(plaintext);
  firstKey = checkLower(firstKey);
  secondKey = checkLower(secondKey);

  printf("first key: %s\n", firstKey.c_str());
  printf("second key: %s\n", secondKey.c_str());
  printf("plaintext: %s\n", plaintext.c_str());

  auto ciphertext = codec::encrypt(plaintext, firstKey, secondKey);

  printf("ciphertext: %s\n", ciphertext.c_str());
  
  auto decrypt = codec::decrypt(ciphertext, firstKey, secondKey);
  
  printf("decrypttext: %s\n", decrypt.c_str());

  auto decryptedPlaintext = codec::decrypt(ciphertext, firstKey, secondKey);

  printf("plaintext: %s\n", decryptedPlaintext.c_str());

  return 0;
}
