#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> src = { 10, 20, 30, 40, 50 };
    std::vector<int> dst(5); // ⚠️ 必须预先分配空间！

    std::copy(src.begin(), src.end(), dst.begin());

    std::cout << "Source: ";
    for (int x : src)
        std::cout << x << " "; // 10 20 30 40 50

    std::cout << "\nDest:   ";
    for (int x : dst)
        std::cout << x << " "; // 10 20 30 40 50

    std::cout << "\n";
    return 0;
}