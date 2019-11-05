//=============================================================================
// Andres Imperial
//=============================================================================

#include <vector>
#include <cstring>

#ifndef GEN_PASSWORDS_HPP
#define GEN_PASSWORDS_HPP

namespace genPasswords
{
  std::vector<std::string> getDictList(void);

  std::vector<std::vector<std::string>> genPasswords(
    std::vector<std::string> wordList);

  std::vector<std::string> genPasswords(std::string word);

  void saveWords(std::vector<std::vector<std::string>> wordSet);

  void writeWords(std::vector<std::string> words, std::ofstream& outFile);

  void extraPasswords(std::vector<std::vector<std::string>>& wordSet);
}

#endif
