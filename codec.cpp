// ============================================================================
// Computer Security
// Assignment 1
// Group:
// Andres Imperial
// ============================================================================

#include <vector>
#include <map>

#include "codec.hpp"

namespace codec
{
  std::string xorEncrypt(std::string key, std::string text)
  {
    // TODO
  }

  std::string xorDecrypt(std::string key, std::string text)
  {
    // TODO
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
                                           std::string plaintext)
  {
    // TODO:
  }

  std::string oneTimePad(std::string key)
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
    auto derivedKey = oneTimePad(firstKey);

    auto ciphertext = columnarTranspositionEncrypt(derivedKey, plaintext);

    // TODO:
    // ciphertext = xorEncrypt(secondKey, ciphertext);

    return ciphertext;
  }

  std::string decrypt(std::string ciphertext,
                      std::string firstKey,
                      std::string secondKey)
  {
    // TODO:
  }
}
