// ============================================================================
// Computer Security
// Assignment 1
// Group:
// Andres Imperial
// ============================================================================

#include <cstdio>
#include <stdexcept>

#include "codec.hpp"

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

  printf("first key: %s\n", firstKey.c_str());
  printf("second key: %s\n", secondKey.c_str());
  printf("plaintext: %s\n", plaintext.c_str());

  auto ciphertext = codec::encrypt(plaintext, firstKey, secondKey);

  printf("ciphertext: %s\n", ciphertext.c_str());

  return 0;
}
