#include <format>
#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    int a { 1995 };
    double b { 11.22 };
    char c { 'c' };
    char d[] { "hello world!" };
    std::string e("hey!");
    auto f = std::format("{}_{}_{}_{}_{}", a, b, c, d, e);
    std::cout << f << std::endl;

    return 0;
}