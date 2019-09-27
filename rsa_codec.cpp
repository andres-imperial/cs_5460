// ============================================================================
// Andres Imperial
// ============================================================================

#include "rsa_codec.hpp"

namespace rsa
{
  mp::mpz_int encryptOrDecrypt(mp::mpz_int value, Key key)
  {
    return mp::powm(value, key.exponent, key.mod);
  }
}
