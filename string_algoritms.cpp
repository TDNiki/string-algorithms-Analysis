#include <vector>
#include <string>

#define ANSI_INDEX_START 97

bool stringCompare(const std::string first, const std::string second)
{
    for (long i = 0; i < first.length(); i++) {
        if (first[i] != second[i]) return false;
    }
    return true;
}

std::vector<long> naiveSearch(const std::string text, const std::string pattern)
{
    std::vector<long> res;
    int p_len = pattern.length();
    int t_len = text.length();
    for (int i = 0; i <= t_len - p_len; i++) {
        if (stringCompare(pattern, text.substr(i, p_len))) res.push_back(i);
    }
    return res;
}

std::vector<long> RKSearch(const std::string text,  const std::string pattern)
{
    std::vector<long> results;
    const long nText = text.length();
    const long nPattern = pattern.length();
    const int firstSymbol = ANSI_INDEX_START;
    const int sigma = 26;
    const long q = 1046527;
    long long hashPattern = 0;
    long long hashText = 0;
    long long mostSignificantDigit = 1;

    for (long i = 0 ; i < nPattern; i++) {
        hashPattern = (hashPattern * sigma + pattern[i] - firstSymbol) % q;
        hashText = (hashText * sigma + text[i] - firstSymbol) % q;
        mostSignificantDigit = (i < nPattern - 1) ? (mostSignificantDigit * sigma) % q : mostSignificantDigit;
    }

    for (long shift = 0 ; shift < nText - nPattern + 1; shift++) {
        if (hashPattern == hashText && stringCompare(pattern, text.substr(shift, nPattern))) results.push_back(shift);

        if (shift < nText - nPattern) {
            hashText = ((hashText - (text[shift] - firstSymbol) * mostSignificantDigit) * sigma + text[shift + nPattern] - firstSymbol) % q;
            hashText = hashText < 0 ? hashText + q : hashText;
        }
    }

    return results;

}

std::vector<long> get_pi_function(const std::string pattern)
{
    const long n = pattern.length();
    std::vector<long> pi(n, 0);
    long q = 0;

    for (long i = 1; i < n; i++) {
        while(q > 0 && pattern[q]  != pattern[i]) q = pi[q - 1];
        if (pattern[q] == pattern[i]) q++;
        pi[i] = q;
    }
    return pi;
}

std::vector<long> kmpSearch(const std::string text, const std::string pattern)
{
    std::vector<long> result;
    long nText = text.length();
    long nPattern = pattern.length();
    std::vector<long> pi = get_pi_function(pattern);
    long q = 0;

    for (long i = 0; i < nText; i++) {
        while(q > 0 && pattern[q]  != text[i]) q = pi[q - 1];
        if (pattern[q] == text[i]) q++;
        if (q == nPattern) {
            result.push_back(i - q + 1);
            q = pi[q - 1];
        }
    }

    return result;
}