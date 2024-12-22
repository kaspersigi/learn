#include <fstream>
#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    std::ifstream ifs("mainlog.txt");
    std::string str;
    if (ifs.is_open()) {
        while (std::getline(ifs, str)) {
            std::cout << str << std::endl;
        }
    }
    return 0;
}