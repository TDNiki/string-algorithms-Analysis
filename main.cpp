#include <iostream>
#include <cstring>
#include <vector>
#include <chrono>
#include "string_algoritms.h"

std::string getText(const long nText, const int firstSymbol, const int sigma)
{
    std::string text;

    for (int i = 0; i < nText; i++) {
        text.push_back(char(firstSymbol + rand() % sigma));
    }

    return text;

}

int main(void)
{
    //const long nText = 10e3;
    const long nTextMax = 10e7;
    const char nTest = 100;
    const int firstSymbol_ANSI = 97; // ANSI start index
    const int sigma = 2; // кол-во уникальных символов 26
    const long nPattern = 10;
    const long nPatternMax = 10e2;
    //const double q = 0.001; 

    const long nText = 1000000;
    std::string text = getText(nText, firstSymbol_ANSI, sigma);

    for (long sizePattern = nPattern; sizePattern < nPatternMax; sizePattern *= 2) {
		
		
		
		//std::cout << text << std::endl;
        long shift = rand() % (nText - sizePattern + 1);
        ///std::cout << shift << std::endl;
        std::string pattern = text.substr(shift, sizePattern);
        //std::cout << pattern << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
		for (char iTest = 0; iTest < nTest; iTest++) {
			std::vector<long> result = naiveSearch(text, pattern);
            //for (long i : result) std::cout << "FOUND: " << i << std::endl;
		}
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
        std::cout << duration.count() / nTest << std::endl;
	}

    /*for (long sizeText = nText; sizeText < nTextMax; sizeText *= 2) {
		
		
		std::string text = getText(sizeText, firstSymbol_ANSI, sigma);
		//std::cout << text << std::endl;
        long shift = rand() % (sizeText - nPattern + 1);
        //std::cout << shift << std::endl;
        std::string pattern = text.substr(shift, nPattern);
        //std::cout << pattern << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
		for (char iTest = 0; iTest < nTest; iTest++) {
			std::vector<long> result = naiveSearch(text, pattern);
            //for (long i : result) std::cout << i << std::endl;
		}
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
        std::cout << duration.count() / nTest << std::endl;

        
	}*/

    return 0;
}