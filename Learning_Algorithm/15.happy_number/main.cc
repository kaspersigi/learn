#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

bool is_happy(int n)
{
    std::unordered_set<int> si {};
    std::string str {};
    int sum { n };
    while (1) {
        if (sum == 1)
            return true;
        else {
            if (si.find(sum) == si.end())
                si.insert(sum);
            else
                return false;
        }
        str = std::to_string(sum);
        sum = 0;
        std::for_each(str.cbegin(), str.cend(), [&](auto e) { sum += (e - '0') * (e - '0'); });
    }
}

auto main(int argc, char* argv[]) -> int
{
    std::cout << is_happy(2) << std::endl;
    return 0;
}