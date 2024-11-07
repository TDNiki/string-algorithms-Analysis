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
    const long nText = 10e3;
    const long nTextMax = 10e7;
    const char nTest = 10;
    const int firstSymbol_ANSI = 97; // ANSI
    long int sigma = 26; // кол-во уникальных символов
    const long nPattern = 10;
    //const double q = 0.001; 

    for (long sizeText = nText; sizeText < nTextMax; sizeText *= 2) {
		
		
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

        
	}

    return 0;
}