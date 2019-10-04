// ============================================================================
// Computer Security
// Assignment 2 - Part 3
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// Cole Buhman
// ============================================================================

#ifndef FIND_KEY_HPP
#define FIND_KEY_HPP

#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

namespace find_key
{
  /** Removes spaces in a string */
  std::string removeSpaces(std::string text);

  /** Returns the minimum length that the key can be */
  int minKeyLength(std::string plaintext, std::string ciphertext);

  /** Sets the plaintext into a vector of strings based on the key length */
  std::vector<std::string> setUpColumns(int keyLength, std::string plaintext);

  /** Gives the string value of the column */
  std::string getColValues(std::vector<std::string> columns, int colNum);

  /** Returns true if all the columns are found in text*/
  bool findColumns(std::vector<std::string> columns, std::string ciphertext, int testKey);

  /** Removes the padding '!' from a string */
  std::string removePadding(std::string text);

  /** Returns the position of the column text in the ciphertext */
  std::vector<int> getCipherIndices(std::vector<std::string> columns, std::string ciphertext);

  /** Prints out the final key result */
  void getKeyOutput(std::vector<std::string> columns, std::string ciphertext);
}

#endif
