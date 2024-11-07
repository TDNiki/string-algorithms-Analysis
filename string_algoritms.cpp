#include <vector>
#include <string>

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