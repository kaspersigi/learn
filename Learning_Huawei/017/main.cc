// HJ17 坐标移动
#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
extern "C" {
#include <string.h>
}

#if 1
auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MAX_SIZE = 10001;
    char buffer[MAX_SIZE] = {};
    std::string pat(R"(^[WASD](\d{1,2})$)");
    std::regex pattern(pat);
    std::smatch result;
    std::string word {};
    int pos[2] {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::string str(buffer);
        std::stringstream ss(str);
        while (std::getline(ss, word, ';')) {
            // std::cout << word << std::endl;
            bool found = std::regex_search(word, result, pattern);
            if (found) {
                int displacement = std::stoi(result[1]);
                // std::cout << word[0] << ": " << displacement << std::endl;
                switch (word[0]) {
                case 'W':
                    pos[1] += displacement;
                    break;
                case 'A':
                    pos[0] -= displacement;
                    break;
                case 'S':
                    pos[1] -= displacement;
                    break;
                case 'D':
                    pos[0] += displacement;
                    break;
                }
            }
        }
        std::cout << pos[0] << "," << pos[1] << std::endl;
        memset(buffer, 0, MAX_SIZE);
        pos[0] = 0;
        pos[1] = 0;
    }
    return 0;
}
#endif

#if 0
auto main(int argc, char* argv[]) -> int
{
    std::stringstream ss;
    std::string word;
    ss.str(R"(A10;S20;W10;D30;X;A1A;B10A11;;A10;)");
    while (std::getline(ss, word, ';')) {
        std::cout << word << std::endl;
    }
    return 0;
}
#endif

#if 0
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::string pat(R"(([WASD])(\d{2}))");
    std::regex pattern(pat);
    std::smatch result;
    std::vector<std::string> vs { "A10", "S20", "W10", "D30", "X", "A1A", "B10A11", "", "A10" };
    for (auto i : vs) {
        bool found = std::regex_search(i, result, pattern);
        if (found) {
            std::string direction = result[1];
            std::string displacement = result[2];
            std::cout << direction << ": " << displacement << std::endl;
        }
    }
    return 0;
}
#endif