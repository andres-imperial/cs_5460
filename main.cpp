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

  std::string message = "Hello World";

  mp::mpz_int numMessage = rsa::stringToMpz_int(message);
  printf("plaintext message: %s\n", numMessage.convert_to<std::string>().c_str());

  auto encodedMessage = rsa::encryptOrDecrypt(numMessage, keys.first);
  printf("encrypted message: %s\n",
         encodedMessage.convert_to<std::string>().c_str());

  auto decodedMessage = rsa::encryptOrDecrypt(encodedMessage, keys.second);
  printf("decrypted message: %s\n",
         decodedMessage.convert_to<std::string>().c_str());

}
