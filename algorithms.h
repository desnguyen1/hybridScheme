#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::uint1024_t;
#ifndef HYBRIDSCHEME_ALGORITHMS_H
#define HYBRIDSCHEME_ALGORITHMS_H
std::string letterToInt(std::string message);
std::string intToLetter(uint1024_t decryptedMessage);
std::string decToBinary(uint1024_t n);
uint1024_t square_and_multiply(uint1024_t a, uint1024_t k, uint1024_t n);
uint1024_t square_and_multiply(uint1024_t a, uint1024_t k, uint1024_t n);
bool millerRabinPrimalityTest(uint1024_t randomNum, int t);
#endif //HYBRIDSCHEME_ALGORITHMS_H
