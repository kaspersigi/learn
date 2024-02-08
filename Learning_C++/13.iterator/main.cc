#include "String.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    String str { "Hello world!" };
    for (auto it = str.begin(); it != str.end(); ++it) {
        std::cout << *it;
    }
    return 0;
}