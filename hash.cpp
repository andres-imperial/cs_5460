// ============================================================================
// Computer Security
// Assignment 3
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// Cole Buhman
// ============================================================================

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdint>
#include "hash.hpp"
#include <boost/algorithm/string/replace.hpp>

namespace hash
{
  std::string removeSpaces(std::string text)
  {
    boost::algorithm::replace_all(text, " ", "");
    return text;
  }

  std::vector<uint32_t> getBlocks(std::string plaintext)
  {
    uint32_t chunk = 0;
    std::vector<uint32_t> blocks;

    for (int i = 0; i < plaintext.length(); i+=4)
    {
      chunk = 0;
      for (int j = 0; j < 4; j++)
      {
        chunk = chunk << 8;
        if (j + i < plaintext.length())
        {
          char temp = plaintext[j+i];
          chunk = chunk | temp;
        }
      }
      blocks.push_back(chunk);
    }
    return blocks;
  }

  std::vector<mp::mpz_int> operation(const std::vector<uint32_t>& blocks, int length) 
  {
    std::vector<mp::mpz_int> mpzBlocks;

    for (int i = 0; i < blocks.size(); i++) 
    {
      mpz_t tempBlock;
      mpz_init(tempBlock);
      mpz_ui_pow_ui(tempBlock, blocks[i], length); // Raise each block to length of the plaintext

      mpz_t shift;
      mpz_init(shift);
      mpz_mod_ui(shift, tempBlock, 32); // Mod tempBlock by 32 to get our shift value
      
      int intShift = mpz_get_ui(shift);
      mp::mpz_int raisedBlock = tempBlock;
      size_t bitSize = mpz_size(tempBlock)*32;
      mp::mpz_int hashedBlock = (raisedBlock << intShift) | (raisedBlock >> (bitSize - intShift)); // Circular bit shift with shift value
      mpzBlocks.push_back(hashedBlock);
    }
    return mpzBlocks;
  }

  mp::mpz_int fixLength(std::vector<mp::mpz_int> blocks)
  {
    mp::mpz_int finalHashValue = 0;
    mpz_t tempBlock;
    mpz_init(tempBlock);

    mpz_t fixedLength;
    mpz_init(fixedLength);
    mpz_ui_pow_ui(fixedLength, 2, 128); // Raise 2 to 128 to get our fixed length

    for (int i = 0; i < blocks.size(); i++)
    {
      mpz_t temp;
      mpz_init_set_str(temp, blocks[i].convert_to<std::string>().c_str(), 10);
      mpz_mod(tempBlock, temp, fixedLength); // Mod each block by our fixed length

      finalHashValue += tempBlock; // add value to final hash
      finalHashValue = finalHashValue % fixedLength; // Mod final hash by our fixed length
    }
    return finalHashValue;
  }
}
