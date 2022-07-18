#include <algorithm>
#include <iostream>
#include <vector>

bool odd(int num)
{
    return num % 2 == 1;
}

class Person {
private:
    std::string _name;

public:
    Person(const std::string& name)
        : _name(name)
    {
    }
    void print() const
    {
        std::cout << _name << std::endl;
    }
    void print2(const std::string& prefix) const
    {
        std::cout << prefix << _name << std::endl;
    }
};

auto main(int argc, char* argv[]) -> int
{
    std::vector nums { 1, 2, 3, 4, 5, 6, 7, 8 };
    // lambda调用全局函数
    for_each(nums.cbegin(), nums.cend(), [](auto e) { if(odd(e)) std::cout<<"odd: "<<e<<std::endl; });
    for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    // lamba修改vector中的值
    for_each(nums.begin(), nums.end(), [](auto& e) { e = e + 3; });
    for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    // lambda调用成员函数
    std::vector coll { Person("Tick"), Person("Trick"), Person("Track") };
    for_each(coll.cbegin(), coll.cend(), [](const auto& p) { p.print(); });
    for_each(coll.cbegin(), coll.cend(), [](const auto& p) { p.print2("Person: "); });

    return 0;
}