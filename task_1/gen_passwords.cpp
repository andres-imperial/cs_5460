//=============================================================================
// Andres Imperial
//=============================================================================

#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <map>

#include "gen_passwords.hpp"

namespace genPasswords
{
  namespace
  {
    // clang-format off
    std::map<char, std::vector<char>> substitutions = {
      { 'a', {'A', '@'} },
      { 'b', {'B', '8'} },
      { 'c', {'C', '('} },
      { 'd', {'D', '6'} },
      { 'e', {'E', '3'} },
      { 'f', {'F'} },
      { 'g', {'G', '9'} },
      { 'h', {'H', '#'} },
      { 'i', {'I', '1', '!'} },
      { 'j', {'J'} },
      { 'k', {'K', '<'} },
      { 'l', {'L', '1', '|'} },
      { 'm', {'M'} },
      { 'n', {'N'} },
      { 'o', {'O', '0'} },
      { 'p', {'P'} },
      { 'q', {'Q', '9'} },
      { 'r', {'R'} },
      { 's', {'S', '5', '$'} },
      { 't', {'T', '7', '+'} },
      { 'u', {'U'} },
      { 'v', {'V', '<', '>'} },
      { 'w', {'W'} },
      { 'x', {'X', '%'} },
      { 'y', {'Y', '?'} },
      { 'z', {'Z'} }
    };
    // clang-format on
  }

  std::vector<std::string> getDictList(void)
  {
    std::ifstream inFile("dict.txt");
    std::vector<std::string> result;

    if (inFile.good())
    {
      while (!inFile.eof())
      {
        std::string word;
        inFile >> word;
        if (!word.empty())
        {
          result.push_back(word);
        }
      }
    }

    inFile.close();

    return result;
  }

  std::vector<std::vector<std::string>> genPasswords(
    std::vector<std::string> wordList)
  {
    std::vector<std::vector<std::string>> result(
      wordList.size(), std::vector<std::string>());

    int index = 0;
    for (auto word : wordList)
    {
      for (int i = 0; word[i]; ++i)
      {
        word[i] = tolower(word[i]);
      }
      result[index] = genPasswords(word);
      ++index;
    }

    return result;
  }

  std::vector<std::string> genPasswords(std::string word)
  {
    std::vector<std::string> results;

    for (int i = 0; word[i]; ++i)
    {
      if (!substitutions[word[i]].empty())
      {
        for (int j = 0; j < substitutions[word[i]].size(); ++j)
        {
          auto temp = word;
          auto subs = substitutions[word[i]];
          temp[i] = subs[j];
          for (auto password : genPasswords(temp))
          {
            results.push_back(password);
          }
        }

        results.push_back(word);
        return results;
      }
    }

    return {word};
  }

  void saveWords(std::vector<std::vector<std::string>> wordSet)
  {
    std::ofstream outFile("ELCP01.txt");

    if (outFile.good())
    {
      for (auto words : wordSet)
      {
        writeWords(words, outFile);
      }
    }

    outFile.close();
  }

  void writeWords(std::vector<std::string> words, std::ofstream& outFile)
  {
    for (auto word : words)
    {
      if (!word.empty())
      {
        outFile << word << "\n";
      }
    }
  }

  void extraPasswords(std::vector<std::vector<std::string>>& wordSet)
  {
    auto results = wordSet;
    for (int i = 0; i < wordSet.size(); ++i)
    {
      for (auto word : wordSet[i])
      {
        results[i].push_back(word + word);
        std::string reverseWord = word;
        std::reverse(reverseWord.begin(), reverseWord.end());
        results[i].push_back(reverseWord);
        results[i].push_back(reverseWord + reverseWord);
      }
    }

    wordSet = results;
  }
}
