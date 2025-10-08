#include <print>

void func()
{
    static int num = 0;
    std::println("num = {}", num);
    ++num;
}

int main(int argc, char* argv[])
{
    func();
    func();
    func();
    std::println("Hello World!");

    return 0;
}