// ============================================================================
// Andres Imperial
// ============================================================================

#ifndef RSA_CODEC_HPP
#define RSA_CODEC_HPP

#include "gen_keys.hpp"

namespace rsa
{
  mp::mpz_int encryptOrDecrypt(mp::mpz_int value, Key key);
}

#endif
