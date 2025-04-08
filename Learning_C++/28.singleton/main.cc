#include <iostream>

class Singleton {
public:
    ~Singleton() = default;
    static Singleton& GetInstance();

protected:
    Singleton() = default;
    Singleton(const Singleton& obj) = delete;
    Singleton(Singleton&& obj) = delete;
    Singleton& operator=(const Singleton& obj) = delete;
    Singleton& operator=(Singleton&& obj) = delete;
};

Singleton& Singleton::GetInstance()
{
    static Singleton instance;
    std::cout << "static instacne addr = " << &instance << std::endl;

    return instance;
}

auto main(int argc, char* argv[]) -> int
{
    Singleton& s1 = Singleton::GetInstance();
    std::cout << "s1 addr = " << &s1 << std::endl;
    Singleton& s2 = Singleton::GetInstance();
    std::cout << "s2 addr = " << &s2 << std::endl;
    Singleton& s3 = Singleton::GetInstance();
    std::cout << "s3 addr = " << &s3 << std::endl;

    return 0;
}