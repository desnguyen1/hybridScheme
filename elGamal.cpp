#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

#include "algorithms.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using boost::multiprecision::uint1024_t;

void encryption(uint1024_t m, uint1024_t p, uint1024_t x, uint1024_t alpha,uint1024_t& gamma, uint1024_t& delta){
    uint1024_t k;

    //find a random integer k given 1 ≤ k ≤ p-2
    k = 1 + rand() % p-2;

    //computing gamma = alpha^k (mod p)
    gamma = square_and_multiply(alpha, k, p);

    //compute delta = m * x^k (mod p), given x = alpha^a
    delta = m * square_and_multiply(x, k, p);
}

//a = private key
uint1024_t decryption(uint1024_t a, uint1024_t p, uint1024_t gamma, uint1024_t delta){
    uint1024_t gammaResult, recover_m;
    //compute gamma^(p-1-a) mod p
    gammaResult = square_and_multiply(gamma, (p-1-a), p);

    //recover 'm'
    recover_m = (gammaResult * delta) % p;
    return recover_m;
}