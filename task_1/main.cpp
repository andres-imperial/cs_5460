//=============================================================================
// Andres Imperial
//=============================================================================

#include <vector>
#include <string>

#include "gen_passwords.hpp"

int main(void)
{
  std::vector<std::string> dictList;

  dictList = genPasswords::getDictList();

  auto passwords = genPasswords::genPasswords(dictList);

  genPasswords::extraPasswords(passwords);

  genPasswords::saveWords(passwords);

  return 0;
}
