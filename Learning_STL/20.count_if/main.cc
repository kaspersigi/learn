#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8 };

    // Lambda 谓词：判断是否为偶数
    size_t even_count = std::count_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;
    });

    std::cout << "Even numbers: " << even_count << "\n"; // 输出: 4

    // ✅ 学习点：高阶函数！谓词(Predicate) = 函数对象/lambda/函数指针
    // ✅ 函数式思想：行为参数化
}