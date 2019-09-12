// ============================================================================
// Computer Security
// Assignment 1
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// ============================================================================

#include <vector>
#include <map>

#include "codec.hpp"
#include <iostream>

namespace codec
{
  std::string oneTimePadEncrypt(std::string key, std::string text)
  {
    // TODO
  }

  std::string oneTimePadDecrypt(std::string key, std::string text)
  {
    // TODO:
    // Break ciphertext into 2 digit numbers
    // Reverse XOR
    // Use XOR result to get characters from poly Square
    //   This should be the call to polySquare()
    //
    // return intermediateText
  }

  std::string columnarTranspositionEncrypt(std::string key,
                                           std::string plaintext)
  {
    std::vector<std::string> columns(key.size());
    for (int i = 0; i < key.size(); ++i)
    {
      for (int j = 0; j < key.size(); ++j)
      {
        if (j * key.size() + i >= plaintext.size())
        {
          break;
        }
        columns[i].push_back(plaintext[j * key.size() + i]);
      }
    }

    std::map<char, std::string> orderedColumns;
    for (int index = 0; index < key.size(); ++index)
    {
      orderedColumns[key.at(index)] += columns[index];
    }

    std::string result;
    for (auto it = orderedColumns.begin(); it != orderedColumns.end(); ++it)
    {
      result.append(it->second);
    }

    return result;
  }

  std::string columnarTranspositionDecrypt(std::string derivedKey,
                                           std::string ciphertext)
  {
    int blockSize = std::ceil((double)ciphertext.size()/derivedKey.size());
    std::string sortedKey = derivedKey;
    std::sort(sortedKey.begin(), sortedKey.end());

    std::map<char, std::string> orderedColumns;
    int positionInCipherText = 0;
    std::vector<std::string> sortedStrings(derivedKey.size());
    for (int index = 0; index < sortedKey.size(); ++index)
    {
      char currCharInSortedKey = sortedKey.at(index);
      auto columnIndex = derivedKey.find(currCharInSortedKey);
      derivedKey[columnIndex] = '+';
      if ((sortedKey.size() * (blockSize - 1)) + columnIndex >= ciphertext.size())
      {
        sortedStrings[columnIndex] = ciphertext.substr(positionInCipherText, blockSize-1);
        positionInCipherText += blockSize-1;
      }
      else 
      {
        sortedStrings[columnIndex] = ciphertext.substr(positionInCipherText, blockSize);
        positionInCipherText += blockSize;
      }
    }

    std::string plaintext(ciphertext.size(), ' ');
    for (int index = 0, colIndex = 0; index < plaintext.size(); ++colIndex)
    {
      for (int i = 0; i < sortedStrings.size() && index < plaintext.size(); ++i, ++index)
      {
        plaintext[index] = sortedStrings[i][colIndex];
      }
    }

    return plaintext;
  }

  // Takes indices and gets letters
  std::string ploySquare(std::string key)
  {
    std::string result;
    result.resize(key.size() / 2);

    for (int index = 0; index < result.size(); ++index)
    {
      int i = (int)(key.at(index * 2)) - '0';
      int j = (int)(key.at((index * 2) + 1)) - '0';

      result[index] = polybiusSquare[i][j];
    }

    return result;
  }

  std::string encrypt(std::string plaintext,
                      std::string firstKey,
                      std::string secondKey)
  {
    auto derivedKey = ploySquare(firstKey);

    printf("derivedKey: %s\n", derivedKey.c_str());

    auto ciphertext = columnarTranspositionEncrypt(derivedKey, plaintext);

    // TODO:
    // ciphertext = oneTimePadEncrypt(secondKey, ciphertext);

    return ciphertext;
  }

  std::string decrypt(std::string ciphertext,
                      std::string firstKey,
                      std::string secondKey)
  {
    // TODO:
    // intermediateText = oneTimePadDecrypt(secondKey, cipherText)
    //
    // auto derivedKey = polySquare(firstKey);
    auto intermediateText = "hlodlwleor";
    auto derivedKey = "MOM";
    auto plaintext = columnarTranspositionDecrypt(derivedKey, intermediateText);

    return plaintext;
  }
}
