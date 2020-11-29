#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using boost::multiprecision::uint1024_t;

//letter -> int
//turns the letter into a number where A = 10, B = 11, a = 42, b = 43
string letterToInt(string message) {
    string output = "";
    int num;
    for (int i = 0; i < message.length(); i++) {
        //set space to 99
        if(message[i] == ' '){
            num = 99;
        }
        else {
            //otherwise A = 65
            num = (int) message[i] - 55;
        }
        output += std::to_string(num);
    }

    return output;
}

//turns the integer back to letter based off of conversion from above function
//int -> letter
string intToLetter(uint1024_t decryptedMessage){
    string output="";
    char letter;
    uint1024_t num;
    while(decryptedMessage > 0){
        //get last two digits;
        num = decryptedMessage % 100;
        decryptedMessage /= 100;
        if(num == 99){
            //for spaces
            letter = ' ';
        }
        else {
            num += 55;
            letter = char(num);
            //cout << "\nletter: " << letter;
        }
        output += letter;
    }
    reverse(output.begin(), output.end());
    return output;
}

//decimal -> binary
string decToBinary(uint1024_t n){
    uint1024_t r;
    string binary ="";

    if(n == 0){
        binary += '0';
    }
    else{
        while(n>0){
            r = n % 2;
            n /= 2;
            if(r==1)
                binary += '1';
            else
                binary += '0';
        }
        reverse(binary.begin(), binary.end());
    }
    return binary;
}

//modular exponentiation
//output: a^k(mod n)
uint1024_t square_and_multiply(uint1024_t a, uint1024_t k, uint1024_t n){
    uint1024_t b, A;
    string binaryRep;

    //first, k must be in binary
    binaryRep = decToBinary(k);

    //reverse bits to get correct order of k
    reverse(binaryRep.begin(), binaryRep.end());

    //starting modular exponentiation
    b = 1;

    //return 1 if power is 0
    if(binaryRep == "0"){
        return b;
    }
    else{
        A = a;
        if(binaryRep[0] == '1')
            b = A;
        for(int i=1; i<binaryRep.length(); i++){
            A = pow(A, 2);
            A = A % n;
            if(binaryRep[i] == '1')
                b = (A*b)%n;
        }

        return b;
    }
}

//returns true if number is prime
bool millerRabinPrimalityTest(uint1024_t randomNum, int t){
    uint1024_t num, r = 1;
    uint1024_t a, y;
    int s=0;

    //step 1: finding 'r' and 's'
    //write n-1 = 2^s * r
    num = randomNum - 1;
    while(num != 1){
        if(num % 2 == 0){
            num /= 2;
            s++;
        }
        else{
            r *= num;
            num /= num;
        }
    }

    //step 2: primality test
    for(int i = 0; i<t; i++){
        //choose a random 'a' given 2 ≤ a ≤ n-2
        //this doesnt include n-3 number in random int, e.g., if n = 27, we will get a random a from [2,25]
        a = 2+rand() % randomNum-3;

        //compute y = a^r mod n
        y = square_and_multiply(a, r, randomNum);

        if(y != 1 && y != randomNum-1){
            int j = 1;
            while( j<= s-1 && y != randomNum-1){
                y = square_and_multiply(y, 2, randomNum);
                if(y==1) {
                    return false; //randomNum is composite
                }
                j++;
            }
            if(y != randomNum-1)
                return false;//composite
        }

    }
    return true;
}