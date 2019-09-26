// ============================================================================
// Andres Imperial
// ============================================================================

#ifndef GEN_KEYS_HPP
#define GEN_KEYS_HPP

namespace rsa
{
  int power(unsigned int x, unsigned int d, unsigned int input);

  bool millerRabinTest(unsigned int d, unsigned int input);

  unsigned int genPrimeNumber(void);

  bool isPrime(unsigned int input, unsigned int numOfRounds);

  int genKeys(void);
}
#endif
