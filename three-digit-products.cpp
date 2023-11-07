#include <iostream>

// Author: Tristan Seto 
// Date: 2023-11-07
// Inspired by the following YouTube video: https://youtu.be/SpNxksyYMeA?si=Scpf4ZHDY8B9mjZ2
// Prompt: Find all pairs of integer numbers {a, b, c} such that 2 < a * b * c < 7
// Description: This program will find all the ordered pairs (a, b, c) such that the product satisfies the conditions imposed by the user.

int main(){

    // Original Declarations for the Original Prompt
    int lower = 2;
    int upper = 7;

    // Program assumes inputs are inputted correctly.
    std::cout << "This program will find all the ordered pairs (a, b, c) such that the product satisfies the conditions imposed by the user: " << std::endl;
    std::cout << "Enter an integer lower bound: ";
    std::cin >> lower;
    std::cout << "Enter an integer upper bound: ";
    std::cin >> upper;

    std::cout << std::endl << "Ordered pairs satisfying " << lower << " < abc < " << upper << ":" << std::endl;

    for(int a = 0; a < upper; a++){
        for(int b = a; b < upper; b++){
            for(int c = b; c < upper; c++){
                if(a * b * c > lower && a * b * c < upper){
                    std::cout << "(" << a << ", " << b << ", " << c << "): prod = " << a*b*c << std::endl;
                }

            }
        }
    }
    return 0;
}
