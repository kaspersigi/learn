#include <format>
#include <print>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    int a { 1995 };
    double b { 11.22 };
    char c { 'c' };
    char d[] { "hello world!" };
    std::string e("hey!");
    std::println("{}_{}_{}_{}_{}", a, b, c, d, e);
    std::print("{}_{}_{}_{}_{}", a, b, c, d, e);

    return 0;
}