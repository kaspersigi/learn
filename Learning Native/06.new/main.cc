#include <iostream>

extern "C" {
#include <mcheck.h>
}

auto main(int argc, char* argv[]) -> int
{
    mtrace();
    char* str = new char[13];
    delete[] str;
    muntrace();

    return 0;
}