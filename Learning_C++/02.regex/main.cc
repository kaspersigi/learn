#include <fstream>
#include <iostream>
#include <regex>

static const std::string str(R"(^(\d+\-\d+) +(\d+:\d+:\d+\.\d+) +(\d+) +(\d+) +([a-zA-Z]?) +([a-zA-Z0-9\.\-\?\\_@]+) *: +(.*)$)");

auto main(int argc, char* argv[]) -> int
{
    std::ifstream ifs("mainlog.txt");
    std::string line;
    std::regex pattern(str);
    std::smatch matched_part;
    if (ifs.is_open()) {
        while (std::getline(ifs, line)) {
            // std::cout << line << std::endl;
            bool found = std::regex_search(line, matched_part, pattern);
            if (found) {
                std::string date = matched_part[1];
                std::string time = matched_part[2];
                std::string pid = matched_part[3];
                std::string tid = matched_part[4];
                std::string level = matched_part[5];
                std::string tag = matched_part[6];
                std::string message = matched_part[7];
                if (pid == "1144")
                    std::cout << tag << std::endl;
                // std::string stand_time = "2022-" + date + " " + time;
                // std::cout << stand_time << std::endl;
            }
        }
    }

    return 0;
}