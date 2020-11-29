#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
using boost::multiprecision::uint1024_t;
#ifndef HYBRIDSCHEME_KEYGENERATOR_H
#define HYBRIDSCHEME_KEYGENERATOR_H
uint1024_t generatePrime(int key_size);
uint1024_t generateAlpha(uint1024_t prime);
void generateKeys(uint1024_t& p, uint1024_t& alpha, uint1024_t& x, uint1024_t& privateKey);
std::string getKey();
std::string leftShift(std::string key);
std::string rightShift(std::string key);
void generateSubKeys(std::string key, std::string subKey[]);
void generateSubKeysDecryption(std::string key, std::string subKey[]);
#endif //HYBRIDSCHEME_KEYGENERATOR_H
