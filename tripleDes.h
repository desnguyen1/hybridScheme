#include <iostream>

#ifndef HYBRIDSCHEME_TRIPLEDES_H
#define HYBRIDSCHEME_TRIPLEDES_H

std::string des(std::string text, std::string subkeys[]);
std::string tripleDESEncryption(std::string& key);
std::string tripleDESDecryption(std::string ciphertext);
#endif //HYBRIDSCHEME_TRIPLEDES_H
