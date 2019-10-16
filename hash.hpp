// ============================================================================
// Computer Security
// Assignment 3
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// Cole Buhman
// ============================================================================

#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <boost/multiprecision/gmp.hpp> 

namespace mp = boost::multiprecision;

namespace hash
{
  /** Removes spaces from the input text */
  std::string removeSpaces(std::string text);

  /** Splits the plaintext into 32 bit blocks */
  std::vector<uint32_t> getBlocks(std::string plaintext);

  /** Performs the hash operation on each 32 bit block */
  std::vector<mp::mpz_int> operation(const std::vector<uint32_t>& blocks, int length);

  /** Reduces the size of the hashed values to a max of 128 bits producing the final hash value */
  mp::mpz_int fixLength(std::vector<mp::mpz_int> blocks);
}

#endif
