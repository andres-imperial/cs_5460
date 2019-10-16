// ============================================================================
// Computer Security
// Assignment 3
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// Cole Buhman
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "hash.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    throw std::runtime_error(
        "Program expected one arguments: plaintext message, ciphertext message.");
  }

  std::string plaintext = argv[1];

  std::string plainNoSpaces = hash::removeSpaces(plaintext);

  std::vector<uint32_t> blocks = hash::getBlocks(plainNoSpaces);

  std::vector<mp::mpz_int> mpzBlocks = hash::operation(blocks, plainNoSpaces.length());

  auto output = hash::fixLength(mpzBlocks);
  std::cout << "Hash: " << output << std::endl;


  return 0;
}
