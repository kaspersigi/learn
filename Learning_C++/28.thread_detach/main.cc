#include <print>

class Singleton {
public:
    ~Singleton() = default;
    static Singleton& GetInstance();

protected:
    Singleton();
    Singleton(const Singleton& obj) = delete;
    Singleton(Singleton&& obj) = delete;
    Singleton& operator=(const Singleton& obj) = delete;
    Singleton& operator=(Singleton&& obj) = delete;
};

Singleton& Singleton::GetInstance()
{
    static Singleton instance;
    return instance;
}

auto main(int argc, char* argv[]) -> int
{
    Singleton& s1 = Singleton::GetInstance();
    std::println("Hello World!");

    return 0;
}