#include <cassert>
#include <filesystem>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::filesystem::path p = "../../..";
    assert(std::filesystem::exists(p));
    if (std::filesystem::is_regular_file(p))
        std::cout << p << " is a regular file, its size is " << std::filesystem::file_size(p) << std::endl;
    else if (std::filesystem::is_directory(p))
        std::cout << p << " is a directory" << std::endl;
    std::cout << p.native() << std::endl;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(p)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            if (0 == entry.path().extension().native().compare(".proto"))
                std::cout << entry.path().extension() << std::endl;
        }
    }

    return 0;
}