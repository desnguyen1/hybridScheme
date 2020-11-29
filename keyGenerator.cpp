#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <math.h>

#include "algorithms.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using boost::multiprecision::uint1024_t;


//generate a large random prime p based off of desire key size
uint1024_t generatePrime(int key_size){
    uint1024_t lowerBound, upperBound, range, prime=0;
    bool isPrime;

    lowerBound = (uint1024_t)pow(2, key_size-1);
    upperBound = (uint1024_t)pow(2, key_size);
    range = upperBound - lowerBound;


    while(!isPrime){
        prime = rand() % lowerBound + range;
        //to find a value with the desired number of bits, we find a number n between 2^(b-1) ≤ n ≤ 2^b

        //check primality of random number
        isPrime = millerRabinPrimalityTest(prime, 10);
        //cout<<"\nNot prime";
    }

    return prime;
}

//generate alpha given alpha is in [1,prime-1]
uint1024_t generateAlpha(uint1024_t prime){
    uint1024_t alpha;
    alpha = 1 + rand() % prime;
    //cout<<"\nalpha: "<<alpha;
    return alpha;
}


void generateKeys(uint1024_t& p, uint1024_t& alpha, uint1024_t& x, uint1024_t& privateKey){
    int key_size;
    uint1024_t a;

    key_size = 256;

    //getting public keys = (p, alpha, x (where x is a^alpha (mod p))
    //getting prime number
    p = generatePrime(key_size);
    //getting alpha (generator)
    alpha = generateAlpha(p);
    //getting x
    //generate a random integer 'a' given 1 ≤ a ≤ p-2;
    a = 1 + rand() % p-2;
    //computing x using modular exponentiation
    x = square_and_multiply(alpha, a, p);

    //private key
    //cout<<"\na: "<<a;
    privateKey = a;

}

//for Triple DES
int pc_one[56] = {56, 48, 40, 32, 24, 16, 8,
                  0, 57, 49, 41, 33, 25, 17,
                  9,	1, 58, 50, 42, 34, 26,
                  18, 10, 2, 59, 51, 43, 35,
                  62, 54, 46, 38, 30, 22 ,14,
                  6, 61, 53, 45, 37, 29, 21,
                  13, 5, 60, 52, 44, 36, 28,
                  20, 12, 4, 27, 19, 11, 3};

int pc_two[48] = {13, 16, 10, 23, 0, 4,
                  2, 27, 14, 5, 20, 9,
                  22,	18, 11,	3, 25, 7,
                  15, 6, 26, 19, 12, 1,
                  40,	51,	30, 36, 46, 54,
                  29, 39,	50,	44,	32,	47,
                  43,	48,	38,	55,	33,	52,
                  45,	41,	49,	35,	28,	31};

//get key
string getKey(){
    string key;
    cout<<"\nSecret Key must be 24 characters with no spaces or numbers (ASCII)";
    cout<<"\nEnter a Secret key: ";
    cin>>key;
    return key;
}

string leftShift(string key){
    string output="";
    for(int i = 1; i< 28;i++){
        //output[0] = key[1]
        output += key[i];
    }
    output += key[0];
    return output;
}

string rightShift(string key){
    string output="";
    //ouput[0] = last bit in key
    output += key[key.length()-1];
    for(int i =0; i<27;i++){
        //output[1]=key[0]
        output += key[i];
    }
    return output;
}

void generateSubKeys(string key, string subKey[]){
    int loc, roundNum;
    string pcOneOut="", pcTwoOut="";
    string c="", d="", combined="";

    //pc_one
    for(int i=0; i<64; i++){
        loc = pc_one[i];
        pcOneOut += key[loc];
    }

    //split
    c = pcOneOut.substr(0, 28);
    d = pcOneOut.substr(28, 28);

    //16 rounds to produce 16 subKeys
    for(roundNum =1; roundNum<=16;roundNum++ ) {
        pcTwoOut = "";

        //shift one for all rounds
        c=leftShift(c);
        d=leftShift(d);

        //shift again for rounds that are not 1,2,9,16
        if (roundNum != 1 && roundNum != 2 && roundNum != 9 && roundNum != 16) {
            c=leftShift(c);
            d=leftShift(d);
        }
        //combine left and d
        combined = c + d;

        //pc_two
        for(int i =0; i<48;i++){
            loc = pc_two[i];
            pcTwoOut += combined[loc];
        }

        //store subkeys for each round
        subKey[roundNum-1] = pcTwoOut;
    }

}

void generateSubKeysDecryption(string key, string subKey[]){
    int loc, roundNum=16, num=16;
    string pcOneOut="", pcTwoOut="";
    string c="", d="", combined="";
    //pc_one

    for(int i=0; i<64; i++){
        loc = pc_one[i];
        pcOneOut += key[loc];
    }

    //split
    c = pcOneOut.substr(0, 28);
    d = pcOneOut.substr(28, 28);

    for(roundNum=1; roundNum<=16; roundNum++){
        pcTwoOut="";
        if(roundNum != 1){
            c=rightShift(c);
            d=rightShift(d);
            //shift right twice if round is not 2,9,16
            if(roundNum != 2 && roundNum != 9 && roundNum != 16){
                c=rightShift(c);
                d=rightShift(d);
            }
        }
        combined = c+d;
        //pc_two
        for(int i =0; i<48;i++){
            loc = pc_two[i];
            pcTwoOut += combined[loc];
        }
        //print k16 to k1
        //so k16 will be k1
        subKey[roundNum-1] = pcTwoOut;

    }
}
