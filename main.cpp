// ============================================================================
// Andres Imperial
// ============================================================================

#include "gen_keys.hpp"
#include "rsa_codec.hpp"

int main(void)
{
  auto keys = rsa::genKeys();

  printf("Public e is: %s -- Public mod is: %s -- Private d is: %s -- Private "
         "mod is: %s\n",
         keys.first.exponent.convert_to<std::string>().c_str(),
         keys.first.mod.convert_to<std::string>().c_str(),
         keys.second.exponent.convert_to<std::string>().c_str(),
         keys.second.mod.convert_to<std::string>().c_str());

  std::string message = "Hello World This is a really cool message. \
  It is also really long and has lot of awesome information in it. Hello World This is a really cool message. \
  It is also really long and has lot of awesome information in it. Hello World This is a really cool message. \
  It is also really long and has lot of awesome information in it. Hello World This is a really cool message. abcde";
  
  printf("Original message: %s\n", message.c_str());

  int lengthOfMessage = message.length();
  printf("Length of Message: %i\n", lengthOfMessage);

  mp::mpz_int numMessage = rsa::stringToMpz_int(message);
  printf("plaintext message: %s\n", numMessage.convert_to<std::string>().c_str());

  auto encodedNumMessage = rsa::encryptOrDecrypt(numMessage, keys.first);
  printf("encrypted message: %s\n",
         encodedNumMessage.convert_to<std::string>().c_str());

  mp::mpz_int decodedNumMessage = rsa::encryptOrDecrypt(encodedNumMessage, keys.second);
  printf("decrypted message: %s\n",
         decodedNumMessage.convert_to<std::string>().c_str());

  std::string decodedMessage = rsa::mpz_intToString(decodedNumMessage);
  printf("original message: %s\n", decodedMessage.c_str());

}
