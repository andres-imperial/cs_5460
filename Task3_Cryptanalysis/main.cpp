// ============================================================================
// Computer Security
// Assignment 2 - Part 3
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

#include "FindKey.hpp"

int main(int argc, char *argv[])
{
  if (argc != 3) {
    throw std::runtime_error(
        "Program expected two arguments: plaintext message, ciphertext message.");
  }

  std::string plaintext = argv[1];
  std::string ciphertext = argv[2];
  std::string plain_no_space = find_key::removeSpaces(plaintext);

  int minKey = find_key::minKeyLength(plain_no_space, ciphertext);
  int maxKey = 7;

  bool keySizeFound = false;
  int testKey = minKey;

  while(!keySizeFound && testKey <= maxKey)
  {
    std::vector<std::string> setUp = find_key::setUpColumns(testKey, plain_no_space);
    
    if(find_key::findColumns(setUp, ciphertext, testKey))
    {
      keySizeFound = true;
      find_key::getKeyOutput(setUp, ciphertext);
    }
    else
    {
      testKey++;
    }
  }
  return 0;
}
