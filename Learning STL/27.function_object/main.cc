#include <algorithm>
#include <iostream>

class Print {
public:
    template <typename T>
    void operator()(T&& e) const
    {
        std::cout << e << " ";
    }
};

auto main(int argc, char* argv[]) -> int
{
    Print()(3);
    std::string s { "Hello" };
    std::for_each(s.cbegin(), s.cend(), Print());
    std::cout << std::endl;

    auto fun = Print();
    fun(3);
    std::for_each(s.cbegin(), s.cend(), fun);
    std::cout << std::endl;

    return 0;
}