#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <cassert>
using namespace std;

// Need a function that takes an arbitrary number of booleans and 


template<bool ...digits>
int reversed_binary_value() {
    int d[] = {digits...};

    int val = 0;
    int power = 1;
    
    int numberofdigits = sizeof(d)/sizeof(int);
    for (int i = 0; i < numberofdigits; i++){
        // val >> d[i];
        val += d[i]*power;
        power *= 2;
    }

    return 1;
}

int main() {
    int i = reversed_binary_value<0,0,1,1>();
}