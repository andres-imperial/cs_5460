// ============================================================================
// Andres Imperial
// ============================================================================

#include "gen_keys.hpp"

#include <cstdlib>
#include <cstdio>
#include <limits>
#include <ctime>
#include <cmath>

namespace rsa
{
  namespace detail
  {
    void ext_euclidean(mp::mpz_int a,
                       mp::mpz_int b,
                       mp::mpz_int& x,
                       mp::mpz_int& y)
    {
      if (b == 0)
      {
        x = 1;
        y = 0;
        return;
      }
      ext_euclidean(b, a % b, x, y);
      mp::mpz_int temp = x - a / b * y;
      x = y;
      y = temp;
    }

    mp::mpz_int mod_mult_inv(mp::mpz_int a, mp::mpz_int mod)
    {
      mp::mpz_int x, y;
      ext_euclidean(a, mod, x, y);
      return x < 0 ? x + mod : x;
    }

    mp::mpz_int gcd(mp::mpz_int a, mp::mpz_int b)
    {
      mp::mpz_int temp{0};

      while (true)
      {
        temp = a % b;
        if (temp == 0)
        {
          return b;
        }

        a = b;
        b = temp;
      }
    }

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
  }

  std::pair<Key, Key> genKeys(void)
  {
    std::srand(std::time(NULL));
    mp::mpz_int p = detail::genPrimeNumber();
    mp::mpz_int q = detail::genPrimeNumber();

    mp::mpz_int n = p * q;
    mp::mpz_int totient = (p - 1) * (q - 1);
    mp::mpz_int e = 65537 < n ? 65537 : 2;

    while (detail::gcd(e, totient) != 1)
    {
      ++e;
      if (e >= totient)
      {
        e = 2;
      }
    }

    const mp::mpz_int k = 2;
    mp::mpz_int d = detail::mod_mult_inv(e, totient);

    printf("p is: %s -- q is: %s -- e is: %s -- d is: %s\n",
           p.convert_to<std::string>().c_str(),
           q.convert_to<std::string>().c_str(),
           e.convert_to<std::string>().c_str(),
           d.convert_to<std::string>().c_str());

    return std::make_pair(Key{e, n}, Key{d, n});
  }
}
