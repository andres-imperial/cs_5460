// ============================================================================
// Andres Imperial
// ============================================================================

#include "gen_keys.hpp"

#include <cstdlib>
#include <cstdio>
#include <limits>
#include <ctime>

namespace rsa
{
  int power(unsigned int x, unsigned int d, unsigned int input)
  {
    int result = 1;
    x = x % input;

    while (d > 0)
    {
      if (d & 1)
      {
        result = (result * x) % input;
      }

      d = d >> 1;
      x = (x * x) % input;
    }

    return result;
  }

  // Test procedure is based on Miller-Rabin test
  bool millerRabinTest(unsigned int d, unsigned int input)
  {
    int a = 2 + (rand() % (input - 4));

    int x = power(a, d, input);

    if (x == 1 || x == input - 1)
    {
      return true;
    }

    while (d != input - 1)
    {
      x = (x * x) % input;
      d *= 2;

      if (x == 1)
      {
        return false;
      }
      if (x == input - 1)
      {
        return true;
      }
    }

    return false;
  }

  bool isPrime(unsigned int input, unsigned int numOfRounds)
  {
    if (input <= 3)
    {
      return false; // we want something larger than 3
    }

    int d = input - 1;
    while (d % 2 == 0)
    {
      d /= 2;
    }

    for (int i = 0; i < numOfRounds; ++i)
    {
      if (!millerRabinTest(d, input))
      {
        return false;
      }
    }

    return true;
  }

  unsigned int genPrimeNumber(void)
  {
    auto randNum = std::rand() % std::numeric_limits<unsigned int>::max();

    while (!isPrime(randNum, 25))
    {
      randNum = std::rand() % std::numeric_limits<unsigned int>::max();
    }

    return randNum;
  }

  int genKeys(void)
  {
    std::srand(std::time(NULL));
    auto p = genPrimeNumber();
    auto q = genPrimeNumber();

    printf("p is: %u -- q is: %u\n", p, q);

    return 0;
  }
}
