// ============================================================================
// Andres Imperial
// ============================================================================

#ifndef GEN_KEYS_HPP
#define GEN_KEYS_HPP

#include <boost/multiprecision/gmp.hpp>

namespace mp = boost::multiprecision;

namespace rsa
{
  struct Key
  {
    mp::mpz_int exponent;
    mp::mpz_int mod;
  };

  // Generates public and private keys.
  // @returns a pair of Key structs with the 'first' being the public key
  // and the 'second' being the private key
  std::pair<Key, Key> genKeys(void);
}
#endif
