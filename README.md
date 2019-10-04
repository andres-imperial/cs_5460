# cs_5460

Compile source code and name the executable 'main' with:  
**g++ main.cpp gen_keys.cpp rsa_codec.cpp -o main -lgmp -lboost_system -lboost_filesystem**

-lgmp includes the gmp library that is a dependency for boost's multiprecision library (mpz_int) you will have to download this library along with boost in the case you don't have it.  
