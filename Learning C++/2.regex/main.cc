#include <iostream>
#include <regex>

std::string str(R"((\d+\-\d+) +(\d+:\d+:\d+\.\d+) +(\d+) +(\d+) +([a-zA-Z]?) +([a-zA-Z0-9\.\-\?\\_@]+) *: +(.*)\n)");

auto main(int argc, char* argv[]) -> int
{
    FILE* origin_log_file = fopen("./mainlog.txt", "r");
    if (NULL == origin_log_file)
        perror("open mainlog file");

    char buffer[1024] {};
    std::regex pattern(str);
    std::smatch matched_part;
    while (!feof(origin_log_file)) {
        memset(buffer, 0, 1024);
        fgets(buffer, 1024, origin_log_file);
        std::string line = buffer;
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
    fclose(origin_log_file);

    return 0;
}