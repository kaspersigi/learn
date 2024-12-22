#include <fstream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    std::ofstream ofs("test.txt");
    std::string str("hello world!");
    for (size_t i = 0; i < 10; ++i)
        ofs << str << '\n';
    return 0;
}