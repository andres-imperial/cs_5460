//=============================================================================
// Andres Imperial
//=============================================================================

#include <vector>
#include <string>
#include <iostream>

#include "gen_passwords.hpp"

int main(void)
{
  std::string userWord;
  printf("Hello!, please enter a word: ");
  std::cin >> userWord;

  auto passwords = genPasswords::genPasswords(userWord);

  std::vector<std::vector<std::string>> passwordSet = {passwords};

  genPasswords::extraPasswords(passwordSet);

  for (unsigned int i = 0; i < passwordSet.size(); ++i)
  {
    auto passwordsExtra = passwordSet[i];
    for (unsigned int index = 0; index < passwordsExtra.size(); ++index)
    {
      printf("%s", passwordsExtra[index].c_str());
      if (index + 1 < passwordsExtra.size())
      {
          printf("->");
      }
    }
  }
  printf("\n");

  return 0;
}
