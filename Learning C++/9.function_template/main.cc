#include <iostream>

// template <typename T>
// T max(T a, T b) { return b < a ? a : b; }

// template <typename T>
// T max(T& a, T& b) { return b < a ? a : b; }

template <typename T>
T max(const T& a, const T& b) { return b < a ? a : b; }

// template <typename T>
// T max(T&& a, T&& b) { return b < a ? a : b; }S

auto main(int argc, char* argv[]) -> int
{
    // 模板类型推断允许我们像调用普通函数一样调用函数模板：我们可以不去显式的指出模板参数的类型
    // 传入什么类型参数，就会实例化为什么类型的函数，不需要max<int>(1,2);
    std::cout << max(1, 3) << std::endl;
    int a {}, b {};
    std::cout << max(a, b) << std::endl;
    std::cout << max(a, 3) << std::endl;
    return 0;
}