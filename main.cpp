#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <sstream>

#include "keyGenerator.h"
#include "algorithms.h"
#include "elGamal.h"
#include "tripleDes.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using boost::multiprecision::uint1024_t;

//function declaration
uint1024_t concatTwoNums(uint1024_t num1, uint1024_t num2);

//outputs a concatenation of two numbers so 10 + 12 = 1012
uint1024_t concatTwoNums(uint1024_t num1, uint1024_t num2){
    uint1024_t times=1;
    if(num2 == 0){
        return num1*1;
    }
    while(times <= num2){
        times *= 10;
    }

    return num1*times + num2;
}

int main(){
    char choice;
    string bobKey, bobEncMessage, bobDecMessage,str_decryptedBobKey;
    uint1024_t decryptedBobKey;
    uint1024_t primeNum, alpha, x, privateKey;
    uint1024_t gamma, delta;
    uint1024_t m, message_int, decryptedBlock, leftover, nextBlock;
    string message, message_substr, decrypted_message="", str_decryptedBlock;
    int messageBlock=1, messageCount = 1;

    cout<<"\nGenerating Alice's Public Key.....";
    generateKeys(primeNum, alpha, x, privateKey);

    cout<<"\nPublic Key: "<<primeNum<<", "<<alpha<<", "<<x;

    //Bob's Triple DES
    cout<<"\n\nBob starting Triple DES...";
    bobEncMessage = tripleDESEncryption(bobKey);

    //Bob encrypting the key using Alice's public key
    cout<<"\nEncrypting Bob's key using Alice's public key.....";
    //turning letters into a string of numbers
    bobKey = letterToInt(bobKey);

    //string of num -> integer, i.e., "1234" -> 1234
    std::stringstream ss;
    ss << bobKey;
    ss >> m;

    //starting elGamal encryption of key
    encryption(m, primeNum, x, alpha, gamma, delta);

    //printing ciphertext for Bob's secret key
    cout << "\n\nCiphertext of Bob's secret key: (" << gamma << ", " << delta << ")";

    cout<<"\n\nSending Alice Bob's ciphered message and ciphered key....";


    cout<<"\n\nDecrypting Bob's secret key....";
    decryptedBobKey = decryption(privateKey, primeNum, gamma, delta);
    str_decryptedBobKey = intToLetter(decryptedBobKey);

    //decryption of Bob's message
    bobDecMessage = tripleDESDecryption(bobEncMessage);
    cout<<"\n\nBob's Decrypted Message: "<<bobDecMessage<<endl;

    return 0;
}

